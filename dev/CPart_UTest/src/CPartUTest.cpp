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

	CGpio::InitStub();
	CGpio* instance = new CGpio();
	CGpio::GetInstance_ret_val[0] = instance;
	CGpio::GetInstance_ret_val[1] = instance;

	part.SetPin(4);

	ASSERT_EQ(4, part.GetPin());
	ASSERT_EQ((uint32_t)1, CGpio::SetMode_called_count);

	delete instance;
}

TEST(CPart, GetSetMode_001)
{
	CPart part(1, 2, 3);

	CGpio::InitStub();
	CGpio* instance = new CGpio();
	CGpio::GetInstance_ret_val[0] = instance;

	part.SetMode(4);

	ASSERT_EQ(4, part.GetMode());

	delete instance;
}

TEST(CPart, Read_001)
{
	CGpio::InitStub();
	CGpio* instance = new CGpio();
	CGpio::GetInstance_ret_val[0] = instance;
	CGpio::Read_ret_val[0] = 10;

	CPart part(1, 2, 3);

	uint8_t read_data = part.Read();

	ASSERT_EQ((uint)1, CGpio::Read_called_count);
	ASSERT_EQ((uint)10, read_data);

	delete instance;
}

TEST(CPart, Write_001)
{
	CGpio::InitStub();
	CGpio* instance = new CGpio();
	CGpio::GetInstance_ret_val[0] = instance;

	CPart part(1, 2, 3);

	part.Write(4);

	ASSERT_EQ((uint32_t)1, CGpio::Write_called_count);
	ASSERT_EQ(1, CGpio::Write_arg1[0]);
	ASSERT_EQ(4, CGpio::Write_arg2[0]);

	delete instance;
}

TEST(CPart, Write_002)
{
	CGpio::InitStub();
	CGpio* instance = new CGpio();
	CGpio::GetInstance_ret_val[0] = instance;

	CPart part(1, 2, 3);

	part.Write(0);

	ASSERT_EQ((uint32_t)1, CGpio::Write_called_count);
	ASSERT_EQ(1, CGpio::Write_arg1[0]);
	ASSERT_EQ(0, CGpio::Write_arg2[0]);

	delete instance;
}

TEST(CPart, Recv_001)
{
	CGpio::InitStub();
	CGpio* instance = new CGpio();
	CGpio::GetInstance_ret_val[0] = instance;
	CGpio::SpiRead_ret_val[0] = 2;

	uint8_t data = 1;
	uint32_t data_size = 2;
	CPart part(1, 2, 3);
	uint32_t ret = part.Recv((uint8_t*)&data, data_size);

	printf("instance = %p\r\n", instance);
	printf("ret = %d\r\n", ret);

	ASSERT_EQ((uint32_t)2, ret);
	ASSERT_EQ((uint32_t)1, CGpio::SpiRead_called_count);

	delete instance;
}
