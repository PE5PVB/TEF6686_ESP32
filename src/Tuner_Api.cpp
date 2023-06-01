#include "TEF6686.h"

uint16_t Radio_CurrentFreq;
uint16_t Radio_CurrentFreq_AM;

void Radio_SetFreq(uint16_t Freq, uint16_t LowEdge, uint16_t HighEdge, bool fullsearchrds)
{
  if ((Freq > HighEdge * 100) || (Freq < LowEdge * 100)) {
    Freq = LowEdge * 100;
  }
  Radio_CurrentFreq = Freq;
  devTEF_Radio_Tune_To(Freq);
  devTEF_Radio_Set_RDS(fullsearchrds);
}

void Radio_SetFreq_AM(uint16_t Freq)
{
  if (Freq > 27000) {
    Freq = 144;
  }
  if (Freq < 144) {
    Freq = 27000;
  }
  Radio_CurrentFreq_AM = Freq;
  devTEF_Radio_Tune_To_AM(Freq);
}

void Radio_ChangeFreqOneStep(uint8_t UpDown, uint8_t stepsize, uint16_t LowEdge, uint16_t HighEdge, bool fullseachrds)
{
  byte temp;
  if (stepsize == 0) {
    temp = 5;
  }
  if (stepsize == 1) {
    temp = 1;
  }
  if (stepsize == 2) {
    temp = 10;
  }
  if (stepsize == 3) {
    temp = 100;
  }
  if (UpDown == 1) {
    Radio_CurrentFreq += temp;
    if (Radio_CurrentFreq > HighEdge * 100) {
      Radio_CurrentFreq = LowEdge * 100;
    }
  } else {
    Radio_CurrentFreq -= temp;
    if (Radio_CurrentFreq < LowEdge * 100) {
      Radio_CurrentFreq = HighEdge * 100;
    }
  }
}

void Radio_ChangeFreqOneStep_AM(uint8_t UpDown, uint8_t stepsize)
{
  byte temp;
  if (stepsize == 0) {
    if (Radio_CurrentFreq_AM < 2000) {
      temp = 9;
    } else {
      temp = 5;
    }
  }
  if (stepsize == 1) {
    temp = 1;
  }
  if (stepsize == 2) {
    temp = 10;
  }
  if (stepsize == 3) {
    temp = 100;
  }
  if (UpDown == 1) {
    Radio_CurrentFreq_AM += temp;
    if (Radio_CurrentFreq_AM > 27000) {
      Radio_CurrentFreq_AM = 144;
    }
  } else {
    Radio_CurrentFreq_AM -= temp;
    if (Radio_CurrentFreq_AM < 144) {
      Radio_CurrentFreq_AM = 27000;
    }
  }
}

uint16_t Radio_GetCurrentFreq(void)
{
  return Radio_CurrentFreq;
}

uint16_t Radio_GetCurrentFreq_AM(void)
{
  return Radio_CurrentFreq_AM;
}

bool Radio_CheckStereo(void)
{
  uint16_t status;
  uint8_t stereo = 0;
  if (1 == devTEF_Radio_Get_Stereo_Status(&status)) {
    stereo = ((status >> 15) & 1) ? 1 : 0;
  }
  return stereo;
}
