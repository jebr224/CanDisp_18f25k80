
#include <p18cxxx.h>
#include "ECAN.h"
#include "startUp.h"
#include "seg.h"
#include "comm.h"
//#include "comm.h"



    //I was planning on using a crystal, but this pretty
	//(in this branch this is the plan)
	// Set the internal oscillator to 64MHz
	//    OSCCONbits.IRCF = 7;
	//    OSCTUNEbits.PLLEN = 1;
    // Initialize global variables to 0


//***************************************************
//High ISR 
#pragma interrupt high_isr 
void high_isr(void){
	//LATBbits.LATB3 ^= 1;       //Toggle portB pin 3 (red LED)
	//parse message and update values
	
	//	newCanMessage(); //can
	
	//PIR5 &= 0b111111100; //clear the interrupt flag so that another interrupt can happen

//		clearCANRX;
//	clearTM1;
}
#pragma code


//sets the interrupt vector to point to the high_isr function   //Section 'low_vector' start=0x00000018, length=0x0000006
#pragma code high_vector = 0x08
void high_interrupt(void){
 	_asm GOTO high_isr _endasm
}
#pragma code



//***************************************************
//LOW ISR

#pragma interrupt low_isr
void low_isr(void){
	//LATBbits.LATB3 ^= 1;       //Toggle portB pin 3 (red LED)
	//segUpDate
	//	 updateSeg();
	//PIR1 &= 0b1111011;///clear the interrupt flag (TM0)so that another interrupt can happen
//	newCanMessage(); 

	updateSeg();

	clearTM1;
}
#pragma code

//sets the interrupt vector to point to the low_isr function
#pragma code low_vector = 0x18
	void low_interrupt(void){
 	_asm GOTO low_isr _endasm
}
#pragma code




	



void startUp_interrupts(void){
	
	//high-priority interrupt vector is at 0x0008
	//low-priority  interrupt vector is at 0x0018

	INTCON = 0b01000000;//global interrupt bit off (when we are done with config we will turn on), 
						//peripheral interrupt on,
						//both tmr0 interrupt off
						//hardware interrupt off,
	INTCON2 = 0b1000100;
	INTCON3 = 0;// no external interupts


	PIE1 = 0b00000001; //TMR1 overflow is enabled
	PIE2 = 0;
	PIE3 = 0;
	PIE4 = 0;
	PIE5 = 0b00000011;//11; //RXB1IE, and RXB0IE 


	IPR1 = 0b00000000; //TMR is low priority; 0b0000000x where x is the bit that matters
	IPR2 = 0;
	IPR3 = 0;
	IPR4 = 0;
	IPR5 = 0b00000011;//RXB1IE, and RXB0IE  are high priority


	BIE0 = 0xff;//0b00000001;

	clearTM1;
	clearCANRX;
	//RCONbits.IPEN =1;//reset reg
	//IPEN=enable 2 priority levels
	RCON =0b10000000;//danger

	PADCFG1bits.CTMUDS=0;
	CM1CON =0;
	CM2CON =0;

	return;
}

void startUp_timer(void){
	//we are using timer1 overflow  
	//each digit must have a freq  of at least 50 Hz, we have 6 digits so a min freq is 50*6=300
	// (foce / prescaler) =  24mHz /1 = 24 Mhz
    //(clk to over flow  = 24Mhz / 2^16 = 366.21 hz
	T1CON = 0b01001101;
			//TMR1CS 01
			//T1CKS  00              11 (1:8)// 10 (1:4)//01 (1:2) 
			//SOSCEN 1 (I think?)
			//T1SYNC 1  
			//RD16   0
			//TMR1ON 1

	T1GCON = 0b000000000;
			//tmr1ge  0
			//t1gpol =0
			//t1gtm 0
			//t1gsmp 0
			//t1ggo 0
			//t1gcal 0
			//t1gss 00

	//24Mzh/8 = 3mHz
	//clk to overflow = 3/2^8
 


}
void startUp_GPIO(void){

    //portA setup
		TRISA  = 0;	//Set all port A pins to output
		LATA   = 0; //set output low
		ANCON0 = 0; //set pins to digital mode

	//	LATA = 0xff;//0b00100000;	//test to dec on

   //portB setup
		TRISB  = 0b00001000; //Set all port B pins to output//RB3 - CANRX
		LATB   = 0; //Set output low 
		ANCON0 = 0; //I think I need this
		ANCON1 = 0; //set it all to digital
		ODCON  = 0; //Open-drain capability is disabled
 

	//portC setup
		ODCON =0;
		TRISC = 0b10000000; //Set all port C pins to output
		LATC  = 0b00001000; //Set output low (testing negative)

	

	return;
}



void startUp_OSCILLATOR(void){
		// Set the internal oscillator to 64MHz
		//(I don't config using the structs below)
	   OSCCONbits.IRCF = 7;
	   OSCTUNEbits.PLLEN = 1;
	
	   //OSCCON = 0b11111110;
			//IDLEN =  0b1	
			//IRCF =   0b111
			//OSTS =   0b1
			//HFIOFS = 0b1
			//scs =    0b10 //(HF-INTOSC, I will change FOSC<3:0>, anyway)

       //OSCTUNE = 0b0100000;
			//INTSRCC = 0
			//PLLEN =   1
			//tune  =   000000

       //6Mhz 4pll to 24Mhz
		//OSCCON = 0b11111110;
			//pg 53
			//IDLEN 1
			//IRCF 111
			//OSTS 1
			//HFIOFS 1
			//scs 1x //00

        
        //OSCTUNE = 0b1100000;
			//intsrc 1
			//pllen 1
			//tun 0

	return;
}



void startUp_device(void){
	unsigned char segDigi[6];
	segDigi[0] = 1;
	segDigi[1] = 2;
	segDigi[2] = 3;
	segDigi[3] = 4;
	segDigi[4] = 5;
	segDigi[5] = 6;

	startUp_interrupts();
	startUp_OSCILLATOR();
	startUp_timer();
	startUp_GPIO();
	startUp_ECAN();


	setSegValues(segDigi);
	interrupts_on;
	return;

}


