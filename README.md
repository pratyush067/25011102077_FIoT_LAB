# Fundamentals of IoT (FIoT) Laboratory Portfolio

**Repository:** `25011102077_FIoT_LAB`  
**Student Name:** PRATYUSH J   
**Registration Number:** 25011102077  
**Degree & Branch:** B.Tech CSE (IoT - B)  
**Institution:** Shiv Nadar University, Chennai — Department of Computer Science & Engineering  
**Course:** 25CS2741 Fundamentals of Internet of Things + Lab  

---

## 1. Overview
This repository contains my lab work, circuit diagrams, code, and project files for the Fundamentals of IoT course at Shiv Nadar University, Chennai.

The exercises are organized across two hardware platforms:
1. **8051 (AT89S52):** Register-level programming in Keil C51 covering GPIO pin control, hardware timer delays, software PWM fading, UART serial communication, 16x2 HD44780 LCD interfacing, and 4x4 matrix keypads.
2. **STM32 (STM32F103 Blue Pill & STM32F401 Nucleo-64):** Firmware development in Keil MDK-ARM with STM32CubeMX HAL, covering button debouncing, serial CLI commands, ESP8266 Wi-Fi AT commands, I2C sensor interfacing with BME280, local HTTP web server hosting, cloud MQTT telemetry, and an end-to-end IoT Capstone Project comparing localized BME280 microclimate telemetry against the OpenWeatherMap API with real-time insights and recommendations on a Node-RED dashboard.

---

## 2. CAT Folders & Task Directory Index

Below is the index of all continuous evaluation assignments across both platforms. Each task folder contains its standalone `README.md`, circuit schematic (`circuit.png`), and complete project/source files:

### 8051 Microcontroller (AT89S52)

| Category Folder | Task Folder | Experiment Title | Hardware Peripherals | Task Documentation |
|---|---|---|---|:---:|
| [8051/CAT2](8051/CAT2/) | [TASK2A](8051/CAT2/TASK2A/) | 8051 Hardware Bring-Up & Power Supply Verification | AT89S52, 11.0592 MHz XTAL, Reset Circuit | [README](8051/CAT2/TASK2A/README.md) |
| [8051/CAT2](8051/CAT2/) | [TASK2B](8051/CAT2/TASK2B/) | Bare-Metal LED Blink | P1.0 LED, 11.0592 MHz Crystal | [README](8051/CAT2/TASK2B/README.md) |
| [8051/CAT2](8051/CAT2/) | [TASK2C](8051/CAT2/TASK2C/) | Modular Millisecond Software Delay Library | Timer/Loop Timing, P1.0 Test Indicator | [README](8051/CAT2/TASK2C/README.md) |
| [8051/CAT3](8051/CAT3/) | [TASK3A](8051/CAT3/TASK3A/) | Switch Polling & LED Chase / Running LED Pattern | P1.0–P1.3 LEDs, P3.2 Switch | [README](8051/CAT3/TASK3A/README.md) |
| [8051/CAT3](8051/CAT3/) | [TASK3B](8051/CAT3/TASK3B/) | 4-Bit Binary Up-Counter on LEDs | Port 1 LEDs, P3.2 Switch Input | [README](8051/CAT3/TASK3B/README.md) |
| [8051/CAT3](8051/CAT3/) | [TASK3C](8051/CAT3/TASK3C/) | Alternating Bitwise LED Flasher (0x55 / 0xAA) | Port 1 LEDs, Software Inversion | [README](8051/CAT3/TASK3C/README.md) |
| [8051/CAT3](8051/CAT3/) | [TASK3D](8051/CAT3/TASK3D/) | Synchronous All-LED Alert Flash | Port 1 LEDs, 500 ms Period | [README](8051/CAT3/TASK3D/README.md) |
| [8051/CAT4](8051/CAT4/) | [TASK4A](8051/CAT4/TASK4A/) | 4x4 Keypad Matrix Scan & 7-Segment Display | Port 2 Keypad, Port 0 7-Segment | [README](8051/CAT4/TASK4A/README.md) |
| [8051/CAT4](8051/CAT4/) | [TASK4B](8051/CAT4/TASK4B/) | 10-Key LED Display Mode Controller | Keypad Input, Multi-Pattern Dispatch | [README](8051/CAT4/TASK4B/README.md) |
| [8051/CAT5](8051/CAT5/) | [TASK5A](8051/CAT5/TASK5A/) | Hardware Timer 0 Periodic Interrupt (1s Timebase) | Timer 0 Mode 1 (TH0=0xFC, TL0=0x66) | [README](8051/CAT5/TASK5A/README.md) |
| [8051/CAT5](8051/CAT5/) | [TASK5B/TASK5B.1](8051/CAT5/TASK5B/TASK5B.1/) | Software PWM LED Fading (500 Hz, 0% to 100%) | Timer 1, P1.0 LED | [README](8051/CAT5/TASK5B/TASK5B.1/README.md) |
| [8051/CAT5](8051/CAT5/) | [TASK5B/TASK5B.2](8051/CAT5/TASK5B/TASK5B.2/) | Variable Frequency Pulse Generation (100 Hz – 5 kHz) | Timer 1, P1.1 Output | [README](8051/CAT5/TASK5B/TASK5B.2/README.md) |
| [8051/CAT5](8051/CAT5/) | [TASK5B/TASK5B.3](8051/CAT5/TASK5B/TASK5B.3/) | Calibrated Duty Cycle Controller & Waveform Synthesizer | Timer 1, Mode 2 Auto-Reload | [README](8051/CAT5/TASK5B/TASK5B.3/README.md) |
| [8051/CAT5](8051/CAT5/) | [TASK5C](8051/CAT5/TASK5C/) | 4-Phase Unipolar Stepper Motor Control | ULN2003 Driver, P1.4–P1.7 | [README](8051/CAT5/TASK5C/README.md) |
| [8051/CAT6](8051/CAT6/) | [TASK6A](8051/CAT6/TASK6A/) | UART String Transmitter (9600-8-N-1) | P3.1 (TxD), USB-UART Bridge | [README](8051/CAT6/TASK6A/README.md) |
| [8051/CAT6](8051/CAT6/) | [TASK6B](8051/CAT6/TASK6B/) | Full-Duplex UART Echo Terminal | P3.0 (RxD), P3.1 (TxD) | [README](8051/CAT6/TASK6B/README.md) |
| [8051/CAT7](8051/CAT7/) | [TASK7A](8051/CAT7/TASK7A/) | 16x2 HD44780 LCD Driver Initialization & Display | Port 2 4-Bit LCD Bus | [README](8051/CAT7/TASK7A/README.md) |
| [8051/CAT7](8051/CAT7/) | [TASK7B](8051/CAT7/TASK7B/) | LCD DDRAM Cursor Positioning & Dynamic Counter | Port 2 4-Bit LCD Bus | [README](8051/CAT7/TASK7B/README.md) |
| [8051/CAT7](8051/CAT7/) | [TASK7C](8051/CAT7/TASK7C/) | 2D Interactive Keypad Cursor Navigation | Port 1 Keypad, Port 2 LCD | [README](8051/CAT7/TASK7C/README.md) |

---

### STM32 ARM Cortex-M (STM32F103 & STM32F401)

| Category Folder | Task Folder | Experiment Title | Hardware Peripherals | Task Documentation |
|---|---|---|---|:---:|
| [STM32/CAT8](STM32/CAT8/) | [TASK8A](STM32/CAT8/TASK8A/) | STM32 Blue Pill GPIO Bring-Up & Switch LED | PC13 LED, PA0 Tactile Button | [README](STM32/CAT8/TASK8A/README.md) |
| [STM32/CAT8](STM32/CAT8/) | [TASK8B](STM32/CAT8/TASK8B/) | Software Push-Button Contact Debounce & Edge Toggle | PC13 LED, PA0 Button, HAL_GetTick() | [README](STM32/CAT8/TASK8B/README.md) |
| [STM32/CAT8](STM32/CAT8/) | [TASK8C](STM32/CAT8/TASK8C/) | Temporal Classifier (<1s Short vs ≥1s Long Press) | PC13 LED, PA0 Button | [README](STM32/CAT8/TASK8C/README.md) |
| [STM32/CAT9](STM32/CAT9/) | [TASK9A](STM32/CAT9/TASK9A/) | USART1 115200-8-N-1 Character Transmit & Echo | USART1 (PA9/PA10), USB-TTL | [README](STM32/CAT9/TASK9A/README.md) |
| [STM32/CAT9](STM32/CAT9/) | [TASK9B](STM32/CAT9/TASK9B/) | Interactive Serial CLI Parser ("LED ON/OFF/TOGGLE") | USART1, PC13 User LED | [README](STM32/CAT9/TASK9B/README.md) |
| [STM32/CAT10](STM32/CAT10/) | [TASK10A](STM32/CAT10/TASK10A/) | STM32 USART Bridge & ESP8266 Modem Bring-Up (`AT` -> `OK`) | USART2 (PA2/PA3), Wemos D1 Mini | [README](STM32/CAT10/TASK10A/README.md) |
| [STM32/CAT10](STM32/CAT10/) | [TASK10B](STM32/CAT10/TASK10B/) | ESP8266 Wi-Fi Mode Setup & AP Scanning (`CWMODE`, `CWLAP`) | USART2, ESP8266 Modem | [README](STM32/CAT10/TASK10B/README.md) |
| [STM32/CAT11](STM32/CAT11/) | [TASK11](STM32/CAT11/TASK11/) | Wi-Fi Station Association & Multi-Client HTTP Server (Port 80) | USART2, ESP8266 TCP Server | [README](STM32/CAT11/TASK11/README.md) |
| [STM32/CAT12](STM32/CAT12/) | [TASK12A](STM32/CAT12/TASK12A/) | NUCLEO-F401RE Onboard LD2 LED 84 MHz Bring-Up | PA5 User LED, ST-LINK V2.1 | [README](STM32/CAT12/TASK12A/README.md) |
| [STM32/CAT12](STM32/CAT12/) | [TASK12B](STM32/CAT12/TASK12B/) | PC13 (B1) User Switch State Remembrance & Temporal Press | PC13 User Button, PA5 LED | [README](STM32/CAT12/TASK12B/README.md) |
| [STM32/CAT13](STM32/CAT13/) | [TASK13A](STM32/CAT13/TASK13A/) | Bosch Sensortec BME280 I²C Environmental Sensor Driver | I2C1 (PB8/PB9), BME280 Sensor | [README](STM32/CAT13/TASK13A/README.md) |
| [STM32/CAT13](STM32/CAT13/) | [TASK13B](STM32/CAT13/TASK13B/) | Dynamic JSON Environmental Telemetry Formatter | I2C1 Sensor, Floating-Point Formatter | [README](STM32/CAT13/TASK13B/README.md) |
| [STM32/CAT13](STM32/CAT13/) | [TASK13C](STM32/CAT13/TASK13C/) | Live HTTP Telemetry Service & Node-RED Flow Ingestion | Port 80 HTTP, Node-RED Dashboard | [README](STM32/CAT13/TASK13C/README.md) |
| [STM32/CAT14](STM32/CAT14/) | [TASK14](STM32/CAT14/TASK14/) | Cloud MQTT Telemetry & Node-RED Dashboard | ESPLib Driver, USART2 Modem, MQTT | [README](STM32/CAT14/TASK14/README.md) |
| [STM32/CAT15](STM32/CAT15/) | [TASK15](STM32/CAT15/TASK15/) | IoT Capstone Project: BME280 Telemetry & OpenWeatherMap Intelligence System | STM32F401RE, BME280 (I2C1), ESP8266 (USART1), OpenWeather API, Node-RED | [README](STM32/CAT15/TASK15/README.md) |

---

## 3. Hardware Platforms

| Platform | Target Microcontroller | Architecture | Operating Voltage | Clock Source | Primary Peripherals / Drivers |
|---|---|---|---|---|---|
| **8051** | Atmel AT89S52 | 8-bit CISC | 5.0V DC | 11.0592 MHz Crystal | GPIOs, Timers 0/1, UART (9600-8-N-1), HD44780 LCD, 4x4 Keypad, ULN2003 Stepper |
| **STM32 Tier 1** | STM32F103C8T6 (Blue Pill) | 32-bit ARM Cortex-M3 | 3.3V DC | 72 MHz (8 MHz HSE + PLL x9) | GPIO (PC13 LED, PA0 Button), USART1, SysTick |
| **STM32 Tier 2** | STM32F401RET6 (Nucleo-64) | 32-bit ARM Cortex-M4 with FPU | 3.3V DC | 84 MHz (HSI / HSE + PLL) | GPIO (PA5 LD2, PC13 B1), USART2, I2C1 (BME280), ESP8266 Modem |
| **Wi-Fi Modem** | Wemos D1 Mini (ESP8266-12F) | 32-bit Tensilica L106 | 3.3V / 5V DC | 80 / 160 MHz | AT Command Interpreter, TCP Server (Port 80), MQTT Client (Port 1883) |
| **Environmental Sensor** | Bosch Sensortec BME280 | Digital Sensor | 3.3V DC | 100 kHz Standard I²C Bus | Temperature, Barometric Pressure, Relative Humidity |

---

## 4. Toolchains & Development Setup

- **Keil µVision C51:** Used for AT89S52 bare-metal development. Open the `.uvproj` file in any task folder to build the project and generate the Intel HEX binary (`Objects/*.hex`) for ISP flash burning.
- **STM32CubeMX & Keil MDK-ARM (µVision5):** Used for STM32 Cortex-M3 and Cortex-M4 targets. Double-click `.uvprojx` inside each task's `MDK-ARM/` directory to open the firmware project, or open the `.ioc` file in STM32CubeMX to inspect pinout configurations and clock trees.
- **Node-RED:** Flow environment used for HTTP telemetry ingestion and real-time MQTT dashboard monitoring on `localhost:1880`.
