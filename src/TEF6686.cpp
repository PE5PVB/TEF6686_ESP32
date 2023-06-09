#include "TEF6686.h"

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
			if (rds.stationID > 21671 &&(rds.stationID & 0xF00U) >> 8 == 0) rds.stationID = ((uint16_t)uint8_t(0xA0 + ((rds.stationID & 0xF000U) >> 12)) << 8) + lowByte(rds.stationID); // C0DE -> ACDE
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
            ps_buffer[(offset * 2)  + 0] = EBU_converter(rds.rdsD >> 8);
            ps_buffer[(offset * 2)  + 1] = EBU_converter(rds.rdsD & 0xFF);
            ps_buffer[(offset * 2)  + 2] = 0;
            ps_process = strlen(ps_buffer) == 8 ? 2 : 1;
          }

          if (ps_process == 2) {
            strcpy(rds.stationName, ps_buffer);
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
            rds.MS = (bitRead(rds.rdsB, 3)) & 0x1F;

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
            for (int i = 0; i < 65; i++) rds.stationText[i] = 0;
            if (rt_timer == 64) strcpy(rds.stationText, stationTextBuffer);

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
            rt_buffer[offset + 0] = EBU_converter(rds.rdsC >> 8);
            rt_buffer[offset + 1] = EBU_converter(rds.rdsC & 0xff);
            rt_buffer[offset + 2] = EBU_converter(rds.rdsD >> 8);
            rt_buffer[offset + 3] = EBU_converter(rds.rdsD & 0xff);

            if (offset > offsetold) offsetold = offset;

            if (offset == offsetold) {
              strcpy(stationTextBuffer, rt_buffer);
              if (rt_timer < 64) {
                strcpy(rds.stationText, stationTextBuffer);
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

uint16_t TEF6686::EBU_converter (uint8_t src)
{
  switch (src)
  {
    case 0x20: return 0x20; break;
    case 0x21: return 0x21; break;
    case 0x22: return 0x22; break;
    case 0x23: return 0x23; break;
    case 0x24: return 0xa4; break;
    case 0x25 ... 0x5d: return src;
    case 0x5e: return 0x2d; break;
    case 0x5f: return 0x5f; break;
    case 0x60: return 0x7c; break;
    case 0x61 ... 0x7d: return src; break;
    case 0x7e: return 0xaf; break;
    case 0x80: return 0xe1; break;
    case 0x81: return 0xe0; break;
    case 0x82: return 0xe9; break;
    case 0x83: return 0xe8; break;
    case 0x84: return 0xed; break;
    case 0x85: return 0xec; break;
    case 0x86: return 0xf3; break;
    case 0x87: return 0xf2; break;
    case 0x88: return 0xfa; break;
    case 0x89: return 0xf9; break;
    case 0x8a: return 0xd1; break;
    case 0x8b: return 0xc7; break;
    case 0x8c: return 0x53; break;
    case 0x8d: return 0xdf; break;
    case 0x8e: return 0xa1; break;
    case 0x8f: return 0x59; break;
    case 0x90: return 0xe2; break;
    case 0x91: return 0xe4; break;
    case 0x92: return 0xea; break;
    case 0x93: return 0xeb; break;
    case 0x94: return 0xee; break;
    case 0x95: return 0xef; break;
    case 0x96: return 0xf4; break;
    case 0x97: return 0xf6; break;
    case 0x98: return 0xfb; break;
    case 0x99: return 0xfc; break;
    case 0x9a: return 0xf1; break;
    case 0x9b: return 0xe7; break;
    case 0x9c: return 0x73; break;
    case 0x9d: return 0x67; break;
    case 0x9e: return 0x7c; break;
    case 0x9f: return 0x79; break;
    case 0xa0: return 0xaa; break;
    case 0xa1: return 0x61; break;
    case 0xa2: return 0xa9; break;
    case 0xa3: return 0x25; break;
    case 0xa4: return 0x47; break;
    case 0xa5: return 0x65; break;
    case 0xa6: return 0x6e; break;
    case 0xa7: return 0xf6; break;
    case 0xa8: return 0x6e; break;
    case 0xa9: return 0x45; break;
    case 0xaa: return 0xa3; break;
    case 0xab: return 0x24; break;
    case 0xc0: return 0xc1; break;
    case 0xc1: return 0xc0; break;
    case 0xc2: return 0xc9; break;
    case 0xc3: return 0xc8; break;
    case 0xc4: return 0xcd; break;
    case 0xc5: return 0xcc; break;
    case 0xc6: return 0xd3; break;
    case 0xc7: return 0xd2; break;
    case 0xc8: return 0xda; break;
    case 0xc9: return 0xd9; break;
    case 0xca: return 0x52; break;
    case 0xcb: return 0x43; break;
    case 0xcc: return 0x53; break;
    case 0xcd: return 0x5a; break;
    case 0xce: return 0xd0; break;
    case 0xcf: return 0x4c; break;
    case 0xd0: return 0xc2; break;
    case 0xd1: return 0xc4; break;
    case 0xd2: return 0xca; break;
    case 0xd3: return 0xcb; break;
    case 0xd4: return 0xce; break;
    case 0xd5: return 0xcf; break;
    case 0xd6: return 0xd4; break;
    case 0xd7: return 0xd6; break;
    case 0xd8: return 0xdb; break;
    case 0xd9: return 0xdc; break;
    case 0xda: return 0x72; break;
    case 0xdb: return 0x63; break;
    case 0xdc: return 0x73; break;
    case 0xdd: return 0x7a; break;
    case 0xde: return 0x64; break;
    case 0xdf: return 0x7c; break;
    case 0xf0: return 0xe3; break;
    case 0xf1: return 0xe5; break;
    case 0xf2: return 0xe6; break;
    case 0xf3: return 0xf6; break;
    case 0xf4: return 0x77; break;
    case 0xf5: return 0xfd; break;
    case 0xf6: return 0xf5; break;
    case 0xf7: return 0xf8; break;
    case 0xf8: return 0xfe; break;
    case 0xf9: return 0x6e; break;
    case 0xfa: return 0x72; break;
    case 0xfb: return 0x63; break;
    case 0xfc: return 0x73; break;
    case 0xfd: return 0x7a; break;
    case 0xfe: return 0x74; break;
    default: return 0x20; break;
  }
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
  for (i = 0; i < 9; i++) {
    rds.stationName[i] = 0;
    ps_buffer[i] = 0;
  }
  for (i = 0; i < 65; i++) {
    rds.stationText[i] = 0;
    stationTextBuffer[i] = 0;
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
  rds.MS = false;
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
}

void TEF6686::tone(uint16_t time, int16_t amplitude, uint16_t frequency) {
  devTEF_Audio_Set_Mute(0);
  devTEF_Radio_Set_Wavegen(1, amplitude, frequency);
  delay (time);
  devTEF_Radio_Set_Wavegen(0, 0, 0);
}
