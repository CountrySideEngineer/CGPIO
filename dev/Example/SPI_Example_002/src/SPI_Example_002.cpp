//============================================================================
// Name        : SPI_Example_002.cpp
// Author      : CountrySideEngineer
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include "cgpio/CSpi.h"
#include "cgpio/CPart.h"
#include "cgpio/CGpio.h"
#include "CMDK001.h"
#include "log.h"
using namespace std;

#define	PIN_SPI0_CE0		(8)
#define	PIN_SPI0_CE1		(7)
#define	SPI_BUFF_SIZE		(10)

int main() {
	uint8_t ce_pin = PIN_SPI0_CE0;
	CMDK001 mdk001(ce_pin, CPart::GPIO_PIN_OUTPUT);

	mdk001.InitDevice();
	mdk001.ExitShutdownMode();
	mdk001.SetContinuousMode();

	int16_t int_part = 0;
	uint16_t dec_part = 0;
	while (1) {
		mdk001.ReadSensorValue();
		mdk001.GetSensorValue(&int_part, &dec_part);

		DLOG("[CMDK001]%5d.%04d", int_part, dec_part);
		sleep(1);
	}

	return 0;
}
