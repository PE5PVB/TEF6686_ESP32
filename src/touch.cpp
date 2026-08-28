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

    if (!menu && !BWtune && !freqkeypadtune && !freqBandPicker) {         // All pages except menu
      if (x > 30 && x < 65 && y > 0 && y < 30 && band < BAND_GAP) {       // ---------------------
        doStereoToggle();                                                 // Stereo toggle
        return;
      } else if (x > 155 && x < 250 && y > 0 && y < 30) {
        BuildBWSelector();                                                // Set bandwidth
        BWtune = true;
        return;
      }
    }

    if (BWtune) {                                                         // BW menu
      if (y > 35 && y < 65) {
        if (x > 7 && x < 77) BWtemp = 1;
        if (x > 87 && x < 157) BWtemp = 2;
        if (x > 167 && x < 237) BWtemp = 3;
        if (x > 247 && x < 317) BWtemp = 4;
      }
      if (band < BAND_GAP) {
        if (y > 75 && y < 105) {
          if (x > 7 && x < 77) BWtemp = 5;
          if (x > 87 && x < 157) BWtemp = 6;
          if (x > 167 && x < 237) BWtemp = 7;
          if (x > 247 && x < 317) BWtemp = 8;
        }

        if (y > 115 && y < 145) {
          if (x > 7 && x < 77) BWtemp = 9;
          if (x > 87 && x < 157) BWtemp = 10;
          if (x > 167 && x < 237) BWtemp = 11;
          if (x > 247 && x < 317) BWtemp = 12;
        }

        if (y > 155 && y < 185) {
          if (x > 7 && x < 77) BWtemp = 13;
          if (x > 87 && x < 157) BWtemp = 14;
          if (x > 167 && x < 237) BWtemp = 15;
          if (x > 247 && x < 317) BWtemp = 16;
        }

        if (y > 195 && y < 225) {
          if (x > 7 && x < 77) BWtemp = 0;
          if (x > 87 && x < 157) iMSset = !iMSset;
          if (x > 167 && x < 237) EQset = !EQset;
          if ((x > 87 && x < 157) || (x > 167 && x < 237)) {
            if (!iMSset && !EQset) iMSEQ = 0;
            else if (iMSset && EQset) iMSEQ = 2;
            else if (!iMSset && EQset) iMSEQ = 3;
            else iMSEQ = 4;
            EEPROM.writeByte(EE_BYTE_IMSSET, iMSset);
            EEPROM.writeByte(EE_BYTE_EQSET, EQset);
            EEPROM.commit();
            updateiMS();
            updateEQ();
            if (XDRGTKUSB || XDRGTKTCP) DataPrint("G" + String(!EQset) + String(!iMSset) + "\n");
          }
        }
      }

      if (y > 195 && y < 225 && x > 247 && x < 317) {
        leave = true;
        bwtouchtune = true;
        BWset = BWtemp;
        doBW();
        BWtune = false;
        bwtouchtune = false;
        if (advancedRDS) {
          BuildAdvancedRDS();
        } else if (afscreen) {
          BuildAFScreen();
        } else {
          BuildDisplay();
          SelectBand();
        }
      } else {
        bwtouchtune = true;
        BWset = BWtemp;
        showBWSelector();
        doBW();
        bwtouchtune = false;
      }
      return;
    }

    if (freqBandPicker) {                                                 // Frequency band choice popup
      int totalHeight = freqPickerCount * 40 - 8;
      int startY = 30 + (210 - totalHeight) / 2;
      if (startY < 35) startY = 35;

      for (byte i = 0; i < freqPickerCount; i++) {
        int by = startY + i * 40;
        if (y > by && y < by + 32 && x > 10 && x < 310) {
          ApplyBandMatch(freqPickerBands[i], freqPickerFreqs[i]);
          freqBandPicker = false;
          freqkeypadtune = false;
          BuildDisplay();
          SelectBand();
          break;
        }
      }
      return;
    }

    if (freqkeypadtune) {                                                 // Frequency entry keypad
      int digit = -1;
      bool doCancel = false;
      bool doClear = false;
      bool doBackspace = false;
      bool doOK = false;

      if (y > 101 && y < 131) {
        if (x > 7 && x < 77) digit = 1;
        else if (x > 87 && x < 157) digit = 2;
        else if (x > 167 && x < 237) digit = 3;
        else if (x > 247 && x < 317) doCancel = true;
      } else if (y > 135 && y < 165) {
        if (x > 7 && x < 77) digit = 4;
        else if (x > 87 && x < 157) digit = 5;
        else if (x > 167 && x < 237) digit = 6;
      } else if (y > 169 && y < 199) {
        if (x > 7 && x < 77) digit = 7;
        else if (x > 87 && x < 157) digit = 8;
        else if (x > 167 && x < 237) digit = 9;
      } else if (y > 203 && y < 233) {
        if (x > 7 && x < 77) doClear = true;
        else if (x > 87 && x < 157) digit = 0;
        else if (x > 167 && x < 237) doBackspace = true;
        else if (x > 247 && x < 317) doOK = true;
      }

      if (digit != -1) {
        if (freq_in / 10000 == 0) freq_in = freq_in * 10 + digit;
        ShowNum(freq_in);
      } else if (doClear) {
        freq_in = 0;
        ShowNum(freq_in);
      } else if (doBackspace) {
        freq_in = freq_in / 10;
        ShowNum(freq_in);
      } else if (doOK) {
        FreqKeypadConfirm();
      } else if (doCancel) {
        freqkeypadtune = false;
        freq_in = 0;
        BuildDisplay();
        SelectBand();
      }
      return;
    }

    if (!BWtune && !menu && !advancedRDS && !seek && !afscreen) {         // Normal radio mode
      if (x > 0 && x < 320 && y > 180 && y < 240 && band < BAND_GAP) {    // -----------------
        leave = true;
        BuildAdvancedRDS();                                               // Switch to Advanced RDS View
        return;
      } else if (x > 60 && x < 240 && y > 40 && y < 100) {
        if (tunemode == TUNE_MEM) {
          doBandToggle();
        } else {
          freqkeypadtune = true;
          BuildFreqKeypad();
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