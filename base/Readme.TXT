
                   Readme File for Code Example: ECAN Ex2
                 		     
             -----------------------------------------------------------------------------------------

This file contains the following sections:
1. Code Example Description
2. Folder Contents
3. Suggested Development Resources
4. Reconfiguring the project for a different PIC18F with ECAN module device
5. Revision History

NOTE: The example code makes use of Peripheral Library support available with MCC18.

1. Code Example Description:
----------------------------
In this code example, ECAN module in PIC18F46K80 is been configured in mode 1 or 2. Device communicates with (Microchip) CAN BUS Analyzer at 100Kbps or 125Kbps or 500Kbps or 1Mbps.

Connections:
	ECAN/LIN Daughterboard			   CAN BUS Analyzer(Microchip)                            PC
								
		CANH 	  <------------------------->	    CANH
         P1             DB9                         DB9                 USB  <------------------------->  USB
		CANL 	  <------------------------->	    CANL 

In ECAN.c file:
// ECAN Mode define, only can choose one mode
#define F_ECAN_Mode1      //ECAN mode 1
#define F_ECAN_Mode2      //ECAN mode 2

//ECAN RxFilter15 as Mask or not, 3 Masks could work at the same time
#define F_ECAN_Mask01      //use Mask 0 1
#define F_ECAN_RxF15Mask   //use RxF15 as mask

// ECAN bitrate define, only can choose one rate
#define F_ECAN_100      //100kbps
#define F_ECAN_125      //125kbps
#define F_ECAN_500      //500kbps
#define F_ECAN_1000     //1Mbps

In  (Microchip) CAN BUS Analyzer PC soft:
bps set:          Setup>> Hardware setup>>CAN Bitrate Control
                  Choose 100Kbps or 125Kbps or 500Kbps or 1000Kbps, 
                  then use 'Set' button to save the config

hex/decimal:      View>>View in hexadecmal

Receive window:   Tools>>Rolling Trace

Send window:      Tools>>Transmit
                  ID: 0x196 0x19E can be received, the board will ignore all the other ID

On PIC18 Explorer Demo Board:
Send message:     RB0 button


2. Folder Contents:
-------------------
This folder refers the following sub-folders:
a. C:\MCC18\bin\LKR
        This folder will have the device LKR file, it is used for building the project. 
	This file was provided with the MCC18 toolsuite.

b. C:\MCC18\h
        This folder contains C header files useful in building this
        project. Device register and bit definitions are provided in
        the *.h file that follows the device name. These files were provided
        with the MCC18 toolsuite.The peripheral library header files contains the macro definition & API
		prototypes.

c. C:\MCC18\lib
        This folder contains library archive files, which are a
        collection of precompiled object files. The file
        named "*.lib" in the name of device contains the C run-time, start-up & Peripheral
        library. These file were provided with the MCC18 toolsuite.

d. C:\MCC18\src
        This folder contains all the C ,Assembler, Peripheral library source files (*.c,
        *.s) used in demonstrating the described example. 
		
e. C:\MCC18\doc
	This folder contains the Peripheral Library description for all modules.		


3. Suggested Development Resources:
-----------------------------------
	a. MPLAB IDE with MCC18 v3.36 or above
        b. PIC18 Explorer Demo Board with PIC18F46K80 (PIC18F66K80 family) controller + ECAN/LIN Daughterboard 
        c. Microchip CAN BUS Analyzer or other High speed CAN BUS Analyzer

4. Reconfiguring the project for a different PIC18F with ECAN module device:
-------------------------------------------------------------
The Project/Workspace can be easily reconfigured for any PIC18F with ECAN module device.
Please use the following general guidelines:
        a. Change device selection within MPLAB IDE to a PIC18F with ECAN module device of
        your choice by using the following menu option:
        MPLAB IDE>>Configure>>Select Device

        b. To configure the device settings, either choose from the MPLAB IDE>>Configure>>"Configuration bits" 
        and configure for necessary settings or the corresponding configuration
	macros to be added into the code can be obtained from device.INC file 
	at the following default location:
	"C:\MCC18\mpasm"
	These macros can be added as depicted in example code.

        c. Re-build the MPLAB project using the menu option:
        MPLAB IDE>>Project>>Build All

        d. Download the hex file into the device and run.

5. Revision History :
---------------------
        12/20/2010 - Initial Release of the Code Example
