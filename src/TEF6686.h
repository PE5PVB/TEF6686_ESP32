#ifndef TEF6686_H
#define TEF6686_H

#include "Arduino.h"
#include "Tuner_Drv_Lithio.h"
#include "Tuner_Interface.h"
#include "RdsPiBuffer.hpp"

extern const unsigned char tuner_init_tab[] PROGMEM;
extern const unsigned char tuner_init_tab9216[] PROGMEM;
extern const unsigned char tuner_init_tab4000[] PROGMEM;
extern const unsigned char tuner_init_tab12000[] PROGMEM;
extern const unsigned char tuner_init_tab55000[] PROGMEM;

enum RDS_GROUPS {
  RDS_GROUP_0A,  RDS_GROUP_0B,  RDS_GROUP_1A,  RDS_GROUP_1B,  RDS_GROUP_2A,  RDS_GROUP_2B,  RDS_GROUP_3A,  RDS_GROUP_3B,
  RDS_GROUP_4A,  RDS_GROUP_4B,  RDS_GROUP_5A,  RDS_GROUP_5B,  RDS_GROUP_6A,  RDS_GROUP_6B,  RDS_GROUP_7A,  RDS_GROUP_7B,
  RDS_GROUP_8A,  RDS_GROUP_8B,  RDS_GROUP_9A,  RDS_GROUP_9B,  RDS_GROUP_10A, RDS_GROUP_10B, RDS_GROUP_11A, RDS_GROUP_11B,
  RDS_GROUP_12A, RDS_GROUP_12B, RDS_GROUP_13A, RDS_GROUP_13B, RDS_GROUP_14A, RDS_GROUP_14B, RDS_GROUP_15A, RDS_GROUP_15B
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

static const uint16_t oda_app_ids[] {
  0x0000, 0x0093, 0x0BCB, 0x0C24, 0x0CC1, 0x0D45, 0x0D8B, 0x0E2C, 0x0E31, 0x0F87,
  0x125F, 0x1BDA, 0x1C5E, 0x1C68, 0x1CB1, 0x1D47, 0x1DC2, 0x1DC5, 0x1E8F, 0x4400,
  0x4AA1, 0x4AB7, 0x4BA2, 0x4BD7, 0x4BD8, 0x4C59, 0x4D87, 0x4D95, 0x4D9A, 0x50DD,
  0x5757, 0x6363, 0x6365, 0x6552, 0x6A7A, 0x7373, 0xA112, 0xA911, 0xABCF, 0xC350,
  0xC3A1, 0xC3B0, 0xC3C3, 0xC4D4, 0xC549, 0xC563, 0xC6A7, 0xC737, 0xCB73, 0xCB97,
  0xCC21, 0xCD46, 0xCD47, 0xCD9E, 0xCE6B, 0xE123, 0xE1C1, 0xE319, 0xE411, 0xE440,
  0xE4A6, 0xE5D7, 0xE911, 0xFF7F, 0xFF80
};

static const char* const ECCtext[] {
  "Germany", // 0
  "Greece", // 1
  "Morocco", // 2
  "Moldova", // 3
  "Algeria", // 4
  "Cyprus", // 5
  "Czech R.", // 6
  "Ireland", // 7
  "Estonia", // 8
  "Andorra", // 9
  "San Marino", // 10
  "Poland", // 11
  "Turkey", // 12
  "Israel", // 13
  "Switzerl.", // 14
  "Vatican", // 15
  "Macedonia", // 16
  "Italy", // 17
  "Jordan", // 18
  "Slovakia", // 19
  "Belgium", // 20
  "Finland", // 21
  "Syria", // 22
  "Serbia", // 23
  "Ukraine", // 24
  "Russia", // 25
  "Luxemb.", // 26
  "Tunisia", // 27
  "Palestine", // 28
  "Bulgaria", // 29
  "Madeira", // 30
  "Netherl.", // 31
  "Portugal", // 32
  "Albania", // 33
  "Denmark", // 34
  "Liechtst.", // 35
  "Latvia", // 36
  "Slovenia", // 37
  "Austria", // 38
  "Gibraltar", // 39
  "Iceland", // 40
  "Lebanon", // 41
  "Hungary", // 42
  "Iraq", // 43
  "Monaco", // 44
  "Malta", // 45
  "U.K.", // 46
  "Lithuania", // 47
  "Croatia", // 48
  "Libya", // 49
  "Canaries", // 50
  "Romania", // 51
  "Spain", // 52
  "Sweden", // 53
  "Egypt", // 54
  "France", // 55
  "Norway", // 56
  "Belarus", // 57
  "Bosnia H.", // 58
  "Monteneg.", // 59
  "Armenia", // 60
  "Azerbaijan", // 61
  "Kosovo", // 62
  "Kyrgystan", // 63
  "Turkmenis.", // 64
  "Tajikistan", // 65
  "Uzbekistan", // 66
  "Malawi", // 67
  "Mali", // 68
  "Mauritania", // 69
  "Mauritius", // 70
  "Mongolia", // 71
  "Mozambiq.", // 72
  "Namibia", // 73
  "Niger", // 74
  "Nigeria", // 75
  "Oman", // 76
  "Qatar", // 77
  "Rwanda", // 78
  "Sao Tome", // 79
  "Saudi Ara.", // 80
  "Senegal", // 81
  "Seychel.", // 82
  "S. Leone", // 83
  "Somalia", // 84
  "S. Africa", // 85
  "S. Sudan", // 86
  "Sudan", // 87
  "Swaziland", // 88
  "Tanzania", // 89
  "Togo", // 90
  "Uganda", // 91
  "W. Sahara", // 92
  "Yemen", // 93
  "Zambia", // 94
  "Zimbabwe", // 95
  "Angola", // 96
  "Ascn. Isl.", // 97
  "Bahrein", // 98
  "Benin", // 99
  "Botswana", // 100
  "Burkina F.", // 101
  "Burundi", // 102
  "Cabinda", // 103
  "Cameroon", // 104
  "Cape Ver.", // 105
  "Centr. Af.", // 106
  "Chad", // 107
  "Comoros", // 108
  "D. Congo", // 109
  "Congo", // 110
  "Cote d'l.", // 111
  "Djibouti", // 112
  "E. Guinea", // 113
  "Eritrea", // 114
  "Ethiopia", // 115
  "Gabon", // 116
  "Gambia", // 117
  "Georgia", // 118
  "Ghana", // 119
  "Guinea", // 120
  "Guinea-B.", // 121
  "Kazakh.", // 122
  "Kenya", // 123
  "Kuwait", // 124
  "Lesotho", // 125
  "Liberia", // 126
  "Madagas.", // 127
  "U.Arab.E.", // 128
  "Anguilla", // 129
  "Antigua.", // 130
  "Argentina", // 131
  "Aruba", // 132
  "Barbados", // 133
  "Belize", // 134
  "Bermuda", // 135
  "Bolivia", // 136
  "Brazil", // 137
  "Canada", // 138
  "Cayman I.", // 139
  "Chile", // 140
  "Colombia", // 141
  "Costa R.", // 142
  "Cuba", // 143
  "Dominica", // 144
  "Domini. R", // 145
  "El Salvad.", // 146
  "Equador", // 147
  "Falkland", // 148
  "Greenland", // 149
  "Grenada", // 150
  "Guadeloupe", // 151
  "Guatemala", // 152
  "Guyana", // 153
  "Haiti", // 154
  "Honduras", // 155
  "Jamaica", // 156
  "Martinique", // 157
  "Mexico", // 158
  "Montserrat", // 159
  "Nether. A.", // 160
  "Nicaragua", // 161
  "Panama", // 162
  "Paraguay", // 163
  "Peru", // 164
  "Puerto R.", // 165
  "St. Kitts", // 166
  "St. Lucia", // 167
  "St. P.& M.", // 168
  "St.Vincent", // 169
  "Suriname", // 170
  "T & T", // 171
  "Turks & C.", // 172
  "U.S.A.", // 173
  "Uruguay", // 174
  "Venezuela", // 175
  "Virgin UK", // 176
  "Virgin USA", // 177
  "Afganist.", // 178
  "Aus. ACT", // 179
  "Aus. NSW", // 180
  "Aus. VIC", // 181
  "Aus. QLD", // 182
  "Aus. SA", // 183
  "Aus. WA", // 184
  "Aus. TAS", // 185
  "Aus. NT", // 186
  "Bhutan", // 187
  "Brunei D.", // 188
  "Cambodia", // 189
  "China", // 190
  "Fiji", // 191
  "Hong Kong", // 192
  "India", // 193
  "Indonesia", // 194
  "Iran", // 195
  "Japan", // 196
  "Kiribati", // 197
  "N. Korea", // 198
  "S. Korea", // 199
  "Laos", // 200
  "Macao", // 201
  "Malaysia", // 202
  "Maldives", // 203
  "Marshall I", // 204
  "Micronesia", // 205
  "Myanmar", // 206
  "Nauru", // 207
  "Nepal", // 208
  "N.Zealand", // 209
  "Pakistan", // 210
  "Papua N.G", // 211
  "Philippin.", // 212
  "Samoa", // 213
  "Singapore", // 214
  "Solomon I.", // 215
  "Sri Lanka", // 216
  "Taiwan", // 217
  "Thailand", // 218
  "Tonga", // 219
  "Vanuatu", // 220
  "Vietnam", // 221
  "Bahamas", // 222
  "BM or BR", // 223
  "EC or BR", // 224
  "AN or BR", // 225
  "USA/VI/ PR", // 226
  "Bangladesh" // 227
};

static const char* const LICtext[] = {
  "Unknown",         // 0
  "Albanian",        // 1
  "Breton",          // 2
  "Catalan",         // 3
  "Croatian",        // 4
  "Welsh",           // 5
  "Czech",           // 6
  "Danish",          // 7
  "German",          // 8
  "English",         // 9
  "Spanish",         // 10
  "Esperanto",       // 11
  "Estonian",        // 12
  "Basque",          // 13
  "Faroese",         // 14
  "French",          // 15
  "Frisian",         // 16
  "Irish",           // 17
  "Gaelic",          // 18
  "Galician",        // 19
  "Icelandic",       // 20
  "Italian",         // 21
  "Lappish",         // 22
  "Latin",           // 23
  "Latvian",         // 24
  "Luxemb.",         // 25
  "Lithua.",         // 26
  "Hungar.",         // 27
  "Maltese",         // 28
  "Dutch",           // 29
  "Norweg.",         // 30
  "Occitan",         // 31
  "Polish",          // 32
  "Portug.",         // 33
  "Romanian",        // 34
  "Romansh",         // 35
  "Serbian",         // 36
  "Slovak",          // 37
  "Slovene",         // 38
  "Finnish",         // 39
  "Swedish",         // 40
  "Turkish",         // 41
  "Flemish",         // 42
  "Walloon",         // 43
  "Unknown",         // 44
  "Unknown",         // 45
  "Unknown",         // 46
  "Unknown",         // 47
  "Unknown",         // 48
  "Unknown",         // 49
  "Unknown",         // 50
  "Unknown",         // 51
  "Unknown",         // 52
  "Unknown",         // 53
  "Unknown",         // 54
  "Unknown",         // 55
  "Unknown",         // 56
  "Unknown",         // 57
  "Unknown",         // 58
  "Unknown",         // 59
  "Unknown",         // 60
  "Unknown",         // 61
  "Unknown",         // 62
  "Unknown",         // 63
  "Backgr.",         // 64
  "Unknown",         // 65
  "Unknown",         // 66
  "Unknown",         // 67
  "Unknown",         // 68
  "Zulu",            // 69
  "Vietnam.",        // 70
  "Uzbek",           // 71
  "Urdu",            // 72
  "Ukrain.",         // 73
  "Thai",            // 74
  "Telugu",          // 75
  "Tatar",           // 76
  "Tamil",           // 77
  "Tadzhik",         // 78
  "Swahili",         // 79
  "SrananT.",        // 80
  "Somali",          // 81
  "Sinhalese",       // 82
  "Shona",           // 83
  "Serbo-C.",        // 84
  "Ruthen.",         // 85
  "Russian",         // 86
  "Quechua",         // 87
  "Pushtu",          // 88
  "Punjabi",         // 89
  "Persian",         // 90
  "Papami.",         // 91
  "Oriya",           // 92
  "Nepali",          // 93
  "Ndebele",         // 94
  "Marathi",         // 95
  "Moldov.",         // 96
  "Malays.",         // 97
  "Malagas.",        // 98
  "Macedon.",        // 99
  "Laotian",         // 100
  "Korean",          // 101
  "Khmer",           // 102
  "Kazakh",          // 103
  "Kannada",         // 104
  "Japanese",        // 105
  "Indones.",        // 106
  "Hindi",           // 107
  "Hebrew",          // 108
  "Hausa",           // 109
  "Gurani",          // 110
  "Gujurati",        // 111
  "Greek",           // 112
  "Georgian",        // 113
  "Fulani",          // 114
  "Dari",            // 115
  "Churash",         // 116
  "Chinese",         // 117
  "Burmese",         // 118
  "Bulgarian",       // 119
  "Bengali",         // 120
  "Belorus.",        // 121
  "Bambora",         // 122
  "Azerbaij.",       // 123
  "Assamese",        // 124
  "Armenian",        // 125
  "Arabic",          // 126
  "Amharic"          // 127
};

static const char* const oda_app_names[] {
  "None",
  "Cross referencing DAB within RDS",
  "Leisure & Practical Info for Drivers",
  "ELECTRABEL-DSM 7",
  "Wireless Playground broadcast control signal",
  "RDS-TMC: ALERT-C / EN ISO 14819-1",
  "ELECTRABEL-DSM 18",
  "ELECTRABEL-DSM 3",
  "ELECTRABEL-DSM 13",
  "ELECTRABEL-DSM 2",
  "I-FM-RDS for fixed and mobile devices",
  "ELECTRABEL-DSM 1",
  "ELECTRABEL-DSM 20",
  "ITIS In-vehicle data base",
  "ELECTRABEL-DSM 10",
  "ELECTRABEL-DSM 4",
  "CITIBUS 4",
  "Encrypted TTI using ALERT-Plus",
  "ELECTRABEL-DSM 17",
  "RDS-Light",
  "RASANT",
  "ELECTRABEL-DSM 9",
  "ELECTRABEL-DSM 5",
  "RadioText+ (RT+)",
  "RadioText Plus / RT+for eRT",
  "CITIBUS 2",
  "Radio Commerce System (RCS)",
  "ELECTRABEL-DSM 16",
  "ELECTRABEL-DSM 11",
  "To warn people in case of disasters or emergency",
  "Personal weather station",
  "Hybradio RDS-Net(for testing use, only)",
  "RDS2 – 9 bit AF lists ODA",
  "Enhanced RadioText (eRT)",
  "Warning receiver",
  "Enhanced early warning system",
  "NL _ Alert system",
  "Data FM Selective Multipoint Messaging",
  "RF Power Monitoring",
  "NRSC Song Title and Artist",
  "Personal Radio Service",
  "iTunes Tagging",
  "NAVTEQ Traffic Plus",
  "eEAS",
  "Smart Grid Broadcast Channel",
  "ID Logic",
  "Veil Enabled Interactive Device",
  "Utility Message Channel (UMC)",
  "CITIBUS 1",
  "ELECTRABEL-DSM 14",
  "CITIBUS 3",
  "RDS-TMC: ALERT-C",
  "RDS-TMC: ALERT-C",
  "ELECTRABEL-DSM 8",
  "Encrypted TTI using ALERT-Plus",
  "APS Gateway",
  "Action code",
  "ELECTRABEL-DSM 12",
  "Beacon downlink",
  "ELECTRABEL-DSM 15",
  "ELECTRABEL-DSM 19",
  "ELECTRABEL-DSM 6",
  "EAS open protocol",
  "RFT: Station logo",
  "RFT+ (work title)"
};

struct DABFrequencyLabel {
  uint32_t frequency;
  const char* label;
};

const DABFrequencyLabel DABfrequencyTable[] = {
  { 174928,  "5A"}, { 176640,  "5B"}, { 178352,  "5C"}, { 180064,  "5D"},
  { 181936,  "6A"}, { 183648,  "6B"}, { 185360,  "6C"}, { 187072,  "6D"},
  { 188928,  "7A"}, { 190640,  "7B"}, { 192352,  "7C"}, { 194064,  "7D"},
  { 195936,  "8A"}, { 197648,  "8B"}, { 199360,  "8C"}, { 201072,  "8D"},
  { 202928,  "9A"}, { 204640,  "9B"}, { 206352,  "9C"}, { 208064,  "9D"},
  { 209936, "10A"}, { 211648, "10B"}, { 213360, "10C"}, { 215072, "10D"},
  { 216928, "11A"}, { 218640, "11B"}, { 220352, "11C"}, { 222064, "11D"},
  { 223936, "12A"}, { 225648, "12B"}, { 227360, "12C"}, { 229072, "12D"},
  { 230784, "13A"}, { 232496, "13B"}, { 234208, "13C"}, { 235776, "13D"},
  { 237488, "13E"}, { 239200, "13F"}, {1452960,  "LA"}, {1454672,  "LB"},
  {1456384,  "LC"}, {1458096,  "LD"}, {1459808,  "LE"}, {1461520,  "LF"},
  {1463232,  "LG"}, {1464944,  "LH"}, {1466656,  "LI"}, {1468368,  "LJ"},
  {1470080,  "LK"}, {1471792,  "LL"}, {1473504,  "LM"}, {1475216,  "LN"},
  {1476928,  "LO"}, {1478640,  "LP"}, {1480352,  "LQ"}, {1482064,  "LR"},
  {1483776,  "LS"}, {1485488,  "LT"}, {1487200,  "LU"}, {1488912,  "LV"},
  {1490624,  "LW"}
};

typedef struct _rds_ {
  byte region;
  byte stationTypeCode;
  byte MS;
  String stationName;
  String stationText;
  String stationText32;
  String RTContent1;
  String RTContent2;
  String PTYN;
  String ECCtext;
  String LICtext;
  String stationIDtext;
  String stationNameLong;
  String stationStatetext;
  String enhancedRTtext;
  char stationType[18];
  char picode[7];
  char stationID[9];
  char stationLongID[33];
  char stationState[3];
  char dabafeid[5];
  char dabafchannel[4];
  uint16_t rdsA, rdsB, rdsC, rdsD, rdsErr, rdsStat, correctPI, rdsplusTag1, rdsplusTag2;
  bool ps12error, ps34error, ps56error, ps78error;
  time_t time;
  int32_t offset;
  uint16_t aid[10];
  uint32_t dabaffreq;
  byte aid_counter;
  byte fastps;
  unsigned int ECC;
  unsigned int LIC;
  byte pinMin;
  byte pinHour;
  byte pinDay;
  bool rdsAerror;
  bool rdsBerror;
  bool rdsCerror;
  bool rdsDerror;
  bool hasArtificialhead;
  bool hasCompressed;
  bool hasDynamicPTY;
  bool hasStereo;
  bool hasRDS;
  bool hasPIN;
  bool hasECC;
  bool hasLIC;
  bool hasDABAF;
  bool hasLongPS;
  bool hasRT;
  bool hasEnhancedRT;
  bool hasTP;
  bool hasTA;
  bool hasEON;
  bool hasAID;
  bool hasTMC;
  bool hasAF;
  bool hasCT;
  bool hasPTYN;
  bool rtAB;
  bool rtAB32;
  bool hasRDSplus;
  bool filter;
  bool rdsreset;
  bool pierrors;
  bool sortaf;
  bool rtbuffer = true;
  bool afreg;
  RdsPiBuffer piBuffer;
} rds_;

typedef struct _af_ {
  uint16_t  frequency;
  int16_t score;
  bool afvalid;
  bool checked;
  bool regional;
  bool same;
} af_;

typedef struct _eon_ {
  uint16_t  mappedfreq;
  uint16_t  mappedfreq2;
  uint16_t  mappedfreq3;
  uint16_t  pi;
  char picode[6];
  String ps;
  bool ta;
  bool tp;
  bool taset;
  uint8_t pty;
} eon_;

typedef struct _logbook_ {
  char picode[6];
  uint16_t frequency;
  int16_t SignalLevel;
  String stationName;
  String DateTime;
} logbook_;

class TEF6686 {
  public:
    af_  af[51];
    eon_ eon[21];
    rds_ rds;
    logbook_ logbook[22];
    uint16_t TestAF();
    void TestAFEON();
    void readRDS(byte showrdserrors);
    void SetFreq(uint16_t frequency);
    void SetFreqAM(uint16_t frequency);
    void SetFreqAIR(uint16_t frequency);
    bool getProcessing(uint16_t &highcut, uint16_t &stereo, uint16_t &sthiblend, uint8_t &stband_1, uint8_t &stband_2, uint8_t &stband_3, uint8_t &stband_4);
    bool getStatus(int16_t &level, uint16_t &USN, uint16_t &WAM, int16_t &offset, uint16_t &bandwidth, uint16_t &modulation, int8_t &snr);
    bool getStatusAM(int16_t &level, uint16_t &noise, uint16_t &cochannel, int16_t &offset, uint16_t &bandwidth, uint16_t &modulation, int8_t &snr);
    bool getIdentification(uint16_t &device, uint16_t &hw_version, uint16_t &sw_version);
    void I2Sin(bool mode);
    void setSoftmuteFM(uint8_t mode);
    void setSoftmuteAM(uint8_t mode);
    void setMono(bool mono);
    bool getStereoStatus();
    void setCoax(uint8_t mode);
    void init(byte TEF);
    void clearRDS(bool fullsearchrds);
    void power(bool mode);
    void setAGC(uint8_t agc);
    void setAMAGC(uint8_t agc);
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
    void setAMCoChannel(uint16_t start, uint8_t level = 3);
    void setAMNoiseBlanker(uint16_t start);
    void setAMAttenuation(uint16_t start);
    void setMute();
    void setOffset(int8_t offset);
    void setAMOffset(int8_t offset);
    void setFMSI(uint8_t mode);
    void setFMSI_Time(uint16_t attack, uint16_t decay);
    void setFMSI_Gain(uint16_t band1, uint16_t band2, uint16_t band3, uint16_t band4);
    void setFMSI_Bias(int16_t band1, int16_t band2, int16_t band3, int16_t band4);
    void setStereoLevel(uint8_t start);
    void setUnMute();
    void setVolume(int8_t volume);
    void tone(uint16_t time, int16_t amplitude, uint16_t frequency);
    uint16_t getBlockA(void);
    String trimTrailingSpaces(String str);
    uint8_t af_counter;
    uint8_t eon_counter;
    uint8_t logbook_counter;
    uint8_t rdsblock;
    bool mute;
    bool afmethodB;
    bool underscore;
    byte af_updatecounter;

  private:
    void RDScharConverter(const char* input, wchar_t* output, size_t size, bool under);
    String convertToUTF8(const wchar_t* input);
    String extractUTF8Substring(const String& utf8String, size_t start, size_t length, bool under);
    String eRTconverter(const wchar_t* input);
    String ucs2ToUtf8(const char* ucs2Input);
    String PSLongtext;
    char ps_buffer[9];
    char ps_buffer2[9];
    char ptyn_buffer[9];
    char eon_buffer[20][9];
    bool ps_process;
    bool pslong_process;
    char eRT_buffer[129];
    bool rt_process;
    char rt_buffer[65];
    char rt_buffer2[65];
    char rt_buffer32[33];
    char pslong_buffer[33];
    char pslong_buffer2[33];
    bool useRTPlus = true;
    bool ABold;
    bool afreset;
    bool mpxmode;
    bool _hasEnhancedRT;
    char stationTextBuffer[65];
    uint16_t piold;
    bool rtABold;
    bool rtAB32old;
    wchar_t PStext[9] = L"";
    wchar_t EONPStext[20][9];
    wchar_t PTYNtext[9] = L"";
    char RDSplus1[45];
    char RDSplus2[45];
    uint16_t  currentfreq;
    uint16_t  currentfreq2;
    bool togglebit;
    bool runningbit;
    bool initrt;
    bool initab;
    bool afinit;
    bool errorfreepi;
    bool rdsAerrorThreshold, rdsBerrorThreshold, rdsCerrorThreshold, rdsDerrorThreshold;
    bool packet0, packet1, packet2, packet3, packet0long, packet1long, packet2long, packet3long;
    uint16_t previous_rdsA, previous_rdsB, previous_rdsC, previous_rdsD;
    bool afmethodBprobe;
    bool eRTcoding;
    uint16_t rdsCold;
    uint8_t af_counterb;
    uint8_t af_number;
    uint8_t af_counterbcheck;
    bool afmethodBtrigger;
    uint16_t correctPIold;
    uint8_t rtplusblock;
    uint8_t DABAFblock;
    uint8_t eRTblock;
    uint8_t doublecounter;
    uint16_t doubletestfreq;
    time_t lastrdstime;
    int32_t lasttimeoffset;
};
#endif