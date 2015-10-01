#define interrupts_off ININTCON &= 0b01111111
#define interrupts_on ININTCON  |= 0b100000001

void high_isr(void);
void low_isr(void);
void startUP_interrupts(void);
void startUP_GPIO(void);
void startUP_OSCILLATOR(void);
void startUp_device(void);
