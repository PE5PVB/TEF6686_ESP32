# Note:
The version in the repository is an ongoing development. It could and will contain bugs. To make sure you use the latest fully tested firmware, check the releases!


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

**Alternative method:** You can download source code from [release page](https://github.com/PE5PVB/TEF6686_ESP32/releases) or using git.\
`git clone https://github.com/PE5PVB/TEF6686_ESP32`

Then compile and upload it using for example Arduino IDE (remember to select ESP's serial port).\
**Important** you need to fill your User_Setup.h file (located in Arduino/libraries/TFT_eSPI folder) with these values:
```
#define ILI9341_DRIVER
#define TFT_CS          5
#define TFT_DC          17
#define TFT_RST         16
#define SPI_FREQUENCY   10000000

#define LOAD_FONT7
#define LOAD_GFXFF
#define SMOOTH_FONT
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
## Contributing
We are open for a new ideas in our project. Feel free to share your thoughts in [Discussions](https://github.com/PE5PVB/TEF6686_ESP32/discussions).\
You can also contribute your own code using [Pull Requests](https://github.com/PE5PVB/TEF6686_ESP32/pulls). We will review it and merge into main branch.

You are using our software and you found a difficulty? Please create new [issue](https://github.com/PE5PVB/TEF6686_ESP32/issues) and describe your problem.

We also would like to invite you to join our Discord community where we share our ideas and help each other with some issues.\
[<img alt="Join the TEF6686 Discord community!" src="https://i.imgur.com/BYqhuLI.png">](https://discord.gg/ZAVNdS74mC)  

Special thanks to all [contributors](https://github.com/PE5PVB/TEF6686_ESP32/graphs/contributors). You are awesome! ❤️
## License
This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details. 
