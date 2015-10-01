/**********************************************************************
* 2010 Microchip Technology Inc.
*
* FileName:        ECAN.c
* Dependencies:    ECAN (.h) & other files if applicable, see below
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
* Author        Date      	Comments on this revision
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Manning C.    12/1/2010	First release of source file
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*
* ADDITIONAL NOTES:
* Code Tested on:
* PIC18 Explorer Demo Board with PIC18F46K80 (PIC18F66K80 family) controller + ECAN/LIN Daughterboard 
* 
*
* DESCRIPTION:
* In this example, CPU is initially configured to run from external 
* secondary osc and then clock switching is initiated to run from 
* Internal FRC.
*********************************************************************/




/*********************************************************************
*
*                            Includes 
*
*********************************************************************/
#include <p18cxxx.h>
#include "ECAN.h"


/*********************************************************************
*
*                             Defines 
*
*********************************************************************/
// ECAN Mode define, only can choose one mode
#define F_ECAN_Mode1      //ECAN mode 1
//#define F_ECAN_Mode2      //ECAN mode 2

//ECAN RxFilter15 as Mask or not, 3 Masks could work at the same time
#define F_ECAN_Mask01
//#define F_ECAN_RxF15Mask

// ECAN bitrate define, only can choose one rate
//#define F_ECAN_100      //100kbps
//#define F_ECAN_125      //125kbps
//#define F_ECAN_500      //500kbps
#define F_ECAN_1000     //1Mbps

// ECAN 
#define   F_ECANMode2_FP        CANCON&0x0F
#define   F_ECANFIFO_0          RXB0CONbits.RXFUL
#define   F_ECANFIFO_1          RXB1CONbits.RXFUL
#define   F_ECANFIFO_2          B0CONbits.RXFUL
#define   F_ECANFIFO_3          B1CONbits.RXFUL
#define   F_ECANFIFO_4          B2CONbits.RXFUL
#define   F_ECANFIFO_5          B3CONbits.RXFUL
#define   F_ECANFIFO_6          B4CONbits.RXFUL
#define   F_ECANFIFO_7          B5CONbits.RXFUL


/*********************************************************************
*
*                            Global Variables 
*
*********************************************************************/
unsigned char temp_EIDH;
unsigned char temp_EIDL;
unsigned char temp_SIDH;
unsigned char temp_SIDL;
unsigned char temp_DLC;
unsigned char temp_D0;
unsigned char temp_D1;
unsigned char temp_D2;
unsigned char temp_D3;
unsigned char temp_D4;
unsigned char temp_D5;
unsigned char temp_D6;
unsigned char temp_D7;





/*********************************************************************
*
*                       Configure the CAN Module
*
*********************************************************************/
void startUp_ECAN(void)
{
    // Enter CAN module into config mode
    CANCON = 0x80;    //REQOP<2:0>=100
    while(!(CANSTATbits.OPMODE ==0x04));

    // Enter CAN module into Mode 1 or 2
    #ifdef F_ECAN_Mode1
    ECANCON = 0x40;
    #endif

    #ifdef F_ECAN_Mode2
    ECANCON = 0x80;
    #endif

    // Initialize CAN Timing  
    #ifdef F_ECAN_100
        //  100 Kbps @ 64MHz  
        BRGCON1 = 0x93; //0001 1111     //SJW=3TQ     BRP  19
        BRGCON2 = 0xB8; //1011 1000     //SEG2PHTS 1    sampled once  PS1=8TQ  PropagationT 1TQ  
        BRGCON3 = 0x05; //0000 0101     //PS2  6TQ
    #endif
    
    #ifdef F_ECAN_125
        //  125 Kbps @ 64MHz  
        BRGCON1 = 0x8F; //0000 0111     //SJW=3TQ     BRP  15
        BRGCON2 = 0xB8; //1011 1000     //SEG2PHTS 1    sampled once  PS1=8TQ  PropagationT 1TQ  
        BRGCON3 = 0x05; //0000 0101     //PS2  6TQ
    #endif

    #ifdef  F_ECAN_500
        //  500 Kbps @ 64MHz 
        BRGCON1 = 0x83; //0000 0111     //SJW=3TQ     BRP  3
        BRGCON2 = 0xB8; //1011 1000     //SEG2PHTS 1    sampled once  PS1=8TQ  PropagationT 1TQ  
        BRGCON3 = 0x05; //0000 0101     //PS2  6TQ
    #endif

    #ifdef F_ECAN_1000
        //  1   Mbps @ 64MHz  
        BRGCON1 = 0x81; //0000 0011     //SJW=3TQ     BRP  1
        BRGCON2 = 0xB8; //1011 1000     //SEG2PHTS 1    sampled once  PS1=8TQ  PropagationT 1TQ  
        BRGCON3 = 0x05; //0000 0101     //PS2  6TQ
    #endif 
    
    // Setup Programmable buffers
    //  B0 is a receive buffer AND B2,B3,B4,B5 are Transmit buffers
    BSEL0 = 0xFC;   //1111 11--
    
    // Initialize Receive Masks
    #ifdef F_ECAN_Mask01
    RXM0EIDH = 0x00;    // 0's for EID and SID
    RXM0EIDL = 0x00;
    RXM0SIDH = 0xFF;    // Standard ID FILTER
    RXM0SIDL = 0xE0;
    
    RXM1EIDH = 0x00;    
    RXM1EIDL = 0x00;
    RXM1SIDH = 0xFF;
    RXM1SIDL = 0xE0;
    #endif 

    #ifdef F_ECAN_RxF15Mask
    // RxF15 as msak
    RXF15EIDH = 0x00;
    RXF15EIDL = 0x00;
    RXF15SIDH = 0xFF;
    RXF15SIDL = 0xE0;
    #endif 

    // Enable Filters
    // 0,1 Filter
    RXFCON0 = 0x03;     // 
    RXFCON1 = 0x00;     //Disable all
    
    // Assign Filters to Masks
    #ifdef F_ECAN_Mask01
    MSEL0 = 0xF4;     //Assign Filters 0 to Mask 0 F1 to MASK 1   // No mask
    MSEL1 = 0xFF;     //Assign Filters 4-7 to       // No mask
    MSEL2 = 0xFF;     //Assign Filters 8-11 to      // No mask
    MSEL3 = 0xFF;     //Assign Filters 12-15 to     // No mask
    #endif 
    
    #ifdef F_ECAN_RxF15Mask
    MSEL0 = 0xFA;     //Assign Filters 0-1 to Mask 3 // and F2-3  No mask
    MSEL1 = 0xFF;     //Assign Filters 4-7 to       // No mask
    MSEL2 = 0xFF;     //Assign Filters 8-11 to      // No mask
    MSEL3 = 0xFF;     //Assign Filters 12-15 to     // No mask
    #endif 

    // Assign Filters to Buffers
    #ifdef F_ECAN_Mode1
    //Assign the rest of the buffers with no filter
    RXFBCON0 = 0x10;
    RXFBCON1 = 0xFF;
    
    RXFBCON2 = 0xFF;
    RXFBCON3 = 0xFF;
    RXFBCON4 = 0xFF;
    RXFBCON5 = 0xFF;
    RXFBCON6 = 0xFF;
    RXFBCON7 = 0xFF;
    #endif

    // Initialize Receive Filters
    //  Filter 0 = 0x196
    RXF0EIDH = 0x00;
    RXF0EIDL = 0x00;
    RXF0SIDH = 0x32;
    RXF0SIDL = 0xC0;
    //  Filter 1 = 0x19e
    RXF1EIDH = 0x00;
    RXF1EIDL = 0x00;
    RXF1SIDH = 0x33;
    RXF1SIDL = 0xC0;

    // Enter CAN module into normal mode
    CANCON = 0x00;
    while(CANSTATbits.OPMODE==0x00);

    // Set Receive Mode for buffers
    RXB0CON = 0x00;
    RXB1CON = 0x00;

}

/*********************************************************************
*
*                Check the buffers, if it have message
*
*********************************************************************/
unsigned char ECAN_Receive(void)
{
    unsigned char RXMsgFlag;
    unsigned char F_ECANFIFO[8];

    RXMsgFlag = 0x00;
    
    #ifdef F_ECAN_Mode1
    if (RXB0CONbits.RXFUL) //CheckRXB0
    {
        temp_EIDH = RXB0EIDH;
        temp_EIDL = RXB0EIDL;
        temp_SIDH = RXB0SIDH;
        temp_SIDL = RXB0SIDL;
        temp_DLC = RXB0DLC;
        temp_D0 = RXB0D0;
        temp_D1 = RXB0D1;
        temp_D2 = RXB0D2;
        temp_D3 = RXB0D3;
        temp_D4 = RXB0D4;
        temp_D5 = RXB0D5;
        temp_D6 = RXB0D6;
        temp_D7 = RXB0D7;
        RXB0CONbits.RXFUL = 0;
        RXMsgFlag = 0x01;
    }
    else if (RXB1CONbits.RXFUL) //CheckRXB1
    {
        temp_EIDH = RXB1EIDH;
        temp_EIDL = RXB1EIDL;
        temp_SIDH = RXB1SIDH;
        temp_SIDL = RXB1SIDL;
        temp_DLC = RXB1DLC;
        temp_D0 = RXB1D0;
        temp_D1 = RXB1D1;
        temp_D2 = RXB1D2;
        temp_D3 = RXB1D3;
        temp_D4 = RXB1D4;
        temp_D5 = RXB1D5;
        temp_D6 = RXB1D6;
        temp_D7 = RXB1D7;
        RXB1CONbits.RXFUL = 0;
        RXMsgFlag = 0x01;
    }
    else if (B0CONbits.RXFUL) //CheckB0
    {
        temp_EIDH = B0EIDH;
        temp_EIDL = B0EIDL;
        temp_SIDH = B0SIDH;
        temp_SIDL = B0SIDL;
        temp_DLC = B0DLC;
        temp_D0 = B0D0;
        temp_D1 = B0D1;
        temp_D2 = B0D2;
        temp_D3 = B0D3;
        temp_D4 = B0D4;
        temp_D5 = B0D5;
        temp_D6 = B0D6;
        temp_D7 = B0D7;
        
        B0CONbits.RXFUL = 0;
        RXMsgFlag = 0x01;
    }
    #endif

    #ifdef F_ECAN_Mode2
    F_ECANFIFO[0]=RXB0CONbits.RXFUL;
    F_ECANFIFO[1]=RXB1CONbits.RXFUL;
    F_ECANFIFO[2]=B0CONbits.RXFUL;
    F_ECANFIFO[3]=B1CONbits.RXFUL;
    F_ECANFIFO[4]=B2CONbits.RXFUL;
    F_ECANFIFO[5]=B3CONbits.RXFUL;
    F_ECANFIFO[6]=B4CONbits.RXFUL;
    F_ECANFIFO[7]=B5CONbits.RXFUL;
    
    if  (F_ECANFIFO[F_ECANMode2_FP])
    {
    switch (F_ECANMode2_FP)
    {
    case 0:
    {
        temp_EIDH = RXB0EIDH;
        temp_EIDL = RXB0EIDL;
        temp_SIDH = RXB0SIDH;
        temp_SIDL = RXB0SIDL;
        temp_DLC = RXB0DLC;
        temp_D0 = RXB0D0;
        temp_D1 = RXB0D1;
        temp_D2 = RXB0D2;
        temp_D3 = RXB0D3;
        temp_D4 = RXB0D4;
        temp_D5 = RXB0D5;
        temp_D6 = RXB0D6;
        temp_D7 = RXB0D7;
        RXB0CONbits.RXFUL = 0;
        RXMsgFlag = 0x01;
        break;
    }
    case 1:
    {
        temp_EIDH = RXB1EIDH;
        temp_EIDL = RXB1EIDL;
        temp_SIDH = RXB1SIDH;
        temp_SIDL = RXB1SIDL;
        temp_DLC = RXB1DLC;
        temp_D0 = RXB1D0;
        temp_D1 = RXB1D1;
        temp_D2 = RXB1D2;
        temp_D3 = RXB1D3;
        temp_D4 = RXB1D4;
        temp_D5 = RXB1D5;
        temp_D6 = RXB1D6;
        temp_D7 = RXB1D7;
        RXB1CONbits.RXFUL = 0;
        RXMsgFlag = 0x01;
        break;
    }
    default:
        break;
    }
    }
    #endif 
    
    

    if  (RXMsgFlag == 0x01)
    {
        RXMsgFlag = 0x00;
        PIR5bits.RXB1IF = 0; //A CAN Receive Buffer has received a new message 
        return TRUE;
    }
    else
    {
        return FALSE;
    }    
}



/*********************************************************************
*
*                      Transmit Sample Mesaage
*
*********************************************************************/
void ECAN_Transmit(void)
{
    TXB0EIDH = 0x00;
    TXB0EIDL = 0x00;
    
    //0x35E    0110 1011 110
    TXB0SIDH = 0x6B;
    TXB0SIDL = 0xC0;

    TXB0DLC = 0x03;
    TXB0D0 = 0xAA;
    TXB0D1 = 0xCC;
    TXB0D2 = 0x55;
    TXB0D3 = 0x00;
    TXB0D4 = 0x00;
    TXB0D5 = 0x00;
    TXB0D6 = 0x00;
    TXB0D7 = 0x00;
    
    TXB0CONbits.TXREQ = 1; //Set the buffer to transmit

    
}

