
#include "seg.h"
#include <p18cxxx.h>


unsigned char g_dispValues[6] ="12345";
unsigned char g_currentDigit = 0;
unsigned char g_digitMask = 0xff;
unsigned char g_decPoint1 = 1;
unsigned char g_decPoint2 = 1;


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
	if((g_currentDigit == g_decPoint1) || (g_currentDigit+3 == g_decPoint2)){
		LATCbits.LATC0=0; //trun on
	}else{
		LATCbits.LATC0=0; //turn off
	}


}

void BCDpins(unsigned char num){
	if (num > 9 || num < 0){
		num =10;
	}
	LATA=num & 0b00001111;
}

unsigned char setSegValues(unsigned char* data){
	unsigned char isError= FALSE;
	int i ;
	for(i =0; i<6;i++){
		if ((data[i] > 9 )||(data[i]<0)){
			isError = TRUE;
		}
		g_dispValues[i] = data[i];//deep copy
	}
	return isError;
}

unsigned char setFrist3SegValues(unsigned char* data){
	unsigned char isError= FALSE;
	int i;
	for(i =0; i<3;i++){
		if ((data[i] > 9 )||(data[i]<0)){
			isError = TRUE;
		}
		g_dispValues[i] = data[i];//deep copy
	}
	return isError;
}

unsigned char setSecondSegValues(unsigned char* data){
	unsigned char isError= FALSE;
	int i;
	for(i =3; i<6;i++){
		if ((data[i] > 9 )||(data[i]<0)){
			isError = TRUE;
		}
		g_dispValues[i] = data[i];//deep copy
	}
	return isError;
}




