#ifndef TOUCH_H
#define TOUCH_H

#include <Arduino.h>
#include <TFT_eSPI.h>
#include "TEF6686.h"

extern TFT_eSPI tft;
extern TEF6686 radio;

extern bool advancedRDS;
extern bool afpage;
extern bool afscreen;
extern bool bwtouchtune;
extern bool BWtune;
extern bool leave;
extern bool menu;
extern bool menuopen;
extern bool scandxmode;
extern bool seek;
extern bool touchrepeat;
extern bool XDRGTKTCP;
extern bool XDRGTKUSB;
extern byte afpagenr;
extern byte band;
extern byte BWset;
extern byte BWtemp;
extern byte EQset;
extern byte iMSEQ;
extern byte iMSset;
extern byte menuitem;
extern byte items[10];
extern byte menupage;
extern int menuoption;

void doTouchEvent(uint16_t x, uint16_t y);

extern void ScreensaverTimerReopen();
extern void BuildDisplay();
extern void BuildBWSelector();
extern void SelectBand();
extern void BuildAdvancedRDS();
extern void doBandToggle();
extern void doTuneMode();
extern void doStereoToggle();
extern void cancelDXScan();
extern void doBW();
extern void drawButton(const char* text, byte button_number, bool active, bool selected);
extern void KeyDown();
extern void KeyUp();
extern void ButtonPress();
extern void DoMenu();
extern void ModeButtonPress();
extern void toggleiMSEQ();
extern void showBWSelector();
extern void updateiMS();
extern void updateEQ();
extern void DataPrint(String string);
extern void BuildAFScreen();

#endif