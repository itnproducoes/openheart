# Open Heart by 32mbit

Multi-region mod for Sega Genesis/Mega Drive using Raspberry Pi Pico (RP2040). This project allows switching between regions, controlling frequency, enabling Master System mode, overclocking, and much more — all via controller or physical button.

---

## 🧩 Overview

Open Heart turns your console into a multi-region hub with advanced features:

- Region switching: Japan, Americas, Europe
- Frequency: 50Hz/60Hz
- Master System mode
- Dynamic overclock
- Reset and pause via controller
- Graphical display on ST7735 or SSD1306
- Bluetooth module control
- Automatic TMSS skip

---

## 🔌 Required Hardware

- Raspberry Pi Pico or compatible RP2040
- ST7735 (TFT) or SSD1306 (OLED) display
- Sega Genesis/Mega Drive (Model 1 or 2)
- Voltage divider resistors (4.7k and 10k) for Model 1 VA5/VA6
- Resistor for controller pin 7 (22k) for Model 1 VA0 to VA4
- Wires for GPIO connections to console and controller

---

## 🎮 Commands

Function: Commands
- Region switch:
  B + C + Start (1s)
- Region switch (physical button):
  Reset Button (3s)
- Game reset:
  A + B + C + Start (1s)
- 50Hz/60Hz switch (Europe):
  A + B + Start (1s)
- Overclock:
  A + Start (1s)
- Pico reset:
  A + C + Start (3s)
- Enable Bluetooth:
  B + Start (2s)
- Master System pause:
  UP + B + C (1s)
- Master System reset:
  UP + C (5s)
- Toggle logo:
  C + Start (1s)

---

## 🖥️ Graphical Display

- ST7735 (TFT): colorful graphics and custom logos
- SSD1306 (OLED): monochrome graphic text

Displayed messages:

- Region and frequency
- Active mode
- Overclock status
- Bluetooth on/off
- Logos: SEGA, 16bit, Custom message

---

## ⚙️ Region Configuration

Region is saved to flash and restored on boot. LED indicators:

- Red: Japan
- Green: Americas
- Amber: Europe

---

## 🚀 TMSS Skip

Advanced technique that automatically bypasses TMSS:

- Monitors !CART_CE
- Resets the 68000 at the exact moment
- Allows direct cartridge boot

---

## Instructions
This mod is very similar to other existing mods, so adapting it to your specific console shouldn't be difficult. Schematics or references from similar mods may be helpful. Remove the oscillator and mount the Pico as close as possible to the original board location.

- **5V** and **ground** can be easily connected to the holes left by removing the oscillator. It is recommended to use a diode (I used a 1n4001) on the 5V point if you plan to update the firmware with the mod installed.

- **MCLK** should be connected to the oscillator clock output.

- **VCLK** is connected to the clock input pin of the 68000 (the VDP is also connected to this pin and should be disconnected from it). These wires should be kept as short as possible. VCLK is optional if you do not wish to use the overclocking feature.

- **Jpn/Export** and **NTSC/PAL** should be connected to the points on your board where +5V and ground determine the region and 50/60Hz respectively.

- **VRES** and **HALT** are connected to the corresponding pins on the 68000. HALT is optional if you do not wish to use the overclocking feature.

- **Pins 1, 6, 7 and 9** (add a 22k resistor to pin 7 of the controller for Model 1 VA0 to VA4) correspond to the pins of the first controller port, counting from 1 to 9 starting with the top left pin when facing the console.

- **Cart Enable** corresponds to pin B17 of the cartridge port. Pin B1 is the leftmost pin at the front, facing the console. This is used for TMSS bypass. If you are installing this on a non-TMSS console, this pin should probably be connected to ground.

- **MRES** corresponds to pin B2 on the cartridge port. It is used for TMSS bypass and reset in Master System mode, when a flashcart enters and exits special modes such as Master System or Sega CD.

- **M3 (B30)** corresponds to pin B30 of the cartridge port.

- **A23 (B11)** corresponds to pin B11 of the cartridge port.

- **Reset Button** correspond to pin 2 the button reset.
Add a voltage divider resistor for Model 1 VA5/VA6 on the reset button. Connect a 4.7k resistor to 5V and a 10k resistor to GND. The connection point between the two resistors should be connected to the Pi Pico's Reset Button pin.

- **RST, CS, DC, SCL, SDA, BLK and Detect Display** are only needed if you plan to use an LCD display.

- **Bluetooth up/down** will only be connected if used to control a retro Bluetooth module for wireless controllers.

If you want a LED to show the mod's status, use a common cathode bi-color LED. Connect the cathode to ground and the two anodes to pins LED1 and LED2. The region is indicated by color:

LED1 color indicates Japan
LED2 color indicates USA/Americas
A mix of both colors indicates Europe

Overclocking is indicated by the LED blinking at 3Hz when enabled.

**Setting up the Pico**
Download the mega drive model 1 va0 until va4 firmware image [openheart8Mhz.uf2](https://github.com/DUSTINODELLOFFICIAL/openheart/raw/refs/heads/main/build/openheart_v200_8MHZ_free.uf2) or va5/va6 [openheart1074Mhz.uf2](https://github.com/DUSTINODELLOFFICIAL/openheart/raw/refs/heads/main/build/openheart_v200_1074MHZ_free.uf2) firmware image from the /build folder and flash it to the Pico by connecting it to your computer while holding down the BOOTSEL button. It will appear as a storage device — just drag the UF2 file onto it. When the storage device disconnects automatically, it's ready to use.

**Installation examples here** [Here](https://github.com/DUSTINODELLOFFICIAL/openheart/tree/main/example).

**Pico pinout here** [here](https://github.com/DUSTINODELLOFFICIAL/openheart/blob/main/pinout.png)

**Notes & considerations**
Use at your own risk: The mod seems to work well on various Model 1 and Model 2 revisions, but not all revisions have been tested.

Overclocking sets the CPU to the master clock divided by 5 (default is MCLK/7). This results in about 10.74 MHz on NTSC. Most games work well with this, but be aware that crashes, graphical glitches, or controller malfunctions may still occur.

The clocks generated by the Pi Pico are imperceptibly different (+0.013% NTSC, -0.006% PAL) compared to the original oscillator specs. This is not noticeable, but may be relevant for speedrunners.

Switching between 50Hz and 60Hz, or toggling overclock on and off frequently during gameplay, may occasionally cause strange behavior. If this happens, just power cycle the console.

Some (few?) NTSC Model 1 VA7 and Model 2 VA0 consoles have a broken 50Hz mode). These consoles still work fine at 60Hz.

PAL mode composite video on NTSC consoles (and vice versa) may or may not work. RGB output will work. This may depend on your TV or the standard being used.

In PAL/60Hz composite video, the image may flicker with altered colors or appear in black and white. RGB output will work.

---

## Demonstration functions

[https://youtu.be/fwqdS2af00g?si=j-Wv8TLf7hVxnpF5]

## 📄 License
This project is licensed under the terms of the **GNU General Public License v3.0 (GPLv3)**.  
You may redistribute and/or modify it under the terms of the license.  
For more information, visit: [https://www.gnu.org/licenses/gpl-3.0.html](https://www.gnu.org/licenses/gpl-3.0.html).

---

## 🧑‍💻 Author

Developed by Irineu Teza Nunes (YouTube @itnproducoes) for the Brazilian retro gaming community.
Project inspired by 32mbit and enhanced.

---

# Open Heart by 32mbit

Mod multi-região para Sega Genesis/Mega Drive usando Raspberry Pi Pico (RP2040). Este projeto permite alternar entre regiões, controlar frequência, ativar modo Master System, overclock, e muito mais — tudo via controle ou botão físico.

---

## 🧩 Visão Geral

Open Heart transforma seu console em uma central multi-região com recursos avançados:

- Troca de região: Japão, Américas, Europa
- Frequência: 50Hz/60Hz
- Modo Master System
- Overclock dinâmico
- Reset e pausa via controle
- Exibição gráfica em ST7735 ou SSD1306
- Controle de módulo Bluetooth
- Skip automático do TMSS

---

## 🔌 Hardware Requerido

- Raspberry Pi Pico ou RP2040 compatível
- Tela ST7735 (TFT) ou SSD1306 (OLED)
- Sega Genesis/Mega Drive (Modelos 1 ou 2)
- Resistores para divisor de tensão (4.7k e 10k) model 1 va5/va6
- Resistor para pino 7 do controle (22k) model 1 va0 to va4
- Fios para GPIOs conectados ao console e controle

---

## 🎮 Comandos

| Função                       | Comandos                             |
|------------------------------|--------------------------------------|
| Troca de região              | B + C + Start (1s)                   |
| Troca de região (botão físico) | Botão Reset (3s)                   |
| Reset do jogo                | A + B + C + Start (1s)               |
| Troca 50Hz/60Hz (Europa)     | A + B + Start (1s)                   |
| Overclock                    | A + Start (1s)                       |
| Reset do Pico                | A + C + Start (3s)                   |
| Ativar Bluetooth             | B + Start (2s)                       |
| Pausa Master System          | UP + B + C (1s)                      |
| Reset Master System          | UP + C (5s)                          |
| Alternar logo                | C + Start (1s)                       |

---

## 🖥️ Exibição Gráfica

- **ST7735 (TFT)**: gráficos coloridos e logos personalizados
- **SSD1306 (OLED)**: texto gráfico monocromático

Mensagens exibidas:

- Região e frequência
- Modo ativo
- Status do overclock
- Bluetooth ligado/desligado
- Logos: SEGA, 16bit, Mensagem personalizada

---

## ⚙️ Configuração de Região

Região salva na flash e restaurada na inicialização. LEDs indicam:

- Vermelho: Japão
- Verde: Américas
- Âmbar: Europa

---

## 🚀 TMSS Skip

Técnica avançada que ignora o TMSS automaticamente:

- Monitora `!CART_CE`
- Reinicia o 68000 no momento exato
- Permite boot direto do cartucho

---

## Instruções

Este mod é muito semelhante a outros mods existentes, então adaptá-lo ao seu console específico não deve ser difícil. Esquemáticos ou referências de outros mods similares podem ser úteis. Remova o oscilador e monte o Pico o mais próximo possível da localização original da placa.

- **5V** e **terra** podem ser facilmente conectados aos furos deixados pela remoção do oscilador. Recomenda-se usar um diodo (eu usei um 1n4001) no ponto de 5V se você pretende atualizar o firmware com o mod instalado.
  
- **MCLK** deve ser conectado à saída de clock do oscilador.
  
- **VCLK** é conectado ao pino de entrada de clock do 68000 (o VDP também está conectado a este pino e deve ser desconectado dele). Esses fios devem ser mantidos o mais curtos possível. VCLK é opcional caso você não deseje usar o recurso de overclock.
  
- **Jpn/Export** e **NTSC/PAL** devem ser conectados aos pontos da sua placa onde +5V e terra determinam a região e 50/60Hz, respectivamente.
  
- **VRES** e **HALT** são conectados aos pinos correspondentes do 68000.  HALT é opcional caso você não deseje usar o recurso de overclock.
  
Os **pinos 1, 6, 7 e 9** (adicionar resistor para pino 7 do controle (22k) model 1 va0 to va4) correspondem aos pinos da primeira porta de controle, contando de 1 a 9 começando pelo pino superior esquerdo visto de frente para o console.

- **Cart Enable** corresponde ao pino B17 da porta do cartucho. O pino B1 é o mais à esquerda na frente, voltado para o console. Isso é usado para o bypass do TMSS. Se você estiver instalando isso em um console sem TMSS, provavelmente deve conectar esse pino ao terra.
  
- **MRES** corresponde ao pino B2 da porta do cartucho. Isso é usado para o bypass do TMSS and reset in mode master system, quando um flashcart entra e sai de modos especiais como Master System ou Sega CD.

- **M3 (B30)** corresponde ao pino B30 da porta do cartucho.
  
- **A23 (B11)** corresponde ao pino B11 da porta do cartucho.

- **Reset Button** corresponde ao pino 2 do botão de reset.
Adicione um resistor divisor para o modelo 1 VA5/VA6 no botão de reset. Conecte um resitor de 4,7k no 5v e 10k no GND. O ponto de conexão entre os dois resistores deve ser conectado ao pino do botão de reset do Pi Pico.

- **RST, CS, DC, SCL, SDA, BLK e Detect Display** são necessários apenas se for utilizar display LCD. 

- **Bluetooth up/down** será conectado apenas se for utilizado para controlar um módulo bluetooth retro para controles sem fio.
  

Se quiser um LED que mostre o estado do mod, use um LED bicolor de cátodo comum. Conecte o cátodo ao terra e os dois ânodos aos pinos LED1 e LED2. A região é indicada pela cor:

Cor do LED1 indica Japão
Cor do LED2 indica EUA/Américas
Mistura das duas cores indica Europa

O overclock é indicado por um piscar do LED a 3Hz quando ativado.

**Configurando o pico**

Baixe a imagem de firmware do Mega Drive modelo 1 VA0 até VA4 [openheart8Mhz.uf2](https://github.com/DUSTINODELLOFFICIAL/openheart/raw/refs/heads/main/build/openheart_v200_8MHZ_free.uf2) ou VA5/VA6 [openheart1074Mhz.uf2](https://github.com/DUSTINODELLOFFICIAL/openheart/raw/refs/heads/main/build/openheart_v200_1074MHZ_free.uf2) da pasta /build e grave-a no Pico conectando-o ao computador enquanto mantém pressionado o botão BOOTSEL. Ele aparecerá como um dispositivo de armazenamento — basta arrastar o arquivo UF2 para ele. Quando o dispositivo de armazenamento se desconectar automaticamente, estará pronto para uso.

**Exemplos de instalação** [aqui](https://github.com/DUSTINODELLOFFICIAL/openheart/tree/main/example).

**Pinagem do pico** [aqui](https://github.com/DUSTINODELLOFFICIAL/openheart/blob/main/pinout.png)

**Notas e considerações**
Use por sua conta e risco: O mod parece funcionar bem em várias revisões dos modelos 1 e 2, mas nem todas as revisões foram testadas.

O overclock ajusta a CPU para o clock mestre dividido por 5 (o padrão é MCLK/7). Isso resulta em cerca de 10,74 MHz no NTSC. A maioria dos jogos funciona bem com isso, mas esteja ciente de que ainda podem ocorrer travamentos, falhas gráficas ou mau funcionamento dos controles.

Os clocks gerados pelo Pi Pico são imperceptivelmente diferentes (+0,013% no NTSC, -0,006% no PAL) em relação às especificações originais do oscilador. Isso não é perceptível, mas pode ser relevante para speedrunners.

Alternar entre 50Hz e 60Hz, ou ativar/desativar o overclock com frequência durante o jogo, pode ocasionalmente causar comportamentos estranhos. Se isso acontecer, basta reiniciar o console.

Alguns (poucos?) consoles NTSC Model 1 VA7 e Model 2 VA0 têm o modo 50Hz quebrado "têm o modo 50Hz quebrado"). Esses consoles ainda funcionam normalmente em 60Hz.

O vídeo composto em modo PAL em consoles NTSC (e vice-versa) pode ou não funcionar. A saída RGB funcionará. Isso pode depender da sua TV ou do padrão utilizado.

Em vídeo composto no modo PAL/60Hz a imagem irá ficar sintilante com cores alteradas ou preto e branco. A saída RGB funcionará.

---

## 📄 Licença

Este projeto está licenciado sob os termos da **GNU General Public License v3.0 (GPLv3)**.  
Você pode redistribuí-lo e/ou modificá-lo conforme os termos da licença.  
Para mais informações, acesse: [https://www.gnu.org/licenses/gpl-3.0.html]

---

## 🧑‍💻 Autor

Desenvolvido por **Irineu Teza Nunes (youtube @itnproducoes)** para a comunidade retro gamer brasileira 🇧🇷  
Projeto inspirado por 32mbit e aprimorado.

