/*
 * CGpioException.cpp
 *
 *  Created on: 2020/03/14
 *      Author: CountrySideEngineer
 */
#include <iostream>
#include <string.h>
#include "CGpioException.h"

/**
 *	@brief	Default constructor.
 */
CGpioException::CGpioException()
: code_(0)
, message_("")
{}

/**
 * @brief	Constructor with error code and error message.
 */
CGpioException::CGpioException(uint16_t code, string message)
: code_(code)
, message_(message)

{}

/**
 * @brief	Destructor
 */
CGpioException::~CGpioException() {}

