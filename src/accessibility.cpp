#include "accessibility.h"

#include <EEPROM.h>

#include "TEF6686.h"
#include "constants.h"

extern bool accessibilityMenuBeep;
extern bool accessibilityConfirmBeep;
extern bool accessibilityBackBeep;
extern bool accessibilityVoiceLite;
extern bool accessibilityVoiceLiteActions;
extern bool accessibilityPanCues;

extern byte accessibilityOnOffCueLength;
extern byte accessibilityMenuCueLength;
extern byte accessibilityConfirmCueLength;
extern byte accessibilityBackCueLength;
extern byte accessibilityCueVolume;
extern byte startupJingleVariant;
extern byte accessibilityTestMode;

extern byte memorypos;
extern byte band;
extern byte BWset;
extern byte BWsettemp;
extern byte showSWMIBand;
extern byte nowToggleSWMIBand;
extern byte stepsize;
extern byte tunemode;
extern bool BWtune;
extern bool StereoToggle;
extern bool edgebeep;

extern TEF6686 radio;
extern unsigned long accessibilityLastCueMs;

namespace {

uint8_t accessibilityCueDurationMs(byte cueLength, uint8_t shortMs, uint8_t mediumMs, uint8_t longMs) {
  switch (cueLength) {
    case ACCESS_CUE_LEN_SHORT: return shortMs;
    case ACCESS_CUE_LEN_LONG: return longMs;
    default: return mediumMs;
  }
}

int8_t accessibilityCueVolumeLevel(int8_t baseLevel) {
  int8_t level = baseLevel;
  switch (accessibilityCueVolume) {
    case ACCESS_CUE_VOL_LOW: level -= 4; break;
    case ACCESS_CUE_VOL_HIGH: level += 4; break;
    default: break;
  }
  if (level < -20) level = -20;
  if (level > -2) level = -2;
  return level;
}

bool accessibilityCueGuard(uint16_t minGapMs = 18) {
  const unsigned long nowMs = millis();
  if (nowMs - accessibilityLastCueMs < minGapMs) return false;
  accessibilityLastCueMs = nowMs;
  return true;
}

uint8_t accessibilityBackCueDurationMs(bool secondTone) {
  return secondTone ? accessibilityCueDurationMs(accessibilityBackCueLength, 62, 95, 145) : accessibilityCueDurationMs(accessibilityBackCueLength, 36, 55, 84);
}

uint8_t accessibilityBackSingleCueDurationMs() {
  return accessibilityCueDurationMs(accessibilityBackCueLength, 30, 45, 70);
}

uint8_t accessibilityBackCueGapMs() {
  return accessibilityCueDurationMs(accessibilityBackCueLength, 6, 10, 14);
}

uint8_t accessibilityOnOffCueDurationMs(bool secondTone) {
  return secondTone ? accessibilityCueDurationMs(accessibilityOnOffCueLength, 44, 72, 108) : accessibilityCueDurationMs(accessibilityOnOffCueLength, 36, 60, 90);
}

bool accessibilityVoiceLiteActionsEnabled() {
  return accessibilityVoiceLite && accessibilityVoiceLiteActions;
}

int16_t clampCueLevel(int16_t level) {
  if (level < -20) return -20;
  if (level > -2) return -2;
  return level;
}

void playCueWithOptionalPan(uint16_t durationMs, int16_t baseLevel, uint16_t frequency, uint8_t pos, uint8_t count) {
  if (!accessibilityPanCues || count < 2) {
    radio.tone(durationMs, baseLevel, frequency);
    return;
  }

  const int16_t kMaxPanAttenuationDb = 12;
  const int16_t balance = static_cast<int16_t>((static_cast<uint32_t>(pos) * 200) / (count - 1)) - 100;

  int16_t leftLevel = baseLevel;
  int16_t rightLevel = baseLevel;

  if (balance < 0) {
    rightLevel = baseLevel - static_cast<int16_t>(((-balance) * kMaxPanAttenuationDb) / 100);
  } else if (balance > 0) {
    leftLevel = baseLevel - static_cast<int16_t>((balance * kMaxPanAttenuationDb) / 100);
  }

  radio.toneStereo(durationMs, clampCueLevel(leftLevel), frequency, clampCueLevel(rightLevel), frequency);
}

}  // namespace

void sanitizeAccessibilitySettings() {
  if (accessibilityMenuBeep > 1) accessibilityMenuBeep = 0;
  if (accessibilityConfirmBeep > 1) accessibilityConfirmBeep = 1;
  if (accessibilityBackBeep > 1) accessibilityBackBeep = 1;
  if (accessibilityVoiceLite > 1) accessibilityVoiceLite = 0;
  if (accessibilityVoiceLiteActions > 1) accessibilityVoiceLiteActions = 0;
  if (accessibilityOnOffCueLength > ACCESS_CUE_LEN_LONG) accessibilityOnOffCueLength = ACCESS_CUE_LEN_MEDIUM;
  if (accessibilityMenuCueLength > ACCESS_CUE_LEN_LONG) accessibilityMenuCueLength = ACCESS_CUE_LEN_MEDIUM;
  if (accessibilityConfirmCueLength > ACCESS_CUE_LEN_LONG) accessibilityConfirmCueLength = ACCESS_CUE_LEN_MEDIUM;
  if (accessibilityBackCueLength > ACCESS_CUE_LEN_LONG) accessibilityBackCueLength = ACCESS_CUE_LEN_MEDIUM;
  if (accessibilityCueVolume > ACCESS_CUE_VOL_HIGH) accessibilityCueVolume = ACCESS_CUE_VOL_MEDIUM;
  if (startupJingleVariant > ACCESS_STARTUP_JINGLE_EXTENDED) startupJingleVariant = ACCESS_STARTUP_JINGLE_CLASSIC;
  if (accessibilityTestMode > ACCESS_TEST_MODE_ON) accessibilityTestMode = ACCESS_TEST_MODE_OFF;
}

void writeAccessibilitySettingsToEEPROM() {
  EEPROM.writeByte(EE_BYTE_ACCESS_MENU_BEEP, accessibilityMenuBeep);
  EEPROM.writeByte(EE_BYTE_ACCESS_CONFIRM_BEEP, accessibilityConfirmBeep);
  EEPROM.writeByte(EE_BYTE_ACCESS_BACK_BEEP, accessibilityBackBeep);
  EEPROM.writeByte(EE_BYTE_ACCESS_VOICE_LITE, accessibilityVoiceLite);
  EEPROM.writeByte(EE_BYTE_ACCESS_VOICE_ACTIONS, accessibilityVoiceLiteActions);
  EEPROM.writeByte(EE_BYTE_ACCESS_ONOFF_CUE_LEN, accessibilityOnOffCueLength);
  EEPROM.writeByte(EE_BYTE_ACCESS_MENU_CUE_LEN, accessibilityMenuCueLength);
  EEPROM.writeByte(EE_BYTE_ACCESS_CONFIRM_CUE_LEN, accessibilityConfirmCueLength);
  EEPROM.writeByte(EE_BYTE_ACCESS_BACK_CUE_LEN, accessibilityBackCueLength);
  EEPROM.writeByte(EE_BYTE_ACCESS_CUE_VOLUME, accessibilityCueVolume);
  EEPROM.writeByte(EE_BYTE_STARTUP_JINGLE_VARIANT, startupJingleVariant);
  EEPROM.writeByte(EE_BYTE_ACCESS_TEST_MODE, accessibilityTestMode);
  EEPROM.writeByte(EE_BYTE_ACCESS_PAN_CUES, accessibilityPanCues ? 1 : 0);
}

void applyFullAccessibilityTestBootProfile() {
  accessibilityMenuBeep = 1;
  accessibilityConfirmBeep = 1;
  accessibilityBackBeep = 1;
  accessibilityVoiceLite = 1;
  accessibilityVoiceLiteActions = 1;
  accessibilityOnOffCueLength = ACCESS_CUE_LEN_LONG;
  accessibilityMenuCueLength = ACCESS_CUE_LEN_MEDIUM;
  accessibilityConfirmCueLength = ACCESS_CUE_LEN_LONG;
  accessibilityBackCueLength = ACCESS_CUE_LEN_LONG;
  accessibilityCueVolume = ACCESS_CUE_VOL_HIGH;
  startupJingleVariant = ACCESS_STARTUP_JINGLE_EXTENDED;
}

void playAccessibilityBackBeep() {
  if (!accessibilityBackBeep || !accessibilityCueGuard()) return;
  radio.tone(accessibilityBackSingleCueDurationMs(), accessibilityCueVolumeLevel(-8), 980);
}

void playAccessibilityEnterMenuBeep() {
  if (!accessibilityBackBeep || !accessibilityCueGuard()) return;
  radio.tone(accessibilityBackCueDurationMs(false), accessibilityCueVolumeLevel(-9), 780);
  delay(accessibilityBackCueGapMs());
  radio.tone(accessibilityBackCueDurationMs(true), accessibilityCueVolumeLevel(-9), 1260);
}

void playAccessibilityExitMenuBeep() {
  if (!accessibilityBackBeep || !accessibilityCueGuard()) return;
  radio.tone(accessibilityBackCueDurationMs(true), accessibilityCueVolumeLevel(-9), 1260);
  delay(accessibilityBackCueGapMs());
  radio.tone(accessibilityBackCueDurationMs(false), accessibilityCueVolumeLevel(-9), 760);
}

void playAccessibilityDigitVoiceLite(uint8_t digit) {
  if (!accessibilityVoiceLite || digit > 9 || !accessibilityCueGuard()) return;

  const uint16_t minFreq = 620;
  const uint16_t maxFreq = 2060;
  const uint16_t frequency = minFreq + static_cast<uint16_t>(((uint32_t)(maxFreq - minFreq) * digit) / 9);
  radio.tone(22, accessibilityCueVolumeLevel(-10), frequency);
}

void playAccessibilityVoiceLitePosition(uint8_t pos, uint8_t count, uint16_t minFreq, uint16_t maxFreq, uint8_t durationMs) {
  if (!accessibilityVoiceLite || count == 0 || !accessibilityCueGuard()) return;
  if (pos >= count) pos = count - 1;
  uint16_t frequency = minFreq;
  if (count > 1) {
    frequency = minFreq + static_cast<uint16_t>(((uint32_t)(maxFreq - minFreq) * pos) / (count - 1));
  }
  playCueWithOptionalPan(durationMs, accessibilityCueVolumeLevel(-10), frequency, pos, count);
}

void playAccessibilityMemoryPosVoiceLite() {
  playAccessibilityVoiceLitePosition(memorypos, EE_PRESETS_CNT, 640, 2080, 22);
}

void playAccessibilityBandVoiceLiteForBand(uint8_t targetBand) {
  uint8_t slot = (targetBand < BAND_GAP) ? targetBand : (targetBand - 1);
#ifdef HAS_AIR_BAND
  const uint8_t count = 6;
#else
  const uint8_t count = 5;
#endif
  playAccessibilityVoiceLitePosition(slot, count, 700, 2200, 14);
}

void playAccessibilityBandVoiceLite() {
  playAccessibilityBandVoiceLiteForBand(band);
}

void playAccessibilityOnOffVoiceLite(bool enabled) {
  if (!accessibilityVoiceLite || !accessibilityCueGuard()) return;
  const uint16_t lowFreq = 860;
  const uint16_t highFreq = 1560;
  radio.tone(accessibilityOnOffCueDurationMs(false), accessibilityCueVolumeLevel(-10), (enabled ? lowFreq : highFreq));
  delay(8);
  radio.tone(accessibilityOnOffCueDurationMs(true), accessibilityCueVolumeLevel(-10), (enabled ? highFreq : lowFreq));
}

void playAccessibilityBWVoiceLite() {
  if (!accessibilityVoiceLite || !BWtune) return;

  if (band < BAND_GAP) {
    uint8_t slot = (BWset > 16) ? 16 : BWset;  // 0..16 (Auto..311 kHz)
    playAccessibilityVoiceLitePosition(slot, 17, 740, 2300, 18);
  } else {
    uint8_t slot = (BWset < 1) ? 0 : ((BWset > 4) ? 3 : (BWset - 1));  // 1..4
    playAccessibilityVoiceLitePosition(slot, 4, 740, 2300, 18);
  }
}

void playAccessibilityBWSelectorCursorVoiceLite() {
  if (!accessibilityVoiceLite) return;

  if (band < BAND_GAP) {
    // FM/OIRT selector slots: 1..16 BW, 17 Auto, 18 iMS, 19 EQ, 20 OK
    uint8_t slot = 0;
    if (BWsettemp == 20) slot = 19;
    else if (BWsettemp >= 1 && BWsettemp <= 19) slot = BWsettemp - 1;
    playAccessibilityVoiceLitePosition(slot, 20, 740, 2300, 18);
  } else {
    // AM selector slots: 1..4 BW, 20 OK
    uint8_t slot = (BWsettemp == 20) ? 4 : ((BWsettemp >= 1 && BWsettemp <= 4) ? (BWsettemp - 1) : 0);
    playAccessibilityVoiceLitePosition(slot, 5, 740, 2300, 18);
  }
}

void playAccessibilityStereoModeVoiceLite() {
  // Stereo ON = low->high, Mono OFF = high->low.
  playAccessibilityOnOffVoiceLite(StereoToggle);
}

void playAccessibilityFreqEnterVoiceLite(bool manualEnter) {
  if (!accessibilityVoiceLite || !manualEnter || !accessibilityCueGuard()) return;
  radio.tone(120, accessibilityCueVolumeLevel(-8), 1420);
}

void playAccessibilityTuneModeVoiceLite() {
  if (!accessibilityVoiceLite) return;

  const bool swBandMode = (band == BAND_SW && showSWMIBand && nowToggleSWMIBand);
  uint8_t slot = 0;
  const uint8_t count = 3;

  if (swBandMode) {
    switch (tunemode) {
      case TUNE_MAN: slot = 0; break;
      case TUNE_MI_BAND: slot = 1; break;
      case TUNE_MEM: slot = 2; break;
      default: return;
    }
  } else {
    switch (tunemode) {
      case TUNE_MAN: slot = 0; break;
      case TUNE_AUTO: slot = 1; break;
      case TUNE_MEM: slot = 2; break;
      default: return;
    }
  }

  playAccessibilityVoiceLitePosition(slot, count, 760, 2200, 18);
}

void playAccessibilityStepSizeVoiceLite() {
  if (!accessibilityVoiceLite) return;
  const uint8_t count = (band == BAND_SW || band < BAND_GAP) ? 5 : 4;
  playAccessibilityVoiceLitePosition(stepsize, count, 760, 2200, 18);
}

void playAccessibilityScanStateVoiceLite(bool start) {
  if (!accessibilityVoiceLiteActionsEnabled() || !accessibilityCueGuard()) return;
  radio.tone(30, accessibilityCueVolumeLevel(-9), (start ? 940 : 1520));
  delay(8);
  radio.tone(36, accessibilityCueVolumeLevel(-9), (start ? 1520 : 940));
}

void playAccessibilityMemoryStoreVoiceLite() {
  if (!accessibilityVoiceLiteActionsEnabled() || !accessibilityCueGuard()) return;
  radio.tone(22, accessibilityCueVolumeLevel(-9), 1120);
  delay(6);
  radio.tone(30, accessibilityCueVolumeLevel(-9), 1760);
}

void playAccessibilityMemoryClearVoiceLite() {
  if (!accessibilityVoiceLiteActionsEnabled() || !accessibilityCueGuard()) return;
  radio.tone(30, accessibilityCueVolumeLevel(-9), 1760);
  delay(8);
  radio.tone(42, accessibilityCueVolumeLevel(-9), 920);
}

void playStartupTriadBeep() {
  if (!edgebeep) return;
  // C major triad for a softer startup cue.
  radio.tone(72, -8, 1047);
  delay(20);
  radio.tone(72, -8, 1319);
  delay(20);
  radio.tone(104, -8, 1568);
  if (startupJingleVariant == ACCESS_STARTUP_JINGLE_EXTENDED) {
    delay(20);
    radio.tone(72, -8, 1319);
    delay(20);
    radio.tone(104, -8, 1568);
  }
}
