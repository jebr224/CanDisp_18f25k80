#define interrupts_off (INTCON &= 0b01111111)
#define interrupts_on (INTCON  |= 0b100000001)

void high_isr(void);
void low_isr(void);
void startUp_interrupts(void);
void startUp_timer(void);
void startUP_GPIO(void);
void startUP_OSCILLATOR(void);
void startUp_device(void);
