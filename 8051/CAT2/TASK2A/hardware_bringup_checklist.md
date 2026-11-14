# AT89S52 Hardware Bring-Up Sheet

| Parameter | Datasheet / Target Value | Student Measured Entry | Status |
|---|---|---|---|
| Target Microcontroller | AT89S52 (DIP-40) | AT89S52-24PU | Verified |
| CPU Core Architecture | 8-bit CISC 8051 | 8051 Standard Core | Verified |
| Operating Voltage Rail | 4.0V - 5.5V DC | 5.02V DC | PASSED |
| Power Rail Ripple | < 50 mV pk-pk | 18 mV pk-pk | PASSED |
| Debug / Programming Interface | SPI In-System Programming (ISP) | USBASP SPI Programmer | Detected |
| Crystal Frequency | 11.0592 MHz ± 30 ppm | 11.0589 MHz | PASSED |
| Reset Voltage (Steady State) | < 0.8V DC (Logic LOW) | 0.04V DC | PASSED |
| EA/VPP Pin 31 State | HIGH (+5V) for On-Chip Flash | 5.01V DC | PASSED |
| Target Device Signature | 0x1E 0x52 (Atmel AT89S52) | 0x1E 0x52 0x06 Read OK | PASSED |
