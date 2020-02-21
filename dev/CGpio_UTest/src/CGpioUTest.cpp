/*
 * CGpioUTest.cpp
 *
 *  Created on: 2020/02/20
 *      Author: CountrySideEngineer
 */
#include <iostream>
#include "gtest/gtest.h"
#include "CGpio.h"
#include "gpio_stub.h"

using namespace std;

TEST(CGpio, Constructor_001)
{
	CGpio* instance = CGpio::GetInstance();

	ASSERT_EQ((-1), instance->GetSpiHandle());
	ASSERT_EQ((uint32_t)0, instance->GetSpiFlg());
	ASSERT_EQ(1, gpioInitialise_called_count);
}

TEST(CGpio, Constructor_002)
{
	gpioInitialise_init();
	gpioInitialise_ret_val[0] = (-1);

	CGpio* instance = CGpio::GetInstance();
	instance->Initialize();

	ASSERT_EQ(1, gpioInitialise_called_count);
}

TEST(CGpio, SetMode_001)
{
	gpioSetMode_init();
	gpioSetMode_ret_val[0] = 0;

	CGpio* instance = CGpio::GetInstance();
	int result = instance->SetMode(0,0);
	uint arg1_0 = gpioSetMode_arg_1[0];
	uint arg2_0 = gpioSetMode_arg_2[0];

	ASSERT_EQ(0, result);
	ASSERT_EQ(1, gpioSetMode_called_count);
	ASSERT_EQ((uint)0, arg1_0);
	ASSERT_EQ((uint)0, arg2_0);
}

TEST(CGpio, SetMode_002)
{
	gpioSetMode_init();
	gpioSetMode_ret_val[0] = (-3);

	CGpio* instance = CGpio::GetInstance();
	int result = instance->SetMode(1,2);
	uint arg1_0 = gpioSetMode_arg_1[0];
	uint arg2_0 = gpioSetMode_arg_2[0];

	ASSERT_EQ((-3), result);
	ASSERT_EQ(1, gpioSetMode_called_count);
	ASSERT_EQ((uint)1, arg1_0);
	ASSERT_EQ((uint)2, arg2_0);
}

TEST(CGpio, SetMode_003)
{
	gpioSetMode_init();
	gpioSetMode_ret_val[0] = (-4);

	CGpio* instance = CGpio::GetInstance();
	int result = instance->SetMode(0,0);
	uint arg1_0 = gpioSetMode_arg_1[0];
	uint arg2_0 = gpioSetMode_arg_2[0];

	ASSERT_EQ((-4), result);
	ASSERT_EQ(1, gpioSetMode_called_count);
	ASSERT_EQ((uint)0, arg1_0);
	ASSERT_EQ((uint)0, arg2_0);
}

TEST(CGpio, GetMode_001)
{
	gpioGetMode_init();
	gpioGetMode_ret_val[0] = 0;

	CGpio* instance = CGpio::GetInstance();
	int result = instance->GetMode(0);
	uint arg1_0 = gpioGetMode_arg_1[0];

	ASSERT_EQ(0, result);
	ASSERT_EQ(1, gpioGetMode_called_count);
	ASSERT_EQ((uint)0, arg1_0);
}

TEST(CGpio, GetMode_002)
{
	gpioGetMode_init();
	gpioGetMode_ret_val[0] = 1;

	CGpio* instance = CGpio::GetInstance();
	int result = instance->GetMode(0);
	uint arg1_0 = gpioGetMode_arg_1[0];

	ASSERT_EQ(1, result);
	ASSERT_EQ(1, gpioGetMode_called_count);
	ASSERT_EQ((uint)0, arg1_0);
}
