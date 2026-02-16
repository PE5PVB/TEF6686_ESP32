#ifndef RTC_RX8010_H
#define RTC_RX8010_H

#include <Arduino.h>
#include <time.h>

extern bool hasRX8010;

bool rx8010_init();
bool rx8010_getTime(struct tm *t);
void rx8010_setTime(struct tm *t);

#endif
