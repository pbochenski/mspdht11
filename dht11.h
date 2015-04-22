/*
 * dth11.h
 *
 *  Created on: 20 kwi 2015
 *      Author: Pawel
 */

#ifndef DTH11_H_
#define DTH11_H_

#include <msp430.h>
#include <stdint.h>

//#define USING_16MHZ_CLK  1
#define USING_8MHZ_CLK  1
//#define USING_1MHZ_CLK  1

//define operation pin
#define DATAPORT 1
#define DATAPIN BIT6

int dth11_read(char* output);

#endif /* DTH11_H_ */
