/*
 * CMDK001.h
 *
 *  Created on: 2020/03/03
 *      Author: CountrySideEngineer
 */

#ifndef CMDK001_H_
#define CMDK001_H_
#include "cgpio/CPart.h"

class CMDK001 : public CPart {
protected:
	const uint8_t COMMAND_CODE_ACCESS_CONFIG_REGISTER = 0x08;
	const uint8_t COMMAND_CODE_EXIT_SHUTDOWN_MODE = 0x00;
	const uint8_t COMMAND_CODE_ENTER_SHUTDONW_MODE = 0x60;
	const uint8_t COMMAND_CODE_SET_CONTINUOUS_READ_MODE = 0x54;

	const uint8_t COMMAND_LENGTH_EXIT_SHUTDOWN_MODE = 2;
	const uint8_t COMMAND_LENGTH_ENTER_SHUTDOWN_MODE = 2;
	const uint8_t COMMAND_LENGTH_SET_CONTINUOUS_READ_MODE = 1;
	const uint8_t RESPONSE_LENGTH_SENSOR_DATA = 2;

public:
	CMDK001();
	CMDK001(uint8_t pin, uint8_t mode, uint32_t chattering_time = 0);
	virtual ~CMDK001();

	virtual void InitDevice();
	int ReadSensorValue();
	void GetSensorValue(int16_t* integer_part, uint16_t* decimal_part);
	virtual void EnterShutdownMode();
	virtual int ExitShutdownMode();
	virtual int SetContinuousMode();

protected:
	uint16_t raw_data_;
	int16_t temperature_;
};

#endif /* CMDK001_H_ */
