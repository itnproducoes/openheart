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

## 🧑‍💻 Autor

Desenvolvido por **Irineu Teza Nunes (youtube @itnproducoes)** para a comunidade retro gamer brasileira 🇧🇷  
Projeto inspirado por 32mbit e aprimorado.


