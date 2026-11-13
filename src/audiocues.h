#ifndef AUDIOCUES_H
#define AUDIOCUES_H
#include <Arduino.h>

// Audio feedback for use without looking at the screen (Audio settings). The setting
// is kept in EE_BYTE_EDGEBEEP: off, cues, cues with morse. The band edge beep and the
// scan beeps are part of it as before.
#define AUDIO_OFF   0
#define AUDIO_ON    1
#define AUDIO_MORSE 2
extern byte audiofeedback;

// A fixed vocabulary of short tones, played through the tone generator of the tuner:
//   cuePosition  tick, pitch rises with the position in a list (menu item, band, step size)
//   cueValue     tick, higher for up and lower for down (value in a popup)
//   cueOpen      two tones low to high: a menu, popup or selector opens
//   cueBack      two tones high to low: back, cancel or close without saving
//   cueOnOff     the same two tones for a setting that goes on or off
//   cueConfirm   one long tone: saved or applied
//   cueError     low buzz: refused
//   cueDigit     tick, pitch per digit 0 - 9 (keypad entry)
void cuePosition(byte index, byte count);
void cueValue(bool up);
void cueOpen();
void cueBack();
void cueOnOff(bool on);
void cueConfirm();
void cueError();
void cueDigit(byte digit);

#endif
