#ifndef USA_STATIONS_H
#define USA_STATIONS_H

#include <Arduino.h>

typedef struct {
    uint16_t pi;
    char call[7];
    char state[3];
} __attribute__((packed)) USAStation;

bool findUSAStation(uint16_t freq, uint16_t pi, char* callOut, char* stateOut);

#endif
