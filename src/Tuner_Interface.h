void Tuner_I2C_Init();
void Tuner_Patch(byte TEF);
bool Tuner_Init();
bool Tuner_Init4000();
bool Tuner_Init9216();
bool Tuner_WriteBuffer(unsigned char *buf, uint16_t len);
bool Tuner_ReadBuffer(unsigned char *buf, uint16_t len);
bool Tuner_Table_Write(const unsigned char *tab);
