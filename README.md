# Temperature and Humidity Monitoring System

## Summary
The firmware sets up communication with the DHT22 and triggers a request for temperature and humidity information every 2 seconds, which is
then displayed through a I²C LCD. The setup provides temperature and humidity information. I used STM32 HAL libraries to help me start I²C communication
and other boilerplate code required to flash the STM32 board. I developed the code needed to interact with the DHT22 by mainly using a custom microsecond delay function
and STM32's read pin function and developed the code needed to interact with I²C and used STM32's I²C transmit function to send data.

![Block Diagram](blockdiagram.png?raw=true "Block Diagram")

Above represents a simple block diagram of this project
### DHT22
- The DHT22 provides temperature and humidity data through its data line.
### STM32 Microcontroller
- The microcontroller requests and handles the incoming data from the DHT22 by sending time-sensitive pulses through the data line to the DHT22. THe incoming data is interpreted accordingly using the datasheet, which is then outputted to the I²C LCD. The microcontroller also employs interrupts that detect when 2 buttons connected to an input pin goes high. The current two ISRs linked to the two buttons toggle the backlight of the LCD and toggle the units of temperature between C and F.
### I²C LCD
- Outputs temperature and humidity measurements.
---

## Demo
https://youtu.be/Xr0c_5vThYU

---

## Technical Highlights
- **Platform:** STM NUCLEO-C031C6 Development Board
- **Language:** C
- **Peripherals:** I²C
- **Notable Features:**
  - Button toggle between Celsius and Fahrenheit
  - Buttom toggle between on/off LCD backlight

---

## Setup

### Wiring Diagram
![Wiring Diagram](wiringdiagram.png?raw=true "Wiring Diagram")

### Peripherals
- STM32 NUCLEOC031C6 microcontroller
- DHT22 Temperature Humidity Module
- I²C LCD (4 pins)
  
### Software Requirements
- STM32CubeIDE
- STM32CubeMX
- HAL

### Build & Flash
1. Open project in STM32CubeIDE
2. Connect board via ST-Link port
3. Build
4. Flash

### Usage
1. Press buttons accordingly to toggle temperature units or to toggle backlight of display.
---
## Vision
in progress
## Issues/Improvements
1. Code documentation
