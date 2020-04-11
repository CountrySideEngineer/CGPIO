/*
 * CGpio.cpp
 *
 *  Created on: 2020/02/09
 *      Author: CountrySideEngineer
 */
#include <iostream>
#include <list>
#include <vector>
#include <map>
#include <assert.h>
#include "CGpio.h"

uint32_t CGpio::GetInstance_called_count;
CGpio* CGpio::GetInstance_ret_val[CGpio::CGPIO_STUB_BUFF_SIZE];
uint32_t CGpio::SetMode_called_count;
uint8_t CGpio::SetMode_arg1[CGpio::CGPIO_STUB_BUFF_SIZE];
uint8_t CGpio::SetMode_arg2[CGpio::CGPIO_STUB_BUFF_SIZE];
int  CGpio::SetMode_ret_val[CGPIO_STUB_BUFF_SIZE];
uint32_t CGpio::GetMode_called_count;
uint8_t CGpio::GetMode_arg1[CGpio::CGPIO_STUB_BUFF_SIZE];
uint16_t CGpio::GetMode_ret_val[CGpio::CGPIO_STUB_BUFF_SIZE];
uint32_t CGpio::SpiRead_called_count;
uint8_t* CGpio::SpiRead_arg1[CGpio::CGPIO_STUB_BUFF_SIZE];
uint32_t CGpio::SpiRead_arg2[CGpio::CGPIO_STUB_BUFF_SIZE];
int CGpio::SpiRead_ret_val[CGpio::CGPIO_STUB_BUFF_SIZE];
uint32_t CGpio::SpiWrite_called_count;
uint8_t* CGpio::SpiWrite_arg1[CGpio::CGPIO_STUB_BUFF_SIZE];
uint32_t CGpio::SpiWrite_arg2[CGpio::CGPIO_STUB_BUFF_SIZE];
int CGpio::SpiWrite_ret_val[CGpio::CGPIO_STUB_BUFF_SIZE];
uint32_t CGpio::Read_called_count;
uint8_t CGpio::Read_arg1[CGpio::CGPIO_STUB_BUFF_SIZE];
uint8_t CGpio::Read_ret_val[CGpio::CGPIO_STUB_BUFF_SIZE];
uint32_t CGpio::Write_called_count;
uint8_t CGpio::Write_arg1[CGpio::CGPIO_STUB_BUFF_SIZE];
uint8_t CGpio::Write_arg2[CGpio::CGPIO_STUB_BUFF_SIZE];

using namespace std;

void CGpio::InitStub()
{
	CGpio::GetInstance_called_count = 0;
	CGpio::SetMode_called_count = 0;
	CGpio::GetMode_called_count = 0;
	CGpio::SpiRead_called_count = 0;
	CGpio::SpiWrite_called_count = 0;
	CGpio::Read_called_count = 0;
	CGpio::Write_called_count = 0;

	for (int index = 0; index < CGpio::CGPIO_STUB_BUFF_SIZE; index++) {
		CGpio::GetInstance_ret_val[index] = nullptr;
		CGpio::Read_arg1[index] = 0;
		CGpio::Read_ret_val[index] = 0;
		CGpio::Write_arg1[index] = 0;
		CGpio::Write_arg2[index] = 0;
		CGpio::SetMode_arg1[index] = 0;
		CGpio::SetMode_arg2[index] = 0;
		CGpio::SetMode_ret_val[index] = 0;
		CGpio::GetMode_arg1[index] = 0;
		CGpio::GetMode_ret_val[index] = 0;
		CGpio::SpiRead_arg1[index] = nullptr;
		CGpio::SpiRead_arg2[index] = 0;
		CGpio::SpiRead_ret_val[index] = 0;
		CGpio::SpiWrite_arg1[index] = nullptr;
		CGpio::SpiWrite_arg2[index] = 0;
		CGpio::SpiWrite_ret_val[index] = 0;
	}
}

/**
 * @brief	Return pointer to CGpio instance.
 * 			CGpio object is SINGLETON.
 */
CGpio* CGpio::GetInstance()
{
	CGpio* ret = CGpio::GetInstance_ret_val[CGpio::GetInstance_called_count];
	GetInstance_called_count++;

	return ret;
}

/**
 * @brief	Set GPIO pin mode, input or output.
 * @param	pin	GPIO pin number.
 * @param	direction	GPIO access direction, input or output.
 * @return	Returns 0 if OK, otherwise return none-zero value.
 */
int CGpio::SetMode(uint8_t pin, uint8_t direction)
{
	CGpio::SetMode_arg1[CGpio::SetMode_called_count] = pin;
	CGpio::SetMode_arg2[CGpio::SetMode_called_count] = direction;
	int ret = CGpio::SetMode_ret_val[SetMode_called_count];
	CGpio::SetMode_called_count++;

	return ret;
}

/**
 * @brief	Returns the GPIO pin mode, input or output.
 * @param	pin	The GPIO pin number.
 * @return	The pin access direction, returns 0 if mode is input, 1 in output.
 */
uint8_t CGpio::GetMode(uint8_t pin)
{
	CGpio::GetMode_arg1[CGpio::GetMode_called_count] = pin;
	uint8_t ret = CGpio::GetMode_ret_val[CGpio::GetMode_called_count];
	CGpio::GetMode_called_count++;

	return ret;
}

/**
 * @brief	Write GPIO pin level. If the value is 0, the pin is set low,
 * 			otherwise it is set high.
 * @param	pin	GPIO pin number.
 */
void CGpio::Write(uint8_t pin, uint8_t value)
{
	CGpio::Write_arg1[CGpio::Write_called_count] = pin;
	CGpio::Write_arg2[CGpio::Write_called_count] = value;
	Write_called_count++;
}

/**
 * @brief	Read GPIO pin level, low or high.
 * @param	pin	GPIO pin number.
 * @return	Returns the GPIO pin level. Returns 0 if it is low, otherwise
 * 			returns 1.
 */
uint8_t CGpio::Read(uint8_t pin)
{
	CGpio::Read_arg1[CGpio::Read_called_count] = pin;
	uint8_t ret = Read_ret_val[CGpio::Read_called_count];
	CGpio::Read_called_count++;

	return ret;
}

/**
 * @brief	Receive data via SPI interface.
 * @param	ce_pin	Pin No. of SPI CE, Chip sElection.
 * @param[in]	data	Pointer to buffer contains data to send.
 * @param	data_size	Data size in "BYTE" unit to send.
 * @return	Returns the size of data transffered if succeeded. Otherwise
 * 			returns value under 0, meaning minus.
 * @throws	CGpioException	Receiving data via SPI interface failed.
 * @remark	This method does not change CE pin level.
 */
int CGpio::SpiRead(uint8_t* data, const uint32_t data_size)
{
	printf("CGpio::SpiRead() called\r\n");

	CGpio::SpiRead_arg1[CGpio::SpiRead_called_count] = data;
	CGpio::SpiRead_arg2[CGpio::SpiRead_called_count] = (uint32_t)data_size;
	int ret = SpiRead_ret_val[CGpio::SpiRead_called_count];
	CGpio::SpiRead_called_count++;

	return ret;
}

/**
 * @brief	Send data via SPI interface.
 * @param[out]	data	Pointer to buffer contains data to send.
 * @param	data_size	Size of data to send.
 * @return	Returns the size of data sent if succeeded. Otherwise
 * 			returns value under 0, meaning minus.
 * @throws	CGpioException	Sending data via SPI interface failed.
 * @remark	This method does not change CE pin level.
 */
int CGpio::SpiWrite(const uint8_t* data, const uint32_t data_size)
{
	CGpio::SpiWrite_arg1[CGpio::SpiWrite_called_count] = (uint8_t*)data;
	CGpio::SpiWrite_arg2[CGpio::SpiWrite_called_count] = (uint32_t)data_size;
	int ret = SpiWrite_ret_val[CGpio::SpiWrite_called_count];
	CGpio::SpiWrite_called_count++;

	return ret;
}

