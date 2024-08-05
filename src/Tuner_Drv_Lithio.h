#ifndef TUNER_DRV_LITHIO_H
#define TUNER_DRV_LITHIO_H

typedef enum {
  TEF_FM                      = 32,
  TEF_AM                      = 33,
  TEF_AUDIO                   = 48,
  TEF_APPL                    = 64
} TEF_MODULE;

typedef enum {
  Cmd_Tune_To                 =  1,
  Cmd_Set_Bandwidth           = 10,
  Cmd_Set_RFAGC               = 11,
  Cmd_Set_Antenna             = 12,
  Cmd_Set_CoChannelDet        = 14,
  Cmd_Set_MphSuppression      = 20,
  Cmd_Set_ChannelEqualizer    = 22,
  Cmd_Set_NoiseBlanker        = 23,
  Cmd_Set_NoiseBlanker_Audio  = 24,
  Cmd_Set_Deemphasis          = 31,
  Cmd_Set_StereoImprovement   = 32,
  Cmd_Set_LevelOffset         = 39,
  Cmd_Set_Softmute_Max        = 45,
  Cmd_Set_Highcut_Level       = 52,
  Cmd_Set_Highcut_Noise       = 53,
  Cmd_Set_Highcut_Mph         = 54,
  Cmd_Set_Highcut_Max         = 55,
  Cmd_Set_Stereo_Level        = 62,
  Cmd_Set_Stereo_Noise        = 63,
  Cmd_Set_Stereo_Mph          = 64,
  Cmd_Set_Stereo_Min          = 66,
  Cmd_Set_StHiBlend_Level     = 72,
  Cmd_Set_StHiBlend_Noise     = 73,
  Cmd_Set_StHiBlend_Mph       = 74,
  Cmd_Set_StHiBlend_Max       = 75,
  Cmd_Set_RDS                 = 81,
  Cmd_Set_Specials            = 85,
  Cmd_Set_StBandBlend_Time    = 90,
  Cmd_Set_StBandBlend_Gain    = 91,
  Cmd_Set_StBandBlend_Bias    = 92,
  Cmd_Get_Quality_Status      = 128,
  Cmd_Get_Quality_Data        = 129,
  Cmd_Get_RDS_Status          = 130,
  Cmd_Get_RDS_Data            = 131,
  Cmd_Get_Signal_Status       = 133,
  Cmd_Get_Processing_Status   = 134
} TEF_RADIO_COMMAND;

typedef enum {
  Cmd_Set_Volume              = 10,
  Cmd_Set_Mute                = 11,
  Cmd_Set_Input               = 12,
  Cmd_Set_WaveGen             = 24
} TEF_AUDIO_COMMAND;

typedef enum {
  Cmd_Set_OperationMode       =   1,
  Cmd_Set_GPIO           =   3,
  Cmd_Get_Operation_Status    = 128,
  Cmd_Get_Identification      = 130
} TEF_APPL_COMMAND;

void devTEF_Radio_Set_RDS(bool fullsearchrds);
void devTEF_Radio_Set_Softmute_Max_FM(uint8_t mode);
void devTEF_Radio_Set_Softmute_Max_AM(uint8_t mode);
void devTEF_Set_Cmd(TEF_MODULE module, uint8_t cmd, uint16_t len, ...);
void devTEF_Radio_Tune_To (uint16_t frequency );
void devTEF_Radio_Tune_AM (uint16_t frequency );
void devTEF_Audio_Set_Mute(uint8_t mode);
void devTEF_Audio_Set_Volume(int16_t volume);
void devTEF_APPL_Set_OperationMode(bool mode);
void devTEF_Radio_Set_Bandwidth(uint8_t mode, uint16_t bandwidth);
void devTEF_Radio_Set_BandwidthAM(uint8_t mode, uint16_t bandwidth);
void devTEF_Radio_Set_Noiseblanker_AM(uint8_t mode, uint16_t start);
void devTEF_Radio_Set_Attenuator_AM(uint16_t start);
void devTEF_Radio_Set_CoChannel_AM(uint8_t mode, uint16_t start, uint8_t level);
void devTEF_Radio_Set_LevelOffset(int16_t offset);
void devTEF_Radio_Set_AMLevelOffset(int16_t offset);
void devTEF_Radio_Set_Stereo_Level(uint8_t mode, uint16_t start, uint16_t slope);
void devTEF_Radio_Set_Stereo_Noise(uint8_t mode, uint16_t start, uint16_t slope);
void devTEF_Radio_Set_Stereo_Mph(uint8_t mode, uint16_t start, uint16_t slope);
void devTEF_Radio_Set_Stereo_Min(bool mode);
void devTEF_Radio_Set_MphSuppression(bool mph);
void devTEF_Radio_Set_ChannelEqualizer(bool eq);
void devTEF_Radio_Set_RFAGC(uint16_t agc);
void devTEF_Radio_Set_AMRFAGC(uint16_t agc);
void devTEF_Radio_Set_Deemphasis(uint16_t timeconstant);
void devTEF_Radio_Specials(uint16_t audio);
void devTEF_APPL_Set_StereoImprovement(bool mode);
void devTEF_APPL_Set_StereoBandBlend_Time(uint16_t attack, uint16_t decay);
void devTEF_APPL_Set_StereoBandBlend_Gain(uint16_t band1, uint16_t band2, uint16_t band3, uint16_t band4);
void devTEF_APPL_Set_StereoBandBlend_Bias(int16_t band1, int16_t band2, int16_t band3, int16_t band4);
void devTEF_Radio_Set_Highcut_Max(uint8_t mode, uint16_t limit);
void devTEF_Radio_Set_Highcut_Level(uint8_t mode, uint16_t start, uint16_t slope);
void devTEF_Radio_Set_Highcut_Noise(uint8_t mode, uint16_t start, uint16_t slope);
void devTEF_Radio_Set_Highcut_Mph(uint8_t mode, uint16_t start, uint16_t slope);
void devTEF_Radio_Set_StHiBlend_Max(uint8_t mode, uint16_t limit);
void devTEF_Radio_Set_StHiBlend_Level(uint8_t mode, uint16_t start, uint16_t slope);
void devTEF_Radio_Set_StHiBlend_Noise(uint8_t mode, uint16_t start, uint16_t slope);
void devTEF_Radio_Set_StHiBlend_Mph(uint8_t mode, uint16_t start, uint16_t slope);
void devTEF_Radio_Set_NoisBlanker(uint8_t mode, uint16_t start);
void devTEF_Radio_Set_Wavegen(bool mode, int16_t amplitude, uint16_t freq);
void devTEF_Radio_Set_I2S_Input(bool mode);
void devTEF_Radio_Set_GPIO(uint8_t mode);

bool devTEF_Radio_Get_Identification (uint16_t *device, uint16_t *hw_version, uint16_t *sw_version);
bool devTEF_Radio_Get_Quality_Status (uint16_t *status, int16_t *level, uint16_t *usn, uint16_t *wam, int16_t *offset, uint16_t *bandwidth, uint16_t *mod, int8_t *snr);
bool devTEF_Radio_Get_Processing_Status (uint16_t *highcut, uint16_t *stereo, uint16_t *sthiblend, uint8_t *stband_1, uint8_t *stband_2, uint8_t *stband_3, uint8_t *stband_4);
bool devTEF_Radio_Get_Quality_Status_AM (int16_t *level, uint16_t *noise, uint16_t *cochannel, int16_t *offset, uint16_t *bandwidth, uint16_t *mod, int8_t *snr);
bool devTEF_APPL_Get_Operation_Status(uint8_t *bootstatus);
bool devTEF_Radio_Get_Stereo_Status(uint16_t *status);
bool devTEF_Radio_Get_RDS_Status(uint16_t *status, uint16_t *A_block, uint16_t *B_block, uint16_t *C_block, uint16_t *D_block, uint16_t *dec_error);
bool devTEF_Radio_Get_RDS_Data(uint16_t *status, uint16_t *A_block, uint16_t *B_block, uint16_t *C_block, uint16_t *D_block, uint16_t *dec_error);
#endif