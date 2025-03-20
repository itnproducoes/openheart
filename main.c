/*  Open Heart by 32mbit
    a Sega Genesis/Mega Drive multi-mod using Raspberry Pi Pico
    or compatible RP2040 board

    Region switching: press reset 3 times within 3 seconds to
    cycle Japan > Americas > Europe > Japan...
    The selected region is saved to internal flash and used
    until it is changed.

    In-game reset: Hold A+B+C+Start for 1 second

    Overclocking: Hold A+Start for 1 second to toggle between
    MCLK/7 (7.67MHz, standard) and MCLK/5 (10.74MHz)

    TMSS skip: automatic
 */

#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "pico/flash.h"
#include "hardware/flash.h"
#include "hardware/pll.h"
#include "hardware/clocks.h"
#include "hardware/pwm.h"
#include "hardware/gpio.h"

#define GPIO_OC_LED_PIN 1
#define GPIO_HALT_PIN 10        // !HALT pin of 68K
#define GPIO_A_B_PIN 11         // Wired to controller port 1 pin 6
#define GPIO_S_C_PIN 12         // Wired to controller port 1 pin 9
#define GPIO_SELECT_PIN 13      // Wired to controller port 1 pin 7
#define GPIO_CART_ENABLE_PIN 14 // !CART_CE, cart port pin B17. Non TMSS consoles can wire to ground.
#define GPIO_VRES_PIN 15        // !VRES
#define GPIO_STANDARD_PIN 16    // low = PAL, high = NTSC
#define GPIO_REGION_PIN 17      // low = Japan, high = Export
#define GPIO_VCLK_PIN 20        // CPU clock, for overclocking, optional
#define GPIO_MCLK_PIN 21        // To master oscillator clock in

#define PAD_A (1 << 0)
#define PAD_B (1 << 1)
#define PAD_S (1 << 2)
#define PAD_C (1 << 3)

#define FLASH_TARGET_OFFSET (256 * 1024)

enum {
    INVALID = 0x80,
    JAPAN,
    AMERICAS,
    EUROPE
};

const uint8_t *nvdata = (const uint8_t *) (XIP_BASE + FLASH_TARGET_OFFSET);
uint8_t config[FLASH_PAGE_SIZE];

// Pad state
volatile uint8_t pad;

uint32_t request;

volatile uint32_t reset_press = 0;
volatile uint32_t reset_timeout = 0;
uint32_t region_swap = 0;
bool oc_on = false;

// FLASH stuff lifted from pico examples
// This function will be called when it's safe to call flash_range_erase
static void call_flash_range_erase(void *param) {
    uint32_t offset = (uint32_t)param;
    flash_range_erase(offset, FLASH_SECTOR_SIZE);
}

// This function will be called when it's safe to call flash_range_program
static void call_flash_range_program(void *param) {
    uint32_t offset = ((uintptr_t*)param)[0];
    const uint8_t *data = (const uint8_t *)((uintptr_t*)param)[1];
    flash_range_program(offset, data, FLASH_PAGE_SIZE);
}

void read_flash()
{
    memcpy(config, nvdata, FLASH_PAGE_SIZE);
}

void write_flash()
{
    int rc; 
    rc = flash_safe_execute(call_flash_range_erase, (void*)FLASH_TARGET_OFFSET, UINT32_MAX);
    hard_assert(rc == PICO_OK);
    
    uintptr_t params[] = { FLASH_TARGET_OFFSET, (uintptr_t)config};
    rc = flash_safe_execute(call_flash_range_program, params, UINT32_MAX);
    hard_assert(rc == PICO_OK);
}

// We set the system PLL to run at 2x our desired MCLK rate
// The pll values were calculated with vcocalc.py
void set_mclk_ntsc() {
    set_sys_clock_pll(1074 * MHZ, 5, 2); // = 107.4MHz
    // output divide by 2: 53.7MHz MCLK
    clock_gpio_init(GPIO_MCLK_PIN,
        CLOCKS_CLK_GPOUT0_CTRL_AUXSRC_VALUE_CLKSRC_PLL_SYS, 2); 
}

void set_mclk_pal() {
    set_sys_clock_pll(1596 * MHZ, 3, 5); // = 106.4MHz
    // output divide by 2: 53.2MHz MCLK
    clock_gpio_init(GPIO_MCLK_PIN, 
        CLOCKS_CLK_GPOUT0_CTRL_AUXSRC_VALUE_CLKSRC_PLL_SYS, 2);
}

// VCLK is generated with PWM which is clocked to pll_sys (the MCLK source)
// The wrap value effectively divides it by 2 to MCLK rate, then it's
// divided down appropriately to make VCLK
void set_vclk_div(uint32_t div) {
    gpio_set_function(GPIO_VCLK_PIN, GPIO_FUNC_PWM);

    uint32_t slice = pwm_gpio_to_slice_num(GPIO_VCLK_PIN);

    // Set up a 50% PWM based on the system clock/MCLK speed
    // and the specified divider
    pwm_set_clkdiv_int_frac(slice, div, 0);
    pwm_set_clkdiv_mode(slice, PWM_DIV_FREE_RUNNING);
    pwm_set_phase_correct(slice, false);
    pwm_set_wrap(slice, 1); // Wrap value of 1 gives us PWM at MCLK rate
    pwm_set_chan_level(slice, pwm_gpio_to_channel(GPIO_VCLK_PIN), 1);
    pwm_set_enabled(slice, true);
}

// Set clock & jumpers for regions
void set_japan()
{
    set_mclk_ntsc();
    set_vclk_div(7);
    gpio_put(GPIO_STANDARD_PIN, true);
    gpio_put(GPIO_REGION_PIN, false);
}

void set_americas()
{
    set_mclk_ntsc();
    set_vclk_div(7);
    gpio_put(GPIO_STANDARD_PIN, true);
    gpio_put(GPIO_REGION_PIN, true);
}

void set_europe()
{
    set_mclk_pal();
    set_vclk_div(7);
    gpio_put(GPIO_STANDARD_PIN, false);
    gpio_put(GPIO_REGION_PIN, true);
}

// (The HALT & RESET lines are open collector and
// need to be asserted in this particular way)
// Assert HALT
void halt_on() {
    gpio_set_dir(GPIO_HALT_PIN, GPIO_OUT);
    gpio_put(GPIO_HALT_PIN, false);
    sleep_ms(1); // for good measure
}

// Negate HALT
void halt_off() {
    sleep_ms(1);
    gpio_set_dir(GPIO_HALT_PIN, GPIO_IN);
}

// Assert VRES
void reset_on() {
    gpio_set_dir(GPIO_VRES_PIN, GPIO_OUT);
    gpio_put(GPIO_VRES_PIN, false);
}

// Negate VRES
void reset_off() {
    gpio_set_dir(GPIO_VRES_PIN, GPIO_IN);
}

// Reset cycle. According to spritesmind, the vdp
// asserts VRES for about 16.7ms on a reset button press 
void reset_genesis()
{
    reset_on();
    sleep_us(16700);
    reset_off();
    reset_press = 0;
}

#define UPDATE_PAD(pad, mask, pin) \
    pad = (pad & ~(mask)) | ((!gpio_get(pin)) ? (mask) : 0);

// ISR to read controller & reset button
// Relies on a game to toggle the select pin so
// that we don't interfere with input
void read_inputs(uint gpio, uint32_t events) {
    if (gpio == GPIO_SELECT_PIN) {
        if (events & GPIO_IRQ_EDGE_FALL) {
            UPDATE_PAD(pad, PAD_A, GPIO_A_B_PIN);
            UPDATE_PAD(pad, PAD_S, GPIO_S_C_PIN);
        }
        if (events & GPIO_IRQ_EDGE_RISE) {
            UPDATE_PAD(pad, PAD_B, GPIO_A_B_PIN);
            UPDATE_PAD(pad, PAD_C, GPIO_S_C_PIN);
        }
    }

    // Reset input. VRES low is a reset button press
    if(gpio == GPIO_VRES_PIN && (events & GPIO_IRQ_EDGE_FALL))
    {
        reset_press++;
        if(reset_press == 1) {
            reset_timeout = 0;
        }
    }
}

int main() {
    reset_on();
    // Do init while reset held down

    // Set up gpio's
    // VRES
    gpio_init(GPIO_VRES_PIN);

    // HALT
    gpio_init(GPIO_HALT_PIN);

    // !CART_CE
    gpio_init(GPIO_CART_ENABLE_PIN);
    gpio_set_dir(GPIO_CART_ENABLE_PIN, GPIO_IN);

    // Japan/Export
    gpio_init(GPIO_REGION_PIN);
    gpio_set_dir(GPIO_REGION_PIN, GPIO_OUT);
    
    // PAL/NTSC
    gpio_init(GPIO_STANDARD_PIN);
    gpio_set_dir(GPIO_STANDARD_PIN, GPIO_OUT);

    // Controller pin 6
    gpio_init(GPIO_A_B_PIN);
    gpio_set_dir(GPIO_A_B_PIN, GPIO_IN);

    // Controller pin 9
    gpio_init(GPIO_S_C_PIN);
    gpio_set_dir(GPIO_S_C_PIN, GPIO_IN);

    // Board LED
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);

    // OC enabled LED
    gpio_init(GPIO_OC_LED_PIN);
    gpio_set_dir(GPIO_OC_LED_PIN, GPIO_OUT);

    // Room for experimentation: clock signal quality
    gpio_set_drive_strength(GPIO_MCLK_PIN, GPIO_DRIVE_STRENGTH_2MA);
    gpio_set_slew_rate(GPIO_MCLK_PIN, GPIO_SLEW_RATE_SLOW);
    gpio_set_drive_strength(GPIO_VCLK_PIN, GPIO_DRIVE_STRENGTH_2MA);
    gpio_set_slew_rate(GPIO_VCLK_PIN, GPIO_SLEW_RATE_SLOW);

    // Controller pin 7 & install input handler
    gpio_init(GPIO_SELECT_PIN);
    gpio_set_irq_enabled_with_callback(GPIO_SELECT_PIN, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true, &read_inputs);
    // Also handles VRES
    gpio_set_irq_enabled_with_callback(GPIO_VRES_PIN, GPIO_IRQ_EDGE_FALL, true, &read_inputs);

    // Restore last setting
    read_flash();

    // Set region & MCLK
    switch(config[0]) {
        case JAPAN:
            set_japan();
            break;
        case AMERICAS:
            set_americas();
            break;
        case EUROPE:
            set_europe();
            break;
        default:
            set_americas();
            config[0] = AMERICAS;
            config[1] = 0;
            write_flash();
            break;
    }

    // Release reset
    reset_off();

    // TMSS skip :)
    // aka "PRODUCED BY OR UNDER LICENSE FROM SEGA ENTERPRISES LTD."
    // When the genesis boots, it boots from an internal rom with the cartridge
    // slot unmapped and copies a small security program to ram. In order to check
    // the header on the cartridge, it has to swap it in to read it for a very short
    // time. When this happens, the !CART_CE signal is asserted. By waiting for this to
    // happen and *immediately* resetting the CPU within the *very* short time the
    // cart is in the address space, the 68000 will reset with the cart mapped in and
    // run from the cart just like a console without it.
    // If this fails, TMSS will run as normal and our code will continue, because
    // !CART_CE will also go low when the TMSS is done.
    // This trick could probably be made more robust by underclocking the CPU first,
    // but the MCU seems fast enough for it to work reliably.
    while(gpio_get(GPIO_CART_ENABLE_PIN));
    reset_genesis();
    gpio_deinit(GPIO_CART_ENABLE_PIN);

    // Setup OK
    gpio_put(PICO_DEFAULT_LED_PIN, true);

    // Main loop, check for controller hotkeys
    for(;; request = 0, reset_timeout++) {
        // IGR: A+B+C+Start for 1 second resets
        while(pad == (PAD_A | PAD_B | PAD_C | PAD_S)) {
            sleep_ms(1);
            request++;
            if(request == 1000) {
                reset_genesis();
            }
        }

        // A + Start for 1 seconds: toggle overclock
        while((pad == (PAD_A | PAD_S))) {
            sleep_ms(1);
            request++;
            if(request == 1000) {
                oc_on = !oc_on;
                halt_on();
                set_vclk_div((oc_on) ? 5 : 7);
                halt_off();
                gpio_put(GPIO_OC_LED_PIN, oc_on);
            }
        }
        
        // Swap region with reset button
        // Press Reset 3x within 1 sec of each other to switch to the next
        // region: Japan > Americas > Europe > Japan ...
        if(reset_timeout >= 3000) {
             reset_press = 0;
        } else if(reset_press >= 3) {
            region_swap++;
            region_swap %= 3;
            switch(region_swap) {
                case 0:
                    set_japan();
                    config[0] = JAPAN;
                break;
                case 1:
                    set_americas();
                    config[0] = AMERICAS;
                break;

                case 2:
                    set_europe();
                    config[0] = EUROPE;
                break;
            }
            write_flash();
            reset_genesis();
        }

        sleep_ms(1);
    }   
}
