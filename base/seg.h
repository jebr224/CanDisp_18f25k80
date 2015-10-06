


#ifndef _SEG_H
#define _SEG_H

#define TRUE    1
#define FALSE   0


void updateSeg(void);            //internal
void BCDpins(unsigned char num); //internal

unsigned char setSegValues(unsigned char* data);
unsigned char setFrist3SegValues(unsigned char* data);
unsigned char setSecondSegValues(unsigned char* data);




#endif
