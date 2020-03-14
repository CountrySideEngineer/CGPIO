/*
 * CGpioUTest.cpp
 *
 *  Created on: 2020/02/20
 *      Author: CountrySideEngineer
 */
#include <iostream>
#include "gtest/gtest.h"
#include "pigpio/pigpio.h"
#include "CGpio.h"
#include "CPart.h"
#include "CGpioTimer.h"
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

TEST(CGpio, SetSpi_001)
{
	int spi_clock = 1;
	int spi_flg = 0x0001;

	spiOpen_init();
	gpioWrite_init();
	gpioSetMode_init();

	spiOpen_ret_val[0] = 0;

	CGpio* instance = CGpio::GetInstance();
	int result = instance->SetSpi(spi_clock, spi_flg);
	int arg1 = spiOpen_arg_1[0];
	int arg2 = spiOpen_arg_2[0];
	int arg3 = spiOpen_arg_3[0];
	int spi_handle = instance->GetSpiHandle();
	uint32_t spi_flag = instance->GetSpiFlg();

	ASSERT_EQ(0, result);
	ASSERT_EQ(0, arg1);
	ASSERT_EQ(1, arg2);
	ASSERT_EQ((int)0x0001, arg3);
	ASSERT_EQ(0, spi_handle);
	ASSERT_EQ((uint32_t)0x0001, spi_flag);
	ASSERT_EQ(2, gpioSetMode_called_count);
	ASSERT_EQ((uint)8, gpioSetMode_arg_1[0]);
	ASSERT_EQ((uint)9, gpioSetMode_arg_1[1]);
	ASSERT_EQ((uint)1, gpioSetMode_arg_2[0]);
	ASSERT_EQ((uint)1, gpioSetMode_arg_2[1]);
	ASSERT_EQ(2, gpioWrite_called_count);
	ASSERT_EQ((uint)8, gpioWrite_arg_1[0]);
	ASSERT_EQ((uint)9, gpioWrite_arg_1[1]);
	ASSERT_EQ((uint)1, gpioWrite_arg_2[0]);
	ASSERT_EQ((uint)1, gpioWrite_arg_2[1]);
}

TEST(CGpio, SetSpi_002)
{
	int spi_clock = 1;
	int spi_flg = 2;

	spiOpen_init();

	spiOpen_ret_val[0] = (-76);

	CGpio* instance = CGpio::GetInstance();
	instance->Finalize();
	int result = instance->SetSpi(spi_clock, spi_flg);
	int arg1 = spiOpen_arg_1[0];
	int arg2 = spiOpen_arg_2[0];
	int arg3 = spiOpen_arg_3[0];
	int spi_handle = instance->GetSpiHandle();
	uint32_t spi_flag = instance->GetSpiFlg();

	ASSERT_EQ((-5), result);
	ASSERT_EQ(0, arg1);
	ASSERT_EQ(1, arg2);
	ASSERT_EQ(2, arg3);
	ASSERT_EQ((-1), spi_handle);
	ASSERT_EQ((uint32_t)0, spi_flag);
}

TEST(CGpio, SetSpi_003)
{
	int spi_clock = 1;
	int spi_flg = 2;

	spiOpen_init();

	spiOpen_ret_val[0] = (-78);

	CGpio* instance = CGpio::GetInstance();
	instance->Finalize();
	int result = instance->SetSpi(spi_clock, spi_flg);
	int arg1 = spiOpen_arg_1[0];
	int arg2 = spiOpen_arg_2[0];
	int arg3 = spiOpen_arg_3[0];
	int spi_handle = instance->GetSpiHandle();
	uint32_t spi_flag = instance->GetSpiFlg();

	ASSERT_EQ((-6), result);
	ASSERT_EQ(0, arg1);
	ASSERT_EQ(1, arg2);
	ASSERT_EQ(2, arg3);
	ASSERT_EQ((-1), spi_handle);
	ASSERT_EQ((uint32_t)0, spi_flag);
}

TEST(CGpio, SetSpi_004)
{
	int spi_clock = 1;
	int spi_flg = 2;

	spiOpen_init();

	spiOpen_ret_val[0] = (-77);

	CGpio* instance = CGpio::GetInstance();
	instance->Finalize();
	int result = instance->SetSpi(spi_clock, spi_flg);
	int arg1 = spiOpen_arg_1[0];
	int arg2 = spiOpen_arg_2[0];
	int arg3 = spiOpen_arg_3[0];
	int spi_handle = instance->GetSpiHandle();
	uint32_t spi_flag = instance->GetSpiFlg();

	ASSERT_EQ((-7), result);
	ASSERT_EQ(0, arg1);
	ASSERT_EQ(1, arg2);
	ASSERT_EQ(2, arg3);
	ASSERT_EQ((-1), spi_handle);
	ASSERT_EQ((uint32_t)0, spi_flag);
}

TEST(CGpio, SetSpi_005)
{
	int spi_clock = 1;
	int spi_flg = 2;

	spiOpen_init();

	spiOpen_ret_val[0] = (-91);

	CGpio* instance = CGpio::GetInstance();
	instance->Finalize();
	int result = instance->SetSpi(spi_clock, spi_flg);
	int arg1 = spiOpen_arg_1[0];
	int arg2 = spiOpen_arg_2[0];
	int arg3 = spiOpen_arg_3[0];
	int spi_handle = instance->GetSpiHandle();
	uint32_t spi_flag = instance->GetSpiFlg();

	ASSERT_EQ((-8), result);
	ASSERT_EQ(0, arg1);
	ASSERT_EQ(1, arg2);
	ASSERT_EQ(2, arg3);
	ASSERT_EQ((-1), spi_handle);
	ASSERT_EQ((uint32_t)0, spi_flag);
}

TEST(CGpio, SetSpi_006)
{
	int spi_clock = 1;
	int spi_flg = 2;

	spiOpen_init();

	spiOpen_ret_val[0] = (-73);

	CGpio* instance = CGpio::GetInstance();
	instance->Finalize();
	int result = instance->SetSpi(spi_clock, spi_flg);
	int arg1 = spiOpen_arg_1[0];
	int arg2 = spiOpen_arg_2[0];
	int arg3 = spiOpen_arg_3[0];
	int spi_handle = instance->GetSpiHandle();
	uint32_t spi_flag = instance->GetSpiFlg();

	ASSERT_EQ((-9), result);
	ASSERT_EQ(0, arg1);
	ASSERT_EQ(1, arg2);
	ASSERT_EQ(2, arg3);
	ASSERT_EQ((-1), spi_handle);
	ASSERT_EQ((uint32_t)0, spi_flag);
}

TEST(CGpio, SetSpi_007)
{
	int spi_clock = 1;
	int spi_flg = 2;

	spiOpen_init();

	spiOpen_ret_val[0] = (-1);

	CGpio* instance = CGpio::GetInstance();
	instance->Finalize();
	int result = instance->SetSpi(spi_clock, spi_flg);
	int arg1 = spiOpen_arg_1[0];
	int arg2 = spiOpen_arg_2[0];
	int arg3 = spiOpen_arg_3[0];
	int spi_handle = instance->GetSpiHandle();
	uint32_t spi_flag = instance->GetSpiFlg();

	ASSERT_EQ((int)(0xFFFF), result);
	ASSERT_EQ(0, arg1);
	ASSERT_EQ(1, arg2);
	ASSERT_EQ(2, arg3);
	ASSERT_EQ((-1), spi_handle);
	ASSERT_EQ((uint32_t)0, spi_flag);
}

TEST(CGpio, SetSpi_008)
{
	int spi_clock = 1;
	int spi_flg = 2;

	spiOpen_init();

	spiOpen_ret_val[0] = (0);

	CGpio* instance = CGpio::GetInstance();
	instance->Finalize();
	int result1 = instance->SetSpi(spi_clock, spi_flg);
	int result2 = instance->SetSpi(spi_clock, spi_flg);
	int arg1 = spiOpen_arg_1[0];
	int arg2 = spiOpen_arg_2[0];
	int arg3 = spiOpen_arg_3[0];
	int spi_handle = instance->GetSpiHandle();
	uint32_t spi_flag = instance->GetSpiFlg();

	ASSERT_EQ(0, result1);
	ASSERT_EQ(0, result2);
	ASSERT_EQ(0, arg1);
	ASSERT_EQ(1, arg2);
	ASSERT_EQ(2, arg3);
	ASSERT_EQ(0, spi_handle);
	ASSERT_EQ((uint32_t)2, spi_flag);
}

TEST(CGpio, SetSpi_009)
{
	int spi_clock = 1;
	int spi_flg = 0x000D;	//b'1101

	spiOpen_init();
	gpioWrite_init();
	gpioSetMode_init();

	spiOpen_ret_val[0] = 0;

	CGpio* instance = CGpio::GetInstance();
	instance->Finalize();
	int result = instance->SetSpi(spi_clock, spi_flg);
	int arg1 = spiOpen_arg_1[0];
	int arg2 = spiOpen_arg_2[0];
	int arg3 = spiOpen_arg_3[0];
	int spi_handle = instance->GetSpiHandle();
	uint32_t spi_flag = instance->GetSpiFlg();

	ASSERT_EQ(0, result);
	ASSERT_EQ(0, arg1);
	ASSERT_EQ(1, arg2);
	ASSERT_EQ((int)0x000D, arg3);
	ASSERT_EQ(0, spi_handle);
	ASSERT_EQ((uint32_t)0x000D, spi_flag);
	ASSERT_EQ(2, gpioSetMode_called_count);
	ASSERT_EQ((uint)8, gpioSetMode_arg_1[0]);
	ASSERT_EQ((uint)9, gpioSetMode_arg_1[1]);
	ASSERT_EQ((uint)1, gpioSetMode_arg_2[0]);
	ASSERT_EQ((uint)1, gpioSetMode_arg_2[1]);
	ASSERT_EQ(2, gpioWrite_called_count);
	ASSERT_EQ((uint)8, gpioWrite_arg_1[0]);
	ASSERT_EQ((uint)9, gpioWrite_arg_1[1]);
	ASSERT_EQ((uint)0, gpioWrite_arg_2[0]);
	ASSERT_EQ((uint)0, gpioWrite_arg_2[1]);
}

TEST(CGpio, SetSpi_010)
{
	int spi_clock = 1;
	int spi_flg = 0x0001;

	spiOpen_init();
	gpioWrite_init();
	gpioSetMode_init();

	spiOpen_ret_val[0] = 0;

	CGpio* instance = CGpio::GetInstance();
	instance->Finalize();
	int result = instance->SetSpi(spi_clock, spi_flg);
	int arg1 = spiOpen_arg_1[0];
	int arg2 = spiOpen_arg_2[0];
	int arg3 = spiOpen_arg_3[0];
	int spi_handle = instance->GetSpiHandle();
	uint32_t spi_flag = instance->GetSpiFlg();

	ASSERT_EQ(0, result);
	ASSERT_EQ(0, arg1);
	ASSERT_EQ(1, arg2);
	ASSERT_EQ((int)0x0001, arg3);
	ASSERT_EQ(0, spi_handle);
	ASSERT_EQ((uint32_t)0x0001, spi_flag);
	ASSERT_EQ(2, gpioSetMode_called_count);
	ASSERT_EQ((uint)8, gpioSetMode_arg_1[0]);
	ASSERT_EQ((uint)9, gpioSetMode_arg_1[1]);
	ASSERT_EQ((uint)1, gpioSetMode_arg_2[0]);
	ASSERT_EQ((uint)1, gpioSetMode_arg_2[1]);
	ASSERT_EQ(2, gpioWrite_called_count);
	ASSERT_EQ((uint)8, gpioWrite_arg_1[0]);
	ASSERT_EQ((uint)9, gpioWrite_arg_1[1]);
	ASSERT_EQ((uint)1, gpioWrite_arg_2[0]);
	ASSERT_EQ((uint)1, gpioWrite_arg_2[1]);
}

TEST(CGpio, CloseSPi_001)
{
	CGpio* instance = CGpio::GetInstance();

	instance->Finalize();
	spiClose_init();
	instance->SetSpi(0, 0);
	instance->CloseSpi();

	ASSERT_EQ(1, spiClose_called_count);
}

TEST(CGpio, CloseSPi_002)
{
	CGpio* instance = CGpio::GetInstance();

	instance->Finalize();
	spiClose_init();
	instance->SetSpi(0, 0);
	instance->CloseSpi();
	instance->CloseSpi();

	ASSERT_EQ(1, spiClose_called_count);
}

TEST(CGpio, SpiRead_001)
{
	uint8_t data = 0;
	uint32_t data_size = 1;

	spiRead_init();

	spiRead_ret_val[0] = 0;

	CGpio* instance = CGpio::GetInstance();
	instance->Finalize();
	int SpiRead_result = instance->SpiRead(&data, data_size);
	ASSERT_EQ(0, SpiRead_result);
	ASSERT_EQ(1, spiRead_called_count);
	ASSERT_EQ((uint)(-1), spiRead_arg_1[0]);
	ASSERT_EQ((char*)&data, spiRead_arg_2[0]);
	ASSERT_EQ((uint)1, spiRead_arg_3[0]);
}

TEST(CGpio, SpiRead_002)
{
	uint8_t data = 0;
	uint32_t data_size = 1;

	spiRead_init();

	spiRead_ret_val[0] = (-25);	//PI_BAD_HANDLE

	CGpio* instance = CGpio::GetInstance();
	instance->Finalize();
	int SpiRead_result = instance->SpiRead(&data, data_size);
	ASSERT_EQ((-11), SpiRead_result);
	ASSERT_EQ(1, spiRead_called_count);
}

TEST(CGpio, SpiRead_003)
{
	uint8_t data = 0;
	uint32_t data_size = 1;

	spiRead_init();

	spiRead_ret_val[0] = (-84);	//PI_BAD_SPI_COUNT

	CGpio* instance = CGpio::GetInstance();
	instance->Finalize();
	int SpiRead_result = instance->SpiRead(&data, data_size);
	ASSERT_EQ((-12), SpiRead_result);
	ASSERT_EQ(1, spiRead_called_count);
}

TEST(CGpio, SpiRead_004)
{
	uint8_t data = 0;
	uint32_t data_size = 1;

	spiRead_init();

	spiRead_ret_val[0] = (-89);	//PI_SPI_XFER_FAILED

	CGpio* instance = CGpio::GetInstance();
	instance->Finalize();
	int SpiRead_result = instance->SpiRead(&data, data_size);
	ASSERT_EQ((-13), SpiRead_result);
	ASSERT_EQ(1, spiRead_called_count);
}

TEST(CGpio, SpiWrite_001)
{
	uint8_t data = 0;
	uint32_t data_size = 1;

	spiWrite_init();

	spiWrite_ret_val[0] = 0;

	CGpio* instance = CGpio::GetInstance();
	instance->Finalize();
	int SpiWrite_result = instance->SpiWrite(&data, data_size);
	ASSERT_EQ(0, SpiWrite_result);
	ASSERT_EQ(1, spiWrite_called_count);
	ASSERT_EQ((uint)(-1), spiWrite_arg_1[0]);
	ASSERT_EQ((char*)(&data), spiWrite_arg_2[0]);
	ASSERT_EQ((uint)1, spiWrite_arg_3[0]);
}

TEST(CGpio, SpiWrite_002)
{
	uint8_t data = 0;
	uint32_t data_size = 1;

	spiWrite_init();

	spiWrite_ret_val[0] = (-25);	//PI_BAD_HANDLE

	CGpio* instance = CGpio::GetInstance();
	instance->Finalize();
	int SpiWrite_result = instance->SpiWrite(&data, data_size);
	ASSERT_EQ((-11), SpiWrite_result);
	ASSERT_EQ(1, spiWrite_called_count);
	ASSERT_EQ((uint)(-1), spiWrite_arg_1[0]);
	ASSERT_EQ((char*)(&data), spiWrite_arg_2[0]);
	ASSERT_EQ((uint)1, spiWrite_arg_3[0]);
}

TEST(CGpio, SpiWrite_003)
{
	uint8_t data = 0;
	uint32_t data_size = 1;

	spiWrite_init();

	spiWrite_ret_val[0] = (-25);	//PI_BAD_HANDLE

	CGpio* instance = CGpio::GetInstance();
	instance->Finalize();
	int SpiWrite_result = instance->SpiWrite(&data, data_size);
	ASSERT_EQ((-11), SpiWrite_result);
	ASSERT_EQ(1, spiWrite_called_count);
	ASSERT_EQ((uint)(-1), spiWrite_arg_1[0]);
	ASSERT_EQ((char*)(&data), spiWrite_arg_2[0]);
	ASSERT_EQ((uint)1, spiWrite_arg_3[0]);
}

TEST(CGpio, SpiWrite_004)
{
	uint8_t data = 0;
	uint32_t data_size = 1;

	spiWrite_init();

	spiWrite_ret_val[0] = (-84);	//PI_BAD_SPI_COUNT

	CGpio* instance = CGpio::GetInstance();
	instance->Finalize();
	int SpiWrite_result = instance->SpiWrite(&data, data_size);
	ASSERT_EQ((-12), SpiWrite_result);
	ASSERT_EQ(1, spiWrite_called_count);
	ASSERT_EQ((uint)(-1), spiWrite_arg_1[0]);
	ASSERT_EQ((char*)(&data), spiWrite_arg_2[0]);
	ASSERT_EQ((uint)1, spiWrite_arg_3[0]);
}

TEST(CGpio, SpiWrite_005)
{
	uint8_t data = 0;
	uint32_t data_size = 1;

	spiWrite_init();

	spiWrite_ret_val[0] = (-89);	//PI_SPI_XFER_FAILED

	CGpio* instance = CGpio::GetInstance();
	instance->Finalize();
	int SpiWrite_result = instance->SpiWrite(&data, data_size);
	ASSERT_EQ((-13), SpiWrite_result);
	ASSERT_EQ(1, spiWrite_called_count);
	ASSERT_EQ((uint)(-1), spiWrite_arg_1[0]);
	ASSERT_EQ((char*)(&data), spiWrite_arg_2[0]);
	ASSERT_EQ((uint)1, spiWrite_arg_3[0]);
}

TEST(CGpio, SetIsr_001)
{
	CPart part;

	CGpio* instance = CGpio::GetInstance();

	gpioSetISRFunc_init();
	gpioSetISRFunc_ret_val[0] = 0;

	int SetIsr_result = instance->SetIsr(1, 2, &part);
	ASSERT_EQ(0, SetIsr_result);
	ASSERT_EQ(1, gpioSetISRFunc_called_count);
	ASSERT_EQ((uint)1, gpioSetISRFunc_arg_1[0]);
	ASSERT_EQ((uint)2, gpioSetISRFunc_arg_2[0]);
	ASSERT_EQ(0, gpioSetISRFunc_arg_3[0]);
	ASSERT_NE((void*)NULL, (void*)gpioSetISRFunc_arg_4[0]);

	instance->Finalize();
}

TEST(CGpio, SetIsr_002)
{
	CPart part;

	CGpio* instance = CGpio::GetInstance();

	gpioSetISRFunc_init();
	gpioSetISRFunc_ret_val[0] = 0;

	instance->SetIsr(1, 2, &part);
	int SetIsr_result = instance->SetIsr(1, 3, &part);
	ASSERT_EQ((-14), SetIsr_result);
	ASSERT_EQ(1, gpioSetISRFunc_called_count);
	ASSERT_EQ((uint)1, gpioSetISRFunc_arg_1[0]);
	ASSERT_EQ((uint)2, gpioSetISRFunc_arg_2[0]);
	ASSERT_EQ(0, gpioSetISRFunc_arg_3[0]);
	ASSERT_NE((void*)NULL, (void*)gpioSetISRFunc_arg_4[0]);

	instance->Finalize();
}

TEST(CGpio, SetIsr_003)
{
	CPart part;

	CGpio* instance = CGpio::GetInstance();

	gpioSetISRFunc_init();
	gpioSetISRFunc_ret_val[0] = (-3);	//PI_BAD_GPIO

	int SetIsr_result = instance->SetIsr(1, 2, &part);
	ASSERT_EQ((-3), SetIsr_result);		//GPIO_ERROR_GPIO
	ASSERT_EQ(1, gpioSetISRFunc_called_count);
	ASSERT_EQ((uint)1, gpioSetISRFunc_arg_1[0]);
	ASSERT_EQ((uint)2, gpioSetISRFunc_arg_2[0]);
	ASSERT_EQ(0, gpioSetISRFunc_arg_3[0]);
	ASSERT_NE((void*)NULL, (void*)gpioSetISRFunc_arg_4[0]);

	instance->Finalize();
}

TEST(CGpio, SetIsr_004)
{
	CPart part;

	CGpio* instance = CGpio::GetInstance();

	gpioSetISRFunc_init();
	gpioSetISRFunc_ret_val[0] = (-122);	//PI_BAD_EDGE

	int SetIsr_result = instance->SetIsr(1, 2, &part);
	ASSERT_EQ((-15), SetIsr_result);		//GPIO_ISR_BAD_EDGE
	ASSERT_EQ(1, gpioSetISRFunc_called_count);
	ASSERT_EQ((uint)1, gpioSetISRFunc_arg_1[0]);
	ASSERT_EQ((uint)2, gpioSetISRFunc_arg_2[0]);
	ASSERT_EQ(0, gpioSetISRFunc_arg_3[0]);
	ASSERT_NE((void*)NULL, (void*)gpioSetISRFunc_arg_4[0]);

	instance->Finalize();
}

TEST(CGpio, SetIsr_005)
{
	CPart part;

	CGpio* instance = CGpio::GetInstance();

	gpioSetISRFunc_init();
	gpioSetISRFunc_ret_val[0] = (-123);	//PI_BAD_ISR_INIT

	int SetIsr_result = instance->SetIsr(1, 2, &part);
	ASSERT_EQ((-16), SetIsr_result);		//GPIO_ISR_BAD_EDGE
	ASSERT_EQ(1, gpioSetISRFunc_called_count);
	ASSERT_EQ((uint)1, gpioSetISRFunc_arg_1[0]);
	ASSERT_EQ((uint)2, gpioSetISRFunc_arg_2[0]);
	ASSERT_EQ(0, gpioSetISRFunc_arg_3[0]);
	ASSERT_NE((void*)NULL, (void*)gpioSetISRFunc_arg_4[0]);

	instance->Finalize();
}

TEST(CGpio, SetIsr_006)
{
	CPart part;

	CGpio* instance = CGpio::GetInstance();

	gpioSetISRFunc_init();
	gpioSetISRFunc_ret_val[0] = 0;
	gpioSetISRFunc_ret_val[1] = 0;

	int SetIsr_result = instance->SetIsr(1, 2, &part);
	ASSERT_EQ(0, SetIsr_result);
	SetIsr_result = instance->SetIsr(3, 4, &part);
	ASSERT_EQ(0, SetIsr_result);
	ASSERT_EQ(2, gpioSetISRFunc_called_count);
	ASSERT_EQ((uint)1, gpioSetISRFunc_arg_1[0]);
	ASSERT_EQ((uint)2, gpioSetISRFunc_arg_2[0]);
	ASSERT_EQ((uint)3, gpioSetISRFunc_arg_1[1]);
	ASSERT_EQ((uint)4, gpioSetISRFunc_arg_2[1]);
	ASSERT_EQ(0, gpioSetISRFunc_arg_3[0]);
	ASSERT_EQ(0, gpioSetISRFunc_arg_3[1]);
	ASSERT_NE((void*)NULL, (void*)gpioSetISRFunc_arg_4[0]);
	ASSERT_NE((void*)NULL, (void*)gpioSetISRFunc_arg_4[1]);

	instance->Finalize();
}

TEST(CGpio, Write_001)
{
	gpioWrite_init();

	uint8_t pin = 1;
	uint8_t level = 0;

	CGpio* instance = CGpio::GetInstance();

	instance->Write(pin, level);

	ASSERT_EQ(1, gpioWrite_called_count);
	ASSERT_EQ((uint)1, gpioWrite_arg_1[0]);
	ASSERT_EQ((uint)0, gpioWrite_arg_2[0]);

	instance->Finalize();
}

TEST(CGpio, Write_002)
{
	gpioWrite_init();

	uint8_t pin = 1;
	uint8_t level = 1;

	CGpio* instance = CGpio::GetInstance();

	instance->Write(pin, level);

	ASSERT_EQ(1, gpioWrite_called_count);
	ASSERT_EQ((uint)1, gpioWrite_arg_1[0]);
	ASSERT_EQ((uint)1, gpioWrite_arg_2[0]);

	instance->Finalize();
}

TEST(CGpio, Write_003)
{
	gpioWrite_init();

	uint8_t pin = 1;
	uint8_t level = 2;

	CGpio* instance = CGpio::GetInstance();

	instance->Write(pin, level);

	ASSERT_EQ(1, gpioWrite_called_count);
	ASSERT_EQ((uint)1, gpioWrite_arg_1[0]);
	ASSERT_EQ((uint)1, gpioWrite_arg_2[0]);

	instance->Finalize();
}

TEST(CGpio, Read_001)
{
	gpioRead_init();

	gpioRead_ret_val[0] = 0;

	CGpio* instance = CGpio::GetInstance();
	uint8_t pin = 1;
	uint8_t read_value = instance->Read(pin);

	ASSERT_EQ(1, gpioRead_called_count);
	ASSERT_EQ(0, read_value);

	instance->Finalize();
}

TEST(CGpio, Read_002)
{
	gpioRead_init();

	gpioRead_ret_val[0] = 1;

	CGpio* instance = CGpio::GetInstance();
	uint8_t pin = 1;
	uint8_t read_value = instance->Read(pin);

	ASSERT_EQ(1, gpioRead_called_count);
	ASSERT_EQ(1, read_value);

	instance->Finalize();
}

TEST(CGpio, StartChatteringTime_001)
{
	CPart part(1, 2, 3);
	CGpio* instance = CGpio::GetInstance();
	instance->StartChatteringTime(&part);

	vector<CGpioTimer*>& part_list = instance->GetChatteringTimeList();

	ASSERT_EQ((unsigned int)1, part_list.size());

	CGpioTimer* timer = part_list.at(0);
	CPart* part_actual = timer->GetPart();
	ASSERT_EQ(part_actual, &part);

	instance->Finalize();
}
