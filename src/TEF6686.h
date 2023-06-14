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
  BAND_FM,  BAND_LW,  BAND_MW,  BAND_SW
};

#define FREQ_MW_STEP_9K     9
#define FREQ_MW_STEP_10K    10
#define FREQ_SW_STEP_5K     5

#define FREQ_LW_START       144 // you can adjust here
#define FREQ_LW_END         513 // you can adjust here
#define FREQ_MW_START_EU    522
#define FREQ_MW_END_EU      1620
#define FREQ_MW_START_US    520
#define FREQ_MW_END_US      1710
#define FREQ_FM_START       65000
#define FREQ_FM_END         108000

// according to https://www.short-wave.info/index.php?feature=frequencies
#define FREQ_SW_START       1800
#define FREQ_SW_END         27000
#define FREQ_SW_160M_START  1800
#define FREQ_SW_160M_END    2000
#define FREQ_SW_120M_START  2300
#define FREQ_SW_120M_END    2495
#define FREQ_SW_90M_START   3200
#define FREQ_SW_90M_END     3400
#define FREQ_SW_75M_START   3900
#define FREQ_SW_75M_END     4000
#define FREQ_SW_60M_START   4750
#define FREQ_SW_60M_END     4995
#define FREQ_SW_49M_START   5900
#define FREQ_SW_49M_END     6200
#define FREQ_SW_41M_START   7200
#define FREQ_SW_41M_END     7450
#define FREQ_SW_31M_START   9400
#define FREQ_SW_31M_END     9900
#define FREQ_SW_25M_START   11600
#define FREQ_SW_25M_END     12100
#define FREQ_SW_22M_START   13570
#define FREQ_SW_22M_END     13870
#define FREQ_SW_19M_START   15100
#define FREQ_SW_19M_END     15800
#define FREQ_SW_16M_START   17480
#define FREQ_SW_16M_END     17900
#define FREQ_SW_15M_START   18900
#define FREQ_SW_15M_END     19020
#define FREQ_SW_13M_START   21450
#define FREQ_SW_13M_END     21850
#define FREQ_SW_11M_START   25670
#define FREQ_SW_11M_END     26100

const char* const PTY_EU[] {
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

const char* const PTY_USA[] {
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
  "Soft",
  "Nostalgia",
  "Jazz",
  "Classical",
  "Rhythm and Blues ",
  "Soft R & B",
  "Foreign_Language",
  "Religious Music",
  "Religious Talk",
  "Personality",
  "Public",
  "College",
  "Hablar Espanol",
  "Musica Espanol",
  "Hip Hop",
  " ",
  " ",
  "Weather",
  "Emergency Test",
  "ALERT! ALERT!",
  "                "
};

typedef struct _rds_ {
  byte region;
  byte stationTypeCode;
  byte MS;
  wchar_t PStext[9] = L"";
  wchar_t RTtext[65] = L"";
  String stationName;
  String stationText;
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
  bool hasPTY;
  bool hasCT;
  bool afclear;
  bool rtAB;
  bool correct;
  bool correctPI;
  bool underscore;
  bool rdsreset;
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
    void tone(uint16_t time, int16_t amplitude, uint16_t frequency);
    uint8_t af_counter;
    bool mute;

  private:
    void RDScharConverter(const char* input, wchar_t* output, size_t size);
    String convertToUTF8(const wchar_t* input);
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
