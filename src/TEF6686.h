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

enum RADIO_BAND {
  BAND_FM, BAND_LW, BAND_MW, BAND_SW
};

enum RADIO_TUNE_MODE {
  TUNE_MAN, TUNE_AUTO, TUNE_MEM, TUNE_MI_BAND
};

static const char* const PTY_EU[] {
  "None",
  "News",
  "Current Affairs",
  "Information",
  "Sport",
  "Education",
  "Drama",
  "Culture",
  "Science",
  "Varied",
  "Pop Music",
  "Rock Music",
  "Easy Listening",
  "Light Classical",
  "Serious Classical",
  "Other Music",
  "Weather",
  "Finance",
  "Children's Progs",
  "Social Affairs",
  "Religion",
  "Phone-In",
  "Travel",
  "Leisure",
  "Jazz Music",
  "Country Music",
  "National Music",
  "Oldies Music",
  "Folk Music",
  "Documentary",
  "Alarm Test",
  "Alarm!!!",
  " "
};

static const char* const PTY_USA[] {
  "None",
  "News",
  "Information",
  "Sports",
  "Talk",
  "Rock",
  "Classic Rock",
  "Adult Hits",
  "Soft Rock",
  "Top 40",
  "Country",
  "Oldies",
  "Soft Music",
  "Nostalgia",
  "Jazz",
  "Classical",
  "Rhythm and Blues",
  "Soft R & B",
  "Language",
  "Religious Music",
  "Religious Talk",
  "Personality",
  "Public",
  "College",
  "Spanish Talk",
  "Spanish Music",
  "Hip Hop",
  " ",
  " ",
  "Weather",
  "Emergency Test",
  "EMERGENCY!",
  " "
};

typedef struct _rds_ {
  byte region;
  byte stationTypeCode;
  byte MS;
  String stationName;
  String stationText;
  String RTArtist;
  String RTTitle;
  String RTHost;
  String RTEvent;
  String PTYN;
  char stationType[18];
  char picode[6];
  uint16_t hours, minutes, days, months, years, offsetplusmin, rdsA, rdsB, rdsC, rdsD, rdsErr;
  int8_t offset;
  int ECC;
  bool rdsAerror;
  bool rdsBerror;
  bool rdsCerror;
  bool rdsDerror;
  bool hasArtificialhead;
  bool hasCompressed;
  bool hasDynamicPTY;
  bool hasStereo;
  bool hasRDS;
  bool hasECC;
  bool hasRT;
  bool hasTP;
  bool hasTA;
  bool hasEON;
  bool hasAF;
  bool hasCT;
  bool rtAB;
  bool hasRDSplus;
  bool hasTitle;
  bool hasArtist;
  bool hasHost;
  bool hasEvent;
  bool correct;
  bool filter;
  bool underscore;
  bool rdsreset;
  bool pierrors;
} rds_;

typedef struct _af_ {
  uint16_t  frequency;
} af_;

typedef struct _eon_ {
  uint16_t  mappedfreq;
  uint16_t  pi;
  String ps;
} eon_;


class TEF6686 {
  public:
    af_  af[50];
    eon_ eon[5];
    rds_ rds;
    void readRDS(bool showrdserrors);
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
    void setFMNoiseBlanker(uint16_t start);
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
    void tone(uint16_t time, int16_t amplitude, uint16_t frequency);
    uint8_t af_counter;
    bool mute;

  private:
    void RDScharConverter(const char* input, wchar_t* output, size_t size, bool under);
    String convertToUTF8(const wchar_t* input);
    String extractUTF8Substring(const String& utf8String, size_t start, size_t length, bool under);
    char ps_buffer[9];
    char ps_buffer2[9];
    char ptyn_buffer[9];
    char eon_buffer[9][5];
    char eon_buffer2[9][5];
    bool ps_process;
    bool rt_process;
    char rt_buffer[65];
    char rt_buffer2[65];
    bool useRTPlus = true;
    bool checkDouble (uint16_t value);
    bool checkDoubleEON (uint16_t value);
    byte eon_counter;
    bool ABold;
    char stationTextBuffer[65];
    uint64_t doublecheck;
    uint16_t rdsBprevious;
    uint16_t rdsCprevious;
    uint16_t rdsDprevious;
    bool rtABold;
    wchar_t PStext[9] = L"";
    wchar_t EONPStext[9] = L"";
    wchar_t PTYNtext[9] = L"";
    byte ps_counter;
    char musicArtist[45];
    char musicTitle[45];
    char stationHost[45];
    char stationEvent[45];
    uint16_t  currentfreq;
};