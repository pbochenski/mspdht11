/*
 * dth11.c
 *
 *  Created on: 20 kwi 2015
 *      Author: Pawel
 */
#include "dth11.h"

#if DATAPORT == 1
#define dataPortDir P1DIR
#define dataPortOut P1OUT
#define dataPortIn  P1IN
#elif DATAPORT == 2
#define dataPortDir P2DIR
#define dataPortOut P2OUT
#define dataPortIn  P2IN
#else
#define dataPortDir P3DIR
#define dataPortOut P3OUT
#define dataPortIn  P3IN
#endif


#define TST(x,y)	(x & (y))
#define SET(x,y)	(x|= (y))
#define CLR(x,y)	(x &= ~(y))
#define TOG(x,y)	(x ^= (y))

void delay(uint16_t milis);
void delayMicro();
void delay40Micro();

uint8_t _count = 13;
uint8_t MAXTIMINGS = 85;

int dth11_read(char* output) {
	uint8_t laststate = DATAPIN;
	uint8_t counter = 0;
	uint8_t j = 0, i;
	uint8_t data[5];

	__disable_interrupt();

	data[0] = data[1] = data[2] = data[3] = data[4] = 0;

	SET(dataPortDir, DATAPIN);		// Set Data pin to output direction
	CLR(dataPortOut, DATAPIN); 		// Set output to low
	delay(18); 	// Low for at least 18ms
	SET(dataPortOut, DATAPIN);
	delay40Micro();		// High for at 20us-40us
	CLR(dataPortDir, DATAPIN);		// Set data pin to input direction

	// read in timings
	for (i = 0; i < MAXTIMINGS; i++) {
		counter = 0;
		while ( TST(dataPortIn, DATAPIN) == laststate) {

			counter++;
			delayMicro();
			if (counter == 255) {
				break;
			}
		}
		laststate = TST(dataPortIn, DATAPIN);

		if (counter == 255)
			break;

		// ignore first 3 transitions
		if ((i >= 4) && (i % 2 == 0)) {
			// shove each bit into the storage bytes
			data[j / 8] <<= 1;
			if (counter > _count)
				data[j / 8] |= 1;
			j++;
		}

	}

	__enable_interrupt();

	// check we read 40 bits and that the checksum matches
	if ((j >= 40)
			&& (data[4] == ((data[0] + data[1] + data[2] + data[3]) & 0xFF))) {
		output[0] = data[0];
		output[1] = data[2];
		return 1;
	}

	return 0;

}

void delayMicro() {
#ifdef USING_16MHZ_CLK
	__delay_cycles(16);
#endif
#ifdef USING_8MHZ_CLK
	__delay_cycles(8);
#endif
#ifdef USING_4MHZ_CLK
	__delay_cycles(4);
#endif
#ifdef USING_1MHZ_CLK
	__delay_cycles(1);
#endif
}

void delay40Micro(){
#ifdef USING_16MHZ_CLK
	__delay_cycles(16*30);
#endif
#ifdef USING_8MHZ_CLK
	__delay_cycles(8*40);
#endif
#ifdef USING_4MHZ_CLK
	__delay_cycles(4*40);
#endif
#ifdef USING_1MHZ_CLK
	__delay_cycles(1*40);
#endif
}

void delay(uint16_t milis) {
	while (milis--) {
#ifdef USING_16MHZ_CLK
		__delay_cycles(16000);
#endif
#ifdef USING_8MHZ_CLK
		__delay_cycles(8000);
#endif
#ifdef USING_4MHZ_CLK
		__delay_cycles(4000);
#endif
#ifdef USING_1MHZ_CLK
		__delay_cycles(1000);
#endif
	}
}
