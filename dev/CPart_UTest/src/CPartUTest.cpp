/*
 * CPartUTest.cpp
 *
 *  Created on: 2020/02/23
 *      Author: CountrySideEngineer.
 */
#include <iostream>
#include "gtest/gtest.h"
#include "../../RaspiGpioLibrary/src/CPart.h"
#include "CGpio.h"
#include "gpio_stub.h"

TEST(CPart, Constructor_001)
{
	CPart part;

	ASSERT_EQ(0, part.GetPin());
	ASSERT_EQ(0, part.GetMode());
	ASSERT_EQ((uint32_t)0, part.GetChatteringTime());
}

TEST(CPart, Constructor_002)
{
	CPart part(1, 2, 3);

	ASSERT_EQ(1, part.GetPin());
	ASSERT_EQ(2, part.GetMode());
	ASSERT_EQ((uid_t)3, part.GetChatteringTime());
}

TEST(CPart, GetSetPin_001)
{
	CPart part(1, 2, 3);

	gpioSetMode_init();

	part.SetPin(4);

	ASSERT_EQ(4, part.GetPin());
	ASSERT_EQ(1, gpioSetMode_called_count);
	ASSERT_EQ((uint)4, gpioSetMode_arg_1[0]);
	ASSERT_EQ((uint)2, gpioSetMode_arg_2[0]);
}

TEST(CPart, GetSetMode_001)
{
	CPart part(1, 2, 3);

	gpioSetMode_init();

	part.SetMode(4);

	ASSERT_EQ(4, part.GetMode());
	ASSERT_EQ(1, gpioSetMode_called_count);
	ASSERT_EQ((uint)1, gpioSetMode_arg_1[0]);
	ASSERT_EQ((uint)4, gpioSetMode_arg_2[0]);
}

TEST(CPart, Read_001)
{
	gpioRead_init();
	gpioRead_ret_val[0] = 1;

	CPart part(1, 2, 3);

	uint8_t read_data = part.Read();

	ASSERT_EQ((uint)1, read_data);
	ASSERT_EQ(1, gpioRead_called_count);
	ASSERT_EQ((uint)1, gpioRead_arg_1[0]);
}

TEST(CPart, Write_001)
{
	gpioWrite_init();

	CPart part(1, 2, 3);

	part.Write(4);

	ASSERT_EQ(1, gpioWrite_called_count);
	ASSERT_EQ((uint)1, gpioWrite_arg_1[0]);
	ASSERT_EQ((uint)1, gpioWrite_arg_2[0]);
}

TEST(CPart, Write_002)
{
	gpioWrite_init();

	CPart part(1, 2, 3);

	part.Write(0);

	ASSERT_EQ(1, gpioWrite_called_count);
	ASSERT_EQ((uint)1, gpioWrite_arg_1[0]);
	ASSERT_EQ((uint)0, gpioWrite_arg_2[0]);
}
