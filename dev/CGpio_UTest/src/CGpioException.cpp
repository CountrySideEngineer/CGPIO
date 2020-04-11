/*
 * CGpioException.cpp
 *
 *  Created on: 2020/03/14
 *      Author: CountrySideEngineer
 */
#include <iostream>
#include <string.h>
#include "CGpioException.h"

uint32_t CGpioException::default_constructor_called_count = 0;
uint32_t CGpioException::constructor_with_argument_called_count = 0;

/**
 * @brief	Initialize parameters
 */
void CGpioException::InitStub()
{
	default_constructor_called_count = 0;
	constructor_with_argument_called_count = 0;
}

/**
 *	@brief	Default constructor.
 */
CGpioException::CGpioException()
: code_(0)
, message_("")
{
	default_constructor_called_count++;
}

/**
 * @brief	Constructor with error code and error message.
 */
CGpioException::CGpioException(uint16_t code, string message)
: code_(code)
, message_(message)
{
	constructor_with_argument_called_count++;
}

/**
 * @brief	Destructor
 */
CGpioException::~CGpioException() {}

