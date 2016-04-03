
#define genericInterface


#include "comm.h"
#include "seg.h"
#include "ECAN.h"
#include "ws22.def"
#include <p18cxxx.h>

//this is some 1990's C codeing

extern unsigned char temp_EIDH; //find this symbol, and link me  to it
extern unsigned char temp_EIDL;
extern unsigned char temp_SIDH;
extern unsigned char temp_SIDL;
extern unsigned char temp_DLC;
extern unsigned char temp_data[8];

extern unsigned char g_dispValues[6];

/*
void newCanMessage(void){
	unsigned int id;
	unsigned char idLow, idHigh;
	unsigned int temp;
	
	
	ECAN_Receive();

	 id = ((temp_SIDH & 0b11100000) << 8) & (temp_SIDL) ;
	
	//if can message is speed, update seg values
	if( id == mcBaseAddress +  mc_velocityMes ){
		//Vehicle Velocity 63 .. 32 m/s Vehicle velocity in metres / second.
		float *velocity;
		velocity = (float*) temp_data + 3;
		temp = (unsigned int) *velocity;
		g_dispValues[0] =  temp / 100;
		g_dispValues[1] =  temp % 100 / 10;
		g_dispValues[2] =  temp % 10;
	}
	//if can message is current, update seg values
	else  if( id == mcBaseAddress + mc_curentVoltageMes ){
		//Bus Current 63 .. 32 A Current drawn from the DC bus by the controller
		float *current;
		current = (float *) temp_data + 3;
		temp = (unsigned int) *current;

		if(temp < 0){
			//RC1 //turn negative sign on. Sink
			LATCbits.LATC1 = 0;
		}else{
			//RC1  //turn negative sign off. sink
			LATCbits.LATC1 = 1;
		}

		g_dispValues[3] = temp / 100;
		g_dispValues[4] = temp % 100 / 10;
		g_dispValues[5] = temp % 10;
	}

	//	g_dispValues[1] = 3;
	id = ((temp_SIDH & 0b11100000) << 8) & (temp_SIDL) ;
	if(id == 0x0224){
     	int *number;
		number = (int *) temp_data;
//		setFrist3SegValues(*number);
			

	}else 
	if(id == 0x0225){
     	int *number;
		number = (int *) temp_data;
//		setSecondSegValues(*number);
			
	}


	return ; 
}

*/





#ifdef  genericInterface

int secondNumberUpdate(){
	unsigned int id;
	unsigned char test;
	int msg1 = 122;
    int msg2 = 133;
	
	test = ECAN_Receive();
	if(1){

		
	//	setFirstNumber(msg2);

		id = ((temp_SIDH & 0b00000111 ) << 8) | (temp_SIDL) ;
		if( id == 0x0224 ){
			int *data;
			setFirstNumber(msg1);
			data =(int *) temp_data;
			setSecondNumber(*data);
			return *data;
		}
		
	}
}