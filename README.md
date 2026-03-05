[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](https://github.com/PE5PVB/TEF6686_ESP32#contributing)
[![License](https://img.shields.io/badge/license%20-%20GNU_GPLv3-GPLv3?color=blue)](https://github.com/PE5PVB/TEF6686_ESP32/blob/main/LICENSE)

# Note:
The version in the repository is an ongoing development. It could and will contain bugs. To make sure you use the latest fully tested firmware, check the releases!



# TEF6686_ESP32
Advanced Tuner software for NXP TEF668x tuners with ESP32 board\
More information: https://www.pe5pvb.nl/tef6686/

## Wiki
- [About the software & features](https://github.com/PE5PVB/TEF6686_ESP32/wiki)
- [Getting started](https://github.com/PE5PVB/TEF6686_ESP32/wiki#getting-started)
- [How to install the software](https://github.com/PE5PVB/TEF6686_ESP32/wiki/Installing-the-software)
- [How to use memory channels](https://github.com/PE5PVB/TEF6686_ESP32/wiki/How-to-use-memory-channels)
- [How to use the FM DX scanner](https://github.com/PE5PVB/TEF6686_ESP32/wiki/How-to-use-the-FM-DX-scanner)
- [Menu options explained](https://github.com/PE5PVB/TEF6686_ESP32/wiki/Menu-options-explained)

## Accessibility
This firmware includes an optional audio accessibility layer for blind and low-vision users.

What it adds in practice:
- variable-pitch navigation cues in menus and submenus, so you can hear your relative position from beginning to end
- clear menu state cues for `enter`, `back`, `exit`, and `confirm`
- consistent toggle pattern: `ON = low -> high`, `OFF = high -> low`
- the same ON/OFF two-tone pattern for quick actions outside menu (including `Stereo/Mono` on supported bands)
- Voice Lite cues for selected actions (for example manual frequency entry digits and menu position feedback)

Shortcut notes:
- `Short press BW` means a quick tap (not hold) of the `BW` button on the main screen (outside menu): it opens the `BW` selector (`Filter/iMS/EQ`).
- `Long press BW` on `FM/OIRT` toggles `Stereo/Mono` and uses the ON/OFF two-tone cue pattern.
- `Long press BW` on `LW/MW/SW` keeps the `BW` selector flow (no Stereo/Mono toggle on AM bands).
- Boot shortcut for quick accessibility toggle: hold `BW + MODE + BAND` while powering on.

BW selector notes (important for audio navigation):
- In `FM/OIRT` selector, item order is: filter values (`56 kHz` ... `311 kHz`), then `Auto BW`, then `iMS`, then `EQ`, and the last item is `OK`.
- The highest cursor tone corresponds to the last selector item (`OK`).
- `iMS` and `EQ` are toggle items (activate with knob press), and `OK` confirms the selector changes.
- In `AM` selector, order is: AM filter values and final `OK` (last/highest-tone item).

## Regression Checklist (2026-03-04)
| Area | Expected behavior | Status |
|---|---|---|
| Main menu navigation | One position-dependent beep per step (no duplicate fixed tone) | PASS |
| Submenu navigation | One position-dependent beep per step (no duplicate fixed tone) | PASS |
| Menu transitions | Distinct cues for enter menu, back, and exit | PASS |
| Confirm action | Confirm cue present in menu and nested submenus | PASS |
| Quick Stereo/Mono (`long BW`, FM/OIRT) | ON/OFF two-tone pattern is applied consistently | PASS |
| BW selector (`Filter/iMS/EQ`) | Cursor navigation and toggle cues are audible | PASS |
| BAND switching | FM/AM switching works without freeze or lockup | PASS |
| Persisted band settings | Invalid stored values are sanitized on startup | PASS |
| FlashWizard i18n | Auto-detect OS language, full UI for PL/EN/DE/ES/FR/IT, EN fallback | PASS |

## OTA And Recovery (2026-03-05)
This tree now includes a serial-triggered HTTP OTA path with a boot-health guard.

Serial commands (only when USB is not in XDR mode):
- `O?` - print OTA status (`running`, `next`, pending guard state)
- `OU<url>` - download firmware from HTTP/HTTPS URL and reboot
- `OR` - rollback to previously saved app partition and reboot
- `OC` - clear pending guard state manually

Important constraints:
- Current 4MB build image is about 3.0 MB (`TEF6686_ESP32.ino.bin`), so dual-slot A/B OTA does **not** fit in 4MB.
- A dedicated 8MB dual-OTA layout is provided in `partitions_8mb_ota.csv`.
- PlatformIO environment for this profile: `esp32_ota8mb`.

Build example:
```bash
pio run -e esp32_ota8mb
```

## Contributing
We are open for a new ideas in our project. Feel free to share your thoughts in [Discussions](https://github.com/PE5PVB/TEF6686_ESP32/discussions).\
You can also contribute your own code using [Pull Requests](https://github.com/PE5PVB/TEF6686_ESP32/pulls). We will review it and merge into main branch.

You are using our software and you found a difficulty? Please create new [issue](https://github.com/PE5PVB/TEF6686_ESP32/issues) and describe your problem.

We also would like to invite you to join our Discord community where we share our ideas and help each other with some issues.\
[<img alt="Join the TEF6686 Discord community!" src="https://i.imgur.com/lI9Tuxf.png" height="120">](https://discord.gg/ZAVNdS74mC)  

Special thanks to all [contributors](https://github.com/PE5PVB/TEF6686_ESP32/graphs/contributors). You are awesome! ❤️
## License
This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details. 

## If you like this software
[!["Buy Me A Coffee"](https://www.buymeacoffee.com/assets/img/custom_images/orange_img.png)](https://www.buymeacoffee.com/pe5pvb)
