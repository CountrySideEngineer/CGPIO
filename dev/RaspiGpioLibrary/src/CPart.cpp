/*
 * CPart.cpp
 *
 *  Created on: 2020/02/09
 *      Author: CountrySideEngineer
 */
#include <assert.h>
#include "CPart.h"
#include "CGpio.h"

/**
 * @brief	Default constructor.
 */
CPart::CPart()
: pin_(0)
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
CPart::CPart(uint8_t pin, uint8_t mode, uint32_t chattering_time)
: pin_(pin)
, mode_(mode)
, chattering_time_(chattering_time)
{}

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

/**
 * @brief	Setup GPIO pin.
 * @param	pin	GPIO pin number.
 */
void CPart::SetPin(uint8_t pin)
{
	this->pin_ = pin;

	CGpio* gpio = CGpio::GetInstance();
	gpio->SetMode(this->pin_, this->mode_);
}

/**
 * @brief	Setup GPIO pin access direction.
 * @param	mode	GPIO pin access direction.
 */
void CPart::SetMode(uint8_t mode)
{
	this->mode_ = mode;

	CGpio* gpio = CGpio::GetInstance();
	gpio->SetMode(this->pin_, this->mode_);
}

/**
 * @brief	Read GPIO pin level, low or high, the H/W part uses.
 * @returns	GPIO pin level. Returns 0 if the pin level is low, otherwise
 * 			returns 1.
 */
uint8_t CPart::Read()
{
	CGpio* gpio = CGpio::GetInstance();
	return gpio->Read(this->pin_);
}

/**
 * @brief	Write GPIO pin.
 * @param	value	Pin level to write into the pin.
 */
void CPart::Write(uint8_t value)
{
	CGpio* gpio = CGpio::GetInstance();
	gpio->Write(this->pin_, value);
}
