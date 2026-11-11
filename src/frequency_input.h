#ifndef FREQUENCY_INPUT_H
#define FREQUENCY_INPUT_H
#include <Arduino.h>

// Direct frequency entry screen: a preview line, five band buttons and a 4 x 4 keypad.
// Works with touch, the rotary encoder (focus + button), the DP-666 keypad and MODE.
extern bool freqKeypadEnabled;          // false: digits hidden, band buttons + X + OK only
extern byte freqInputBand;              // band the entered number is interpreted in
extern byte freqKeyFocus;               // 0..4 band buttons, 5..20 keypad cells
extern const byte freqInputBands[5];
static const char* const freqInputBandNames[5] = {"FM", "OIRT", "LW", "MW", "SW"};
static const char* const freqInputKeys[16] = {"1", "2", "3", "X", "4", "5", "6", "", "7", "8", "9", "", "C", "0", "<-", "OK"};

inline bool FreqInputControlVisible(byte focus) {
  if (focus < 5) return true;
  byte key = focus - 5;
  return key < 16 && freqInputKeys[key][0] && (freqKeypadEnabled || key == 3 || key == 15);
}
struct FreqInputRect {
  int x, y, w, h;
  bool contains(uint16_t px, uint16_t py) const {
    return px >= x && px < x + w && py >= y && py < y + h;
  }
};
inline FreqInputRect FreqInputBounds(byte focus) {
  if (focus < 5) return {5 + focus * 63, 68, 58, 28};
  byte key = focus - 5;
  return {4 + (key % 4) * 80, 99 + (key / 4) * 34, 74, 34};
}
inline int FreqInputHitTest(uint16_t x, uint16_t y) {
  for (byte focus = 0; focus < 21; ++focus)
    if (FreqInputControlVisible(focus) && FreqInputBounds(focus).contains(x, y)) return focus;
  return -1;
}

byte FindBandMatches(int temp, byte* outBands, int* outFreqs);
void OpenFreqInput(int value);
void CancelFreqEntry();
void FreqKeypadConfirm();
void FreqInputAction(byte focus);
void FreqInputNumber(int num);
void FreqInputMove(bool dir);
void FreqInputCycleBand();
void FreqInputBackspace();
#endif
