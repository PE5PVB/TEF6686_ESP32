#include "touch.h"
#include "language.h"
#include "constants.h"
#include "config.h"

void doTouchEvent(uint16_t x, uint16_t y) {
  if (seek) radio.setUnMute();
  seek = false;
  if (scandxmode) {
    cancelDXScan();
  } else {
    if (!menu) {                                                          // All pages except menu
      if (x > 40 && x < 80 && y > 0 && y < 25 && band < BAND_GAP) {      // ---------------------
        doStereoToggle();
      }                                                                   // Stereo toggle
    }

    if (!menu && !advancedRDS && !seek && !afscreen) {                    // Normal radio mode
      if (x > 0 && x < 320 && y > 180 && y < 240 && band < BAND_GAP) {    // -----------------
        leave = true;
        BuildAdvancedRDS();                                               // Switch to Advanced RDS View
        return;
      } else if (x > 60 && x < 240 && y > 40 && y < 100) {
        doBandToggle();                                                   // Toggle bands
        return;
      } else if (x > 0 && x < 30 && y > 25 && y < 90) {
        doTuneMode();                                                     // Toggle tune mode
        return;
      }
    }

    if (!menu && advancedRDS && !seek && !afscreen) {                     // Advanced RDS mode
      if (x > 0 && x < 320 && y > 180 && y < 240) {                       // -----------------
        leave = true;
        BuildDisplay();
        SelectBand();
        ScreensaverTimerReopen();                                         // Switch to normal radio view
        return;
      }
    }
  }
}