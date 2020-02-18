/*
 * CGpio.cpp
 *
 *  Created on: 2020/02/09
 *      Author: CountrySideEngineer
 */
#include "CGpio.h"
#include <iostream>
#include "pigpio/pigpio.h"
#include "Log.h"

using namespace std;

/**
 * @brief	Default constructor
 */
CGpio::CGpio()
	: spi_handle_(-1)
	, spi_flgs_(0)
{}

/**
 * @brief	Destructor.
 */
CGpio::~CGpio() {}

/**
 * @brief	Initialize GPIO.
 */
void CGpio::Initialize()
{
	int init_result = gpioInitialise();
	if (init_result < 0) {
		WLOG("GPIO initialize failed");
	} else {
		DLOG("GPIO initialize succeeded.");
	}
}

/**
 * @brief	Finalize GPIO.
 */
void CGpio::Finalize()
{
	gpioTerminate();
}

/**
 * @brief	Return pointer to CGpio instance.
 * 			CGpio object is SINGLETON.
 */
CGpio* CGpio::GetInstance()
{
	static CGpio instance_;	//Static, singleton object.

	return (CGpio*)(&instance_);
}

/**
 * @brief	Set GPIO pin mode, input or output.
 * @param	pin	GPIO pin number.
 * @param	direction	GPIO access direction, input or output.
 * @return	Returns 0 if OK, otherwise return none-zero value.
 */
int CGpio::SetMode(uint8_t pin, uint8_t direction)
{
	int set_mode_result = gpioSetMode(pin, direction);
	if (PI_BAD_MODE == set_mode_result) {
		WLOG("GPIO bad mode");

		return GPIO_ERROR_MODE;
	} else if (PI_BAD_GPIO == set_mode_result) {
		WLOG("GPIO bad GPIO.");

		return GPIO_ERROR_GPIO;
	} else {
		DLOG("GPIO set mode OK");

		return GPIO_ERROR_OK;
	}
}

/**
 * @brief	Returns the GPIO pin mode, input or output.
 * @param	pin	The GPIO pin number.
 * @return	The pin access direction, returns 0 if mode is input, 1 in output.
 */
uint8_t CGpio::GetMode(uint8_t pin)
{
	return gpioGetMode(pin);
}

int CGpio::SetSpi(const int spi_clock, const uint32_t spi_flg)
{
	int setup_spi_result = this->spi_handle_;
	if (0 <= this->spi_handle_) {
		/*
		 * The SPI has already open.
		 * In this case, nothing to do!
		 */
	} else {
		int spi_result = spiOpen(0, spi_clock, spi_flg);
		if (0 <= spi_result) {
			this->spi_handle_ = spi_result;
			this->spi_flgs_ = spi_flg;



			setup_spi_result = this->spi_handle_;
		} else {
			this->spi_handle_ = (-1);	//Reset SPI handle.
			if (PI_BAD_SPI_CHANNEL == spi_result) {
				setup_spi_result = SPI_ERROR_BAD_CHANNEL;
			} else if (PI_BAD_SPI_SPEED == spi_result) {
				setup_spi_result = SPI_ERROR_BAD_SPEED;
			} else if (PI_BAD_FLAGS == spi_result) {
				setup_spi_result = SPI_ERROR_BAD_FLGS;
			} else if (PI_NO_AUX_SPI == spi_result) {
				setup_spi_result = SPI_ERROR_AUX_SPI;
			} else if (PI_SPI_OPEN_FAILED == spi_result) {
				setup_spi_result = SPI_ERROR_OPEN_FAILED;
			} else {
				setup_spi_result = GPIO_FATAL_ERROR;
			}
		}
	}
	return setup_spi_result;
}

#define	GPIO_PIN_MAIN_CE0	(8)
#define	GPIO_PIN_MAIN_CE1	(9)
#define	GPIO_PIN_AUX_CE0	(18)
#define	GPIO_PIN_AUX_CE1	(17)
#define	GPIO_PIN_AUX_CE2	(16)
/**
 * @brief	Activate or deactivate SPI CEx pin.
 * @param	spi_flg	Bit data for SPI configuration.
 */
void CGpio::DeactivateCe(const uint32_t spi_flg)
{
	int ce_pin_0 = GPIO_PIN_MAIN_CE0;
	int ce_pin_1 = GPIO_PIN_MAIN_CE1;
	int ce_pin_2 = 0;

	if (0 == (spi_flg & (0x0010))) {
		//Main channel
		ce_pin_0 = GPIO_PIN_MAIN_CE0;
		ce_pin_1 = GPIO_PIN_MAIN_CE1;

		if (0 == spi_flg & (SPI_CONFIG_FLG_ACTIVE_MODE_CE0_HIGH)) {
			//CE0 is active when low -> deactive when high.
			gpioWrite(ce_pin_0, PI_HIGH);
		} else {
			//CE0 is active when high -> deactive when low.
			gpioWrite(ce_pin_0, PI_LOW);
		}
		if (0 == spi_flg & (SPI_CONFIG_FLG_ACTIVE_MODE_CE1_HIGH)) {
			//CE1 is active when low -> deactive when high.
			gpioWrite(ce_pin_1, PI_HIGH);
		} else {
			//CE1 is active when high -> deactive when low.
			gpioWrite(ce_pin_1, PI_LOW);
		}
	} else {
		//AUX channel
		ce_pin_0 = GPIO_PIN_AUX_CE0;
		ce_pin_1 = GPIO_PIN_AUX_CE1;
		ce_pin_2 = GPIO_PIN_AUX_CE2;

		if (0 == spi_flg & (SPI_CONFIG_FLG_ACTIVE_MODE_CE0_HIGH)) {
			//CE0 is active when low -> deactive when high.
			gpioWrite(ce_pin_0, PI_HIGH);
		} else {
			//CE0 is active when high -> deactive when low.
			gpioWrite(ce_pin_0, PI_LOW);
		}
		if (0 == spi_flg & (SPI_CONFIG_FLG_ACTIVE_MODE_CE1_HIGH)) {
			//CE1 is active when low -> deactive when high.
			gpioWrite(ce_pin_1, PI_HIGH);
		} else {
			//CE1 is active when high -> deactive when low.
			gpioWrite(ce_pin_1, PI_LOW);
		}
		if (0 == spi_flg & (SPI_CONFIG_FLG_ACTIVE_MODE_CE2_HIGH)) {
			//CE2 is active when low -> deactive when high.
			gpioWrite(ce_pin_2, PI_HIGH);
		} else {
			//CE2 is active when high -> deactive when low.
			gpioWrite(ce_pin_2, PI_LOW);
		}
	}
}

/**
 * @brief	Deactivate CE pin.
 * @param	pin	GPIO pin number.
 * @param	spi_flg	SPI configuration flg.
 * @param	spi_flg_index	SPI flag index.
 */
void CGpio::DeactivateCe(
		const int pin,
		const uint32_t spi_flg,
		const int spi_flg_index)
{
	if (0 == (spi_flg & (1 << spi_flg_index))) {
		//	Active when low, to deactivate ce, set GPIO level high.
		gpioWrite(pin, PI_HIGH);
	} else {
		gpioWrite(pin, PI_LOW);
	}

}
