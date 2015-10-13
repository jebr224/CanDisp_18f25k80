#define interrupts_off (INTCON &= 0b01111111)
#define interrupts_on  (INTCON |= 0b10000000)
#define clearTM1  (PIR1 &= 0b11111110)
#define clearCANRX (PIE5 &= 0b11111100)


void high_isr(void);
void low_isr(void);
void startUp_interrupts(void);
void startUp_timer(void);
void startUP_GPIO(void);
void startUP_OSCILLATOR(void);
void startUp_device(void);
