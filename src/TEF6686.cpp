#include "TEF6686.h"

const char* const PTY[]
{
  "None",
  "News",
  "Current Affairs",
  "Information",
  "Sport",
  "Education",
  "Drama",
  "Cultures",
  "Science",
  "Varied Speech",
  "Pop Music",
  "Rock Music",
  "Easy Listening",
  "Light Classics",
  "Serious Classics",
  "Other Music",
  "Weather",
  "Finance",
  "Children's Progs",
  "Social Affair",
  "Religion",
  "Phone In",
  "Travel & Touring",
  "Leisure & Hobby",
  "Jazz Music",
  "Country Music",
  "National Music",
  "Oldies Music",
  "Folk Music",
  "Documentary",
  "Alarm Test",
  "Alarm!!!",
  "                "
};

void TEF6686::init(byte TEF) {
  uint8_t bootstatus;
  Tuner_I2C_Init();
  getBootStatus(bootstatus);
  if (bootstatus == 0) {
    Tuner_Patch(TEF);
    delay(50);
    if (digitalRead(15) == LOW) {
      Tuner_Init9216();
    } else {
      Tuner_Init4000();
    }
    power(1);
    Tuner_Init();
  }
}

void TEF6686::power(uint8_t mode) {
  devTEF_APPL_Set_OperationMode(mode);
  if (mode == 0) {
    devTEF_Set_Cmd(TEF_FM, Cmd_Tune_To, 7, 1, 10000);
  }
}

bool TEF6686::getIdentification(uint16_t &device, uint16_t &hw_version, uint16_t &sw_version) {
  bool result = devTEF_Radio_Get_Identification(&device, &hw_version, &sw_version);
  return device;
  return hw_version;
  return sw_version;
}

void TEF6686::setFrequency(uint16_t frequency, uint16_t LowEdge, uint16_t HighEdge, bool fullsearchrds) {
  Radio_SetFreq(frequency, LowEdge, HighEdge, fullsearchrds);
}

void TEF6686::setFrequency_AM(uint16_t frequency) {
  Radio_SetFreq_AM(frequency);
}

uint16_t TEF6686::getFrequency() {
  return Radio_GetCurrentFreq();
}

uint16_t TEF6686::getFrequency_AM() {
  return Radio_GetCurrentFreq_AM();
}

void TEF6686::setOffset(int16_t offset) {
  devTEF_Radio_Set_LevelOffset(offset * 10);
}

void TEF6686::setFMBandw(uint16_t bandwidth) {
  devTEF_Radio_Set_Bandwidth(0, bandwidth * 10, 1000, 1000);
}
void TEF6686::setFMABandw() {
  devTEF_Radio_Set_Bandwidth(1, 3110, 1000, 1000);
}

void TEF6686::setAMBandw(uint16_t bandwidth) {
  devTEF_Radio_Set_Bandwidth_AM(0, bandwidth * 10, 1000, 1000);
}

void TEF6686::setiMS(uint16_t mph) {
  devTEF_Radio_Set_MphSuppression(mph);
}

void TEF6686::setEQ(uint16_t eq) {
  devTEF_Radio_Set_ChannelEqualizer(eq);
}

bool TEF6686::getStereoStatus() {
  return Radio_CheckStereo();
}

void TEF6686::setMono(uint8_t mono) {
  devTEF_Radio_Set_Stereo_Min(mono);
}

uint16_t TEF6686::tuneUp(uint8_t stepsize, uint16_t LowEdge, uint16_t HighEdge, bool fullsearchrds) {
  return tune(1, stepsize, LowEdge, HighEdge, fullsearchrds);
}

uint16_t TEF6686::tuneDown(uint8_t stepsize, uint16_t LowEdge, uint16_t HighEdge, bool fullsearchrds) {
  return tune(0, stepsize, LowEdge, HighEdge, fullsearchrds);
}

uint16_t TEF6686::tuneUp_AM(uint8_t stepsize) {
  return tune_AM(1, stepsize);
}

uint16_t TEF6686::tuneDown_AM(uint8_t stepsize) {
  return tune_AM(0, stepsize);
}

void TEF6686::setVolume(int16_t volume) {
  devTEF_Audio_Set_Volume(volume);
}

void TEF6686::setMute() {
  devTEF_Audio_Set_Mute(1);
}

void TEF6686::setUnMute() {
  devTEF_Audio_Set_Mute(0);
}

void TEF6686::setAGC(uint8_t start) {
  if (start == 0) {
    devTEF_Radio_Set_RFAGC(920);
  }
  if (start == 1) {
    devTEF_Radio_Set_RFAGC(900);
  }
  if (start == 2) {
    devTEF_Radio_Set_RFAGC(870);
  }
  if (start == 3) {
    devTEF_Radio_Set_RFAGC(840);
  }
}

void TEF6686::setDeemphasis(uint8_t timeconstant) {
  if (timeconstant == 0) {
    devTEF_Radio_Set_Deemphasis(500);
  }
  if (timeconstant == 1) {
    devTEF_Radio_Set_Deemphasis(750);
  }
  if (timeconstant == 2) {
    devTEF_Radio_Set_Deemphasis(0);
  }
}

void TEF6686::setStereoLevel(uint16_t start) {
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

void TEF6686::setHighCutOffset(uint16_t start) {
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

bool TEF6686::getBootStatus(uint8_t &bootstatus) {
  uint8_t result = devTEF_APPL_Get_Operation_Status(&bootstatus);
  return bootstatus;
}

bool TEF6686::getStatus(int16_t &level, uint16_t &USN, uint16_t &WAM, int16_t &offset, uint16_t &bandwidth, uint16_t &modulation) {
  uint8_t result = devTEF_Radio_Get_Quality_Status(&level, &USN, &WAM, &offset, &bandwidth, &modulation);
  return level;
  return USN;
  return WAM;
  return bandwidth;
  return modulation;
}

bool TEF6686::getStatus_AM(int16_t &level, uint16_t &USN, uint16_t &WAM, int16_t &offset, uint16_t &bandwidth, uint16_t &modulation) {
  uint8_t result = devTEF_Radio_Get_Quality_Status_AM(&level, &USN, &WAM, &offset, &bandwidth, &modulation);
  return level;
  return USN;
  return WAM;
  return bandwidth;
  return modulation;
}

bool TEF6686::readRDS()
{
  char     status;
  uint16_t rdsStat  = 0, rdsErr = 65535, rdsErrA = 65535, rdsErrB = 65535, rdsErrC = 65535, rdsErrD = 65535;
  uint16_t result   = devTEF_Radio_Get_RDS_Data(&rdsStat, &rds.rdsA, &rds.rdsB, &rds.rdsC, &rds.rdsD, &rdsErr);
  uint8_t  rds_group;
  uint8_t  offset;
  bool     rdsErrCheck = false, rdsDataReady = false;

  rdsErrA = ((rdsErr >> 14) & 0x02);
  rdsErrB = ((rdsErr >> 12) & 0x02);
  rdsErrC = ((rdsErr >> 10) & 0x02);
  rdsErrD = ((rdsErr >>  8) & 0x02);

  rdsErrCheck = rdsErr == 0;
  rdsDataReady = ((rdsStat & (1 << 15))  && (rdsStat & (1 << 9)));
  rds.errors = rdsErr;
  if (rdsDataReady && rdsErrCheck)
  {
    //RDS PI
    if (rds.stationID == 0) rds.stationID = rds.rdsA;
    char Hex[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
    rds.picode[0] = Hex[(rds.rdsA & 0xF000U) >> 12];
    rds.picode[1] = Hex[(rds.rdsA & 0x0F00U) >> 8];
    rds.picode[2] = Hex[(rds.rdsA & 0x00F0U) >> 4];
    rds.picode[3] = Hex[(rds.rdsA & 0x000FU)];
    rds.picode[4] = '\0';
    rds_group  = (rds.rdsB >> 11);
    switch (rds_group)
    {
      case RDS_GROUP_0A:
      case RDS_GROUP_0B:
        {
          //RDS PS
          offset = rds.rdsB & 0x03;

          if ((offset == 0) && (ps_process == 0))ps_process = 1;

          if (ps_process == 1)
          {
            ps_buffer[(offset * 2)  + 0] = ascii_converter(rds.rdsD >> 8);
            ps_buffer[(offset * 2)  + 1] = ascii_converter(rds.rdsD & 0xFF);
            ps_buffer[(offset * 2)  + 2] = 0;
            ps_process = strlen(ps_buffer) == 8 ? 2 : 1;
          }

          if (ps_process == 2)
          {
            strcpy(rds.stationName, ps_buffer);
            for (int i = 0; i < 9; i++)
              ps_buffer[i]  = '\0';
            ps_process = 0;
          }

          //RDS PTY Code
          rds.stationTypeCode = (rds.rdsB >> 5) & 0x1F;
          strcpy(rds.stationType, PTY[rds.stationTypeCode]);
        } break;

      case RDS_GROUP_2A:
      case RDS_GROUP_2B:
        {
          //RDS RT Code
          boolean limit_reached = false;
          offset = (rds.rdsB & 0xf) * 4;
          rds.rtAB = (bitRead(rds.rdsB, 4));
          limit_reached = (offset == 60 || (rds.rdsC >> 8) == '\r' || (rds.rdsC & 0xFF) == '\r' || (rds.rdsD >> 8) == '\r' || (rds.rdsD & 0xFF) == '\r')  ? true : false;
          rt_process = (rt_process == 0) && (offset == 0) ? 1 : rt_process;

          if (rds.rtAB != ABold) {
            offsetold = 0;
            for (int i = 0; i < 65; i++) {
              rds.stationText[i] = 0;
            }
            if (rt_timer == 64) {
              strcpy(rds.stationText, stationTextBuffer);
            }
            for (int i = 0; i < 65; i++) {
              rt_buffer[i]  = 0;
              stationTextBuffer[i] = 0;
            }
            rt_process = 0;
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
            rt_buffer[offset + 0] = ascii_converter(rds.rdsC >> 8);
            rt_buffer[offset + 1] = ascii_converter(rds.rdsC & 0xff);
            rt_buffer[offset + 2] = ascii_converter(rds.rdsD >> 8);
            rt_buffer[offset + 3] = ascii_converter(rds.rdsD & 0xff);

            if (offset > offsetold) {
              offsetold = offset;
            }
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
              rt_buffer[i]  = 0;
            }
          }
        } break;

      case RDS_GROUP_4A:
      case RDS_GROUP_4B:
        {
          //RDS CT
          rds.hours = ((rds.rdsD >> 12) & 0x0f);
          rds.hours += ((rds.rdsC <<  4) & 0x0010);
          rds.minutes = ((rds.rdsD >>  6) & 0x3f);
          rds.offsetplusmin = ((bitRead(rds.rdsD, 5)) & 0x3f);
          rds.offset = (rds.rdsD & 0x3f);
          rds.hasCT = true;
        } break;
    }
  }
  return rdsDataReady;
}

uint8_t TEF6686::ascii_converter (uint8_t src)
{
  char dest = src;
  switch (src)
  {
    case 0x91: dest = 225; break; //ä
    case 0x97: dest = 239; break; //ö
    case 0x99: dest = 245; break; //ü
    case 0xD1: dest = 225; break; //Ä
    case 0xD7: dest = 239; break; //Ö
    case 0xD9: dest = 245; break; //Ü
    case 0x8D: dest = 226; break; //ß
    case 0xBB: dest = 223; break; //°
  }
  return (dest);
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
  }
  for (i = 0; i < 17; i++) {
    rds.stationType[i] = 0;
  }

  for (i = 0; i < 5; i++) {
    rds.picode[i] = 0;
  }

  rds.stationType[i] = '\0';
  rds.stationID = 0;
  offsetold = 0;
  rds.stationTypeCode = 32;
  rds.hasCT = false;
  rds.stationTextOffset  = 0;
  rt_process = 0;
  ps_process = 1;
  af_counter = 0;
  rt_timer = 0;
  rds.errors = 0;
}

uint16_t TEF6686::tune(uint8_t up, uint8_t stepsize, uint16_t LowEdge, uint16_t HighEdge, bool fullsearchrds) {
  Radio_ChangeFreqOneStep(up, stepsize, LowEdge, HighEdge, fullsearchrds);
  Radio_SetFreq(Radio_GetCurrentFreq(), LowEdge, HighEdge, fullsearchrds);

  return Radio_GetCurrentFreq();
}

uint16_t TEF6686::tune_AM(uint8_t up, uint8_t stepsize) {
  Radio_ChangeFreqOneStep_AM(up, stepsize);
  Radio_SetFreq_AM(Radio_GetCurrentFreq_AM());
  return Radio_GetCurrentFreq_AM();
}
