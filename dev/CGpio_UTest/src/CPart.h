/*
 * CPart.h
 *
 *  Created on: 2020/02/09
 *      Author: CountrySideEngineer
 */

#ifndef CPART_H_
#define CPART_H_
#include <cstdint>

/**
 * @class	Class for a H/W using GPIO or other pin via GPIO library.
 */
class CPart {
public:
	enum GPIO_PIN_LEVEL {
		GPIO_PIN_LOW = 0,
		GPIO_PIN_HIGH,
		GPIO_PIN_LEVEL_MAX
	};
	enum GPIO_PIN_DIRECTION {
		GPIO_PIN_INPUT,
		GPIO_PIN_OUTPUT,
		GPIO_PIN_DIRECTION_MAX
	};

public:
	CPart();
	CPart(uint8_t pin, uint8_t mode);
	CPart(uint8_t pin, uint8_t mode, uint8_t edge, uint32_t chattering_time = 0);
	virtual ~CPart();

	virtual void SetPin(uint8_t pin);
	virtual uint8_t GetPin() const { return this->pin_; }
	virtual void SetMode(uint8_t mode);
	virtual uint8_t GetMode() const { return this->mode_; }
	virtual uint32_t GetChatteringTime() const { return this->chattering_time_; }

	virtual void InterruptCallback(uint32_t state);

	virtual uint8_t Read();
	virtual void Write(uint8_t value);
	virtual uint32_t Send(uint8_t* data, uint32_t data_size);
	virtual uint32_t Recv(uint8_t* data, uint32_t data_size);

protected:
	uint8_t		pin_;
	uint8_t		mode_;
	uint32_t	chattering_time_;
};

#endif /* CPART_H_ */
