#define TEF6686_h

#include "Arduino.h"
#include "Tuner_Drv_Lithio.h"
#include "Tuner_Interface.h"

enum RDS_GROUPS {
  RDS_GROUP_0A,  RDS_GROUP_0B,  RDS_GROUP_1A,  RDS_GROUP_1B,  RDS_GROUP_2A,  RDS_GROUP_2B,  RDS_GROUP_3A,  RDS_GROUP_3B,
  RDS_GROUP_4A,  RDS_GROUP_4B,  RDS_GROUP_5A,  RDS_GROUP_5B,  RDS_GROUP_6A,  RDS_GROUP_6B,  RDS_GROUP_7A,  RDS_GROUP_7B,
  RDS_GROUP_8A,  RDS_GROUP_8B,  RDS_GROUP_9A,  RDS_GROUP_9B,  RDS_GROUP_10A, RDS_GROUP_10B, RDS_GROUP_11A, RDS_GROUP_11B,
  RDS_GROUP_12A, RDS_GROUP_12B, RDS_GROUP_13A, RDS_GROUP_13B, RDS_GROUP_14A, RDS_GROUP_14B, RDS_GROUP_15A, RDS_GROUP_15B
};

typedef struct _rds_ {
  byte stationTypeCode;
  char stationName[9];
  char stationText[65];
  char stationType[17];
  char musicTitle[48];
  char musicArtist[48];
  char stationHost[48];
  char stationEvent[48];
  char picode[5];
  uint16_t hours, minutes, days, months, years, offsetplusmin, stationID = 0, rdsA, rdsB, rdsC, rdsD, rdsError, errors = 0;
  int8_t offset;
  uint8_t stationTextOffset = 0;
  int ECC;
  bool hasMusicTitle;
  bool hasMusicArtist;
  bool hasStationHost;
  bool hasStationEvent;
  bool hasRDSplus;
  bool hasRDS;
  bool hasPS;
  bool hasRT;
  bool hasTP;
  bool hasTA;
  bool hasEON;
  bool hasAF;
  bool MS;
  bool hasPTY;
  bool hasCT;
  bool afclear;
  bool rtAB;
  bool correct;
  bool correctPI;
} rds_;

typedef struct _af_ {
  uint16_t  frequency;
} af_;


class TEF6686 {
  public:
    af_  af[50];
    rds_ rds;
    bool readRDS(bool showrdserrors);
    void SetFreq(uint16_t frequency);
    void SetFreqAM(uint16_t frequency);
    bool getProcessing(uint16_t &highcut, uint16_t &stereo, uint16_t &sthiblend, uint8_t &stband_1, uint8_t &stband_2, uint8_t &stband_3, uint8_t &stband_4);
    bool getStatus(int16_t &level, uint16_t &USN, uint16_t &WAM, int16_t &offset, uint16_t &bandwidth, uint16_t &modulation);
    bool getStatusAM(int16_t &level, uint16_t &noise, uint16_t &cochannel, int16_t &offset, uint16_t &bandwidth, uint16_t &modulation);
    bool getIdentification(uint16_t &device, uint16_t &hw_version, uint16_t &sw_version);
    void setSoftmuteFM(uint8_t mode);
    void setSoftmuteAM(uint8_t mode);
    void setMono(bool mono);
    bool getStereoStatus();
    void init(byte TEF);
    void clearRDS(bool fullsearchrds);
    void power(bool mode);
    void setAGC(uint8_t agc);
    void setiMS(bool mph);
    void setEQ(bool eq);
    void setDeemphasis(uint8_t timeconstant);
    void setAudio(uint8_t audio);
    void setFMABandw();
    void setFMBandw(uint16_t bandwidth);
    void setAMBandw(uint16_t bandwidth);
    void setHighCutLevel(uint16_t limit);
    void setHighCutOffset(uint8_t start);
    void setStHiBlendLevel(uint16_t limit);
    void setStHiBlendOffset(uint8_t start);
    void setNoiseBlanker(uint16_t start);
    void setAMCoChannel(uint16_t start);
    void setAMNoiseBlanker(uint16_t start);
    void setAMAttenuation(uint16_t start);
    void setMute();
    void setOffset(int8_t offset);
    void setFMSI(uint8_t mode);
    void setFMSI_Time(uint16_t attack, uint16_t decay);
    void setFMSI_Gain(uint16_t band1, uint16_t band2, uint16_t band3, uint16_t band4);
    void setFMSI_Bias(int16_t band1, int16_t band2, int16_t band3, int16_t band4);
    void setStereoLevel(uint8_t start);
    void setUnMute();
    void setVolume(int8_t volume);
    uint8_t af_counter;
	bool mute;
    void tone(uint16_t time, int16_t amplitude, uint16_t frequency);

  private:
	uint8_t ascii_converter   (uint8_t src);
    uint16_t rdsTimeOut = 32768;
    uint8_t ps_process;
    uint8_t rt_process;
    char ps_buffer[9];
    char rt_buffer[65];
    char rt_buffer2[65];
    bool useRTPlus = true;
    bool checkDouble (uint16_t value);
    bool ABold;
    byte rt_timer;
    byte offsetold;
    char stationTextBuffer[65];
};
