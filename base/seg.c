
#include "seg.h"
#include <p18cxxx.h>


unsigned char g_dispValues[6];// ="12345";
unsigned char g_currentDigit=0;
unsigned char g_digitMask = 0xff;
unsigned char g_count = 0;
//unsigned char g_decPoint1 = 1;
//unsigned char g_decPoint2 = 1;




void updateSeg(void){
	g_count++;
//	if(g_count < 0)
//		return;
	g_count = 0;

	 g_currentDigit++;
	if (g_currentDigit > 5){
		g_currentDigit = 0;
	}


//	BCDpins(0);
	BCDpins(g_dispValues[g_currentDigit]);
/*

//#define	(LATCbits.LATC1) digi0
#define	(LATAbits.LATA7) digi0
#define	(LATBbits.LATB0) digi1
#define	(LATBbits.LATB1) digi2
#define	(LATBbits.LATB4) digi3
#define	(LATBbits.LATB5) digi4

#define (LATAbits.LATA6) digi0//	//(LATCbits.LATC0) digi5
*/

#define on 0
#define off 1

	switch(g_currentDigit){  // g_currentDigit
		case 0:


			LATAbits.LATA7 = on;  //0
			LATBbits.LATB0 = off; //1
			LATBbits.LATB1 = off; //2
			LATBbits.LATB4 = off; //3
			LATBbits.LATB5 = off; //4
			LATAbits.LATA6 = off; //5


	
			break;
		case 1:
			LATAbits.LATA7 = off;  //0
			LATBbits.LATB0 = on; //1
			LATBbits.LATB1 = off; //2
			LATBbits.LATB4 = off; //3
			LATBbits.LATB5 = off; //4
			LATAbits.LATA6 = off; //5
			break;
		case 2:
			LATAbits.LATA7 = off;  //0
			LATBbits.LATB0 = off; //1
			LATBbits.LATB1 = on; //2
			LATBbits.LATB4 = off; //3
			LATBbits.LATB5 = off; //4
			LATAbits.LATA6 = off; //5
	
			break;
		case 3:
			LATAbits.LATA7 = off;  //0
			LATBbits.LATB0 = off; //1
			LATBbits.LATB1 = off; //2
			LATBbits.LATB4 = on; //3
			LATBbits.LATB5 = off; //4
			LATAbits.LATA6 = off; //5
	
			break;
		case 4:
			LATAbits.LATA7 = off;  //0
			LATBbits.LATB0 = off; //1
			LATBbits.LATB1 = off; //2
			LATBbits.LATB4 = off; //3
			LATBbits.LATB5 = on; //4
			LATAbits.LATA6 = off; //5

			break;
		case  5:
			LATAbits.LATA7 = off;  //0
			LATBbits.LATB0 = off; //1
			LATBbits.LATB1 = off; //2
			LATBbits.LATB4 = off; //3
			LATBbits.LATB5 = off; //4
			LATAbits.LATA6 = on; //5
/*
			LATAbits.LATA7 = off;  //0
			LATBbits.LATB0 = off; //1
			LATBbits.LATB1 = off; //2
			LATBbits.LATB4 = off; //3
			LATBbits.LATB5 = off; //4
*/ 
	
			
	}
//	if((g_currentDigit == g_decPoint1) || (g_currentDigit+3 == g_decPoint2)){
	//	LATCbits.LATC0=0; //trun on
//	}else{
	//	LATCbits.LATC0=0; //turn off
//	}
//	BCDpins(g_dispValues[g_currentDigit]);
	TMR1H =0b10000000;
		
}

void BCDpins(unsigned char num){
	if (num > 9 || num < 0){
		num =10;
	}
	LATA=num &  0b00001111;//0b11110000;//
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




