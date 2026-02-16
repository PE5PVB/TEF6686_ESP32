#include "rtc_rx8010.h"
#include <RX8010SJ.h>
#include <Wire.h>

bool hasRX8010 = false;
static RX8010SJ::Adapter rtcChip(0x32);

bool rx8010_init() {
  // Probe I2C address 0x32 to check if chip is present
  Wire.beginTransmission(0x32);
  if (Wire.endTransmission() != 0) return false;

  // Chip responded; don't call initAdapter() as it overrides Wire.begin() pins
  hasRX8010 = true;
  rtcChip.initModule();
  return true;
}

bool rx8010_getTime(struct tm *t) {
  if (!hasRX8010) return false;

  RX8010SJ::DateTime dt = rtcChip.readDateTime();

  if (dt.year == 0 && dt.month == 0 && dt.dayOfMonth == 0) return false;

  t->tm_sec  = dt.second;
  t->tm_min  = dt.minute;
  t->tm_hour = dt.hour;
  t->tm_wday = dt.dayOfWeek;
  t->tm_mday = dt.dayOfMonth;
  t->tm_mon  = dt.month - 1;        // struct tm: 0-11
  t->tm_year = dt.year + 100;        // struct tm: years since 1900

  return true;
}

void rx8010_setTime(struct tm *t) {
  if (!hasRX8010) return;

  RX8010SJ::DateTime dt;
  dt.second     = t->tm_sec;
  dt.minute     = t->tm_min;
  dt.hour       = t->tm_hour;
  dt.dayOfWeek  = t->tm_wday;
  dt.dayOfMonth = t->tm_mday;
  dt.month      = t->tm_mon + 1;    // RTC: 1-12
  dt.year       = t->tm_year - 100;  // RTC: 0-99

  rtcChip.writeDateTime(dt);
}
