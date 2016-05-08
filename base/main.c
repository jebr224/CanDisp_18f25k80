/**********************************************************************
* 2010 Microchip Technology Inc.
*
* FileName:        main.c
* Dependencies:    main (.h) files if applicable, see below
* Processor:       PIC18F66K80 family
* Linker:          MPLINK 4.37+
* Compiler:        C18 3.36+
*
* SOFTWARE LICENSE AGREEMENT:
* Microchip Technology Incorporated ("Microchip") retains all 
* ownership and intellectual property rights in the code accompanying
* this message and in all derivatives hereto.  You may use this code,
* and any derivatives created by any person or entity by or on your 
* behalf, exclusively with Microchip's proprietary products.  Your 
* acceptance and/or use of this code constitutes agreement to the 
* terms and conditions of this notice.
*
* CODE ACCOMPANYING THIS MESSAGE IS SUPPLIED BY MICROCHIP "AS IS". NO 
* WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT 
* NOT LIMITED TO, IMPLIED WARRANTIES OF NON-INFRINGEMENT, 
* MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS 
* CODE, ITS INTERACTION WITH MICROCHIP'S PRODUCTS, COMBINATION WITH 
* ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
*
* YOU ACKNOWLEDGE AND AGREE THAT, IN NO EVENT, SHALL MICROCHIP BE 
* LIABLE, WHETHER IN CONTRACT, WARRANTY, TORT (INCLUDING NEGLIGENCE OR
* BREACH OF STATUTORY DUTY), STRICT LIABILITY, INDEMNITY, 
* CONTRIBUTION, OR OTHERWISE, FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
* EXEMPLARY, INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, FOR COST OR 
* EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE CODE, HOWSOEVER 
* CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE
* DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT ALLOWABLE BY LAW, 
* MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY RELATED TO THIS
* CODE, SHALL NOT EXCEED THE PRICE YOU PAID DIRECTLY TO MICROCHIP 
* SPECIFICALLY TO HAVE THIS CODE DEVELOPED.
*
* You agree that you are solely responsible for testing the code and 
* determining its suitability.  Microchip has no obligation to modify,
* test, certify, or support the code.
*
* REVISION HISTORY:
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Author           Date      	Comments on this revision
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Manning C.       12/1/2010	First release of source file
* John Broadbent   9/30/2015    CanDisp
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*
* ADDITIONAL NOTES:
* Code Tested on:
* Changing to code for PIC18f25k50 (JB) Not tested
*
* DESCRIPTION:
* This is the code base for the CanDisp project.
*********************************************************************/



/*********************************************************************
*
*                            Includes 
*
*********************************************************************/
#include <p18cxxx.h>
#include "ECAN.h"
#include "startUp.h"
/*
extern unsigned char temp_EIDH;
extern unsigned char temp_EIDL;
extern unsigned char temp_SIDH;
extern unsigned char temp_SIDL;
extern unsigned char temp_DLC;
extern unsigned char temp_data[8];
*/



/*********************************************************************
*
*                       Config Bit Settings
*
*********************************************************************/
#pragma config XINST = OFF


/*********************************************************************
*
*                             Defines 
*
*********************************************************************/
#define BTN1        PORTBbits.RB0

#define PRESSED     0

#define TRUE    1
#define FALSE   0

#define DEVICE_OSC  64
#define ONE_MS      (unsigned int)(DEVICE_OSC/4)*80


/*********************************************************************
*
*                        Function Prototypes 
*
*********************************************************************/
void Delay();




/*********************************************************************
*
*                            Main Function 
*
*********************************************************************/
void main(void)
{   
	unsigned char u = 0,j = 0,k = 0x12;
	unsigned char testValues[3]={1,2,4};
	int  t = 123;
    unsigned int i =0;
 
    //InitDevice();
	startUp_device();//startup.c

	setFirstNumber(t);

   while(1)
    {
		i = i+1;
		j = j+1;
		Delay();
		Delay();
		Delay();
		Delay();
		Delay();
		Delay();
		Delay();
		Delay();
		Delay();
		Delay();
		Delay();
		Delay();
		Delay();
		Delay();        


		setFirstNumber(i);

		ECAN_Transmit_user_msg(j,u,0,testValues);
		
		if( ECAN_Receive () ){
			int id;
			//ECAN_Transmit_user_msg(0x11,0x11,2,testValues);
				id = ((temp_SIDH & 0b00000111 ) << 8) | (temp_SIDL) ;
			if(id == 0x0224)
			{
				if(*temp_data == 0x01 && temp_DLC ==3 ){
					int number = (unsigned int) temp_data[1];
					setSecondNumber(number);

					}
			}
	
		
    	}
}



}

/*********************************************************************
*
*                 Perform a simple delay 
*
*********************************************************************/
void Delay()
{
		volatile int j = 0xffff;
		while(j){
			j--;
		}

   
}    
