
#include "seg.h"
#include <p18cxxx.h>

void updateSeg(void){
	 g_currentDigit++;
	if (g_currentDigit > 6){
		g_currentDigit = 0;
	}

	BCDpins(g_dispValues[g_currentDigit]);
	
	switch(g_currentDigit){
		case 0:
			LATBbits.LATB5 = 1;
			LATAbits.LATA5 = 0;
			break;
		case 1:
			LATAbits.LATA5 = 1;
			LATBbits.LATB0 = 0;
			break;
		case 2:
			LATBbits.LATB0 = 1;
			LATBbits.LATB1 = 0;
			break;
		case 3:
			LATBbits.LATB1 = 1;
			LATBbits.LATB4 = 0;
			break;
		case 4:
			LATBbits.LATB4 = 1;
			LATBbits.LATB5 = 0;
			break;
		case 5:
			LATBbits.LATB5 = 1;			
			LATBbits.LATB5 = 0;
	}

}

void BCDpins(unsigned char num){
	if (num > 9 || num < 0){
		num =10;
	}
	LATA=num & 0b00001111;
}