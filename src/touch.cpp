#include "touch.h"
#include "constants.h"
#include <EEPROM.h>

void doTouchEvent(uint16_t x, uint16_t y) {
  if (batteryWarningActive) {
    batteryWarningActive = false;
    BuildDisplay();
    return;
  }
  if (seek) radio.setUnMute();
  seek = false;
  if (scandxmode) {
    cancelDXScan();
  } else {
    if (menu) {
      if (x > 0 && x < 320 && y > 0 && y < 33) {
        ModeButtonPress();
        return;
      }
      if (menuopen) {                                                     // Menu navigation
        if (x > 18 && x < 78 && y > 150 && y < 190) KeyDown();            // ---------------
        if (x > 240 && x < 300 && y > 150 && y < 190) KeyUp();
        if ((x > 240 && x < 300 && y > 40 && y < 80) || (x > 130 && x < 190 && y > 150 && y < 190)) {
          touchrepeat = false;
          ButtonPress();
        }
        return;
      } else {
        if (x > 8 && x < 158) {
          if (y > 38 && y < 70) {
            if (items[menupage] > 0) {
              menuitem = 0;
              menuoption = ITEM1;
              DoMenu();
            }
          } else if (y > 78 && y < 110) {
            if (items[menupage] > 1) {
              menuitem = 1;
              menuoption = ITEM2;
              DoMenu();
            }
          } else if (y > 118 && y < 150) {
            if (items[menupage] > 2) {
              menuitem = 2;
              menuoption = ITEM3;
              DoMenu();
            }
          } else if (y > 158 && y < 190) {
            if (items[menupage] > 3) {
              menuitem = 3;
              menuoption = ITEM4;
              DoMenu();
            }
          } else if (y > 198 && y < 230) {
            if (items[menupage] > 4) {
              menuitem = 4;
              menuoption = ITEM5;
              DoMenu();
            }
          }
        } else if (x > 163 && x < 313) {
          if (y > 38 && y < 70) {
            if (items[menupage] > 5) {
              menuitem = 5;
              menuoption = ITEM6;
              DoMenu();
            }
          } else if (y > 78 && y < 110) {
            if (items[menupage] > 6) {
              menuitem = 6;
              menuoption = ITEM7;
              DoMenu();
            }
          } else if (y > 118 && y < 150) {
            if (items[menupage] > 7) {
              menuitem = 7;
              menuoption = ITEM8;
              DoMenu();
            }
          } else if (y > 158 && y < 190) {
            if (items[menupage] > 8) {
              menuitem = 8;
              menuoption = ITEM9;
              DoMenu();
            }
          } else if (y > 198 && y < 230) {
            if (items[menupage] > 9) {
              menuitem = 9;
              menuoption = ITEM10;
              DoMenu();
            }
          }
        }
        touchrepeat = true;
        return;
      }
    }

    if (!menu && !BWtune && !freqkeypadtune && !freqBandPicker) {                           // All pages except menu
      if (x >= 276 && x < 319 && y >= 1 && y < 30 && batterydetect && !wifi && !screenmute) {
        touchrepeat = false;
        CycleBatteryDisplay();                                            // Battery icon: cycle display mode
        return;
      }
      if (x > 30 && x < 65 && y > 0 && y < 30 && band < BAND_GAP) {       // ---------------------
        doStereoToggle();                                                 // Stereo toggle
        return;
      } else if (x > 155 && x < 250 && y > 0 && y < 30) {
        BWSelectorOpen();                                                 // Set bandwidth
        return;
      }
    }

    if (BWtune) {                                                         // BW selector, 4 x 5 buttons
      int col = -1, row = -1;
      for (byte i = 0; i < 4; i++) if (x > 7 + i * 80 && x < 77 + i * 80) col = i;
      for (byte i = 0; i < 5; i++) if (y > 35 + i * 40 && y < 65 + i * 40) row = i;
      if (col < 0 || row < 0) return;
      byte sel = row * 4 + col + 1;                                       // same numbering as the rotary cursor
      if (sel != 20 && (band < BAND_GAP ? sel > 19 : sel > 4)) return;
      BWsettemp = sel;
      if (sel == 20) {
        leave = true;
        BWSelectorClose(true);
      } else {
        if (sel == 18 || sel == 19) BWSelectorToggle(sel == 18); else BWSelectorPreview();
        showBWSelector();
      }
      return;
    }

    if (freqBandPicker) {                                                 // Band choice popup (DP-666 entry)
      int startY, pitch;
      FreqBandPickerLayout(startY, pitch);
      for (byte i = 0; i < freqPickerCount; i++) {
        int by = startY + i * pitch;
        if (y >= by && y < by + pitch && x > 10 && x < 310) {
          freqPickerSel = i;
          FreqPickerConfirm();
          return;
        }
      }
      return;
    }

    if (freqkeypadtune) {                                                 // Frequency entry screen
      touchrepeat = false;
      int focus = FreqInputHitTest(x, y);
      if (focus >= 0) {
        freqKeyFocus = focus;
        FreqInputAction(freqKeyFocus);
      }
      return;
    }

    if (!BWtune && !menu && !advancedRDS && !seek && !afscreen) {         // Normal radio mode
      if (x > 0 && x < 320 && y > 180 && y < 240 && band < BAND_GAP) {    // -----------------
        leave = true;
        BuildAdvancedRDS();                                               // Switch to Advanced RDS View
        return;
      } else if (x > 60 && x < 240 && y > 40 && y < 100) {
        touchrepeat = false;
        if (tunemode == TUNE_MEM || !freqKeypadEnabled) {
          doBandToggle();
        } else {
          OpenFreqInput(0);
        }
        return;
      } else if (x > 0 && x < 30 && y > 25 && y < 90) {
        doTuneMode();                                                     // Toggle tune mode
        return;
      } else if (x > 250 && x < 320 && y > 50 && y < 80) {
        toggleiMSEQ();                                                    // Toggle iMQ/EQ
      }
    }

    if (!BWtune && !menu && advancedRDS && !seek && !afscreen) {          // Advanced RDS mode
      if (x > 0 && x < 320 && y > 120 && y < 170) {                       // -----------------
        leave = true;
        BuildDisplay();                                                   // Switch to normal radio view
        SelectBand();
        return;
      } else if (x > 0 && x < 320 && y > 180 && y < 240) {
        BuildAFScreen();
        return;
      }
    }

    if (!BWtune && !menu && !advancedRDS && !seek && afscreen) {
      if (x > 0 && x < 320 && y > 100 && y < 170) {
        if (afpagenr == 1) afpagenr = 2; else if (afpagenr == 2 && afpage) afpagenr = 3; else afpagenr = 1;
        BuildAFScreen();
        return;
      }
      if (x > 0 && x < 320 && y > 180 && y < 240) {
        leave = true;
        BuildAdvancedRDS();
        return;
      }
    }
  }
}