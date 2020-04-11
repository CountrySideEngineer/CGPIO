/*
 * CGpioExceptionUTest.cpp
 *
 *  Created on: 2020/03/14
 *      Author: CountrySideEngineer
 */
#include <iostream>
#include "gtest/gtest.h"
#include "CGpioException.h"

TEST(CGpioException, Constructor_001)
{
	CGpioException exception;

	ASSERT_EQ(0, exception.GetCode());
	ASSERT_STREQ("", exception.GetMessage().c_str());
}

TEST(CGpioException, Constructor_002)
{
	CGpioException exception(0x0001, string("error message"));

	ASSERT_EQ(1, exception.GetCode());
	ASSERT_STREQ("error message", exception.GetMessage().c_str());
}

TEST(CGpioException, Constructor_003)
{
	CGpioException exception(0xFFFF, "e");

	ASSERT_EQ(0xFFFF, exception.GetCode());
	ASSERT_STREQ("e", exception.GetMessage().c_str());
}


