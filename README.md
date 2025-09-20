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

## 🧑‍💻 Author

Developed by Irineu Teza Nunes (YouTube @itnproducoes) for the Brazilian retro gaming community.
Project inspired by 32mbit and enhanced.


---

## 📄 License
This project is licensed under the terms of the **GNU General Public License v3.0 (GPLv3)**.  
You may redistribute and/or modify it under the terms of the license.  
For more information, visit: [https://www.gnu.org/licenses/gpl-3.0.html](https://www.gnu.org/licenses/gpl-3.0.html).

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
  
- **MRES** corresponde ao pino B2 da porta do cartucho. Isso é usado para o bypass do TMSS, quando um flashcart entra e sai de modos especiais como Master System ou Sega CD. Se estiver instalando em um console sem TMSS, este pino não deve ser conectado.

- **M3 (B30)** corresponde ao pino B30 da porta do cartucho.
  
- **A23 (B11)** corresponde ao pino B11 da porta do cartucho.

- **RST, CS, DC, SCL, SDA, BLK e Detect Display** são necessários apenas se for utilizar display LCD. 

- **Bluetooth up/down** será conectado apenas se for utilizado para controlar um módulo bluetooth retro para controles sem fio.
  

Se quiser um LED que mostre o estado do mod, use um LED bicolor de cátodo comum. Conecte o cátodo ao terra e os dois ânodos aos pinos LED1 e LED2. A região é indicada pela cor:

Cor do LED1 indica Japão
Cor do LED2 indica EUA/Américas
Mistura das duas cores indica Europa

O overclock é indicado por um piscar do LED a 3Hz quando ativado.

**Configurando o pico**

Baixe a imagem [openheart.uf2 firmware image](https://github.com/DUSTINODELLOFFICIAL/openheart/raw/refs/heads/main/build/openheart.uf2) da pasta /build e grave-a no Pico conectando-o ao computador enquanto mantém pressionado o botão BOOTSEL. Ele aparecerá como um dispositivo de armazenamento — basta arrastar o arquivo UF2 para dentro dele.
Quando o dispositivo de armazenamento se desconectar automaticamente, significa que está pronto para uso.

---

## 📄 Licença

Este projeto está licenciado sob os termos da **GNU General Public License v3.0 (GPLv3)**.  
Você pode redistribuí-lo e/ou modificá-lo conforme os termos da licença.  
Para mais informações, acesse: [https://www.gnu.org/licenses/gpl-3.0.html]

---

## 🧑‍💻 Autor

Desenvolvido por **Irineu Teza Nunes (youtube @itnproducoes)** para a comunidade retro gamer brasileira 🇧🇷  
Projeto inspirado por 32mbit e aprimorado.

