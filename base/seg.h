
unsigned char g_dispValues[6] ="12345";
unsigned char g_currentDigit = 0;

void updateSeg(void);
void BCDpins(unsigned char num);

unsigned char setSegValues(char* data);
unsigned char setFrist3SegValues(char* data);
unsigned char setSecondSegValues(char* data);
