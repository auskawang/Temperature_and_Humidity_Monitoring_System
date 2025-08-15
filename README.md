# Temperature and Humidity Monitoring System

## Summary
The firmware sets up communication with the DHT22 and triggers a request for temperature and humidity information every 2 seconds, which is
then displayed through a I²C LCD. The setup provides temperature and humidity information. I used STM32 HAL libraries to help me start I²C communication
and other boilerplate code required to flash the STM32 board. I developed the code needed to interact with the DHT22 by mainly using a custom microsecond delay function
and STM32's read pin function and developed the code needed to interact with I²C and used STM32's I²C transmit function to send data.

---

## Demo
insert something

---

## Technical Highlights
- **Platform:** STM NUCLEO-C031C6 Development Board
- **Language:** C
- **Peripherals:** I²C
- **Notable Features:**
  - Button toggle between Celsius and Fahrenheit
  - Buttom toggle between on/off LCD backlight
---

## Skills Demonstrated
- Embedded C firmware development
- Hardware–software integration & debugging
- Protocol implementation (I²C, UART)
- Version control (Git/GitHub)
- Reading and applying datasheets & hardware manuals

---

## Quick Start
### Requirements
- Toolchain: (?)
- Libraries: [List exact library versions]
- Hardware: [STM NUCLEO-C031C6 Development Board, DHT22, I²C LCD, Buttons, Wires]

### Build & Flash
...
