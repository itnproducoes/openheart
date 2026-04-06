The ESP32's 5V power supply must pass through the relay, which will activate or deactivate it according to the signal from the Raspberry Pi's Bluetooth up/down pin.

To integrate the Raspberry Pi Pico programmed with OpenHeart and the ESP32 programmed with BlueRetro, you will need:

Materials:

1 × SRS-05VDC-SL Relay
1 × NPN Transistor (2N2222, BC337 or BC548)
1 × 1N4007 Diode (protection)
1 × 1kΩ Resistor

Connection:

--> Raspberry Pi Pico
Bluetooth up/down pin → 1kΩ resistor
1kΩ resistor → Transistor base
Pico GND → Circuit GND

--> SRS-05VDC-SL Relay
One side of the coil → +5V
Other side of the coil → Transistor collector
COM → +5V
NO → +5V ESP 32

--> 1N4007 Diode (protection)
Cathode (strip side) → +5V
Anode → Collector side / relay coil

###########################


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


