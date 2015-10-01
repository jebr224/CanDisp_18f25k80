
#include <p18cxxx.h>
#include "ECAN.h"
#include "startUp.h"



    //I was planning on using a crystal, but this pretty
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
	
	PIR5 &= 0b111111100; //clear the interrupt flag so that another interrupt can happen
	
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

	PIR1 &= 0b1111011;///clear the interrupt flag (TM0)so that another interrupt can happen
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

	INTCON = 0b11100100;//global interrupt bit on, 
						//peripheral interrupt on,
						//both timer interrupt on
						//hardware interrupt off,
	INTCON2 = 0b1000100;
	INTCON3 = 0;// no external interupts

	//PIR1

	PIE1 = 0b00000100; //TMR int is enabled
	PIE2 = 0;
	PIE3 = 0;
	PIE4 = 0;
	PIE5 = 0b00000011; //RXB1IE, and RXB0IE 


	IPR1 = 0b00000000; //TMR is low priority; 0b00000x00 where x is the bit that matters
	IPR2 = 0;
	IPR3 = 0;
	IPR4 = 0;
	IPR5 = 0b00000011;//RXB1IE, and RXB0IE  are high priority
	return;
}


void startUp_GPIO(void){

    //portA setup
		TRISA  = 0;	//Set all port A pins to output
		LATA   = 0; //set output low
		ANCON0 = 0; //set pins to digital mode
	
   //portB setup
		TRISB  = 0; //Set all port B pins to output
		LATB   = 0; //Set output low
		ANCON0 = 0; //I think I need this
		ANCON1 = 0; //set it all to digital
		ODCON  = 0; //Open-drain capability is disabled 

	//portC setup
		TRISC = 0; //Set all port C pins to output
		LATC  = 0; //Set output low

	return;
}



void startUp_OSCILLATOR(void){
	//external osc freq will be 6Mhz
	//4X pll, mean system freq will be 24 Mhz
	
	OSCCON = 0b11111000;
			//pg 53
			//IDLEN 1
			//IRCF 111
			//OSTS 1
			//HFIOFS 0
			//scs 00
	OSCTUNE = 0b1100000;
			//intsrc 1
			//pllen 1
			//tun 0

	return;
}



void startUp_device(void){

	startUp_interrupts();
	startUp_OSCILLATOR();
	startUp_GPIO();
	startUp_ECAN();

	return;

}


