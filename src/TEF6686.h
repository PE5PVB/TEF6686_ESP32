#define TEF6686_h

#include "Arduino.h"
#include "Tuner_Api.h"
#include "Tuner_Drv_Lithio.h"
#include "Tuner_Interface.h"


enum RDS_GROUPS
{
  RDS_GROUP_0A,  RDS_GROUP_0B,  RDS_GROUP_1A,  RDS_GROUP_1B,  RDS_GROUP_2A,  RDS_GROUP_2B,  RDS_GROUP_3A,  RDS_GROUP_3B,
  RDS_GROUP_4A,  RDS_GROUP_4B,  RDS_GROUP_5A,  RDS_GROUP_5B,  RDS_GROUP_6A,  RDS_GROUP_6B,  RDS_GROUP_7A,  RDS_GROUP_7B,
  RDS_GROUP_8A,  RDS_GROUP_8B,  RDS_GROUP_9A,  RDS_GROUP_9B,  RDS_GROUP_10A, RDS_GROUP_10B, RDS_GROUP_11A, RDS_GROUP_11B,
  RDS_GROUP_12A, RDS_GROUP_12B, RDS_GROUP_13A, RDS_GROUP_13B, RDS_GROUP_14A, RDS_GROUP_14B, RDS_GROUP_15A, RDS_GROUP_15B
};

typedef struct _rds_
{
  char picode[5];
  char stationName[9];
  char stationText[65];
  byte stationTypeCode;
  char stationType[17];
  uint16_t hours, minutes, days, offsetplusmin, stationID = 0, rdsA, rdsB, rdsC, rdsD, rdsError, errors = 0;
  int8_t offset;
  uint8_t stationTextOffset = 0;
  bool hasCT = false;
  bool rtAB = false;
} rds_;

class TEF6686 {
  public:
    rds_ rds;
    bool readRDS(void);
    uint16_t getFrequency();
    uint16_t getFrequency_AM();
    uint16_t tuneDown(uint8_t stepsize, uint16_t LowEdge, uint16_t HighEdge, bool fullsearchrds);
    uint16_t tuneUp(uint8_t stepsize, uint16_t LowEdge, uint16_t HighEdge, bool fullsearchrds);
    uint16_t tuneDown_AM(uint8_t stepsize);
    uint16_t tuneUp_AM(uint8_t stepsize);
    bool getStatus(int16_t &level, uint16_t &USN, uint16_t &WAM, int16_t &offset, uint16_t &bandwidth, uint16_t &modulation);
    bool getStatus_AM(int16_t &level, uint16_t &USN, uint16_t &WAM, int16_t &offset, uint16_t &bandwidth, uint16_t &modulation);
    bool getIdentification(uint16_t &device, uint16_t &hw_version, uint16_t &sw_version);
    bool getBootStatus(uint8_t &bootstatus);
    void setMono(uint8_t mono);
    bool getStereoStatus();
    void init(byte TEF);
    void clearRDS(bool fullsearchrds);
    void power(uint8_t mode);
    void setAGC(uint8_t start);
    void setiMS(uint16_t mph);
    void setEQ(uint16_t eq);
    void setDeemphasis(uint8_t timeconstant);
    void setFMABandw();
    void setFMBandw(uint16_t bandwidth);
    void setAMBandw(uint16_t bandwidth);
    void setFrequency(uint16_t frequency, uint16_t LowEdge, uint16_t HighEdge, bool fullsearchrds);
    void setFrequency_AM(uint16_t frequency);
    void setHighCutLevel(uint16_t limit);
    void setHighCutOffset(uint16_t start);
    void setMute();
    void setOffset(int16_t offset);
    void setStereoLevel(uint16_t start);
    void setUnMute();
    void setVolume(int16_t volume);
	void tone(uint16_t time, int16_t amplitude, uint16_t frequency);
    uint8_t af_counter;

  private:
    uint16_t tune(uint8_t up, uint8_t stepsize, uint16_t LowEdge, uint16_t HighEdge, bool fullsearchrds);
    uint16_t tune_AM(uint8_t up, uint8_t stepsize);
    uint8_t ascii_converter (uint8_t src);
    uint8_t ps_process;
    uint8_t rt_process;
    char ps_buffer[9];
    char rt_buffer[65];
    bool ABold;
    byte rt_timer;
    byte offsetold;
    char stationTextBuffer[65];
};
