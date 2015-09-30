

void set_GPIO(void){

    //portA setup
		TRISA  = 0;	//Set all port A pins to output
		LATA   = 0; //set output low
		ANCON0 = 0; //set pins to digital mode
	
   //portB setup
		TRISB  = 0; //Set all port B pins to output
		LATB   = 0; //Set output low
		ANCON1 = 0; //set it all to digital
		ODCON  = 0; //Open-drain capability is disabled 

	//portC setup
		TRISC = 0; //Set all port C pins to output
		LATC  = 0 //Set output low
}	

void set_interrupts(void){
	
	INTCON = 0b11100100;//global interrupt bit on, 
						//peripheral interrupt on,
						//both timer interrupt on
						//hardware interrupt off,
	INTCON2 = 0b1000100;
	INTCON3 = 0;
}

void set_OSCILLATOR(void){
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
}

void set_can(void){


}

