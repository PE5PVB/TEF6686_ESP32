#include "TEF6686.h"
#include <map>
#include <Arduino.h>


void TEF6686::init(byte TEF) {
  uint8_t bootstatus;
  Tuner_I2C_Init();
  devTEF_APPL_Get_Operation_Status(&bootstatus);
  if (bootstatus == 0) {
    Tuner_Patch(TEF);
    delay(50);
    if (digitalRead(15) == LOW) Tuner_Init9216(); else Tuner_Init4000();
    power(1);
    Tuner_Init();
  }
}

bool TEF6686::getIdentification(uint16_t &device, uint16_t &hw_version, uint16_t &sw_version) {
  bool result = devTEF_Radio_Get_Identification(&device, &hw_version, &sw_version);
  return device;
  return hw_version;
  return sw_version;
}

void TEF6686::power(bool mode) {
  devTEF_APPL_Set_OperationMode(mode);
  if (mode == 0) devTEF_Set_Cmd(TEF_FM, Cmd_Tune_To, 7, 1, 10000);
}

void TEF6686::SetFreq(uint16_t frequency) {
  devTEF_Radio_Tune_To(frequency);
}

void TEF6686::SetFreqAM(uint16_t frequency) {
  devTEF_Radio_Tune_AM (frequency);
}

void TEF6686::setOffset(int8_t offset) {
  devTEF_Radio_Set_LevelOffset(offset * 10);
}

void TEF6686::setFMBandw(uint16_t bandwidth) {
  devTEF_Radio_Set_Bandwidth(0, bandwidth * 10, 1000, 1000);
}

void TEF6686::setAMBandw(uint16_t bandwidth) {
  devTEF_Radio_Set_BandwidthAM(0, bandwidth * 10, 1000, 1000);
}

void TEF6686::setAMCoChannel(uint16_t start) {
  devTEF_Radio_Set_CoChannel_AM(start * 10);
}

void TEF6686::setSoftmuteAM(uint8_t mode) {
  devTEF_Radio_Set_Softmute_Max_AM(mode);
}

void TEF6686::setSoftmuteFM(uint8_t mode) {
  devTEF_Radio_Set_Softmute_Max_FM(mode);
}

void TEF6686::setAMNoiseBlanker(uint16_t start) {
  if (start == 0) devTEF_Radio_Set_Noiseblanker_AM(0, 1000); else devTEF_Radio_Set_Noiseblanker_AM(1, (start * 10) + 500);
}

void TEF6686::setAMAttenuation(uint16_t start) {
  devTEF_Radio_Set_Attenuator_AM(start * 10);
}

void TEF6686::setFMABandw() {
  devTEF_Radio_Set_Bandwidth(1, 3110, 1000, 1000);
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
  devTEF_Audio_Set_Mute(1);
}

void TEF6686::setUnMute() {
  mute = false;
  devTEF_Audio_Set_Mute(0);
}

void TEF6686::setAGC(uint8_t agc) {
  if (agc == 0) devTEF_Radio_Set_RFAGC(920);
  if (agc == 1) devTEF_Radio_Set_RFAGC(900);
  if (agc == 2) devTEF_Radio_Set_RFAGC(870);
  if (agc == 3) devTEF_Radio_Set_RFAGC(840);
}

void TEF6686::setDeemphasis(uint8_t timeconstant) {
  if (timeconstant == 1) devTEF_Radio_Set_Deemphasis(500);
  if (timeconstant == 2) devTEF_Radio_Set_Deemphasis(750);
  if (timeconstant == 3) devTEF_Radio_Set_Deemphasis(0);
}

void TEF6686::setAudio(uint8_t audio) {
  if (audio == 1) devTEF_Radio_Specials(0);
  if (audio == 2) devTEF_Radio_Specials(1);
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


void TEF6686::setNoiseBlanker(uint16_t start) {
  if (start == 0) devTEF_Radio_Set_NoisBlanker(0, 1000); else devTEF_Radio_Set_NoisBlanker(1, (start * 10) + 500);
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
  bool result = devTEF_Radio_Get_Processing_Status(&highcut, &stereo, &sthiblend, &stband_1, &stband_2, &stband_3, &stband_4);
  return highcut;
  return stereo;
  return sthiblend;
  return stband_1;
  return stband_2;
  return stband_3;
  return stband_4;
}

bool TEF6686::getStatus(int16_t &level, uint16_t &USN, uint16_t &WAM, int16_t &offset, uint16_t &bandwidth, uint16_t &modulation) {
  bool result = devTEF_Radio_Get_Quality_Status(&level, &USN, &WAM, &offset, &bandwidth, &modulation);
  return level;
  return USN;
  return WAM;
  return bandwidth;
  return modulation;
}

bool TEF6686::getStatusAM(int16_t &level, uint16_t &noise, uint16_t &cochannel, int16_t &offset, uint16_t &bandwidth, uint16_t &modulation) {
  bool result = devTEF_Radio_Get_Quality_Status_AM(&level, &noise, &cochannel, &offset, &bandwidth, &modulation);
  return level;
  return noise;
  return cochannel;
  return bandwidth;
  return modulation;
}

bool TEF6686::readRDS(bool showrdserrors)
{
  char  status;
  uint16_t rdsStat = 0, rdsErr = 65535, rdsErrA = 65535, rdsErrB = 65535, rdsErrC = 65535, rdsErrD = 65535;
  uint16_t result = devTEF_Radio_Get_RDS_Data(&rdsStat, &rds.rdsA, &rds.rdsB, &rds.rdsC, &rds.rdsD, &rdsErr);
  uint8_t rds_group;
  uint8_t offset;
  bool rdsErrCheck = false, rdsDataReady = false;

  rdsErrA = ((rdsErr >> 14) & 0x02);
  rdsErrB = ((rdsErr >> 12) & 0x02);
  rdsErrC = ((rdsErr >> 10) & 0x02);
  rdsErrD = ((rdsErr >>  8) & 0x02);

  rdsTimeOut += rdsErr == 0 && rds.rdsA != 0 ? -rdsTimeOut : rdsTimeOut < 32768  ? 1 : 0;
  rds.hasRDS  = rdsTimeOut < 32768 ? true : false;

  rdsErrCheck = rdsErr == 0;
  rdsDataReady = ((rdsStat & (1 << 15)) && (rdsStat & (1 << 9)));
  rds.errors = rdsErr;
  bool x;
  if (showrdserrors == false) x = rdsErrCheck; else x = true;
  if (rdsErrCheck) rds.correct = true; else rds.correct = false;

  if (rdsDataReady && x)
  {
    //PI
    if (rds.stationID == 0) rds.stationID = rds.rdsA;
    if (rds.region == 0) {
      char Hex[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
      rds.picode[0] = Hex[(rds.rdsA & 0xF000U) >> 12];
      rds.picode[1] = Hex[(rds.rdsA & 0x0F00U) >> 8];
      rds.picode[2] = Hex[(rds.rdsA & 0x00F0U) >> 4];
      rds.picode[3] = Hex[(rds.rdsA & 0x000FU)];
      rds.picode[4] = '\0';
    }
    if (rds.region == 1) {
      if (rds.stationID > 4096) {
        if (rds.stationID > 21671 && (rds.stationID & 0xF00U) >> 8 == 0) rds.stationID = ((uint16_t)uint8_t(0xA0 + ((rds.stationID & 0xF000U) >> 12)) << 8) + lowByte(rds.stationID); // C0DE -> ACDE
        if (rds.stationID > 21671 && lowByte(rds.stationID) == 0) rds.stationID = 0xAF00 + uint8_t(highByte(rds.stationID)); // CD00 -> AFCD
        if (rds.stationID < 39247) {
          if (rds.stationID > 21671) {
            rds.picode[0] = 'W';
            rds.stationID -= 21672;
          } else {
            rds.picode[0] = 'K';
            rds.stationID -= 4096;
          }
          rds.picode[1] = char(rds.stationID / 676 + 65);
          rds.picode[2] = char((rds.stationID - 676 * int(rds.stationID / 676)) / 26 + 65);
          rds.picode[3] = char(((rds.stationID - 676 * int(rds.stationID / 676)) % 26) + 65);
          rds.picode[4] = '\0';
        } else {
          rds.stationID -= 4835;
          rds.picode[0] = 'K';
          rds.picode[1] = char(rds.stationID / 676 + 65);
          rds.picode[2] = char((rds.stationID - 676 * int(rds.stationID / 676)) / 26 + 65);
          rds.picode[3] = char(((rds.stationID - 676 * int(rds.stationID / 676)) % 26) + 65);
          rds.picode[4] = '\0';
        }
      }
    }

    rds_group  = (rds.rdsB >> 11);
    if (rds.correctPI == false && rds.correct == true) rds.correctPI = true;
    switch (rds_group) {
      case RDS_GROUP_0A:
      case RDS_GROUP_0B: {
          //RDS Programm-Service
          offset = rds.rdsB & 0x03;
          if ((offset == 0) && (ps_process == 0)) ps_process = 1;

          if (ps_process == 1) {
            ps_buffer[(offset * 2)  + 0] = rds.rdsD >> 8;
            ps_buffer[(offset * 2)  + 1] = rds.rdsD & 0xFF;
            ps_buffer[(offset * 2)  + 2] = 0;
            ps_process = strlen(ps_buffer) == 8 ? 2 : 1;
          }

          if (ps_process == 2) {
            for (int i = 0; i < 9; i++) rds.PStext[i] = 0;
            rds.stationName = "";
            RDScharConverter(ps_buffer, rds.PStext, sizeof(rds.PStext) / sizeof(wchar_t));
            rds.stationName = convertToUTF8(rds.PStext);

            for (int i = 0; i < 9; i++) ps_buffer[i]  = '\0';
            ps_process = 0;
            rds.hasPS = true;
          }

          if (rds.correct) {
            //PTY
            rds.stationTypeCode = (rds.rdsB >> 5) & 0x1F;
            rds.hasPTY = true;
            if (rds.region == 0) strcpy(rds.stationType, PTY_EU[rds.stationTypeCode]);
            if (rds.region == 1) strcpy(rds.stationType, PTY_USA[rds.stationTypeCode]);

            //TP-TA-EON-MS
            if ((bitRead(rds.rdsB, 4)) == 1 && ((bitRead(rds.rdsB, 10)) == 0)) rds.hasEON = true; else rds.hasEON = false;
            if ((bitRead(rds.rdsB, 4)) == 0 && ((bitRead(rds.rdsB, 10)) == 1)) rds.hasTP = true; else rds.hasTP = false;
            rds.hasTA = (bitRead(rds.rdsB, 4)) && (bitRead(rds.rdsB, 10)) & 0x1F;
            if (((bitRead(rds.rdsB, 3)) & 0x1F) == 1) rds.MS = 1; else rds.MS = 2;

            //AF
            uint8_t  af_controlCode = rds.rdsC >> 8;
            if ((af_controlCode < 224) && (af_counter < 50))
            {
              uint16_t buffer0 = (rds.rdsC >> 8);
              uint16_t buffer1 = (rds.rdsC & 0xFF);
              rds.hasAF = true;
              if (buffer0 != 0 && buffer1 != 0)
              {
                buffer0 = buffer0 * 10 + 8750;
                buffer1 = buffer1 * 10 + 8750;
                bool isDouble = false;
                isDouble = checkDouble(buffer0);
                if (!isDouble && buffer0 != 0) {
                  af[af_counter].frequency = buffer0;
                  af_counter++;
                }

                isDouble = checkDouble(buffer1);
                if (!isDouble && buffer1 != 0) {
                  af[af_counter].frequency = buffer1;
                  af_counter++;
                }
              }
            }
          }
        } break;

      case RDS_GROUP_1A:
        if (rds.correct) if (rds.rdsC < 255) rds.ECC = rds.rdsC;
        break;

      case RDS_GROUP_2A:
      case RDS_GROUP_2B: {
          boolean limit_reached = false;
          rds.hasRT = true;
          offset = (rds.rdsB & 0xf) * 4;
          rds.rtAB = (bitRead(rds.rdsB, 4));
          limit_reached = (offset == 60 || (rds.rdsC >> 8) == '\r' || (rds.rdsC & 0xFF) == '\r' || (rds.rdsD >> 8) == '\r' || (rds.rdsD & 0xFF) == '\r')  ? true : false;
          rt_process = (rt_process == 0) && (offset == 0) ? 1 : rt_process;

          if (rds.rtAB != ABold) {
            offsetold = 0;
            rds.stationText = "";
            if (rt_timer == 64) {
              for (int i = 0; i < 65; i++) rds.RTtext[i] = 0;
              RDScharConverter(stationTextBuffer, rds.RTtext, sizeof(rds.RTtext) / sizeof(wchar_t));
              rds.stationText = convertToUTF8(rds.RTtext);
            }

            for (int i = 0; i < 65; i++) {
              rt_buffer[i]  = 0;
              stationTextBuffer[i] = 0;
            }
            if (rds.hasRDSplus == false) rt_process = 0;
          }
          ABold = rds.rtAB;

          if ((!limit_reached) && (offset - rds.stationTextOffset > 4) && (rt_process == 1))
          {
            rds.stationTextOffset = 0;
            rt_process = 0;
          }

          if (rt_process == 1)
          {
            rds.stationTextOffset = offset;
            rt_buffer[offset + 0] = rds.rdsC >> 8;
            rt_buffer[offset + 1] = rds.rdsC & 0xff;
            rt_buffer[offset + 2] = rds.rdsD >> 8;
            rt_buffer[offset + 3] = rds.rdsD & 0xff;
            if (offset > offsetold) offsetold = offset;

            if (offset == offsetold) {
              strcpy(stationTextBuffer, rt_buffer);
              for (int i = 0; i < 64; i++)  stationTextBuffer[i] = stationTextBuffer[i];
              if (rt_timer < 64) {
                rds.stationText = "";
                for (int i = 0; i < 65; i++) rds.RTtext[i] = 0;
                RDScharConverter(stationTextBuffer, rds.RTtext, sizeof(rds.RTtext) / sizeof(wchar_t));
                rds.stationText = convertToUTF8(rds.RTtext);
                rt_timer++;
              } else {
                rt_timer = 64;
              }
            }
          }

          rt_process = (rt_process == 1) && (strlen(rt_buffer)) && (limit_reached) ? 2 : rt_process;
          if ((rt_process == 2) && (strlen(rt_buffer) != 0))
          {
            for (int i = 0; i < 64; i++)
            {
              rt_buffer2[i]   = rt_buffer[i];
              rt_buffer[i]  = 0;
            }
          }
        } break;

      case RDS_GROUP_4A:
      case RDS_GROUP_4B: {
          if (rds.correct) {
            uint32_t mjd;
            rds.hasCT = true;
            mjd = (rds.rdsB & 0x03);
            mjd <<= 15;
            mjd += ((rds.rdsC >> 1) & 0x7FFF);

            long J, C, Y, M;
            uint8_t LocalOffset;
            J = mjd + 2400001 +  68569;
            C = 4 * J / 146097;
            J = J - (146097 * C + 3) / 4;
            Y = 4000 * (J + 1) / 1461001;
            J = J - 1461 * Y / 4 + 31;
            M = 80 * (J + 0) / 2447;

            rds.days = J - 2447 * M / 80;
            J = M / 11;

            rds.months = M +  2 - (12 * J);
            rds.years = 100 * (C - 49) + Y + J;
            rds.hours = ((rds.rdsD >> 12) & 0x0f);
            rds.hours += ((rds.rdsC <<  4) & 0x0010);
            rds.minutes = ((rds.rdsD >>  6) & 0x3f);
            rds.offsetplusmin = ((bitRead(rds.rdsD, 5)) & 0x3f);
            rds.offset = (rds.rdsD & 0x3f);
            rds.hasCT = true;
          }
        } break;

      case RDS_GROUP_10A:
      case RDS_GROUP_10B:
      case RDS_GROUP_11A:
      case RDS_GROUP_11B:
      case RDS_GROUP_12A:
      case RDS_GROUP_12B: {
          if (useRTPlus)
          {
            uint16_t  content_byte_1 = (rds.rdsB & 0x07);
            content_byte_1 = (content_byte_1  << 0x03);
            content_byte_1 += (rds.rdsC >> 0x0D);
            uint16_t  content_byte_2 = (rds.rdsC & 0x01);
            content_byte_2 = (content_byte_2 << 0x05);
            content_byte_2 += (rds.rdsD >> 0x0B);
            uint16_t  start_marker_1 = (rds.rdsC >> 0x07);
            start_marker_1 = (start_marker_1 & 0x3F);
            uint16_t length_marker_1 = (rds.rdsC >> 0x01);
            length_marker_1 = (length_marker_1  & 0x3F);
            uint16_t start_marker_2 = (rds.rdsD >> 0x05);
            start_marker_2 = (start_marker_2 & 0x3F);
            uint16_t length_marker_2 = (rds.rdsD & 0x1F);
            rds.hasRDSplus   = true;

            if (rt_process == 2)
            {
              if (content_byte_1 == 0x04) { //ArtistID
                rds.hasMusicArtist = true;
                for (int i = 0; i <= length_marker_1; i++)rds.musicArtist[i] = rt_buffer2[i + start_marker_1];
                rds.musicArtist[length_marker_1 + 1] = 0;
              }
              else if (content_byte_1 == 0x01) {//TitleID
                rds.hasMusicTitle = true;
                for (int i = 0; i <= length_marker_1; i++)rds.musicTitle[i] = rt_buffer2[i + start_marker_1];
                rds.musicTitle[length_marker_1 + 1] = 0;
              }
              if (content_byte_2 == 0x04) {//ArtistID
                rds.hasMusicArtist = true;
                for (int i = 0; i <= length_marker_2; i++)rds.musicArtist[i] = rt_buffer2[i + start_marker_2];
                rds.musicArtist[length_marker_2 + 1] = 0;
              }
              else if (content_byte_2 == 0x01) {//TitleID
                rds.hasMusicTitle = true;
                for (int i = 0; i <= length_marker_2; i++)rds.musicTitle[i] = rt_buffer2[i + start_marker_2];
                rds.musicTitle[length_marker_2 + 1] = 0;
              }
              if (content_byte_1 == 0x24) {//HostID
                rds.hasStationHost = true;
                for (int i = 0; i <= length_marker_1; i++)rds.stationHost[i] = rt_buffer2[i + start_marker_1];
                rds.stationHost[length_marker_1 + 1] = 0;
              }
              else if (content_byte_2 == 0x24) {
                rds.hasStationHost = true;
                for (int i = 0; i <= length_marker_2; i++)rds.stationHost[i] = rt_buffer2[i + start_marker_2];
                rds.stationHost[length_marker_2 + 1] = 0;
              }
              if (content_byte_1 == 0x21) {//EventID
                rds.hasStationEvent = true;
                for (int i = 0; i <= length_marker_1; i++)rds.stationEvent[i] = rt_buffer2[i + start_marker_1];
                rds.stationEvent[length_marker_1 + 1] = 0;
              }
              else if (content_byte_2 == 0x21) {
                rds.hasStationEvent = true;
                for (int i = 0; i <= length_marker_2; i++)rds.stationEvent[i] = rt_buffer2[i + start_marker_2];
                rds.stationEvent[length_marker_2 + 1] = 0;
              }
              rt_process = 0;
            }
          }
        } break;
    }
  }
  return rdsDataReady;
}

bool TEF6686::checkDouble (uint16_t value)
{
  for (int i = 0; i < 50; i++) if (af[i].frequency == value)return (true);
  return (false);
}

void TEF6686::clearRDS (bool fullsearchrds)
{
  devTEF_Radio_Set_RDS(fullsearchrds);
  uint8_t i;
  rds.stationName = "";
  rds.stationText = "";
  for (i = 0; i < 9; i++) {
    rds.PStext[i] = 0;
    ps_buffer[i] = 0;
  }
  for (i = 0; i < 65; i++) {
    stationTextBuffer[i] = 0;
    rds.RTtext[i] = 0;
    rt_buffer[i] = 0;
    rt_buffer2[i] = 0;
  }
  for (i = 0; i < 17; i++) {
    rds.stationType[i] = 0;
  }

  for (i = 0; i < 32; i++) {
    rds.musicArtist[i] = 0;
    rds.musicTitle[i] = 0;
    rds.stationEvent[i] = 0;
    rds.stationHost[i] = 0;
  }
  for (i = 0; i < 5; i++) rds.picode[i] = 0;

  for (i = 0; i < 50; i++) af[i].frequency = 0;

  rds.stationType[i] = '\0';
  rds.stationID = 0;
  rds.ECC = 0;
  offsetold = 0;
  rds.stationTypeCode = 32;
  rdsTimeOut = 32768;
  rds.hasRDSplus = false;
  rds.afclear = false;
  rds.hasRT = false;
  rds.hasRDS = false;
  rds.hasPS = false;
  rds.hasTP = false;
  rds.hasTA = false;
  rds.hasEON = false;
  rds.MS = 0;
  rds.hasPTY = false;
  rds.hasCT = false;
  rds.hasMusicTitle = false;
  rds.hasMusicArtist = false;
  rds.hasStationEvent = false;
  rds.hasStationHost = false;
  rds.stationTextOffset  = 0;
  rds.errors = 0;
  rds.correct = 0;
  rds.correctPI = 0;
  rt_process = 0;
  ps_process = 1;
  af_counter = 0;
  rt_timer = 0;
  rds.rdsreset = true;
}

void TEF6686::tone(uint16_t time, int16_t amplitude, uint16_t frequency) {
  devTEF_Audio_Set_Mute(0);
  devTEF_Radio_Set_Wavegen(1, amplitude, frequency);
  delay (time);
  devTEF_Radio_Set_Wavegen(0, 0, 0);
}

String TEF6686::convertToUTF8(const wchar_t* input) {
  String output;
  while (*input) {
    uint16_t unicode = *input;
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

void TEF6686::RDScharConverter(const char* input, wchar_t* output, size_t size) {
  for (size_t i = 0; i < size - 1; i++) {
    char currentChar = input[i];
    switch (currentChar) {
      case 0x20: if (rds.underscore) output[i] = L'_'; else output[i] = L' '; break;
      case 0x21 ... 0x5D: output[i] = static_cast<wchar_t>(currentChar); break;
      case 0x5E: output[i] = L'―'; break;
      case 0x5F: output[i] = L'_'; break;
      case 0x60: output[i] = L'‖'; break;
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
