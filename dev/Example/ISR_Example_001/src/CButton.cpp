/*
 * CButton.cpp
 *
 *  Created on: 2020/04/05
 *      Author: CountrySideEngineer
 */
#include <iostream>
#include <stdio.h>
#include "CButton.h"
#include "cgpio/CPart.h"
#include "cgpio/CGpio.h"
#include "log.h"

/**
 * @brief	Default constructor
 */
CButton::CButton()
: CPart()
, targetPart_(nullptr)
{}

/**
 * @brief	Constructor of CButton class.
 * @param	pin	GPIO pin number the button is set.
 * @param	mode	The GPIO pin access mode, input or output.
 * @param	edge	Change of level to notify interruption occurred.
 * @param	chattering_time	Time to wait while H/W chattering.
 * 							The default value is zero, meaning no chattering
 * 							wait.
 * 							Default value is zero.
 */
CButton::CButton(uint8_t pin, uint8_t mode, uint8_t edge, uint32_t chattering_time)
: CPart(pin, mode, edge, chattering_time)
, targetPart_(nullptr)
{}

/**
 * @brief	Constructor of CButton class.
 * @param[in]	part	Pointer to CPart instance abstracting H/W to notify
 * 						interruption detected and the GPIO pin level has been
 * 						changed.
 * @param	pin	GPIO pin number the button is set.
 * @param	mode	The GPIO pin access mode, input or output.
 * @param	edge	Change of level to notify interruption occurred.
 * @param	chattering_time	Time to wait while H/W chattering.
 * 							The default value is zero, meaning no chattering
 * 							wait.
 * 							Default value is zero.
 */
CButton::CButton(
		CPart* part,
		uint8_t pin,
		uint8_t mode,
		uint8_t edge,
		uint32_t chattering_time)
: CPart(pin, mode, edge, chattering_time)
, targetPart_(part)
{
	CGpio* instance = CGpio::GetInstance();
	instance->SetupChatteringTimer();
}

/**
 * @brief	Destructor of CButton class.
 */
CButton::~CButton() {}

/**
 * @brief	Callback function to notify the interruption has been detected.
 */
void CButton::InterruptCallback(uint32_t state)
{
	DLOG("state = %d", state);

	if (nullptr == this->targetPart_) {
		return;
	} else {
		this->targetPart_->Write(state);
	}
}

