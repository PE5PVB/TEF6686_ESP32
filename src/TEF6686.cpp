#include "TEF6686.h"
#include <map>
#include <Arduino.h>
#include <TimeLib.h>                // https://github.com/PaulStoffregen/Time
#include "SPIFFS.h"
#include "constants.h"

unsigned long rdstimer = 0;
unsigned long bitStartTime = 0;
bool lastBitState = false;

uint16_t TEF6686::getBlockA(void) {
  uint16_t blockA, dummy;
  devTEF_Radio_Get_RDS_Status(&dummy, &blockA, &dummy, &dummy, &dummy, &dummy);
  return blockA;
}


void TEF6686::TestAFEON() {
  uint16_t status;
  uint16_t dummy1;
  uint16_t dummy2;
  int8_t dummy3;
  int16_t aflevel;
  uint16_t afusn;
  uint16_t afwam;
  int16_t afoffset;
  byte timing;

  if (af_counter != 0) {
    setMute();
    for (int x = 0; x < af_counter; x++) {
      timing = 0;
      devTEF_Set_Cmd(TEF_FM, Cmd_Tune_To, 7, 3, af[x].frequency);
      while (timing == 0 && !bitRead(timing, 15)) {
        devTEF_Radio_Get_Quality_Status(&status, &aflevel, &afusn, &afwam, &afoffset, &dummy1, &dummy2, &dummy3);
        timing = lowByte(status);
      }
      if (afoffset > -125 || afoffset < 125) {
        devTEF_Set_Cmd(TEF_FM, Cmd_Tune_To, 7, 4, af[x].frequency);
        delay(187);
        devTEF_Radio_Get_RDS_Status(&rds.rdsStat, &rds.rdsA, &rds.rdsB, &rds.rdsC, &rds.rdsD, &rds.rdsErr);

        if (rds.rdsStat & (1 << 9)) {
          if ((afmethodB && rds.afreg ? (((rds.rdsA >> 8) & 0xF) > 2 && ((rds.correctPI >> 8) & 0xF) > 2 && ((rds.rdsA >> 12) & 0xF) == ((rds.correctPI >> 12) & 0xF) && (rds.rdsA & 0xFF) == (rds.correctPI & 0xFF)) || rds.rdsA == rds.correctPI : rds.rdsA == rds.correctPI)) {
            af[x].checked = true;
            af[x].afvalid = true;
          } else {
            af[x].checked = false;
            af[x].afvalid = false;
          }
        } else {
          af[x].checked = false;
        }
      }
    }
  }
  devTEF_Set_Cmd(TEF_FM, Cmd_Tune_To, 7, 4, currentfreq);
  setUnMute();
}

uint16_t TEF6686::TestAF() {
  if (af_counter != 0) {
    uint16_t status;
    uint16_t dummy1;
    uint16_t dummy2;
    int8_t dummy3;

    int16_t aflevel;
    uint16_t afusn;
    uint16_t afwam;
    int16_t afoffset;

    int16_t currentlevel;
    uint16_t currentusn;
    uint16_t currentwam;
    int16_t currentoffset;

    byte timing;

    devTEF_Radio_Get_Quality_Status(&status, &currentlevel, &currentusn, &currentwam, &currentoffset, &dummy1, &dummy2, &dummy3);
    devTEF_Radio_Get_RDS_Status(&rds.rdsStat, &rds.rdsA, &rds.rdsB, &rds.rdsC, &rds.rdsD, &rds.rdsErr);

    for (int x = 0; x < af_counter; x++) {
      timing = 0;
      devTEF_Set_Cmd(TEF_FM, Cmd_Tune_To, 7, 3, af[x].frequency);
      while (timing == 0 && !bitRead(timing, 15)) {
        devTEF_Radio_Get_Quality_Status(&status, &aflevel, &afusn, &afwam, &afoffset, &dummy1, &dummy2, &dummy3);
        timing = lowByte(status);
      }
      af[x].score = aflevel - afusn - afwam;
      if (afoffset < -125 || afoffset > 125) af[x].score = -32767;
    }

    int16_t highestValue = af[0].score;
    int highestIndex = 0;

    for (int i = 1; i < af_counter; i++) {
      if (af[i].score > highestValue) {
        highestValue = af[i].score;
        highestIndex = i;
      }
    }

    if (af_counter != 0 && af[highestIndex].afvalid && af[highestIndex].score > (currentlevel - currentusn - currentwam) && (af[highestIndex].score - (currentlevel - currentusn - currentwam)) >= 70) {
      devTEF_Set_Cmd(TEF_FM, Cmd_Tune_To, 7, 4, af[highestIndex].frequency);
      delay(187);
      devTEF_Radio_Get_RDS_Status(&rds.rdsStat, &rds.rdsA, &rds.rdsB, &rds.rdsC, &rds.rdsD, &rds.rdsErr);
      if (rds.rdsStat & (1 << 9)) {
        if ((afmethodB && rds.afreg ? (((rds.rdsA >> 8) & 0xF) > 2 && ((rds.correctPI >> 8) & 0xF) > 2 && ((rds.rdsA >> 12) & 0xF) == ((rds.correctPI >> 12) & 0xF) && (rds.rdsA & 0xFF) == (rds.correctPI & 0xFF)) || rds.rdsA == rds.correctPI : rds.rdsA == rds.correctPI)) {
          currentfreq = af[highestIndex].frequency;
          for (byte y = 0; y < 50; y++) {
            af[y].frequency = 0;
            af[y].score = -32767;
            af[y].afvalid = true;
            af[y].checked = false;
          }
          af_counter = 0;
        } else {
          af[highestIndex].afvalid = false;
          devTEF_Set_Cmd(TEF_FM, Cmd_Tune_To, 7, 4, currentfreq);
        }
      } else {
        devTEF_Set_Cmd(TEF_FM, Cmd_Tune_To, 7, 4, currentfreq);
      }
    }
  }
  return currentfreq;
}


void TEF6686::init(byte TEF) {
  uint8_t bootstatus;
  int xtalADC = 0;
  Tuner_I2C_Init();
  devTEF_APPL_Get_Operation_Status(&bootstatus);
  if (bootstatus == 0) {
    Tuner_Patch(TEF);
    delay(50);

    xtalADC = analogRead(15);

    if (xtalADC < XTAL_0V_ADC + XTAL_ADC_TOL) {
      Tuner_Init(tuner_init_tab9216);
      log_d("TEF668X XTAL : 9.216M");
    } else if (xtalADC > XTAL_1V_ADC - XTAL_ADC_TOL && xtalADC < XTAL_1V_ADC + XTAL_ADC_TOL) {
      Tuner_Init(tuner_init_tab12000);
      log_d("TEF668X XTAL : 12M");
    } else if (xtalADC > XTAL_2V_ADC - XTAL_ADC_TOL && xtalADC < XTAL_2V_ADC + XTAL_ADC_TOL) {
      Tuner_Init(tuner_init_tab55000);
      log_d("TEF668X XTAL : 55M");
    } else {
      Tuner_Init(tuner_init_tab4000);
      log_d("TEF668X XTAL : 4M");
    }
    power(1);
    Tuner_Init(tuner_init_tab);
  }
}

bool TEF6686::getIdentification(uint16_t &device, uint16_t &hw_version, uint16_t &sw_version) {
  devTEF_Radio_Get_Identification(&device, &hw_version, &sw_version);
  return device;
  return hw_version;
  return sw_version;
}

void TEF6686::setCoax(uint8_t mode) {
  devTEF_Radio_Set_GPIO(mode);
}


void TEF6686::power(bool mode) {
  devTEF_APPL_Set_OperationMode(mode);
  if (mode == 0) devTEF_Set_Cmd(TEF_FM, Cmd_Tune_To, 7, 1, 10000);
}

void TEF6686::SetFreq(uint16_t frequency) {
  devTEF_Radio_Tune_To(frequency);
  currentfreq = ((frequency + 5) / 10) * 10;
  currentfreq2 = frequency;
}

void TEF6686::SetFreqAM(uint16_t frequency) {
  devTEF_Radio_Tune_AM (frequency);
}

void TEF6686::SetFreqAIR(uint16_t frequency) {
  devTEF_Radio_Tune_AM (10700);
}

void TEF6686::setOffset(int8_t offset) {
  devTEF_Radio_Set_LevelOffset(offset * 10);
}

void TEF6686::setAMOffset(int8_t offset) {
  devTEF_Radio_Set_AMLevelOffset(offset * 10);
}

void TEF6686::setFMBandw(uint16_t bandwidth) {
  devTEF_Radio_Set_Bandwidth(0, bandwidth * 10);
}

void TEF6686::setAMBandw(uint16_t bandwidth) {
  devTEF_Radio_Set_BandwidthAM(0, bandwidth * 10);
}

void TEF6686::setAMCoChannel(uint16_t start, uint8_t level) {
  if (start == 0) devTEF_Radio_Set_CoChannel_AM(0, start * 10, level); else devTEF_Radio_Set_CoChannel_AM(1, start * 10, level);
}

void TEF6686::setSoftmuteAM(uint8_t mode) {
  devTEF_Radio_Set_Softmute_Max_AM(mode);
}

void TEF6686::setSoftmuteFM(uint8_t mode) {
  devTEF_Radio_Set_Softmute_Max_FM(mode);
}

void TEF6686::setAMNoiseBlanker(uint16_t start) {
  if (start == 0) devTEF_Radio_Set_Noiseblanker_AM(0, 1000); else devTEF_Radio_Set_Noiseblanker_AM(1, start * 10);
}

void TEF6686::setAMAttenuation(uint16_t start) {
  devTEF_Radio_Set_Attenuator_AM(start * 10);
}

void TEF6686::setFMABandw() {
  devTEF_Radio_Set_Bandwidth(1, 3110);
}

void TEF6686::setiMS(bool mph) {
  devTEF_Radio_Set_MphSuppression(mph);
}

void TEF6686::setEQ(bool eq) {
  devTEF_Radio_Set_ChannelEqualizer(eq);
}

bool TEF6686::getStereoStatus() {
  uint16_t status;
  bool stereo = 0;
  if (1 == devTEF_Radio_Get_Stereo_Status(&status)) stereo = ((status >> 15) & 1) ? 1 : 0;
  return stereo;
}

void TEF6686::setMono(bool mono) {
  devTEF_Radio_Set_Stereo_Min(mono);
}

void TEF6686::setVolume(int8_t volume) {
  devTEF_Audio_Set_Volume(volume);
}

void TEF6686::setMute() {
  mute = true;
  if (mpxmode) devTEF_Radio_Specials(0);
  devTEF_Audio_Set_Mute(1);
}

void TEF6686::setUnMute() {
  mute = false;
  if (mpxmode) devTEF_Radio_Specials(1);
  devTEF_Audio_Set_Mute(0);
}

void TEF6686::setAGC(uint8_t agc) {
  devTEF_Radio_Set_RFAGC(agc);
}

void TEF6686::setAMAGC(uint8_t agc) {
  devTEF_Radio_Set_AMRFAGC(agc);
}

void TEF6686::setDeemphasis(uint8_t timeconstant) {
  switch (timeconstant) {
    case 1: devTEF_Radio_Set_Deemphasis(500); break;
    case 2: devTEF_Radio_Set_Deemphasis(750); break;
    default: devTEF_Radio_Set_Deemphasis(0); break;
  }
}

void TEF6686::setAudio(uint8_t audio) {
  devTEF_Radio_Specials(audio);
  if (audio == 0) mpxmode = false; else mpxmode = true;
}

void TEF6686::setFMSI(uint8_t mode) {
  if (mode == 1) devTEF_APPL_Set_StereoImprovement(0);
  if (mode == 2) devTEF_APPL_Set_StereoImprovement(1);
}

void TEF6686::setFMSI_Time(uint16_t attack, uint16_t decay) {
  devTEF_APPL_Set_StereoBandBlend_Time(attack, decay);
}

void TEF6686::setFMSI_Gain(uint16_t band1, uint16_t band2, uint16_t band3, uint16_t band4) {
  devTEF_APPL_Set_StereoBandBlend_Gain(band1 * 10, band2 * 10, band3 * 10, band4 * 10);
}

void TEF6686::setFMSI_Bias(int16_t band1, int16_t band2, int16_t band3, int16_t band4) {
  devTEF_APPL_Set_StereoBandBlend_Bias(band1 - 250, band2 - 250, band3 - 250, band4 - 250);
}


void TEF6686::setFMNoiseBlanker(uint16_t start) {
  if (start == 0) devTEF_Radio_Set_NoisBlanker(0, 1000); else devTEF_Radio_Set_NoisBlanker(1, start * 10);
}

void TEF6686::setStereoLevel(uint8_t start) {
  if (start == 0) {
    devTEF_Radio_Set_Stereo_Level(0, start * 10, 60);
    devTEF_Radio_Set_Stereo_Noise(0, 240, 200);
    devTEF_Radio_Set_Stereo_Mph(0, 240, 200);
  } else {
    devTEF_Radio_Set_Stereo_Level(3, start * 10, 60);
    devTEF_Radio_Set_Stereo_Noise(3, 240, 200);
    devTEF_Radio_Set_Stereo_Mph(3, 240, 200);
  }
}

void TEF6686::setHighCutOffset(uint8_t start) {
  if (start == 0) {
    devTEF_Radio_Set_Highcut_Level(0, start * 10, 300);
    devTEF_Radio_Set_Highcut_Noise(0, 360, 300);
    devTEF_Radio_Set_Highcut_Mph(0, 360, 300);
  } else {
    devTEF_Radio_Set_Highcut_Level(3, start * 10, 300);
    devTEF_Radio_Set_Highcut_Noise(3, 360, 300);
    devTEF_Radio_Set_Highcut_Mph(3, 360, 300);
  }
}

void TEF6686::setHighCutLevel(uint16_t limit) {
  devTEF_Radio_Set_Highcut_Max(1, limit * 100);
}

void TEF6686::setStHiBlendLevel(uint16_t limit) {
  devTEF_Radio_Set_StHiBlend_Max(1, limit * 100);
}

void TEF6686::setStHiBlendOffset(uint8_t start) {
  if (start == 0) {
    devTEF_Radio_Set_StHiBlend_Level(0, start * 10, 300);
    devTEF_Radio_Set_StHiBlend_Noise(0, 360, 300);
    devTEF_Radio_Set_StHiBlend_Mph(0, 360, 300);
  } else {
    devTEF_Radio_Set_StHiBlend_Level(3, start * 10, 300);
    devTEF_Radio_Set_StHiBlend_Noise(3, 360, 300);
    devTEF_Radio_Set_StHiBlend_Mph(3, 360, 300);
  }
}

bool TEF6686::getProcessing(uint16_t &highcut, uint16_t &stereo, uint16_t &sthiblend, uint8_t &stband_1, uint8_t &stband_2, uint8_t &stband_3, uint8_t &stband_4) {
  devTEF_Radio_Get_Processing_Status(&highcut, &stereo, &sthiblend, &stband_1, &stband_2, &stband_3, &stband_4);
  return highcut;
  return stereo;
  return sthiblend;
  return stband_1;
  return stband_2;
  return stband_3;
  return stband_4;
}

bool TEF6686::getStatus(int16_t &level, uint16_t &USN, uint16_t &WAM, int16_t &offset, uint16_t &bandwidth, uint16_t &modulation, int8_t &snr) {
  uint16_t status;
  devTEF_Radio_Get_Quality_Status(&status, &level, &USN, &WAM, &offset, &bandwidth, &modulation, &snr);
  return level;
  return USN;
  return WAM;
  return bandwidth;
  return modulation;
  return snr;
}

bool TEF6686::getStatusAM(int16_t &level, uint16_t &noise, uint16_t &cochannel, int16_t &offset, uint16_t &bandwidth, uint16_t &modulation, int8_t &snr) {
  devTEF_Radio_Get_Quality_Status_AM(&level, &noise, &cochannel, &offset, &bandwidth, &modulation, &snr);
  return level;
  return noise;
  return cochannel;
  return bandwidth;
  return modulation;
  return snr;
}

void TEF6686::readRDS(byte showrdserrors) {
  uint8_t offset;
  if (rds.filter && ps_process) {
    devTEF_Radio_Get_RDS_Status(&rds.rdsStat, &rds.rdsA, &rds.rdsB, &rds.rdsC, &rds.rdsD, &rds.rdsErr);
  } else {
    if (millis() >= rdstimer + 87) {
      rdstimer += 87;
      devTEF_Radio_Get_RDS_Data(&rds.rdsStat, &rds.rdsA, &rds.rdsB, &rds.rdsC, &rds.rdsD, &rds.rdsErr);

      if ((rds.rdsStat & (1 << 14))) {
        for (int i = 0; i < 22; i++) devTEF_Radio_Get_RDS_Data(&rds.rdsStat, &rds.rdsA, &rds.rdsB, &rds.rdsC, &rds.rdsD, &rds.rdsErr);
      }
    }
  }

  if (bitRead(rds.rdsStat, 9)) {
    rds.hasRDS = true;                                                                            // RDS decoder synchronized and data available
    bitStartTime = 0;
  } else {
    if (bitStartTime == 0) {
      bitStartTime = millis();
    } else if (millis() - bitStartTime >= 87) {
      rds.hasRDS = false;
    }
  }

  rdsAerrorThreshold = (((rds.rdsErr >> 14) & 0x03) > showrdserrors);
  rdsBerrorThreshold = (((rds.rdsErr >> 12) & 0x03) > showrdserrors);
  rdsCerrorThreshold = (((rds.rdsErr >> 10) & 0x03) > showrdserrors);
  rdsDerrorThreshold = (((rds.rdsErr >> 8) & 0x03) > showrdserrors);

  if (bitRead(rds.rdsStat, 9) && (rds.rdsA != previous_rdsA || rds.rdsB != previous_rdsB || rds.rdsC != previous_rdsC || rds.rdsD != previous_rdsD)) {
    rds.rdsAerror = (((rds.rdsErr >> 14) & 0x03) > 1);                                                                 // We have all data to decode... let's go...
    rds.rdsBerror = (((rds.rdsErr >> 12) & 0x03) > 1);
    rds.rdsCerror = (((rds.rdsErr >> 10) & 0x03) > 1);
    rds.rdsDerror = (((rds.rdsErr >> 8) & 0x03) > 1);

    //PI decoder
    if (!rdsAerrorThreshold && afreset) {
      rds.correctPI = rds.rdsA;
      afreset = false;
    }

    if (((!rdsAerrorThreshold && !rdsBerrorThreshold && !rdsCerrorThreshold && !rdsDerrorThreshold) || (rds.pierrors && !errorfreepi))) {
      if (rds.rdsA != piold && rds.rdsA != 0) {
        piold = rds.rdsA;
        rds.picode[0] = (rds.rdsA >> 12) & 0xF;
        rds.picode[1] = (rds.rdsA >> 8) & 0xF;
        rds.picode[2] = (rds.rdsA >> 4) & 0xF;
        rds.picode[3] = rds.rdsA & 0xF;
        for (int i = 0; i < 4; i++) {
          if (rds.picode[i] < 10) {
            rds.picode[i] += '0';                                                                 // Add ASCII offset for decimal digits
          } else {
            rds.picode[i] += 'A' - 10;                                                            // Add ASCII offset for hexadecimal letters A-F
          }
        }
      }

      if (!rdsAerrorThreshold && !rdsBerrorThreshold && !rdsCerrorThreshold && !rdsDerrorThreshold) {
        rds.picode[4] = ' ';
        rds.picode[5] = ' ';
        errorfreepi = true;
      }

      if (!errorfreepi) {
        if (((rds.rdsErr >> 14) & 0x03) > 2) rds.picode[5] = '?'; else rds.picode[5] = ' ';
        if (((rds.rdsErr >> 14) & 0x03) > 1) rds.picode[4] = '?'; else rds.picode[4] = ' ';       // Not sure, add a ?
      } else {
        rds.picode[4] = ' ';
        rds.picode[5] = ' ';
      }
      rds.picode[6] = '\0';
      if (strncmp(rds.picode, "0000", 4) == 0) {
        if (piold != 0) {
          rds.picode[0] = (piold >> 12) & 0xF;
          rds.picode[1] = (piold >> 8) & 0xF;
          rds.picode[2] = (piold >> 4) & 0xF;
          rds.picode[3] = piold & 0xF;
          for (int i = 0; i < 4; i++) {
            if (rds.picode[i] < 10) {
              rds.picode[i] += '0';                                                               // Add ASCII offset for decimal digits
            } else {
              rds.picode[i] += 'A' - 10;                                                          // Add ASCII offset for hexadecimal letters A-F
            }
          }
        } else {
          if (rds.stationName.length() == 0) {
            memset(rds.picode, 0, sizeof(rds.picode));
          }

          memset(rds.picode, 0, sizeof(rds.picode));
        }
      }

      // USA Station callsign decoder
      if (ps_process && rds.correctPI != 0 && rds.region == 1 && correctPIold != rds.correctPI) {
        bool foundMatch = false;
        File file;

        if (SPIFFS.begin(true)) {
          delay(5);
          if (currentfreq2 < 9000) {
            file = SPIFFS.open("/USA_87-90.csv");
          } else if (currentfreq2 > 9000 && currentfreq2 < 9200) {
            file = SPIFFS.open("/USA_90-92.csv");
          } else if (currentfreq2 > 9200 && currentfreq2 < 9400) {
            file = SPIFFS.open("/USA_92-94.csv");
          } else if (currentfreq2 > 9400 && currentfreq2 < 9600) {
            file = SPIFFS.open("/USA_94-96.csv");
          } else if (currentfreq2 > 9600 && currentfreq2 < 9800) {
            file = SPIFFS.open("/USA_96-98.csv");
          } else if (currentfreq2 > 9800 && currentfreq2 < 10000) {
            file = SPIFFS.open("/USA_98-100.csv");
          } else if (currentfreq2 > 10000 && currentfreq2 < 10200) {
            file = SPIFFS.open("/USA_100-102.csv");
          } else if (currentfreq2 > 10200 && currentfreq2 < 10400) {
            file = SPIFFS.open("/USA_102-104.csv");
          } else if (currentfreq2 > 10400 && currentfreq2 < 10600) {
            file = SPIFFS.open("/USA_104-106.csv");
          } else if (currentfreq2 > 10600) {
            file = SPIFFS.open("/USA_106-108.csv");
          }

          delay(5);
          if (file) {
            int i = 0;
            while (file.available() && !isprint(file.peek())) {
              file.read();
              i++;
            }

            char buffer[25];
            while (file.available()) {
              int bytesRead = file.readBytesUntil('\n', buffer, sizeof(buffer) - 1);
              buffer[bytesRead] = '\0';

              char *token = strtok(buffer, ";");

              int firstColumnValue = 0;
              uint16_t frequencyValue = 0;
              char stationID[8];
              char stationState[8];

              if (token) {
                firstColumnValue = atoi(token);
                token = strtok(NULL, ";");
                frequencyValue = atoi(token);
                token = strtok(NULL, ";");
                strncpy(stationID, token, sizeof(stationID) - 1);
                stationID[sizeof(stationID) - 1] = '\0';
                token = strtok(NULL, ";");
                strncpy(stationState, token, sizeof(stationState) - 1);
                stationState[sizeof(stationState) - 1] = '\0';
              }

              if (frequencyValue == currentfreq2 && static_cast<uint16_t>(firstColumnValue) == rds.correctPI) {
                strncpy(rds.stationID, stationID, 7);
                strncpy(rds.stationState, stationState, 2);
                foundMatch = true;
                break;
              }
            }
          }
        }

        if (!foundMatch) {
          uint16_t stationID = rds.rdsA;
          if (stationID > 4096) {
            if (stationID > 21671 && (stationID & 0xF00U) >> 8 == 0) stationID = ((uint16_t)uint8_t(0xA0 + ((stationID & 0xF000U) >> 12)) << 8) + lowByte(stationID); // C0DE -> ACDE
            if (stationID > 21671 && lowByte(stationID) == 0) stationID = 0xAF00 + uint8_t(highByte(stationID)); // CD00 -> AFCD
            if (stationID < 39247) {
              if (stationID > 21671) {
                rds.stationID[0] = 'W';
                stationID -= 21672;
              } else {
                rds.stationID[0] = 'K';
                stationID -= 4096;
              }
              rds.stationID[1] = char(stationID / 676 + 65);
              rds.stationID[2] = char((stationID - 676 * int(stationID / 676)) / 26 + 65);
              rds.stationID[3] = char(((stationID - 676 * int(stationID / 676)) % 26) + 65);
            } else {
              stationID -= 4835;
              rds.stationID[0] = 'K';
              rds.stationID[1] = char(stationID / 676 + 65);
              rds.stationID[2] = char((stationID - 676 * int(stationID / 676)) / 26 + 65);
              rds.stationID[3] = char(((stationID - 676 * int(stationID / 676)) % 26) + 65);
            }
          }

          bool faultyID = false;

          for (byte i = 0; i < 4; i++) {
            if (!(rds.stationID[i] >= 'A' && rds.stationID[i] <= 'Z')) {
              faultyID = true;
              break;
            }
          }

          if (faultyID) {
            strcpy(rds.stationID, "Unknown");
          } else {
            rds.stationID[7] = '?';
          }
          rds.stationID[8] = '\0';
        }
        correctPIold = rds.correctPI;
        rds.stationIDtext = rds.stationID;
        rds.stationStatetext = rds.stationState;
      }
    }

    if (!rds.rdsBerror || showrdserrors == 3) rdsblock = rds.rdsB >> 11; else return;
    switch (rdsblock) {
      case RDS_GROUP_0A:
      case RDS_GROUP_0B:
        {
          //PS decoder
          if (showrdserrors == 3 || (!rdsBerrorThreshold && !rdsDerrorThreshold)) {
            offset = rds.rdsB & 0x03;                                                           // Let's get the character offset for PS

            ps_buffer2[(offset * 2) + 0] = ps_buffer[(offset * 2) + 0];                         // Make a copy of the PS buffer
            ps_buffer2[(offset * 2) + 1] = ps_buffer[(offset * 2) + 1];
            ps_buffer2[8] = '\0';                                                               // Endmarker

            ps_buffer[(offset * 2)  + 0] = rds.rdsD >> 8;                                       // First character of segment
            ps_buffer[(offset * 2)  + 1] = rds.rdsD & 0xFF;                                     // Second character of segment
            ps_buffer[8] = '\0';                                                                // Endmarker

            if (ps_process || rds.fastps == 0) {
              if (offset == 0) {
                packet0 = true;
                packet1 = false;
                packet2 = false;
                packet3 = false;
              }
              if (offset == 1) packet1 = true;
              if (offset == 2) packet2 = true;
              if (offset == 3) packet3 = true;
            }

            if (packet0 && packet1 && packet2 && packet3 && (ps_process || (rds.fastps == 0 && rds.fastps != 2))) { // Last chars are received
              if (strcmp(ps_buffer, ps_buffer2) == 0) {                                                             // When no difference between current and buffer, let's go...
                ps_process = true;
                RDScharConverter(ps_buffer2, PStext, sizeof(PStext) / sizeof(wchar_t), true);                       // Convert 8 bit ASCII to 16 bit ASCII
                String utf8String = convertToUTF8(PStext);                                                          // Convert RDS characterset to ASCII
                rds.stationName = extractUTF8Substring(utf8String, 0, 8, true);                                     // Make sure PS does not exceed 8 characters
                for (byte x = 0; x < 8; x++) {
                  ps_buffer[x] = '\0';
                  ps_buffer2[x] = '\0';
                }
              }
            }

            if ((!ps_process && rds.fastps > 0 && rds.fastps != 2) || rds.fastps == 2) {                            // Let's get 2 runs of 8 PS characters fast and without refresh
              if (offset == 0) packet0 = true;
              if (offset == 1) packet1 = true;
              if (offset == 2) packet2 = true;
              if (offset == 3) packet3 = true;
              RDScharConverter(ps_buffer, PStext, sizeof(PStext) / sizeof(wchar_t), true);                          // Convert 8 bit ASCII to 16 bit ASCII
              String utf8String = convertToUTF8(PStext);                                                            // Convert RDS characterset to ASCII
              rds.stationName = extractUTF8Substring(utf8String, 0, 8, true);
              if (packet0 && packet1 && packet2 && packet3) ps_process = true;                                      // OK, we had one runs, now let's go the idle PS writing
            }

            if (offset == 0) rds.hasDynamicPTY = bitRead(rds.rdsB, 2) & 0x1F;                   // Dynamic PTY flag
            if (offset == 1) rds.hasCompressed = bitRead(rds.rdsB, 2) & 0x1F;                   // Compressed flag
            if (offset == 2) rds.hasArtificialhead = bitRead(rds.rdsB, 2) & 0x1F;               // Artificial head flag
            if (offset == 3) rds.hasStereo = bitRead(rds.rdsB, 2) & 0x1F;                       // Stereo flag
          }

          if (!rdsBerrorThreshold) {
            rds.stationTypeCode = (rds.rdsB >> 5) & 0x1F;                                       // Get 5 PTY bits from Block B
            if (rds.region == 0) strcpy(rds.stationType, PTY_EU[rds.stationTypeCode]);
            if (rds.region == 1) strcpy(rds.stationType, PTY_USA[rds.stationTypeCode]);

            rds.hasTA = (bitRead(rds.rdsB, 4));                                                 // Read TA flag

            if ((bitRead(rds.rdsB, 3)) == 1) rds.MS = 1; else rds.MS = 2;                       // Read MS flag
          }

          rds.hasTP = (bitRead(rds.rdsB, 10));                                                  // Read TP flag

          if (!rdsCerrorThreshold) {
            //AF decoder
            if (rdsblock == 0 && rds.rdsC != rdsCold) {                                         // Only when in GROUP 0A

              if ((rds.rdsC >> 8) > 224 && (rds.rdsC >> 8) < 250) {
                afinit = true;  // AF detected
                rds.hasAF = true;
              }

              if (afinit) {
                if ((rds.rdsC >> 8) > 224 && (rds.rdsC >> 8) < 250 && ((rds.rdsC & 0xFF) * 10 + 8750) == currentfreq && rds.hasAF) {
                  if (afmethodBtrigger) afmethodB = true;                                       // Check for AF method B
                  afmethodBprobe = true;
                  af_counterb = (rds.rdsC >> 8) - 224;
                  af_number = (rds.rdsC >> 8) - 224;
                  af_counterbcheck = 1;
                  doublecounter = 0;
                  doubletestfreq = (rds.rdsC & 0xFF) * 10 + 8750;
                } else if ((rds.rdsC >> 8) > 224 && (rds.rdsC >> 8) < 250 && ((rds.rdsC & 0xFF) * 10 + 8750) != currentfreq && rds.hasAF) {
                  afmethodBprobe = false;
                  afmethodBtrigger = true;
                  af_counterb = 0;
                  af_number = (rds.rdsC >> 8) - 224;
                  af_counterbcheck = 0;
                  doublecounter = 0;
                  doubletestfreq = (rds.rdsC & 0xFF) * 10 + 8750;
                }

                if (((rds.rdsC >> 8) > 0 && (rds.rdsC >> 8) < 205) && ((rds.rdsC >> 8) > 0 && (rds.rdsC >> 8) < 205)) {
                  if (afmethodBprobe) af_counterbcheck += 2;
                }

                if ((rds.rdsB >> 11) == 0 && af_counter < 50) {
                  uint16_t buffer0;
                  uint16_t buffer1;

                  if ((rds.rdsC >> 8) > 0 && (rds.rdsC >> 8) < 205) buffer0 = (rds.rdsC >> 8) * 10 + 8750; else buffer0 = 0;
                  if ((rds.rdsC & 0xFF) > 0 && (rds.rdsC & 0xFF) < 205) buffer1 = (rds.rdsC & 0xFF) * 10 + 8750; else buffer1 = 0;

                  if (((rds.rdsC >> 8) > 0 && (rds.rdsC >> 8) < 205) && (buffer0 == doubletestfreq || buffer1 == doubletestfreq)) doublecounter++;
                  if (doublecounter > (af_number / 2)) afmethodB = true;                        // If signed frequency also appears more than once in the AF list, AF Method B detected

                  if (afmethodBprobe && af_counterbcheck > af_counterb) afmethodBprobe = false; // If more than counter received disable probe flag

                  if (afmethodBprobe) {                                                         // Check for Reg. flags
                    if (buffer1 == currentfreq && buffer0 > buffer1) {
                      for (int x = 0; x < af_counter; x++) {
                        if (af[x].frequency == buffer0 && !af[x].regional) {
                          af[x].regional = true;
                          af_updatecounter++;
                          break;
                        }
                      }
                    } else if (buffer1 == currentfreq && buffer0 < buffer1) {
                      for (int x = 0; x < af_counter; x++) {
                        if (af[x].frequency == buffer0 && !af[x].same) {
                          af[x].same = true;
                          af_updatecounter++;
                          break;
                        }
                      }
                    }

                    if (buffer0 == currentfreq && buffer0 > buffer1) {
                      for (int x = 0; x < af_counter; x++) {
                        if (af[x].frequency == buffer1 && !af[x].regional) {
                          af[x].regional = true;
                          af_updatecounter++;
                          break;
                        }
                      }
                    } else if (buffer0 == currentfreq && buffer0 < buffer1) {
                      for (int x = 0; x < af_counter; x++) {
                        if (af[x].frequency == buffer1 && !af[x].same) {
                          af[x].same = true;
                          af_updatecounter++;
                          break;
                        }
                      }
                    }
                  }

                  if (buffer0 != currentfreq && buffer1 != currentfreq && afmethodB && afmethodBprobe) {
                    afmethodBprobe = false;                                                     // Remove faulty Reg. flags
                    for (int x = 0; x < af_counter; x++) {
                      if (af[x].frequency == buffer0 || af[x].frequency == buffer1) {
                        if (af[x].same) {
                          af[x].same = false;
                          af_updatecounter++;
                        }
                        if (af[x].regional) {
                          af[x].regional = false;
                          af_updatecounter++;
                        }
                      }
                      break;
                    }
                  }

                  bool isValuePresent = false;
                  for (int i = 0; i < 50; i++) {                                                // Check if already in list
                    if ((rds.sortaf && (buffer0 == currentfreq)) || buffer0 == 0 || af[i].frequency == buffer0) {
                      isValuePresent = true;
                      break;
                    }
                  }

                  if (!isValuePresent) {                                                        // Add frequency to list
                    af[af_counter].frequency = buffer0;
                    if (af_counter < 50) af_counter++;
                    af_updatecounter++;
                  }

                  isValuePresent = false;
                  for (int i = 0; i < 50; i++) {                                                // Check if already in list
                    if ((rds.sortaf && (buffer1 == currentfreq)) || buffer1 == 0 || af[i].frequency == buffer1) {
                      isValuePresent = true;
                      break;
                    }
                  }

                  if (!isValuePresent) {
                    af[af_counter].frequency = buffer1;                                         // Add frequency to list
                    if (af_counter < 50) af_counter++;
                    af_updatecounter++;
                  }

                  if (rds.sortaf) {                                                             // Sort AF list (low to high)
                    for (int i = 0; i < 50; i++) {
                      for (int j = 0; j < 50 - i; j++) {
                        if (af[j].frequency == 0) continue;

                        if (af[j].frequency > af[j + 1].frequency && af[j + 1].frequency != 0) {
                          uint16_t temp = af[j].frequency;
                          bool temp3 = af[j].afvalid;
                          bool temp4 = af[j].checked;
                          bool temp5 = af[j].regional;
                          bool temp6 = af[j].same;
                          af[j].frequency = af[j + 1].frequency;
                          af[j].afvalid = af[j + 1].afvalid;
                          af[j].checked = af[j + 1].checked;
                          af[j].regional = af[j + 1].regional;
                          af[j].same = af[j + 1].same;
                          af[j + 1].frequency = temp;
                          af[j + 1].afvalid = temp3;
                          af[j + 1].checked = temp4;
                          af[j + 1].regional = temp5;
                          af[j + 1].same = temp6;
                        }
                      }
                    }
                  }
                }
              }
              rdsCold = rds.rdsC;
            }
          }
        } break;

      case RDS_GROUP_1A:
      case RDS_GROUP_1B: {
          if (!rdsCerrorThreshold) {
            if (((rds.rdsC >> 12) & 0x07) == 0 && rdsblock == RDS_GROUP_1A) {                               // ECC code readout
              rds.ECC = rds.rdsC & 0xff;
              rds.hasECC = true;

              switch (rds.picode[0]) {
                case '1': {
                    if (rds.ECC == 160) rds.ECCtext = ECCtext[226];
                    if (rds.ECC == 162) rds.ECCtext = ECCtext[129];
                    if (rds.ECC == 163) rds.ECCtext = ECCtext[136];
                    if (rds.ECC == 164) rds.ECCtext = ECCtext[152];
                    if (rds.ECC == 208) rds.ECCtext = ECCtext[104];
                    if (rds.ECC == 209) rds.ECCtext = ECCtext[73];
                    if (rds.ECC == 210) rds.ECCtext = ECCtext[83];
                    if (rds.ECC == 224) rds.ECCtext = ECCtext[0];
                    if (rds.ECC == 225) rds.ECCtext = ECCtext[1];
                    if (rds.ECC == 226) rds.ECCtext = ECCtext[2];
                    if (rds.ECC == 227) rds.ECCtext = ECCtext[59];
                    if (rds.ECC == 228) rds.ECCtext = ECCtext[3];
                    if (rds.ECC == 240) rds.ECCtext = ECCtext[179];
                    if (rds.ECC == 241) rds.ECCtext = ECCtext[197];
                    if (rds.ECC == 242) rds.ECCtext = ECCtext[124];
                    if (rds.ECC == 243) rds.ECCtext = ECCtext[200];
                    break;
                  }

                case '2': {
                    if (rds.ECC == 160) rds.ECCtext = ECCtext[226];
                    if (rds.ECC == 162) rds.ECCtext = ECCtext[130];
                    if (rds.ECC == 163) rds.ECCtext = ECCtext[141];
                    if (rds.ECC == 164) rds.ECCtext = ECCtext[155];
                    if (rds.ECC == 208) rds.ECCtext = ECCtext[106];
                    if (rds.ECC == 209) rds.ECCtext = ECCtext[126];
                    if (rds.ECC == 210) rds.ECCtext = ECCtext[95];
                    if (rds.ECC == 224) rds.ECCtext = ECCtext[4];
                    if (rds.ECC == 225) rds.ECCtext = ECCtext[5];
                    if (rds.ECC == 226) rds.ECCtext = ECCtext[6];
                    if (rds.ECC == 227) rds.ECCtext = ECCtext[7];
                    if (rds.ECC == 228) rds.ECCtext = ECCtext[8];
                    if (rds.ECC == 240) rds.ECCtext = ECCtext[180];
                    if (rds.ECC == 241) rds.ECCtext = ECCtext[187];
                    if (rds.ECC == 242) rds.ECCtext = ECCtext[77];
                    if (rds.ECC == 243) rds.ECCtext = ECCtext[218];
                    break;
                  }

                case '3': {
                    if (rds.ECC == 160) rds.ECCtext = ECCtext[226];
                    if (rds.ECC == 162) rds.ECCtext = ECCtext[224];
                    if (rds.ECC == 163) rds.ECCtext = ECCtext[156];
                    if (rds.ECC == 164) rds.ECCtext = ECCtext[132];
                    if (rds.ECC == 208) rds.ECCtext = ECCtext[112];
                    if (rds.ECC == 209) rds.ECCtext = ECCtext[119];
                    if (rds.ECC == 210) rds.ECCtext = ECCtext[72];
                    if (rds.ECC == 211) rds.ECCtext = ECCtext[92];
                    if (rds.ECC == 224) rds.ECCtext = ECCtext[9];
                    if (rds.ECC == 225) rds.ECCtext = ECCtext[10];
                    if (rds.ECC == 226) rds.ECCtext = ECCtext[11];
                    if (rds.ECC == 227) rds.ECCtext = ECCtext[12];
                    if (rds.ECC == 228) rds.ECCtext = ECCtext[16];
                    if (rds.ECC == 229) rds.ECCtext = ECCtext[63];
                    if (rds.ECC == 240) rds.ECCtext = ECCtext[181];
                    if (rds.ECC == 241) rds.ECCtext = ECCtext[227];
                    if (rds.ECC == 242) rds.ECCtext = ECCtext[189];
                    if (rds.ECC == 243) rds.ECCtext = ECCtext[219];
                    break;
                  }

                case '4': {
                    if (rds.ECC == 160) rds.ECCtext = ECCtext[226];
                    if (rds.ECC == 162) rds.ECCtext = ECCtext[148];
                    if (rds.ECC == 163) rds.ECCtext = ECCtext[157];
                    if (rds.ECC == 208) rds.ECCtext = ECCtext[127];
                    if (rds.ECC == 209) rds.ECCtext = ECCtext[69];
                    if (rds.ECC == 210) rds.ECCtext = ECCtext[91];
                    if (rds.ECC == 211) rds.ECCtext = ECCtext[103];
                    if (rds.ECC == 224) rds.ECCtext = ECCtext[13];
                    if (rds.ECC == 225) rds.ECCtext = ECCtext[14];
                    if (rds.ECC == 226) rds.ECCtext = ECCtext[15];
                    if (rds.ECC == 240) rds.ECCtext = ECCtext[182];
                    if (rds.ECC == 241) rds.ECCtext = ECCtext[210];
                    if (rds.ECC == 242) rds.ECCtext = ECCtext[213];
                    break;
                  }

                case '5': {
                    if (rds.ECC == 160) rds.ECCtext = ECCtext[226];
                    if (rds.ECC == 162) rds.ECCtext = ECCtext[133];
                    if (rds.ECC == 164) rds.ECCtext = ECCtext[159];
                    if (rds.ECC == 208) rds.ECCtext = ECCtext[68];
                    if (rds.ECC == 209) rds.ECCtext = ECCtext[79];
                    if (rds.ECC == 210) rds.ECCtext = ECCtext[88];
                    if (rds.ECC == 211) rds.ECCtext = ECCtext[78];
                    if (rds.ECC == 224) rds.ECCtext = ECCtext[17];
                    if (rds.ECC == 225) rds.ECCtext = ECCtext[18];
                    if (rds.ECC == 226) rds.ECCtext = ECCtext[19];
                    if (rds.ECC == 227) rds.ECCtext = ECCtext[65];
                    if (rds.ECC == 240) rds.ECCtext = ECCtext[183];
                    if (rds.ECC == 241) rds.ECCtext = ECCtext[191];
                    if (rds.ECC == 242) rds.ECCtext = ECCtext[193];
                    break;
                  }

                case '6': {
                    if (rds.ECC == 160) rds.ECCtext = ECCtext[226];
                    if (rds.ECC == 162) rds.ECCtext = ECCtext[134];
                    if (rds.ECC == 163) rds.ECCtext = ECCtext[163];
                    if (rds.ECC == 164) rds.ECCtext = ECCtext[171];
                    if (rds.ECC == 208) rds.ECCtext = ECCtext[96];
                    if (rds.ECC == 209) rds.ECCtext = ECCtext[105];
                    if (rds.ECC == 210) rds.ECCtext = ECCtext[123];
                    if (rds.ECC == 211) rds.ECCtext = ECCtext[125];
                    if (rds.ECC == 224) rds.ECCtext = ECCtext[20];
                    if (rds.ECC == 225) rds.ECCtext = ECCtext[21];
                    if (rds.ECC == 226) rds.ECCtext = ECCtext[22];
                    if (rds.ECC == 228) rds.ECCtext = ECCtext[24];
                    if (rds.ECC == 240) rds.ECCtext = ECCtext[184];
                    if (rds.ECC == 241) rds.ECCtext = ECCtext[76];
                    if (rds.ECC == 242) rds.ECCtext = ECCtext[201];
                    break;
                  }

                case '7': {
                    if (rds.ECC == 160) rds.ECCtext = ECCtext[226];
                    if (rds.ECC == 162) rds.ECCtext = ECCtext[139];
                    if (rds.ECC == 163) rds.ECCtext = ECCtext[161];
                    if (rds.ECC == 164) rds.ECCtext = ECCtext[164];
                    if (rds.ECC == 208) rds.ECCtext = ECCtext[113];
                    if (rds.ECC == 209) rds.ECCtext = ECCtext[81];
                    if (rds.ECC == 210) rds.ECCtext = ECCtext[84];
                    if (rds.ECC == 224) rds.ECCtext = ECCtext[25];
                    if (rds.ECC == 225) rds.ECCtext = ECCtext[26];
                    if (rds.ECC == 226) rds.ECCtext = ECCtext[27];
                    if (rds.ECC == 228) rds.ECCtext = ECCtext[62];
                    if (rds.ECC == 240) rds.ECCtext = ECCtext[185];
                    if (rds.ECC == 241) rds.ECCtext = ECCtext[207];
                    if (rds.ECC == 242) rds.ECCtext = ECCtext[221];
                    break;
                  }

                case '8': {
                    if (rds.ECC == 160) rds.ECCtext = ECCtext[226];
                    if (rds.ECC == 162) rds.ECCtext = ECCtext[142];
                    if (rds.ECC == 164) rds.ECCtext = ECCtext[170];
                    if (rds.ECC == 208) rds.ECCtext = ECCtext[116];
                    if (rds.ECC == 209) rds.ECCtext = ECCtext[117];
                    if (rds.ECC == 210) rds.ECCtext = ECCtext[74];
                    if (rds.ECC == 211) rds.ECCtext = ECCtext[82];
                    if (rds.ECC == 224) rds.ECCtext = ECCtext[28];
                    if (rds.ECC == 225) rds.ECCtext = ECCtext[29];
                    if (rds.ECC == 226) rds.ECCtext = ECCtext[30];
                    if (rds.ECC == 227) rds.ECCtext = ECCtext[31];
                    if (rds.ECC == 228) rds.ECCtext = ECCtext[32];
                    if (rds.ECC == 240) rds.ECCtext = ECCtext[186];
                    if (rds.ECC == 241) rds.ECCtext = ECCtext[195];
                    if (rds.ECC == 242) rds.ECCtext = ECCtext[212];
                    if (rds.ECC == 243) rds.ECCtext = ECCtext[190];
                    break;
                  }

                case '9': {
                    if (rds.ECC == 160) rds.ECCtext = ECCtext[226];
                    if (rds.ECC == 162) rds.ECCtext = ECCtext[143];
                    if (rds.ECC == 163) rds.ECCtext = ECCtext[162];
                    if (rds.ECC == 164) rds.ECCtext = ECCtext[174];
                    if (rds.ECC == 208) rds.ECCtext = ECCtext[120];
                    if (rds.ECC == 209) rds.ECCtext = ECCtext[102];
                    if (rds.ECC == 210) rds.ECCtext = ECCtext[107];
                    if (rds.ECC == 224) rds.ECCtext = ECCtext[33];
                    if (rds.ECC == 225) rds.ECCtext = ECCtext[34];
                    if (rds.ECC == 226) rds.ECCtext = ECCtext[35];
                    if (rds.ECC == 227) rds.ECCtext = ECCtext[36];
                    if (rds.ECC == 228) rds.ECCtext = ECCtext[37];
                    if (rds.ECC == 240) rds.ECCtext = ECCtext[80];
                    if (rds.ECC == 241) rds.ECCtext = ECCtext[209];
                    if (rds.ECC == 242) rds.ECCtext = ECCtext[196];
                    if (rds.ECC == 243) rds.ECCtext = ECCtext[211];
                    if (rds.ECC == 244) rds.ECCtext = ECCtext[190];
                    break;
                  }

                case 'A': {
                    if (rds.ECC == 160) rds.ECCtext = ECCtext[226];
                    if (rds.ECC == 162) rds.ECCtext = ECCtext[131];
                    if (rds.ECC == 163) rds.ECCtext = ECCtext[144];
                    if (rds.ECC == 164) rds.ECCtext = ECCtext[166];
                    if (rds.ECC == 208) rds.ECCtext = ECCtext[85];
                    if (rds.ECC == 209) rds.ECCtext = ECCtext[97];
                    if (rds.ECC == 210) rds.ECCtext = ECCtext[121];
                    if (rds.ECC == 211) rds.ECCtext = ECCtext[70];
                    if (rds.ECC == 212) rds.ECCtext = ECCtext[86];
                    if (rds.ECC == 224) rds.ECCtext = ECCtext[38];
                    if (rds.ECC == 225) rds.ECCtext = ECCtext[39];
                    if (rds.ECC == 226) rds.ECCtext = ECCtext[40];
                    if (rds.ECC == 227) rds.ECCtext = ECCtext[41];
                    if (rds.ECC == 228) rds.ECCtext = ECCtext[60];
                    if (rds.ECC == 240) rds.ECCtext = ECCtext[178];
                    if (rds.ECC == 241) rds.ECCtext = ECCtext[215];
                    if (rds.ECC == 242) rds.ECCtext = ECCtext[214];
                    break;
                  }

                case 'B': {
                    if (rds.ECC == 160) rds.ECCtext = ECCtext[226];
                    if (rds.ECC == 161) rds.ECCtext = ECCtext[138];
                    if (rds.ECC == 162) rds.ECCtext = ECCtext[137];
                    if (rds.ECC == 163) rds.ECCtext = ECCtext[145];
                    if (rds.ECC == 164) rds.ECCtext = ECCtext[167];
                    if (rds.ECC == 165) rds.ECCtext = ECCtext[158];
                    if (rds.ECC == 208) rds.ECCtext = ECCtext[101];
                    if (rds.ECC == 210) rds.ECCtext = ECCtext[109];
                    if (rds.ECC == 209) rds.ECCtext = ECCtext[100];
                    if (rds.ECC == 224) rds.ECCtext = ECCtext[42];
                    if (rds.ECC == 225) rds.ECCtext = ECCtext[43];
                    if (rds.ECC == 226) rds.ECCtext = ECCtext[44];
                    if (rds.ECC == 227) rds.ECCtext = ECCtext[61];
                    if (rds.ECC == 228) rds.ECCtext = ECCtext[66];
                    if (rds.ECC == 240) rds.ECCtext = ECCtext[206];
                    if (rds.ECC == 241) rds.ECCtext = ECCtext[188];
                    if (rds.ECC == 242) rds.ECCtext = ECCtext[203];
                    if (rds.ECC == 243) rds.ECCtext = ECCtext[93];
                    if (rds.ECC == 244) rds.ECCtext = ECCtext[204];
                    break;
                  }

                case 'C': {
                    if (rds.ECC == 161) rds.ECCtext = ECCtext[138];
                    if (rds.ECC == 162) rds.ECCtext = ECCtext[223];
                    if (rds.ECC == 163) rds.ECCtext = ECCtext[140];
                    if (rds.ECC == 164) rds.ECCtext = ECCtext[146];
                    if (rds.ECC == 165) rds.ECCtext = ECCtext[169];
                    if (rds.ECC == 208) rds.ECCtext = ECCtext[110];
                    if (rds.ECC == 209) rds.ECCtext = ECCtext[108];
                    if (rds.ECC == 210) rds.ECCtext = ECCtext[111];
                    if (rds.ECC == 211) rds.ECCtext = ECCtext[87];
                    if (rds.ECC == 224) rds.ECCtext = ECCtext[45];
                    if (rds.ECC == 225) rds.ECCtext = ECCtext[46];
                    if (rds.ECC == 226) rds.ECCtext = ECCtext[47];
                    if (rds.ECC == 227) rds.ECCtext = ECCtext[48];
                    if (rds.ECC == 228) rds.ECCtext = ECCtext[118];
                    if (rds.ECC == 240) rds.ECCtext = ECCtext[190];
                    if (rds.ECC == 241) rds.ECCtext = ECCtext[216];
                    if (rds.ECC == 242) rds.ECCtext = ECCtext[194];
                    break;
                  }

                case 'D': {
                    if (rds.ECC == 160) rds.ECCtext = ECCtext[226];
                    if (rds.ECC == 161) rds.ECCtext = ECCtext[138];
                    if (rds.ECC == 162) rds.ECCtext = ECCtext[225];
                    if (rds.ECC == 163) rds.ECCtext = ECCtext[150];
                    if (rds.ECC == 164) rds.ECCtext = ECCtext[154];
                    if (rds.ECC == 165) rds.ECCtext = ECCtext[158];
                    if (rds.ECC == 208) rds.ECCtext = ECCtext[90];
                    if (rds.ECC == 209) rds.ECCtext = ECCtext[89];
                    if (rds.ECC == 224) rds.ECCtext = ECCtext[0];
                    if (rds.ECC == 225) rds.ECCtext = ECCtext[49];
                    if (rds.ECC == 226) rds.ECCtext = ECCtext[23];
                    if (rds.ECC == 227) rds.ECCtext = ECCtext[122];
                    if (rds.ECC == 240) rds.ECCtext = ECCtext[198];
                    if (rds.ECC == 241) rds.ECCtext = ECCtext[217];
                    if (rds.ECC == 242) rds.ECCtext = ECCtext[128];
                    break;
                  }

                case 'E': {
                    if (rds.ECC == 160) rds.ECCtext = ECCtext[226];
                    if (rds.ECC == 161) rds.ECCtext = ECCtext[138];
                    if (rds.ECC == 162) rds.ECCtext = ECCtext[151];
                    if (rds.ECC == 163) rds.ECCtext = ECCtext[172];
                    if (rds.ECC == 164) rds.ECCtext = ECCtext[175];
                    if (rds.ECC == 165) rds.ECCtext = ECCtext[158];
                    if (rds.ECC == 208) rds.ECCtext = ECCtext[99];
                    if (rds.ECC == 209) rds.ECCtext = ECCtext[115];
                    if (rds.ECC == 210) rds.ECCtext = ECCtext[94];
                    if (rds.ECC == 224) rds.ECCtext = ECCtext[50];
                    if (rds.ECC == 225) rds.ECCtext = ECCtext[51];
                    if (rds.ECC == 226) rds.ECCtext = ECCtext[52];
                    if (rds.ECC == 227) rds.ECCtext = ECCtext[53];
                    if (rds.ECC == 228) rds.ECCtext = ECCtext[64];
                    if (rds.ECC == 240) rds.ECCtext = ECCtext[98];
                    if (rds.ECC == 241) rds.ECCtext = ECCtext[199];
                    if (rds.ECC == 242) rds.ECCtext = ECCtext[208];
                    if (rds.ECC == 243) rds.ECCtext = ECCtext[205];
                    break;
                  }

                case 'F': {
                    if (rds.ECC == 161) rds.ECCtext = ECCtext[149];
                    if (rds.ECC == 162) rds.ECCtext = ECCtext[222];
                    if (rds.ECC == 163) rds.ECCtext = ECCtext[153];
                    if (rds.ECC == 164) rds.ECCtext = ECCtext[176];
                    if (rds.ECC == 165) rds.ECCtext = ECCtext[158];
                    if (rds.ECC == 166) rds.ECCtext = ECCtext[168];
                    if (rds.ECC == 208) rds.ECCtext = ECCtext[67];
                    if (rds.ECC == 209) rds.ECCtext = ECCtext[75];
                    if (rds.ECC == 210) rds.ECCtext = ECCtext[114];
                    if (rds.ECC == 224) rds.ECCtext = ECCtext[54];
                    if (rds.ECC == 225) rds.ECCtext = ECCtext[55];
                    if (rds.ECC == 226) rds.ECCtext = ECCtext[56];
                    if (rds.ECC == 227) rds.ECCtext = ECCtext[57];
                    if (rds.ECC == 228) rds.ECCtext = ECCtext[58];
                    if (rds.ECC == 240) rds.ECCtext = ECCtext[202];
                    if (rds.ECC == 241) rds.ECCtext = ECCtext[192];
                    if (rds.ECC == 242) rds.ECCtext = ECCtext[220];
                    if (rds.ECC == 243) rds.ECCtext = ECCtext[71];
                    break;
                  }
                default: {
                    rds.ECCtext = "";
                    break;
                  }
              }
            }

            if (((rds.rdsC >> 12) & 0x07) == 3 && rdsblock == RDS_GROUP_1A) {                   // LIC code readout
              rds.LIC = rds.rdsC & 0xff;
              rds.hasLIC = true;
              if (rds.LIC > 0 && rds.LIC < 128) rds.LICtext = LICtext[rds.LIC]; else rds.LICtext = "";
            }
          }

          if (rds.rdsC >> 12 == 1 && rdsblock == RDS_GROUP_1A) rds.hasTMC = true;               // TMC flag

          if (!rdsDerrorThreshold) {
            if (rds.rdsD != 0) {                                                                // PIN decoder
              if ((rds.rdsD & 0x3f) < 61 && ((rds.rdsD >> 6) & 0x1f) < 24) {
                rds.hasPIN = true;
                rds.pinMin = rds.rdsD & 0x3f;
                rds.pinHour = rds.rdsD >> 6 & 0x1f;
                rds.pinDay = rds.rdsD >> 11 & 0x1f;
              }
            }
          }
        } break;

      case RDS_GROUP_2A: {
          if (showrdserrors == 3 || (!rdsBerrorThreshold && !rdsCerrorThreshold && !rdsDerrorThreshold)) {
            // RT decoder (64 characters)
            rds.hasRT = true;
            rds.rtAB = (bitRead(rds.rdsB, 4));                                                  // Get AB flag

            if (initab) {
              rtABold = rds.rtAB;
              initab = false;
            }

            byte endmarkerRT64 = 64;
            for (byte i = 0; i < endmarkerRT64; i++) {
              if (rt_buffer[i] == 0x0d) {
                endmarkerRT64 = i;
                break;
              }
            }

            if (rds.rtAB != rtABold) {                                                          // Erase old RT, because of AB change
              initrt = false;
              if (rds.rtbuffer) {
                char rt_buffer_temp[129];
                bool found = false;
                strcpy(rt_buffer_temp, rt_buffer);

                for (int i = 0; i < 129; i++) {
                  if (rt_buffer_temp[i] == 0x0D) {
                    found = true;
                  }
                  if (found) {
                    rt_buffer_temp[i] = '\0';
                  }
                }

                wchar_t RTtext[65] = L"";                                                         // Create 16 bit char buffer for Extended ASCII
                RDScharConverter(rt_buffer_temp, RTtext, sizeof(RTtext) / sizeof(wchar_t), true); // Convert 8 bit ASCII to 16 bit ASCII
                rds.stationText = convertToUTF8(RTtext);                                          // Convert RDS characterset to ASCII
                rds.stationText = extractUTF8Substring(rds.stationText, 0, endmarkerRT64, true);  // Make sure RT does not exceed 64 characters
                rds.stationText = trimTrailingSpaces(rds.stationText);                            // Trim empty spaces at the end
              }

              for (byte i = 0; i < 64; i++) {
                rt_buffer[i] = 0x20;
              }
              rt_buffer[64] = '\0';
              rtABold = rds.rtAB;
            }

            offset = (rds.rdsB & 0xf) * 4;                                                      // Get RT character segment
            rt_buffer[offset + 0] = rds.rdsC >> 8;                                              // First character of segment
            rt_buffer[offset + 1] = rds.rdsC & 0xff;                                            // Second character of segment
            rt_buffer[offset + 2] = rds.rdsD >> 8;                                              // Thirth character of segment
            rt_buffer[offset + 3] = rds.rdsD & 0xff;                                            // Fourth character of segment


            if (initrt || !rds.rtbuffer) {
              char rt_buffer_temp[129];
              bool found = false;
              strcpy(rt_buffer_temp, rt_buffer);

              for (int i = 0; i < 129; i++) {
                if (rt_buffer_temp[i] == 0x0D) {
                  found = true;
                }
                if (found) {
                  rt_buffer_temp[i] = '\0';
                }
              }

              wchar_t RTtext[65] = L"";                                                         // Create 16 bit char buffer for Extended ASCII
              RDScharConverter(rt_buffer_temp, RTtext, sizeof(RTtext) / sizeof(wchar_t), true); // Convert 8 bit ASCII to 16 bit ASCII
              rds.stationText = convertToUTF8(RTtext);                                          // Convert RDS characterset to ASCII
              rds.stationText = extractUTF8Substring(rds.stationText, 0, endmarkerRT64, true);  // Make sure RT does not exceed 64 characters
              rds.stationText = trimTrailingSpaces(rds.stationText);                            // Trim empty spaces at the end
            }

            for (int i = 0; i < 64; i++) rt_buffer2[i] = rt_buffer[i];
          }
        } break;

      case RDS_GROUP_2B: {
          if (showrdserrors == 3 || (!rdsBerrorThreshold && !rdsDerrorThreshold)) {
            // RT decoder (32 characters)
            rds.hasRT = true;
            rds.rtAB32 = (bitRead(rds.rdsB, 4));                                                // Get AB flag

            if (rds.rtAB32 != rtAB32old) {                                                      // Erase old RT, because of AB change
              for (byte i = 0; i < 33; i++) {
                rt_buffer32[i] = 0x20;
              }
              rt_buffer32[32] = '\0';
              rtAB32old = rds.rtAB32;
            }

            offset = (rds.rdsB & 0xf) * 2;                                                      // Get RT character segment
            rt_buffer32[offset + 0] = rds.rdsD >> 8;                                            // First character of segment
            rt_buffer32[offset + 1] = rds.rdsD & 0xff;                                          // Second character of segment

            byte endmarkerRT32 = 32;
            for (byte i = 0; i < endmarkerRT32; i++) {
              if (rt_buffer[i] == 0x0d) {
                endmarkerRT32 = i;
                break;
              }
            }

            char rt_buffer_temp[129];
            bool found = false;
            strcpy(rt_buffer_temp, rt_buffer32);

            for (int i = 0; i < 129; i++) {
              if (rt_buffer_temp[i] == 0x0D) {
                found = true;
              }
              if (found) {
                rt_buffer_temp[i] = '\0';
              }
            }

            wchar_t RTtext[33] = L"";                                                           // Create 16 bit char buffer for Extended ASCII
            RDScharConverter(rt_buffer_temp, RTtext, sizeof(RTtext) / sizeof(wchar_t), true);   // Convert 8 bit ASCII to 16 bit ASCII
            rds.stationText32 = convertToUTF8(RTtext);                                          // Convert RDS characterset to ASCII
            rds.stationText32 = extractUTF8Substring(rds.stationText32, 0, endmarkerRT32, true);// Make sure RT does not exceed 32 characters
            rds.stationText = trimTrailingSpaces(rds.stationText);                              // Trim empty spaces at the end
          }
        } break;

      case RDS_GROUP_3A: {
          if (!rdsDerrorThreshold) {
            if (rds.rdsD != 0) rds.hasAID = true;

            bool isValuePresent = false;
            for (int i = 0; i < 10; i++) {
              if (rds.aid[i] == rds.rdsD) {
                isValuePresent = true;
                break;
              }
            }

            if (!isValuePresent) {
              rds.aid[rds.aid_counter] = rds.rdsD;
              rds.aid_counter++;
            }

            if (rds.rdsD == 0xCD46) {                                                           // Check for TMC application
              rds.hasTMC = true;                                                                // TMC flag
            }

            // RT+ init
            if (rds.rdsD == 0x4BD7) {                                                           // Check for RT+ application
              rds.hasRDSplus = true;                                                            // Set flag
              rtplusblock = ((rds.rdsB & 0x1F) >> 1) * 2;                                       // Get RT+ Block
            }

            if (rds.rdsD == 0x0093) {                                                           // Check for DAB+ AF application
              rds.hasDABAF = true;                                                              // Set flag
              DABAFblock = ((rds.rdsB & 0x1F) >> 1) * 2;                                        // Get DAB AF Block
            }

            if (rds.rdsD == 0x6552) {                                                           // Check for Enhanced RT application
              _hasEnhancedRT = true;                                                            // Set flag
              eRTblock = ((rds.rdsB & 0x1F) >> 1) * 2;                                          // Get eRT block
              eRTcoding = bitRead(rds.rdsC, 0);                                                 // 0 = UCS-2, 1 = UTF-8
            }
          }
        } break;

      case RDS_GROUP_4A: {
          if (!rdsBerrorThreshold && !rdsCerrorThreshold && !rdsDerrorThreshold) {
            // CT
            uint32_t mjd;
            mjd = (rds.rdsB & 0x03);
            mjd <<= 15;
            mjd += ((rds.rdsC >> 1) & 0x7FFF);
            uint16_t hour, minute, day, month, year;
            int32_t timeoffset;

            long J, C, Y, M;
            J = mjd + 2400001 +  68569;
            C = 4 * J / 146097;
            J = J - (146097 * C + 3) / 4;
            Y = 4000 * (J + 1) / 1461001;
            J = J - 1461 * Y / 4 + 31;
            M = 80 * (J + 0) / 2447;

            if ((J - 2447 * M / 80) < 32) day = J - 2447 * M / 80;
            J = M / 11;

            if ((M +  2 - (12 * J)) < 13) month = M +  2 - (12 * J);
            if ((100 * (C - 49) + Y + J) > 2022) year = 100 * (C - 49) + Y + J;

            hour = ((rds.rdsD >> 12) & 0x000f);
            hour += ((rds.rdsC << 4) & 0x0010);
            timeoffset = rds.rdsD & 0x001f;
            if (bitRead(rds.rdsD, 5)) timeoffset *= -1;
            timeoffset *= 1800;
            minute = (rds.rdsD & 0x0fc0) >> 6;
            if (year < 2024 || hour > 23 || minute > 59 || timeoffset > 55800 || timeoffset < -55800) break;

            struct tm tm;
            tm.tm_year = year - 1900;
            tm.tm_mon = month - 1;
            tm.tm_mday = day;
            tm.tm_hour = hour;
            tm.tm_min = minute;
            tm.tm_sec = 0;
            tm.tm_isdst = -1;
            time_t rdstime = mktime(&tm);
            if (lastrdstime == 0) {
              lastrdstime = rdstime;
              lasttimeoffset = timeoffset;
            }
            if (rdstime == lastrdstime + 60 && timeoffset == lasttimeoffset) {
              rds.hasCT = true;
              rds.time = rdstime;
              rds.offset = timeoffset;
            } else {
              rds.hasCT = false;
            }
            lastrdstime = rdstime;
            lasttimeoffset = timeoffset;
          }
        } break;

      case RDS_GROUP_10A: {
          if (!rdsCerrorThreshold && !rdsDerrorThreshold) {
            // PTYN
            offset = bitRead(rds.rdsB, 0);                                                        // Get char offset
            if (rds.rdsC != 0 && rds.rdsD != 0) {
              ptyn_buffer[(offset * 4) + 0] = rds.rdsC >> 8;                                      // Get position 1 and 5
              ptyn_buffer[(offset * 4) + 1] = rds.rdsC & 0xFF;                                    // Get position 2 and 6
              ptyn_buffer[(offset * 4) + 2] = rds.rdsD >> 8;                                      // Get position 3 and 7
              ptyn_buffer[(offset * 4) + 3] = rds.rdsD & 0xFF;                                    // Get position 4 and 8
              for (byte i = 0; i < 8; i++) PTYNtext[i] = L'\0';
              RDScharConverter(ptyn_buffer, PTYNtext, sizeof(PTYNtext) / sizeof(wchar_t), false); // Convert 8 bit ASCII to 16 bit ASCII
              String utf8String = convertToUTF8(PTYNtext);                                        // Convert RDS characterset to ASCII
              rds.PTYN = extractUTF8Substring(utf8String, 0, 8, false);                           // Make sure text is not longer than 8 chars
              rds.hasPTYN = true;
            }
          }
        } break;

      case RDS_GROUP_5A:
      case RDS_GROUP_6A:
      case RDS_GROUP_7A:
      case RDS_GROUP_8A:
      case RDS_GROUP_9A:
      case RDS_GROUP_11A:
      case RDS_GROUP_12A:
      case RDS_GROUP_13A:   {
          // RT+ decoding
          if ((!rdsBerrorThreshold && !rdsCerrorThreshold && !rdsDerrorThreshold) && rtplusblock == rdsblock && rds.hasRDSplus) {
            rds.rdsplusTag1 = ((rds.rdsB & 0x07) << 3) + (rds.rdsC >> 13);                      // Are we in the right RT+ block and is all ok to go?
            rds.rdsplusTag2 = ((rds.rdsC & 0x01) << 5) + (rds.rdsD >> 11);
            uint16_t start_marker_1 = (rds.rdsC >> 7) & 0x3F;
            uint16_t length_marker_1 = (rds.rdsC >> 1) & 0x3F;
            uint16_t start_marker_2 = (rds.rdsD >> 5) & 0x3F;
            uint16_t length_marker_2 = (rds.rdsD & 0x1F);
            togglebit = bitRead(lowByte(rds.rdsB), 4);
            runningbit = bitRead(lowByte(rds.rdsB), 3);

            switch (rds.rdsplusTag1) {
              case 0: rds.rdsplusTag1 = 169; break;
              case 1 ... 53: rds.rdsplusTag1 += 111; break;
              case 59 ... 63: rds.rdsplusTag1 += 105; break;
              default: rds.rdsplusTag1 = 169; break;
            }

            switch (rds.rdsplusTag2) {
              case 0: rds.rdsplusTag2 = 169; break;
              case 1 ... 53: rds.rdsplusTag2 += 111; break;
              case 59 ... 63: rds.rdsplusTag2 += 105; break;
              default: rds.rdsplusTag2 = 169; break;
            }

            if (togglebit) {
              for (int i = 0; i < 44; i++) {
                RDSplus1[i] = 0x20;
                RDSplus2[i] = 0x20;
              }
              RDSplus1[44] = 0;
              RDSplus2[44] = 0;
            }

            if (rds.rtAB == rtABold) {
              for (int i = 0; i <= length_marker_1; i++)RDSplus1[i] = rt_buffer2[i + start_marker_1];
              RDSplus1[length_marker_1 + 1] = 0;

              for (int i = 0; i <= length_marker_2; i++)RDSplus2[i] = rt_buffer2[i + start_marker_2];
              RDSplus2[length_marker_2 + 1] = 0;
            }

            wchar_t RTtext1[45] = L"";                                                          // Create 16 bit char buffer for Extended ASCII
            RDScharConverter(RDSplus1, RTtext1, sizeof(RTtext1) / sizeof(wchar_t), false);      // Convert 8 bit ASCII to 16 bit ASCII
            rds.RTContent1 = convertToUTF8(RTtext1);                                            // Convert RDS characterset to ASCII
            rds.RTContent1 = extractUTF8Substring(rds.RTContent1, 0, 44, false);                // Make sure RT does not exceed 32 characters

            wchar_t RTtext2[45] = L"";                                                          // Create 16 bit char buffer for Extended ASCII
            RDScharConverter(RDSplus2, RTtext2, sizeof(RTtext2) / sizeof(wchar_t), false);      // Convert 8 bit ASCII to 16 bit ASCII
            rds.RTContent2 = convertToUTF8(RTtext2);                                            // Convert RDS characterset to ASCII
            rds.RTContent2 = extractUTF8Substring(rds.RTContent2, 0, 44, false);                // Make sure RT does not exceed 32 characters
          }

          // eRT decoding
          if ((!rdsBerrorThreshold && !rdsCerrorThreshold && !rdsDerrorThreshold) && eRTblock == rdsblock && _hasEnhancedRT) {
            offset = (rds.rdsB & 0x1f) * 4;
            eRT_buffer[offset + 0] = rds.rdsC >> 8;                                             // First character of segment
            eRT_buffer[offset + 1] = rds.rdsC & 0xff;                                           // Second character of segment
            eRT_buffer[offset + 2] = rds.rdsD >> 8;                                             // Thirth character of segment
            eRT_buffer[offset + 3] = rds.rdsD & 0xff;                                           // Fourth character of segment
            eRT_buffer[127] = '\0';

            byte endmarkereRT = 127;
            bool foundendmarker = false;
            for (byte i = 0; i < endmarkereRT; i++) {
              if (eRT_buffer[i] == 0x0d) {
                foundendmarker = true;
                endmarkereRT = i;
                break;
              }
            }

            if (offset == 0 || foundendmarker) {
              if (eRTcoding) rds.enhancedRTtext = eRT_buffer; else rds.enhancedRTtext = ucs2ToUtf8(eRT_buffer); // Convert to UTF-8 or UCS-2
              rds.enhancedRTtext = trimTrailingSpaces(rds.enhancedRTtext);
              if (rds.enhancedRTtext.length() > 0) rds.hasEnhancedRT = true;
            }
          }


          if (!rdsBerrorThreshold && rdsblock == 16 && (bitRead(rds.rdsB, 15))) rds.hasTMC = true;  // TMC flag

          if ((!rdsBerrorThreshold && !rdsCerrorThreshold && !rdsDerrorThreshold) && DABAFblock == rdsblock && rds.hasDABAF) {
            rds.dabaffreq = (rds.rdsC * 16);

            for (size_t i = 0; i < sizeof(DABfrequencyTable) / sizeof(DABfrequencyTable[0]); ++i) {
              if (DABfrequencyTable[i].frequency == rds.dabaffreq) strcpy(rds.dabafchannel, DABfrequencyTable[i].label);
            }

            rds.dabafeid[0] = (rds.rdsD >> 12) & 0xF;
            rds.dabafeid[1] = (rds.rdsD >> 8) & 0xF;
            rds.dabafeid[2] = (rds.rdsD >> 4) & 0xF;
            rds.dabafeid[3] = rds.rdsD & 0xF;
            for (int i = 0; i < 4; i++) {
              if (rds.dabafeid[i] < 10) {
                rds.dabafeid[i] += '0';                                                         // Add ASCII offset for decimal digits
              } else {
                rds.dabafeid[i] += 'A' - 10;                                                    // Add ASCII offset for hexadecimal letters A-F
              }
            }
            rds.dabafeid[4] = 0;
          }
        }
        break;

      case RDS_GROUP_14A: {
          // EON
          if (!rdsAerrorThreshold && !rdsBerrorThreshold && !rdsCerrorThreshold && !rdsDerrorThreshold) {
            rds.hasEON = true;                                                                  // Group is there, so we have EON

            bool isValuePresent = false;
            int eonIndex = -1;
            int i = 0;
            for (; i < 20; i++) {
              if (eon[i].pi == rds.rdsD || rds.rdsA == rds.rdsD) {                              // Check if EON is already in array
                isValuePresent = true;
                eonIndex = i;
                break;
              }
            }

            if (!isValuePresent) {
              eon[eon_counter].picode[0] = (rds.rdsD >> 12) & 0xF;
              eon[eon_counter].picode[1] = (rds.rdsD >> 8) & 0xF;
              eon[eon_counter].picode[2] = (rds.rdsD >> 4) & 0xF;
              eon[eon_counter].picode[3] = rds.rdsD & 0xF;
              for (int j = 0; j < 4; j++) {
                if (eon[eon_counter].picode[j] < 10) {
                  eon[eon_counter].picode[j] += '0';                                            // Add ASCII offset for decimal digits
                } else {
                  eon[eon_counter].picode[j] += 'A' - 10;                                       // Add ASCII offset for hexadecimal letters A-F
                }
              }

              eon[eon_counter].pi = rds.rdsD;                                                   // Store PI on next array
              if (eon_counter < 20) eon_counter++;
              eonIndex = eon_counter - 1;
            } else {
              eonIndex = i;
            }

            offset = rds.rdsB & 0x0F;  // Read offset

            if (offset < 4 && eon[eonIndex].pi == rds.rdsD) {
              eon_buffer[eonIndex][(offset * 2)  + 0] = rds.rdsC >> 8;                          // First character of segment
              eon_buffer[eonIndex][(offset * 2)  + 1] = rds.rdsC & 0xFF;                        // Second character of segment
            }

            if (eon[eonIndex].pi == rds.rdsD) {                                                                                   // Last chars are received
              RDScharConverter(eon_buffer[eonIndex], EONPStext[eonIndex], sizeof(EONPStext[eonIndex]) / sizeof(wchar_t), false);  // Convert 8 bit ASCII to 16 bit ASCII
              String utf8String = convertToUTF8(EONPStext[eonIndex]);                                                             // Convert RDS characterset to ASCII
              eon[eonIndex].ps = extractUTF8Substring(utf8String, 0, 8, false);                                                   // Make sure PS does not exceed 8 characters
            }

            if (offset == 13 && eon[eonIndex].pi == rds.rdsD) {
              eon[eonIndex].taset = true;
              eon[eonIndex].ta = bitRead(rds.rdsC, 0);
              eon[eonIndex].pty = (rds.rdsC >> 11) & 0xF;
            }

            if (bitRead(rds.rdsB, 4) && eon[eonIndex].pi == rds.rdsD) eon[eonIndex].tp = true;

            if (offset > 4 && offset < 9 && eon[eonIndex].pi == rds.rdsD) {                                                       // Check if mapped frequency belongs to current frequency
              if (((rds.rdsC >> 8) * 10 + 8750) == currentfreq && (rds.rdsC >> 8) > 0 && (rds.rdsC >> 8) < 205) {
                if (eon[eonIndex].mappedfreq == 0) {
                  eon[eonIndex].mappedfreq = ((rds.rdsC & 0xFF) * 10 + 8750);                                                     // Add mapped frequency to array
                } else if (eon[eonIndex].mappedfreq2 == 0 && eon[eonIndex].mappedfreq != ((rds.rdsC & 0xFF) * 10 + 8750) && (rds.rdsC >> 8) > 0 && (rds.rdsC >> 8) < 205) {
                  eon[eonIndex].mappedfreq2 = ((rds.rdsC & 0xFF) * 10 + 8750);
                } else if (eon[eonIndex].mappedfreq3 == 0 && eon[eonIndex].mappedfreq2 != ((rds.rdsC & 0xFF) * 10 + 8750) && eon[eonIndex].mappedfreq != ((rds.rdsC & 0xFF) * 10 + 8750) && (rds.rdsC >> 8) > 0 && (rds.rdsC >> 8) < 205) {
                  eon[eonIndex].mappedfreq3 = ((rds.rdsC & 0xFF) * 10 + 8750);
                }
              }
            }

            for (int i = 0; i < 20; i++) {
              for (int j = 0; j < 20 - i - 1; j++) {
                if (eon[j].pi == 0) continue;

                if (eon[j].pi > eon[j + 1].pi && eon[j + 1].pi != 0) {
                  std::swap(eon[j].pi, eon[j + 1].pi);
                  std::swap(eon[j].mappedfreq, eon[j + 1].mappedfreq);
                  std::swap(eon[j].mappedfreq2, eon[j + 1].mappedfreq2);
                  std::swap(eon[j].mappedfreq3, eon[j + 1].mappedfreq3);
                  char temp6[6];
                  strncpy(temp6, eon[j].picode, sizeof(temp6) - 1);
                  temp6[sizeof(temp6) - 1] = '\0';
                  strncpy(eon[j].picode, eon[j + 1].picode, sizeof(eon[j].picode) - 1);
                  eon[j].picode[sizeof(eon[j].picode) - 1] = '\0';
                  strncpy(eon[j + 1].picode, temp6, sizeof(eon[j + 1].picode) - 1);
                  eon[j + 1].picode[sizeof(eon[j + 1].picode) - 1] = '\0';
                  std::swap(eon[j].pty, eon[j + 1].pty);
                  std::swap(eon[j].ps, eon[j + 1].ps);
                  std::swap(eon[j].ta, eon[j + 1].ta);
                  std::swap(eon[j].tp, eon[j + 1].tp);
                  std::swap(eon[j].taset, eon[j + 1].taset);
                  std::swap(eon_buffer[j], eon_buffer[j + 1]);
                  std::swap(EONPStext[j], EONPStext[j + 1]);
                }
              }
            }
          }
        }
        break;

      case RDS_GROUP_15A: {
          if (showrdserrors == 3 || (!rdsBerrorThreshold && !rdsCerrorThreshold && !rdsDerrorThreshold)) {
            if (pslong_process && rds.stationNameLong.length() > 0) rds.hasLongPS = true;
            offset = (rds.rdsB & 0xf) * 4;                                                                // Get Long PS character segment

            pslong_buffer2[offset + 0] = pslong_buffer[offset + 0];                                       // Copy PS long buffer
            pslong_buffer2[offset + 1] = pslong_buffer[offset + 1];
            pslong_buffer2[offset + 2] = pslong_buffer[offset + 2];
            pslong_buffer2[offset + 3] = pslong_buffer[offset + 3];
            pslong_buffer2[32] = '\0';

            pslong_buffer[offset + 0] = rds.rdsC >> 8;                                                    // First character of segment
            pslong_buffer[offset + 1] = rds.rdsC & 0xff;                                                  // Second character of segment
            pslong_buffer[offset + 2] = rds.rdsD >> 8;                                                    // Thirth character of segment
            pslong_buffer[offset + 3] = rds.rdsD & 0xff;                                                  // Fourth character of segment
            pslong_buffer[32] = '\0';

            byte endmarkerLPS = 32;
            bool foundendmarker = false;
            for (byte i = 0; i < endmarkerLPS; i++) {
              if (pslong_buffer[i] == 0x0d) {
                foundendmarker = true;
                endmarkerLPS = i;
                break;
              }
            }

            if ((offset == 0 || foundendmarker) && (pslong_process || !rds.fastps)) {                     // Last chars are received
              if (strcmp(pslong_buffer, pslong_buffer2) == 0) {                                           // When no difference between current and buffer, let's go...
                pslong_process = true;
                PSLongtext = pslong_buffer;
                rds.stationNameLong = extractUTF8Substring(pslong_buffer, 0, endmarkerLPS, true);         // Make sure PS Long does not exceed 32 characters
                rds.stationNameLong = trimTrailingSpaces(rds.stationNameLong);
              }
            }

            if (!pslong_process && rds.fastps) {                                                          // Let's get 2 runs of 32 PS characters fast and without refresh
              if (offset == 0) packet0long = true;
              if (offset == 4) packet1long = true;
              if (offset == 8) packet2long = true;
              if (offset == 16) packet3long = true;
              PSLongtext = pslong_buffer;
              rds.stationNameLong = extractUTF8Substring(pslong_buffer, 0, endmarkerLPS, true);
              rds.stationNameLong = trimTrailingSpaces(rds.stationNameLong);
              if ((packet0long && packet1long && packet2long && packet3long) || foundendmarker) pslong_process = true;        // OK, we had one runs, now let's go the idle PS Long writing
            }
          }
        }
        break;
    }
    previous_rdsA = rds.rdsA;
    previous_rdsB = rds.rdsB;
    previous_rdsC = rds.rdsC;
    previous_rdsD = rds.rdsD;
  }
}

void TEF6686::clearRDS (bool fullsearchrds) {
  devTEF_Radio_Set_RDS(fullsearchrds);
  rds.piBuffer.clear();
  rds.stationName = "";
  rds.stationText = "";
  rds.stationNameLong = "";
  rds.stationText32 = "";
  rds.RTContent1 = "";
  rds.RTContent2 = "";
  rds.PTYN = "";
  rds.ECCtext = "";
  rds.LICtext = "";
  rds.stationIDtext = "";
  rds.stationStatetext = "";
  rds.enhancedRTtext = "";
  PSLongtext = "";

  uint8_t i;
  for (i = 0; i < 8; i++) {
    ps_buffer[i] = 0x20;
    PStext[i] = L'\0';
    ptyn_buffer[i] = 0x20;
    PTYNtext[i] = L'\0';
  }
  ps_buffer[8] = 0;
  ptyn_buffer[8] = 0;
  PStext[8] = L'\0';
  PTYNtext[8] = L'\0';

  for (i = 0; i < 64; i++) rt_buffer[i] = 0x20;
  rt_buffer[64] = 0;

  for (i = 0; i < 128; i++) eRT_buffer[i] = 0x20;
  eRT_buffer[128] = '\0';

  for (i = 0; i < 32; i++) {
    rt_buffer32[i] = 0x20;
    pslong_buffer[i] = 0x20;
    pslong_buffer2[i] = 0x20;
    //    PSLongtext[i] = L'\0';
  }
  rt_buffer32[32] = 0;
  pslong_buffer[32] = 0;
  //  PSLongtext[32] = L'\0';

  for (i = 0; i < 17; i++) rds.stationType[i] = 0x20;
  rds.stationType[17] = 0;

  for (i = 0; i < 6; i++) rds.picode[i] = 0x20;
  rds.picode[6] = 0;

  for (i = 0; i < 4; i++) rds.dabafeid[i] = 0x20;
  rds.dabafeid[4] = 0;

  for (i = 0; i < 3; i++) rds.dabafchannel[i] = 0x20;
  rds.dabafchannel[3] = 0;

  for (i = 0; i < 8; i++) rds.stationID[i] = 0x20;
  rds.stationID[8] = 0;

  for (i = 0; i < 2; i++) rds.stationState[i] = 0x20;
  rds.stationState[2] = 0;

  for (i = 0; i < 50; i++) {
    af[i].frequency = 0;
    af[i].score = -32767;
    af[i].afvalid = true;
    af[i].checked = false;
    af[i].regional = false;
    af[i].same = false;
  }

  for (i = 0; i < 20; i++) {
    eon[i].pty = 254;
    eon[i].pi = 0;
    eon[i].ps = "";
    eon[i].mappedfreq = 0;
    eon[i].mappedfreq2 = 0;
    eon[i].mappedfreq3 = 0;
    eon[i].ta = false;
    eon[i].tp = false;
    eon[i].taset = false;
    for (int y = 0; y < 5; y++) {
      eon[i].picode[y] = '\0';
    }
    for (int j = 0; j < 9; j++) {
      EONPStext[i][j] = L'\0';
      eon_buffer[i][j] = '\0';
    }
  }

  for (i = 0; i < 45; i++) {
    RDSplus1[i] = 0;
    RDSplus2[i] = 0;
  }

  for (i = 0; i < 10; i++) rds.aid[i] = 0;

  rdsblock = 254;
  piold = 0;
  rds.correctPI = 0;
  rds.ECC = 254;
  rds.LIC = 254;
  rds.pinHour = 0;
  rds.pinMin = 0;
  rds.pinDay = 0;
  rds.stationTypeCode = 32;
  rds.dabaffreq = 0;
  rds.hasPIN = false;
  rds.hasECC = false;
  rds.hasLIC = false;
  rds.hasRT = false;
  rds.hasRDS = false;
  rds.hasTP = false;
  rds.hasAF = false;
  rds.hasTA = false;
  rds.hasEON = false;
  rds.hasCT = false;
  rds.hasTMC = false;
  rds.hasAID = false;
  rds.hasPTYN = false;
  rds.hasLongPS = false;
  rds.hasRDSplus = false;
  rds.hasDABAF = false;
  rds.hasEnhancedRT = false;
  rt_process = false;
  ps_process = false;
  pslong_process = false;
  rds.rdsreset = true;
  rds.hasArtificialhead = false;
  rds.hasCompressed = false;
  rds.hasDynamicPTY = false;
  rds.hasStereo = false;
  af_counter = 0;
  af_updatecounter = 0;
  eon_counter = 0;
  afreset = true;
  rds.MS = 0;
  rds.rdsAerror = true;
  rds.rdsBerror = true;
  rds.rdsCerror = true;
  rds.rdsDerror = true;
  initrt = true;
  initab = true;
  rds.rdsplusTag1 = 169;
  rds.rdsplusTag2 = 169;
  afinit = false;
  errorfreepi = false;
  afmethodB = false;
  packet0 = false;
  packet1 = false;
  packet2 = false;
  packet3 = false;
  packet0long = false;
  packet1long = false;
  packet2long = false;
  packet3long = false;
  rds.aid_counter = 0;
  afmethodBprobe = false;
  afmethodBtrigger = false;
  correctPIold = 0;
  af_number = 0;
  _hasEnhancedRT = false;
}

void TEF6686::tone(uint16_t time, int16_t amplitude, uint16_t frequency) {
  devTEF_Audio_Set_Mute(0);
  devTEF_Radio_Set_Wavegen(1, amplitude, frequency);
  delay (time);
  devTEF_Radio_Set_Wavegen(0, 0, 0);
}

void TEF6686::I2Sin(bool mode) {
  devTEF_Radio_Set_I2S_Input(mode);
}

String TEF6686::convertToUTF8(const wchar_t* input) {
  String output;
  while (*input) {
    uint32_t unicode = *input;
    if (unicode < 0x80) {
      output += (char)unicode;
    } else if (unicode < 0x800) {
      output += (char)(0xC0 | (unicode >> 6));
      output += (char)(0x80 | (unicode & 0x3F));
    } else if (unicode < 0x10000) {
      output += (char)(0xE0 | (unicode >> 12));
      output += (char)(0x80 | ((unicode >> 6) & 0x3F));
      output += (char)(0x80 | (unicode & 0x3F));
    } else {
      output += (char)(0xF0 | (unicode >> 18));
      output += (char)(0x80 | ((unicode >> 12) & 0x3F));
      output += (char)(0x80 | ((unicode >> 6) & 0x3F));
      output += (char)(0x80 | (unicode & 0x3F));
    }
    input++;
  }
  return output;
}

String TEF6686::extractUTF8Substring(const String & utf8String, size_t start, size_t length, bool under) {
  String substring;
  size_t utf8Length = utf8String.length();
  size_t utf8Index = 0;
  size_t charIndex = 0;

  while (utf8Index < utf8Length && charIndex < start + length) {
    uint8_t currentByte = utf8String.charAt(utf8Index);
    uint8_t numBytes = 0;

    if (currentByte < 0x80) {
      numBytes = 1;
    } else if ((currentByte >> 5) == 0x6) {
      numBytes = 2;
    } else if ((currentByte >> 4) == 0xE) {
      numBytes = 3;
    } else if ((currentByte >> 3) == 0x1E) {
      numBytes = 4;
    }

    if (charIndex >= start) {
      substring += utf8String.substring(utf8Index, utf8Index + numBytes);
    }

    utf8Index += numBytes;
    charIndex++;
  }

  if (under && underscore) {
    while (substring.length() < length) {
      substring += '_';
    }
  }

  return substring;
}


void TEF6686::RDScharConverter(const char* input, wchar_t* output, size_t size, bool under) {
  for (size_t i = 0; i < size - 1; i++) {
    char currentChar = input[i];
    switch (currentChar) {
      case 0x0A: if (under && underscore) output[i] = L'_'; else output[i] = L' '; break;
      case 0x20: if (under && underscore) output[i] = L'_'; else output[i] = L' '; break;
      case 0x21 ... 0x5D: output[i] = static_cast<wchar_t>(currentChar); break;
      case 0x5E: output[i] = L'―'; break;
      case 0x5F: output[i] = L'_'; break;
      case 0x60: output[i] = L'`'; break;
      case 0x61 ... 0x7d: output[i] = static_cast<wchar_t>(currentChar); break;
      case 0x7E: output[i] = L'¯'; break;
      case 0x7F: output[i] = L' '; break;
      case 0x80: output[i] = L'á'; break;
      case 0x81: output[i] = L'à'; break;
      case 0x82: output[i] = L'é'; break;
      case 0x83: output[i] = L'è'; break;
      case 0x84: output[i] = L'í'; break;
      case 0x85: output[i] = L'ì'; break;
      case 0x86: output[i] = L'ó'; break;
      case 0x87: output[i] = L'ò'; break;
      case 0x88: output[i] = L'ú'; break;
      case 0x89: output[i] = L'ù'; break;
      case 0x8A: output[i] = L'Ñ'; break;
      case 0x8B: output[i] = L'Ç'; break;
      case 0x8C: output[i] = L'Ş'; break;
      case 0x8D: output[i] = L'β'; break;
      case 0x8E: output[i] = L'¡'; break;
      case 0x8F: output[i] = L'Ĳ'; break;
      case 0x90: output[i] = L'â'; break;
      case 0x91: output[i] = L'ä'; break;
      case 0x92: output[i] = L'ê'; break;
      case 0x93: output[i] = L'ë'; break;
      case 0x94: output[i] = L'î'; break;
      case 0x95: output[i] = L'ï'; break;
      case 0x96: output[i] = L'ô'; break;
      case 0x97: output[i] = L'ö'; break;
      case 0x98: output[i] = L'û'; break;
      case 0x99: output[i] = L'ü'; break;
      case 0x9A: output[i] = L'ñ'; break;
      case 0x9B: output[i] = L'ç'; break;
      case 0x9C: output[i] = L'ş'; break;
      case 0x9D: output[i] = L'ǧ'; break;
      case 0x9E: output[i] = L'ı'; break;
      case 0x9F: output[i] = L'ĳ'; break;
      case 0xA0: output[i] = L'ª'; break;
      case 0xA1: output[i] = L'α'; break;
      case 0xA2: output[i] = L'©'; break;
      case 0xA3: output[i] = L'‰'; break;
      case 0xA4: output[i] = L'Ǧ'; break;
      case 0xA5: output[i] = L'ě'; break;
      case 0xA6: output[i] = L'ň'; break;
      case 0xA7: output[i] = L'ő'; break;
      case 0xA8: output[i] = L'π'; break;
      case 0xA9: output[i] = L'€'; break;
      case 0xAA: output[i] = L'£'; break;
      case 0xAB: output[i] = L'$'; break;
      case 0xAC: output[i] = L'←'; break;
      case 0xAD: output[i] = L'↑'; break;
      case 0xAE: output[i] = L'→'; break;
      case 0xAF: output[i] = L'↓'; break;
      case 0xB0: output[i] = L'º'; break;
      case 0xB1: output[i] = L'¹'; break;
      case 0xB2: output[i] = L'²'; break;
      case 0xB3: output[i] = L'³'; break;
      case 0xB4: output[i] = L'±'; break;
      case 0xB5: output[i] = L'İ'; break;
      case 0xB6: output[i] = L'ń'; break;
      case 0xB7: output[i] = L'ű'; break;
      case 0xB8: output[i] = L'µ'; break;
      case 0xB9: output[i] = L'¿'; break;
      case 0xBA: output[i] = L'÷'; break;
      case 0xBB: output[i] = L'°'; break;
      case 0xBC: output[i] = L'¼'; break;
      case 0xBD: output[i] = L'½'; break;
      case 0xBE: output[i] = L'¾'; break;
      case 0xBF: output[i] = L'§'; break;
      case 0xC0: output[i] = L'Á'; break;
      case 0xC1: output[i] = L'À'; break;
      case 0xC2: output[i] = L'É'; break;
      case 0xC3: output[i] = L'È'; break;
      case 0xC4: output[i] = L'Í'; break;
      case 0xC5: output[i] = L'Ì'; break;
      case 0xC6: output[i] = L'Ó'; break;
      case 0xC7: output[i] = L'Ò'; break;
      case 0xC8: output[i] = L'Ú'; break;
      case 0xC9: output[i] = L'Ù'; break;
      case 0xCA: output[i] = L'Ř'; break;
      case 0xCB: output[i] = L'Č'; break;
      case 0xCC: output[i] = L'Š'; break;
      case 0xCD: output[i] = L'Ž'; break;
      case 0xCE: output[i] = L'Ð'; break;
      case 0xCF: output[i] = L'Ŀ'; break;
      case 0xD0: output[i] = L'Â'; break;
      case 0xD1: output[i] = L'Ä'; break;
      case 0xD2: output[i] = L'Ê'; break;
      case 0xD3: output[i] = L'Ë'; break;
      case 0xD4: output[i] = L'Î'; break;
      case 0xD5: output[i] = L'Ï'; break;
      case 0xD6: output[i] = L'Ô'; break;
      case 0xD7: output[i] = L'Ö'; break;
      case 0xD8: output[i] = L'Û'; break;
      case 0xD9: output[i] = L'Ü'; break;
      case 0xDA: output[i] = L'ř'; break;
      case 0xDB: output[i] = L'č'; break;
      case 0xDC: output[i] = L'š'; break;
      case 0xDD: output[i] = L'ž'; break;
      case 0xDE: output[i] = L'đ'; break;
      case 0xDF: output[i] = L'ŀ'; break;
      case 0xE0: output[i] = L'Ã'; break;
      case 0xE1: output[i] = L'Å'; break;
      case 0xE2: output[i] = L'Æ'; break;
      case 0xE3: output[i] = L'Œ'; break;
      case 0xE4: output[i] = L'ŷ'; break;
      case 0xE5: output[i] = L'Ý'; break;
      case 0xE6: output[i] = L'Õ'; break;
      case 0xE7: output[i] = L'Ø'; break;
      case 0xE8: output[i] = L'Þ'; break;
      case 0xE9: output[i] = L'Ŋ'; break;
      case 0xEA: output[i] = L'Ŕ'; break;
      case 0xEB: output[i] = L'Ć'; break;
      case 0xEC: output[i] = L'Ś'; break;
      case 0xED: output[i] = L'Ź'; break;
      case 0xEE: output[i] = L'Ŧ'; break;
      case 0xEF: output[i] = L'ð'; break;
      case 0xF0: output[i] = L'ã'; break;
      case 0xF1: output[i] = L'å'; break;
      case 0xF2: output[i] = L'æ'; break;
      case 0xF3: output[i] = L'œ'; break;
      case 0xF4: output[i] = L'ŵ'; break;
      case 0xF5: output[i] = L'ý'; break;
      case 0xF6: output[i] = L'õ'; break;
      case 0xF7: output[i] = L'ø'; break;
      case 0xF8: output[i] = L'þ'; break;
      case 0xF9: output[i] = L'ŋ'; break;
      case 0xFA: output[i] = L'ŕ'; break;
      case 0xFB: output[i] = L'ć'; break;
      case 0xFC: output[i] = L'ś'; break;
      case 0xFD: output[i] = L'ź'; break;
      case 0xFE: output[i] = L'ŧ'; break;
      case 0xFF: output[i] = L' '; break;
    }
  }
  output[size - 1] = L'\0';
}

String TEF6686::trimTrailingSpaces(String str) {
  int end = str.length() - 1;
  while (end >= 0 && isspace(str[end])) end--;
  return str.substring(0, end + 1);
}

String TEF6686::ucs2ToUtf8(const char* ucs2Input) {
  String utf8Output;

  size_t length = 0;
  while (ucs2Input[length] != '\0' || ucs2Input[length + 1] != '\0') {
    length += 2;
  }

  for (size_t i = 0; i < length; i += 2) {
    uint16_t ucs2Char = ((uint8_t)ucs2Input[i] << 8) | (uint8_t)ucs2Input[i + 1];

    if (ucs2Char <= 0x7F) {
      utf8Output += (char)ucs2Char;
    } else if (ucs2Char <= 0x7FF) {
      utf8Output += (char)(0xC0 | (ucs2Char >> 6));
      utf8Output += (char)(0x80 | (ucs2Char & 0x3F));
    } else {
      utf8Output += (char)(0xE0 | (ucs2Char >> 12));
      utf8Output += (char)(0x80 | ((ucs2Char >> 6) & 0x3F));
      utf8Output += (char)(0x80 | (ucs2Char & 0x3F));
    }
  }
  return utf8Output;
}