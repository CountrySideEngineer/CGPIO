//============================================================================
// Name        : ISR_Example_001.cpp
// Author      : CountrySideEngineer
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <cstdint>
#include "cgpio/raspigpio.h"
#include "CButton.h"
#include "log.h"
using namespace std;

#define	GPIO_PIN_INPUT				(0)
#define	GPIO_PIN_OUTPUT				(1)
#define	LED_GPIO_PIN_DIRECTION		(GPIO_PIN_OUTPUT)
#define	LED_GPIO_PIN				(26)
#define	BUTTON_GPIO_PIN_DIRECTION	(GPIO_PIN_INPUT)
#define	BUTTON_GPIO_PIN				(13)
#define	BUTTON_CHATTERING_TIME		(30)	//30milli second.

int main() {
	CPart ledPart(LED_GPIO_PIN, LED_GPIO_PIN_DIRECTION);
	CButton button(&ledPart,
			BUTTON_GPIO_PIN,
			BUTTON_GPIO_PIN_DIRECTION,
			CPart::ISR_EDGE_EITHER,
			BUTTON_CHATTERING_TIME);
	button.SetInterruptPart(&ledPart);

	while (1) {
		//Main loop
	}

	return 0;
}
