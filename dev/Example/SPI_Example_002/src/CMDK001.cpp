/*
 * CMDK001.cpp
 *
 *  Created on: 2020/03/03
 *      Author: CountrySideEngineer
 */
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <assert.h>
#include "CMDK001.h"
#include "cgpio/CGpio.h"
#include "log.h"

/**
 * @brief	Default constructor.
 */
CMDK001::CMDK001()
:CPart()
, raw_data_(0)
, temperature_(0)
{}

/**
 * @brief	Constructor with parameters.
 * @param	pin	GPIO pin number the device uses.
 * 				In the CMDK001 class, the pin supposed to use it as CE.
 * @param	mode	GPIO pin access mode, input or output.
 * @param	chattering_time	Time to wait while chattering.
 * 							In the CMDK001, this value does not use.
 */
CMDK001::CMDK001(uint8_t pin, uint8_t mode, uint32_t chattering_time)
: CPart(pin, mode, chattering_time)
, raw_data_(0)
, temperature_(0)
{}

/**
 * @brief	Destructor.
 */
CMDK001::~CMDK001() {}

/**
 * @brief	Initialize device.
 */
void CMDK001::InitDevice()
{
	CSpi spi(CSpi::SPI_CHANNEL::MAIN,
			CSpi::SPI_MODE::MODE_3,
			CSpi::SPI_ACTIVE_MODE::ACTIVE_LOW,
			CSpi::SPI_ACTIVE_MODE::ACTIVE_LOW,
			CSpi::SPI_ACTIVE_MODE::ACTIVE_LOW,
			CSpi::SPI_CLOCK::CLOCK_40K);

	CGpio* instance = CGpio::GetInstance();
	instance->SetMode(this->pin_, this->mode_);
	instance->Write(this->pin_, 1);

	instance->SetSpi(spi);
	/*
	 * The method above "SetSpi" set the pin CE level set into deactive SPI.
	 */
}

/**
 * @brief	Set MDK001 into shutdown mode.
 */
void CMDK001::EnterShutdownMode()
{
	uint8_t tx_buff[COMMAND_LENGTH_ENTER_SHUTDOWN_MODE];
	tx_buff[0] = this->COMMAND_CODE_ACCESS_CONFIG_REGISTER;
	tx_buff[1] = this->COMMAND_CODE_ENTER_SHUTDONW_MODE;

	DLOG("[CMDK001]Command to enter shutdonw mode : 0x%02x 0x%02x",
			tx_buff[0], tx_buff[1]);
	this->Send(tx_buff, COMMAND_LENGTH_ENTER_SHUTDOWN_MODE);
	this->Write(GPIO_PIN_HIGH);
}

/**
 * @brief	Exit MDK001 from shutdown mode.
 * @return	Returns 0 if the device can exit shutdown mode, otherwise returns
 * 			none 0 value.
 */
int CMDK001::ExitShutdownMode()
{
	uint8_t tx_buff[COMMAND_LENGTH_EXIT_SHUTDOWN_MODE];
	tx_buff[0] = this->COMMAND_CODE_ACCESS_CONFIG_REGISTER;
	tx_buff[1] = this->COMMAND_CODE_EXIT_SHUTDOWN_MODE;

	this->Write(GPIO_PIN_LOW);
	uint32_t send_data_size =
			this->Send(tx_buff, COMMAND_LENGTH_EXIT_SHUTDOWN_MODE);

	//To exit shutdown mode, it takes 1m sec.
	struct timespec waitTime = { 0 };
	waitTime.tv_sec = 0;
	waitTime.tv_nsec = 1 * 1000 * 1000;	//1m sec.
	nanosleep((const struct timespec*)&waitTime, 0);

	if (COMMAND_LENGTH_EXIT_SHUTDOWN_MODE == send_data_size) {
		DLOG("[CMDK001]Exit shutdown mode");
		return 0;
	} else {
		WLOG("[CMDK001]Can not exit shutdown mode");
		return (-1);
	}
}

/**
 * @brief	Set MDK001 into continuous read mode.
 * @return	Returns 0 if the device can enter into continuous read model.
 * 			(This method returns 0 only.)
 */
int CMDK001::SetContinuousMode()
{
	uint8_t tx_buff = COMMAND_CODE_SET_CONTINUOUS_READ_MODE;

	this->Write(GPIO_PIN_LOW);
	int send_data_size = this->Send(&tx_buff, COMMAND_LENGTH_EXIT_SHUTDOWN_MODE);
	if (send_data_size < 0) {
		WLOG("[CMDK001]Set continuous mode fialed.");
	} else {
		DLOG("[CMDK001]Set continuous mode succeeded.");
	}

	//To set continuous read mode, wait for 240 msec.
	struct timespec waitTime = { 0 };
	waitTime.tv_sec = 0;
	waitTime.tv_nsec = 240 * 1000 * 1000;	//1m sec.
	nanosleep((const struct timespec*)&waitTime, 0);

	/*
	 * After entering continuous mode, the CE pin need to be in low level.
	 */
	return send_data_size;
}

/**
 * @brief	Run sequence to read value from sensor.
 * @reutrn	Returns 0 if the sequence finishes successfully, otherwise none
 * 			0 value.
 */
int CMDK001::ReadSensorValue()
{
	uint8_t rx_buff[RESPONSE_LENGTH_SENSOR_DATA];
	int data_len = this->Recv(rx_buff, RESPONSE_LENGTH_SENSOR_DATA);
	if (RESPONSE_LENGTH_SENSOR_DATA != data_len) {
		return (-1);
	}

	DLOG("[CMDK001]Read sensor value : 0x%02x 0x%02x",
			rx_buff[0], rx_buff[1]);

	this->raw_data_ = (((uint16_t)rx_buff[0]) << 8) + (uint16_t)rx_buff[1];
	this->raw_data_ >>= 3;	//Remove lower 3 bit.
	if (0x8000 & this->raw_data_) {
		this->temperature_ = (int16_t)(this->raw_data_ - 8192);
	} else {
		this->temperature_ = (int16_t)raw_data_;
	}

	return 0;
}

/**
 * @brief	Get sensor value interger and decimal part.
 * @param[out]	integer_part	Pointer to buffer to store integer part.
 * @param[out]	decimal_part	Pointer to buffer to streo decimal part.
 */
void CMDK001::GetSensorValue(int16_t* integer_part, uint16_t* decimal_part)
{
	assert(NULL != integer_part);
	assert(NULL != decimal_part);

	*integer_part = this->temperature_ / 16;
	*decimal_part = (uint16_t)(((uint32_t)this->temperature_ * 625) % 1000);
}
