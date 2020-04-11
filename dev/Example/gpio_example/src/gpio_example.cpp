//============================================================================
// Name        : gpio_example.cpp
// Author      : CountrySideEngineer
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <time.h>
#include "CGpio.h"
#include "CPart.h"
using namespace std;

#define	LED_GPIO_PIN		(26)
#define	GPIO_PIN_INPUT		(0)
#define	GPIO_PIN_OUTPUT		(1)
#define	LED_GPIO_PIN_DIRECTION	(GPIO_PIN_OUTPUT)
#define	LED_BLINK_COUNT		(10)
int main() {

	//GPIO pin No.26 / Mode = OUTPUT
	CPart led(LED_GPIO_PIN, LED_GPIO_PIN_DIRECTION);

	for (int loop_index = 0; loop_index < LED_BLINK_COUNT; loop_index++) {
		uint8_t led_on_off = (loop_index % 2);
		led.Write(led_on_off);

		sleep(1);
	}

	led.Write(0);	//Turn off.
	return 0;
}
