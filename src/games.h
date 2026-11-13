#ifndef GAMES_H
#define GAMES_H
#include <Arduino.h>

// Games on the radio, reached by holding MODE for three seconds in the menu: a menu
// to choose Snake or Tetris. The knob and the buttons are the controls, the tone
// generator of the tuner makes the sounds. Returns when the player leaves with MODE.
void GamesMenu(byte knobPin, byte modePin, byte bwPin, byte bandPin);

#endif
