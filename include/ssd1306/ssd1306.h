/*
   Lightweight, standalone driver for ssd1306 displays on Raspberry Pi Pico.
   Author: Irineu Teza Nunes
   This code was written from scratch based on public.

   License
   Source-Available Freeware License
   License Grant The Licensor grants the Licensee a non-exclusive, non-transferable right to access and view the Software’s source code, as well as use it internally, exclusively for personal or corporate purposes, under the terms of this agreement.
   Rights and Restrictions Unless expressly authorized in writing by the Licensor, the Licensee may not:
   (a) commercially use the Software or any derivative work (including selling, renting, offering as a service/SaaS, or consulting involving distribution of the Software);
   (b) redistribute, publish, make available, or sublicense the Software or its source code, in whole or in part;
   (c) modify or create derivative works for external distribution;
   (d) remove or alter copyright notices, trademarks, or credits;
   (e) circumvent technical protection mechanisms.

    Internal Modification Permission The Licensee may modify the source code only for internal use, without distribution to third parties. Any external distribution requires prior written authorization from the Licensor.
    Intellectual Property The Software and its source code remain the property of the Licensor. No ownership rights are transferred to the Licensee.
    Warranty and Liability The Software is provided “as is,” without warranties of any kind. The Licensor shall not be liable for any damages arising from the use or inability to use the Software.
    Termination and Compliance The Licensor may revoke this license in case of violation. The Licensee agrees to provide reasonable information to verify compliance upon request.
    Governing Law and Jurisdiction This agreement is governed by Brazilian law, and the courts of the Licensor’s city shall have jurisdiction over any disputes.

*/


#ifndef SSD1306_H
#define SSD1306_H

#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include <string.h> // Para memcpy e memset

// Definições para o display SSD1306
#define SSD1306_I2C_ADDR 0x3C
#define SSD1306_WIDTH 128
#define SSD1306_HEIGHT 64

// Prototipação das funções
void ssd1306_init(i2c_inst_t *i2c);
void ssd1306_clear();
void ssd1306_update(i2c_inst_t *i2c);
void ssd1306_draw_pixel(int x, int y, bool color);
void ssd1306_draw_char(int x, int y, char c, bool color);
void ssd1306_draw_string(int x, int y, const char *str, bool color);
void ssd1306_draw_string_mid(int x, int y, const char *str, bool color);
void ssd1306_draw_string_large(int x, int y, const char *str, bool color);
void ssd1306_draw_bitmap(int x, int y, const uint8_t *bitmap, int w, int h, bool color);

#endif // SSD1306_H
