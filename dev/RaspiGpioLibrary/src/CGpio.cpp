/*
 * CGpio.cpp
 *
 *  Created on: 2020/02/09
 *      Author: CountrySideEngineer
 */
#include "CGpio.h"
#include <iostream>
#include <assert.h>
#include "pigpio/pigpio.h"
#include "Log.h"

using namespace std;

/**
 * @brief	Default constructor
 */
CGpio::CGpio()
	: spi_handle_(-1)
	, spi_flgs_(0)
{
	this->isr_pin_map_.clear();

	CGpio::Initialize();
}

/**
 * @brief	Destructor.
 */
CGpio::~CGpio()
{
	CGpio::Finalize();
}

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
	this->CloseSpi();

	//Remove ISR handler.
	for (auto it = this->isr_pin_map_.begin();
			it != this->isr_pin_map_.end();
			it++)
	{
		uint pin = it->first;
		gpioSetISRFunc(pin, 0, 0, NULL);
	}
	this->isr_pin_map_.clear();

	gpioTerminate();
	this->spi_handle_ = (-1);
	this->spi_flgs_ = 0;

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

/**
 * @brief	Write GPIO pin level. If the value is 0, the pin is set low,
 * 			otherwise it is set high.
 * @param	pin	GPIO pin number.
 */
void CGpio::Write(uint8_t pin, uint8_t value)
{
	uint value_to_write = 0;
	if (0 == value) {
		value_to_write = PI_LOW;
	} else {
		value_to_write = PI_HIGH;
	}
	gpioWrite(pin, value_to_write);
}

/**
 * @brief	Read GPIO pin level, low or high.
 * @param	pin	GPIO pin number.
 * @return	Returns the GPIO pin level. Returns 0 if it is low, otherwise
 * 			returns 1.
 */
uint8_t CGpio::Read(uint8_t pin)
{
	return (uint8_t)gpioRead(pin);
}

/**
 * @param	Register interrupt object called when an interrutp detected on
 * 			the GPIO pin.
 * @param	pin	GPIO pin number an interrupt to be detected.
 * @param	edge	The change type the interrupt to be detected, hight to low
 * 					(low edge), low to high (high edge), or both.
 * @param	part	Pointer to object to handle the interruption.
 * @return	Returns the result of regist. Returns 0 if the regist succeeded,
 * 			otherwise return none-zero value.
 */
int CGpio::SetIsr(uint pin, uint edge, CPart* part)
{
	assert(nullptr != part);

	int set_isr_result = GPIO_ERROR_OK;
	if (this->isr_pin_map_.end() == this->isr_pin_map_.find(pin)) {
		//The pin has not been registered as interrupt service register.
		this->isr_pin_map_.insert(make_pair(pin, part));
		set_isr_result =
				gpioSetISRFunc(pin, edge, 0, CGpio::GpioInterruptHandle);
		if (PI_BAD_GPIO == set_isr_result) {
			set_isr_result = GPIO_ERROR_GPIO;
		} else if (PI_BAD_EDGE == set_isr_result) {
			set_isr_result = GPIO_ISR_BAD_EDGE;
		} else if (PI_BAD_ISR_INIT == set_isr_result) {
			set_isr_result = GPIO_ISR_BAD_INIT;
		} else {
			set_isr_result = GPIO_ERROR_OK;
		}
	} else {
		set_isr_result = GPIO_ISR_ALREADY_REGISTERED;
	}
	return set_isr_result;
}

/**
 * @brief	Setup SPI by SPI configration bit flags.
 * @param	spi_config	Reference of SPI configuration.
 * @return	Returns the over 0 value, SPI handle, if the operation succeeded,
 * 			otherwise under 0, minus value.
 */
int CGpio::SetSpi(const CSpi& spi_config)
{
	uint32_t spi_flg = 0;
	spi_flg |= (spi_config.GetMode() << SPI_CONFIG_INDEX_MODE_LOW);
	spi_flg |= (spi_config.GetActiveMode0() << SPI_CONFIG_INDEX_ACTIVE_MODE_CE0);
	spi_flg |= (spi_config.GetActiveMode1() << SPI_CONFIG_INDEX_ACTIVE_MODE_CE1);
	spi_flg |= (spi_config.GetActiveMode2() << SPI_CONFIG_INDEX_ACTIVE_MODE_CE2);
	spi_flg |= (spi_config.GetChannel() << SPI_CONFIG_INDEX_SPI_CHANNEL);

	return this->SetSpi(spi_config.GetClock(), spi_flg);
}

/**
 * @brief	Setup SPI by SPI configration bit flags.
 * @param	spi_clock	Source clock speed to synchronize.
 * @param	spi_flg		Bit array of SPI configuration.
 * @return	Returns the over 0 value, SPI handle, if the operation succeeded,
 * 			otherwise under 0, minus value.
 */
int CGpio::SetSpi(const int spi_clock, const uint32_t spi_flg)
{
	/*
	 * Deactivate Chip sElect(CE) pin before setup SPI.
	 * If the CE pin is not deactivated before the SPI setup, the receive
	 * action can not work. No data can be received.
	 */
	this->DeactivateCe(this->spi_flgs_);
	int setup_spi_result = this->spi_handle_;
	if (0 <= this->spi_handle_) {
		DLOG("SPI has already opened.");
		/*
		 * The SPI has already open.
		 * In this case, nothing to do!
		 */
	} else {
		int spi_result = spiOpen(0, spi_clock, spi_flg);
		if (0 <= spi_result) {
			DLOG("SPI open succeeded.");

			this->spi_handle_ = spi_result;
			this->spi_flgs_ = spi_flg;

			setup_spi_result = this->spi_handle_;
		} else {
			WLOG("SPI open failed.");

			/*
			 *	When opening SPI failed, reset the SPI handle.
			 */
			this->spi_flgs_ = 0;
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

	if (0 == (spi_flg & (0x0100))) {
		//Main channel
		ce_pin_0 = GPIO_PIN_MAIN_CE0;
		ce_pin_1 = GPIO_PIN_MAIN_CE1;

		this->DeactivateCe(ce_pin_0, spi_flg, SPI_CONFIG_INDEX_ACTIVE_MODE_CE0);
		this->DeactivateCe(ce_pin_1, spi_flg, SPI_CONFIG_INDEX_ACTIVE_MODE_CE1);
	} else {
		//AUX channel
		ce_pin_0 = GPIO_PIN_AUX_CE0;
		ce_pin_1 = GPIO_PIN_AUX_CE1;
		ce_pin_2 = GPIO_PIN_AUX_CE2;

		this->DeactivateCe(ce_pin_0, spi_flg, SPI_CONFIG_INDEX_ACTIVE_MODE_CE0);
		this->DeactivateCe(ce_pin_1, spi_flg, SPI_CONFIG_INDEX_ACTIVE_MODE_CE1);
		this->DeactivateCe(ce_pin_2, spi_flg, SPI_CONFIG_INDEX_ACTIVE_MODE_CE2);
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
	gpioSetMode(pin, PI_OUTPUT);
	if (0 == (spi_flg & (1 << spi_flg_index))) {
		//	Active when low, to deactivate ce, set GPIO level high.
		gpioWrite(pin, PI_HIGH);
	} else {
		gpioWrite(pin, PI_LOW);
	}
}

/**
 * @brief	Close SPI interface.
 */
void CGpio::CloseSpi()
{
	if (0 <= this->spi_handle_) {
		spiClose(this->spi_handle_);

		this->spi_handle_ = (-1);
	} else {
		DLOG("SPI port does not open or has already been closed.");
	}
}

/**
 * @brief	Receive data via SPI interface.
 * @param	ce_pin	Pin No. of SPI CE, Chip sElection.
 * @param[in]	data	Pointer to buffer contains data to send.
 * @param	data_size	Data size in "BYTE" unit to send.
 * @return	Returns the size of data transffered if succeeded. Otherwise
 * 			returns value under 0, meaning minus.
 * @remark	This method does not change CE pin level.
 */
int CGpio::SpiRead(uint8_t* data, const uint32_t data_size)
{
	assert(NULL != data);

	int read_result = GPIO_FATAL_ERROR;
	int read_byte = spiRead(this->spi_handle_, (char*)data, data_size);
	if (PI_BAD_HANDLE == read_byte) {
		read_result = SPI_ERROR_BAD_HANDLE;
	} else if (PI_BAD_SPI_COUNT == read_byte) {
		read_result = SPI_ERROR_BAD_COUNT;
	} else if (PI_SPI_XFER_FAILED == read_byte) {
		read_result = SPI_ERROR_XFER_FAILED;
	} else {
		read_result = read_byte;
	}
	return read_result;
}

/**
 * @brief	Send data via SPI interface.
 * @param[out]	data	Pointer to buffer contains data to send.
 * @param	data_size	Size of data to send.
 * @return	Returns the size of data sent if succeeded. Otherwise
 * 			returns value under 0, meaning minus.
 * @remark	This method does not change CE pin level.
 */
int CGpio::SpiWrite(const uint8_t* data, const uint32_t data_size)
{
	assert(NULL != data);

	int write_result = GPIO_FATAL_ERROR;
	int write_byte = spiWrite(this->spi_handle_, (char*)data, data_size);
	if (PI_BAD_HANDLE == write_byte) {
		write_result = SPI_ERROR_BAD_HANDLE;
	} else if (PI_BAD_SPI_COUNT == write_byte) {
		write_result = SPI_ERROR_BAD_COUNT;
	} else if (PI_SPI_XFER_FAILED == write_byte) {
		write_result = SPI_ERROR_XFER_FAILED;
	} else {
		write_result = write_byte;
	}
	return write_result;
}

