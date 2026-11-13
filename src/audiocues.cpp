#include "audiocues.h"
#include "TEF668X.h"

extern TEF6686 radio;
extern bool setupmode;

static const int8_t CUE_LEVEL = -5;  // same level as the band edge beep

static bool cuesOff() {
  return audiofeedback == AUDIO_OFF || setupmode;
}

// radio.tone() unmutes the audio, so the mute is put back when it was on
static void cueTone(uint16_t ms, uint16_t hz) {
  morseStop();
  radio.tone(ms, CUE_LEVEL, hz);
  if (radio.mute) radio.setMute();
}

static void cueTwoTones(uint16_t first, uint16_t second) {
  morseStop();
  radio.tone(35, CUE_LEVEL, first);
  delay(10);
  cueTone(45, second);
}

void cuePosition(byte index, byte count) {
  if (cuesOff()) return;
  if (index >= count) index = count - 1;
  cueTone(25, count > 1 ? 600 + 1200UL * index / (count - 1) : 1200);
}

void cueValue(bool up) {
  if (cuesOff()) return;
  cueTone(25, up ? 1500 : 900);
}

void cueOpen() {
  if (cuesOff()) return;
  cueTwoTones(800, 1200);
}

void cueBack() {
  if (cuesOff()) return;
  cueTwoTones(1200, 800);
}

void cueOnOff(bool on) {
  if (cuesOff()) return;
  if (on) cueTwoTones(700, 1800); else cueTwoTones(1800, 700);
}

void cueConfirm() {
  if (cuesOff()) return;
  cueTone(80, 1500);
}

void cueError() {
  if (cuesOff()) return;
  cueTone(120, 300);
}

void cueDigit(byte digit) {
  if (cuesOff()) return;
  if (audiofeedback == AUDIO_MORSE) morseSend(String(digit));
  else cueTone(25, 600 + 140 * digit);
}

// ---------------------------------------------------------------------------
// Morse player. 20 words per minute: a dit is one unit, a dah three, the gap in a
// character one, between characters three and between words seven.
static const uint16_t MORSE_HZ = 700;
static const uint16_t MORSE_UNIT = 60;
static char morseText[24];
static byte morseIdx;        // character being sent
static byte morseElem;       // element of that character
static bool morseActive, morseKeyed;
static uint32_t morseNext;

static const char *morsePattern(char c) {
  static const char *const digits[] = {"-----", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----."};
  static const char *const letters[] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--",
                                        "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.."};
  if (c >= '0' && c <= '9') return digits[c - '0'];
  if (c >= 'A' && c <= 'Z') return letters[c - 'A'];
  if (c >= 'a' && c <= 'z') return letters[c - 'a'];
  if (c == '.') return ".-.-.-";
  return "";  // space and anything else: just a gap
}

// The tone generator plays through the audio path, so the mute goes off while a tone
// sounds and back on in the gaps when it is on at that moment (the squelch may change
// its mind while a text plays)
static void morseKey(bool on) {
  if (on) {
    radio.toneStart(CUE_LEVEL, MORSE_HZ);
  } else {
    radio.toneStop();
    if (radio.mute) radio.setMute();
  }
  morseKeyed = on;
}

void morseSend(const String &text) {
  if (audiofeedback != AUDIO_MORSE || setupmode) return;
  morseStop();
  text.toCharArray(morseText, sizeof(morseText));
  morseIdx = morseElem = 0;
  morseActive = true;
  morseNext = millis() + 3 * MORSE_UNIT;  // a little silence first, a cue may just have ended
}

void morseStop() {
  if (!morseActive) return;
  if (morseKeyed) morseKey(false);
  morseActive = false;
}

void morseStep() {
  if (!morseActive || millis() < morseNext) return;
  if (morseKeyed) {  // element done: the gap inside the character
    morseKey(false);
    morseElem++;
    morseNext = millis() + MORSE_UNIT;
    return;
  }
  if (morseText[morseIdx] == 0) {
    morseActive = false;
    return;
  }
  const char *code = morsePattern(morseText[morseIdx]);
  if (code[morseElem] == 0) {  // character done
    morseIdx++;
    morseElem = 0;
    byte gap = 2;  // one unit has passed already
    if (morseText[morseIdx] == ' ') {
      morseIdx++;
      gap = 6;
    }
    if (morseText[morseIdx] == 0) {
      morseActive = false;
      return;
    }
    morseNext = millis() + gap * MORSE_UNIT;
    return;
  }
  morseKey(true);
  morseNext = millis() + (code[morseElem] == '-' ? 3 : 1) * MORSE_UNIT;
}
