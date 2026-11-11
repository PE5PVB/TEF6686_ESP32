#ifndef SETUP_MENU_H
#define SETUP_MENU_H
#include <Arduino.h>
extern byte displayflip, rotarymode;
extern bool invertdisplay, optenc;
bool IsSetupPage(byte page);
int SetupMenuLabel(byte page, byte item);
int SetupMenuTitle(byte page);
String SetupMenuValue(byte page, byte item);
String FitSetupText(String text, int width);
void SetupPrompt(int label);
void DrawTouchCalibrationScreen();
void OpenSetupMenu();
void AdjustSetupMenu(bool dir);
void AcceptSetupMenu();
void CancelSetupMenu();
void BackSetupMenu();
void ApplyScreenFlip(byte flipped);
void RunTouchCalibration();
void WaitSetupControlsReleased();
void DefaultSettings();
void showMenuOpenTouchButtons();
#endif
