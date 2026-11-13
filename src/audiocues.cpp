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
  radio.tone(ms, CUE_LEVEL, hz);
  if (radio.mute) radio.setMute();
}

static void cueTwoTones(uint16_t first, uint16_t second) {
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
  cueTone(25, 600 + 140 * digit);
}
