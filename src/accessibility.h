#pragma once

#include <Arduino.h>

void sanitizeAccessibilitySettings();
void writeAccessibilitySettingsToEEPROM();
void applyFullAccessibilityTestBootProfile();

void playAccessibilityBackBeep();
void playAccessibilityEnterMenuBeep();
void playAccessibilityExitMenuBeep();
void playAccessibilityDigitVoiceLite(uint8_t digit);
void playAccessibilityVoiceLitePosition(uint8_t pos, uint8_t count, uint16_t minFreq, uint16_t maxFreq, uint8_t durationMs);
void playAccessibilityMemoryPosVoiceLite();
void playAccessibilityBandVoiceLiteForBand(uint8_t targetBand);
void playAccessibilityBandVoiceLite();
void playAccessibilityOnOffVoiceLite(bool enabled);
void playAccessibilityBWVoiceLite();
void playAccessibilityBWSelectorCursorVoiceLite();
void playAccessibilityStereoModeVoiceLite();
void playAccessibilityFreqEnterVoiceLite(bool manualEnter);
void playAccessibilityTuneModeVoiceLite();
void playAccessibilityStepSizeVoiceLite();
void playAccessibilityScanStateVoiceLite(bool start);
void playAccessibilityMemoryStoreVoiceLite();
void playAccessibilityMemoryClearVoiceLite();
void playStartupTriadBeep();
