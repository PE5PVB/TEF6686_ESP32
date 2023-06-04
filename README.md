# TEF6686_ESP32
Advanced Tuner software for NXP TEF668x tuners with ESP32 board\
Based on Catena / NXP semiconductors API

More information: https://www.pe5pvb.nl/tef6686/

## Setup
During boot hold:
- **BW** button to change rotary encoder direction
- **Mode** button the flip screen
- **Standby** button to calibrate analogue S-meter
- **Rotary** button to switch between normal and optical rotary encoder

## Manual
- **STANDBY SHORT** PRESS: Switch band
- **STANDBY LONG** PRESS: Standby
- **ROTARY SHORT** PRESS: Set stepsize or navigate
- **ROTARY LONG** PRESS: Toggle iMS & EQ
- **MODE SHORT** PRESS: Switch between auto/manual or exit menu
- **MODE LONG** PRESS: Open menu
- **BW SHORT** PRESS: Switch bandwidth setting
- **BW LONG** PRESS: Switch mono, or auto stereo

## Instalation
**Recommended method:** You can download already compiled software and upload it using prepared script from [release page](https://github.com/PE5PVB/TEF6686_ESP32/releases).

**Alternative method:** You can download source code from [release page](https://github.com/PE5PVB/TEF6686_ESP32/releases) or using git. Then compile and upload it using for example Arduino IDE. **Important** you need to fill your User_Setup.h file (located in Arduino/libraries/TFT_eSPI folder) with these values:
```
#define ILI9341_DRIVER
#define TFT_CS          5
#define TFT_DC          17
#define TFT_RST         16
#define LOAD_GLCD
#define LOAD_FONT2
#define LOAD_FONT4
#define LOAD_FONT6
#define LOAD_FONT7
#define LOAD_FONT8
#define LOAD_GFXFF
#define SMOOTH_FONT
#define SPI_FREQUENCY   10000000
```
**ALL OTHER SETTINGS SHOULD BE REMARKED!**

From v1.16 you **need to** update your ESP32 boards in board manager to v2.x  
In case you experience QRM from the screen on 90MHz, try to lower the SPI_FREQUENCY parameter.

### Connecting analog signal meter
```
                      to meter
                          |
                R         V
  IO27 -------=====-----=====---|
               1 k     5 k POT
```
## License
This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details. 
