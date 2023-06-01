extern uint16_t Radio_GetCurrentFreq(void);
extern uint16_t Radio_GetCurrentFreq_AM(void);
extern void Radio_ChangeFreqOneStep(uint8_t UpDown, uint8_t stepsize, uint16_t LowEdge, uint16_t HighEdge, bool fullsearchrds);
extern void Radio_ChangeFreqOneStep_AM(uint8_t UpDown, uint8_t stepsize);
extern void Radio_SetFreq(uint16_t Freq, uint16_t LowEdge, uint16_t HighEdge, bool fullsearchrds);
extern void Radio_SetFreq_AM(uint16_t Freq);
bool Radio_CheckStereo(void);
