/*
 * CPart.cpp
 *
 *  Created on: 2020/02/09
 *      Author: CountrySideEngineer
 */
#include <assert.h>
#include "CPart.h"
#include "pigpio/pigpio.h"
#include "CGpio.h"
#include "CSpi.h"

/**
 * @brief	Default constructor.
 */
CPart::CPart()
	: gpio_(NULL)
	, pin_(0)
	, mode_(0)
	, chattering_time_(0)
{}

/**
 * @brief	Constructor with parameters, GPIO pin number, GPIO access direction
 * 			input or output, and pointer to GPIO abstracting object.
 * @param[in]	gpio	Pointer to object abstracting GPIO, H/W interface.
 * @param	pin	GPIO pin number the part uses.
 * @param	mode	GPIO pin access mode, input or output.
 * @param	chattering_time	Time to wait while H/W chattering.
 * 							The default value is zero, meaning no chattering
 * 							wait.
 */
CPart::CPart(
		CGpio* gpio,
		uint8_t pin,
		uint8_t mode,
		uint32_t chattering_time)
: gpio_(gpio)
, pin_(pin)
, mode_(mode)
, chattering_time_(0)
{
	this->gpio_->SetMode(this->pin_, this->mode_);
}

/**
 * @brief	Destructor.
 */
CPart::~CPart() {}

/**
 * @brief	Callback function when interrupt occurred, detected.
 * @param	state	State of pin level, high or low.
 * @remark	This function does nothing. The operation to do when interruption
 * 			is detected should implement in a derived class, override this
 * 			method.
 */
void CPart::InterruptCallback(uint32_t state) {}

uint32_t CPart::SetSpi(CSpi* spi_config)
{
	assert(NULL != spi_config);

	uint32_t spi_flg = (spi_config->GetMode() +
			(((uint32_t)spi_config->GetActiveMode0()) << 2) +
			(((uint32_t)spi_config->GetActiveMode1()) << 3) +
			(((uint32_t)spi_config->GetActiveMode2()) << 4));
	CGpio* instance = CGpio::GetInstance();
	instance->SetSpi(spi_config->GetClock(), spi_flg);

	return 0;
}

