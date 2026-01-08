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
- Led Bright:
  UP + Start (1s)  

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
- Amber: Europe 50Hz
- Purple: Europe 60Hz

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
| Ativar/ Desativar no iniciar | UP in ON                             |
| Pausa Master System          | UP + B + C (1s)                      |
| Reset Master System          | UP + C (5s)                          |
| Alternar logo                | C + Start (1s)                       |
| Alternar brilho do LED       | UP + Start (1s)                      |

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
- Âmbar: Europa 50Hz
- Roxo: Europa 60Hz

---

## 🚀 TMSS Skip

Técnica avançada que ignora o TMSS automaticamente:

- Monitora `!CART_CE`
- Reinicia o 68000 no momento exato
- Permite boot direto do cartucho

---

## 🧑‍💻 Autor

Desenvolvido por **Irineu Teza Nunes (youtube @itnproducoes)** para a comunidade retro gamer brasileira 🇧🇷  
Projeto inspirado por 32mbit e aprimorado.

---

## 📄 Licença

Licença de Uso de Código-Fonte – Freeware

    Concessão de Licença O Licenciante concede ao Licenciado o direito não exclusivo e intransferível de acessar e visualizar o código-fonte do Software, bem como utilizá-lo internamente, exclusivamente para fins pessoais ou corporativos, conforme estes termos.

    Direitos e Restrições Salvo autorização prévia e por escrito do Licenciante, o Licenciado não poderá:

(a) usar comercialmente o Software ou qualquer obra derivada (inclui venda, aluguel, prestação como serviço/SaaS, consultoria com distribuição do Software);

(b) redistribuir, publicar, disponibilizar ou sublicenciar o Software ou o código-fonte, no todo ou em parte;

(c) modificar ou criar obras derivadas com finalidade de distribuição externa;

(d) remover ou alterar avisos de direitos autorais, marcas e créditos;

(e) contornar mecanismos técnicos de proteção.

    Permissão de Modificação Interna O Licenciado pode modificar o código apenas para uso interno, sem distribuição a terceiros. Qualquer distribuição externa exige autorização prévia do Licenciante.

    Propriedade Intelectual O Software e o código-fonte são de titularidade do Licenciante. Nenhum direito de propriedade é transferido ao Licenciado.

    Garantias e Responsabilidade O Software é fornecido “no estado em que se encontra”, sem garantias. O Licenciante não se responsabiliza por danos de qualquer natureza decorrentes do uso.

    Termo, Revogação e Auditoria O Licenciante pode revogar esta licença em caso de violação. O Licenciado concorda em fornecer informações razoáveis para verificar conformidade, quando solicitado.

    Lei Aplicável e Foro Este acordo é regido pela legislação brasileira e fica eleito o foro da cidade do Licenciante para dirimir controvérsias.

