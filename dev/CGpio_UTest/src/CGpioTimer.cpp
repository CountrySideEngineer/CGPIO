/*
 * CGpioTimer.cpp
 *
 *  Created on: 2020/03/13
 *      Author: CountrySideEngineer
 */

#include "CGpioTimer.h"
uint32_t CGpioTimer::default_constructor_called_count;
uint32_t CGpioTimer::constructor_called_count;

void CGpioTimer::InitStub()
{
	CGpioTimer::default_constructor_called_count = 0;
	CGpioTimer::constructor_called_count = 0;
}

/**
 * @brief	Default constructor.
 */
CGpioTimer::CGpioTimer()
: part_(nullptr)
, start_time_(0)
{}

/**
 * @brief	Constructor with parameter.
 *
 * @param[in]	part	Pointer to call when the time dispatch_time_ passed.
 * @param	start_time	Time when start.
 */
CGpioTimer::CGpioTimer(CPart* part, uint32_t start_time)
: part_(part)
, start_time_(start_time)
{}

/**
 * @brief	Destructor
 */
CGpioTimer::~CGpioTimer() {}

/**
 * @brief	Check whethe time to wait is passed.
 *
 * @param	current_time	Current time in micro second unit.
 */
bool CGpioTimer::IsExpires(const uint32_t current_time)
{
	bool is_expires = false;
	uint32_t passed_time = current_time - this->start_time_;
	if (this->part_->GetChatteringTime() < passed_time) {
		is_expires = true;
	} else {
		is_expires = false;
	}
	return is_expires;
}
