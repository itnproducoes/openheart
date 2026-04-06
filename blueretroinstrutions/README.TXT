O ponto de alimentação (5v) do Esp32 deve passar pelo rele, o qual irá ativar ou desativar de acordo com o sinal do pino Bluethooh up/down do raspberry. 

Para integrar o raspberry pico programado com o Open heart com o esp32 programado com o Blueretro você irá precisar:

Material:

1 × Relé SRS‑05VDC‑SL
1 × Transistor NPN (2N2222, BC337 ou BC548)
1 × Diodo 1N4007 (proteção)
1 × Resistor 1 kΩ


Conexão:

--> Raspberry Pi Pico

Pin Bluethooh up/down → Resistor 1 kΩ
Resistor 1 kΩ → Base do transistor
GND do Pico → GND do circuito

--> Relé SRS‑05VDC‑SL
Um lado da bobina → +5 V
Outro lado da bobina → Coletor do transistor
COM  → +5 V
NO → +5 V ESP 32

-->  Diodo 1N4007 (proteção)

Catodo (lado da faixa) → +5 V
Ânodo → Lado do coletor / bobina do relé


