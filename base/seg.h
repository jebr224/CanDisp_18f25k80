
#define TRUE    1
#define FALSE   0

unsigned char g_dispValues[6] ="12345";
unsigned char g_currentDigit = 0;
unsigned char g_digitMask = 0xff;
unsigned char g_decPoint1 = 1;
unsigned char g_decPoint2 = 1;

void updateSeg(void);
void BCDpins(unsigned char num);

unsigned char setSegValues(unsigned char* data);
unsigned char setFrist3SegValues(unsigned char* data);
unsigned char setSecondSegValues(unsigned char* data);
