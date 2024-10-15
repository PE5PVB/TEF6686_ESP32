#ifndef TOUCH_H
#define TOUCH_H

#include <Arduino.h>
#include <TFT_eSPI.h>

extern TFT_eSPI tft;

extern bool advancedRDS;
extern bool afscreen;
extern bool leave;
extern bool menu;
extern bool seek;
extern byte band;

void doTouchEvent(uint16_t x, uint16_t y);

extern void ScreensaverTimerReopen();
extern void BuildDisplay();
extern void SelectBand();
extern void BuildAdvancedRDS();
extern void doBandToggle();
extern void doTuneMode();
#endif