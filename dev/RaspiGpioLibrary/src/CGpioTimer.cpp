/*
 * CGpioTimer.cpp
 *
 *  Created on: 2020/03/13
 *      Author: CountrySideEngineer
 */

#include "CGpioTimer.h"

/**
 * @brief	Default constructor.
 */
CGpioTimer::CGpioTimer()
: part_(nullptr)
, start_time_(0)
, dispatch_time_(0)
{}

/**
 * @brief	Constructor with parameter.
 *
 * @param[in]	part	Pointer to call when the time dispatch_time_ passed.
 * @param	start_time	Time when start.
 * @param	dispatch_time_ Time to wait.
 */
CGpioTimer::CGpioTimer(CPart* part, uint32_t start_time, uint32_t dispatch_time)
: part_(part)
, start_time_(start_time)
, dispatch_time_(dispatch_time)
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
	if (dispatch_time_ < passed_time) {
		is_expires = true;
	} else {
		is_expires = false;
	}
	return is_expires;
}
