/*
 * CGPioTimerUTest.cpp
 *
 *  Created on: 2020/03/14
 *      Author: CountrySideEngineer
 */
#include <iostream>
#include "gtest/gtest.h"
#include "CGpioTimer.h"
using namespace std;

TEST(CGpioTimer, Constructor_001)
{
	CGpioTimer gpio_timer;

	ASSERT_EQ(nullptr, gpio_timer.GetPart());
}

TEST(CGpioTimer, Constructor_002)
{
	CPart part;
	CGpioTimer gpio_timer(&part, 1);

	ASSERT_EQ(&part, gpio_timer.GetPart());
	ASSERT_EQ(1, gpio_timer.GetStartTime());
}

TEST(CGpioTimer, SetStartTime_001)
{
	CPart part;
	CGpioTimer gpio_timer;

	gpio_timer.SetStartTime(1);

	ASSERT_EQ(1, gpio_timer.GetStartTime());
}

TEST(CGpioTimer, SetStartTime_002)
{
	CPart part;
	CGpioTimer gpio_timer(nullptr, 1);

	gpio_timer.SetStartTime(3);

	ASSERT_EQ(3, gpio_timer.GetStartTime());
}

TEST(CGpioTimer, IsExpires_001)
{
	CPart part(3, 2, 1);
	CGpioTimer gpio_timer(&part, 1);

	bool is_expires = gpio_timer.IsExpires(2);

	ASSERT_EQ(false, is_expires);
}

TEST(CGpioTimer, IsExpires_002)
{
	CPart part(3, 2, 2);
	CGpioTimer gpio_timer(&part, 1);

	bool is_expires = gpio_timer.IsExpires(3);

	ASSERT_EQ(false, is_expires);
}

TEST(CGpioTimer, IsExpires_003)
{
	CPart part(3, 2, 2);
	CGpioTimer gpio_timer(&part, 1);

	bool is_expires = gpio_timer.IsExpires(4);

	ASSERT_EQ(true, is_expires);
}

