/*
 * CPart.h
 *
 *  Created on: 2020/02/09
 *      Author: CountrySideEngineer
 */

#ifndef CPART_H_
#define CPART_H_
#include "pigpio/pigpio.h"
#include "CSpi.h"

class CGpio;

/**
 * @class	Class for a H/W using GPIO or other pin via GPIO library.
 */
class CPart {
public:
	CPart();
	CPart(CGpio* gpio);
	CPart(CGpio* gpio, uint8_t pin, uint8_t mode, uint32_t chattering_time = 0);
	virtual ~CPart();

	virtual void SetPin(uint8_t pin);
	virtual uint8_t GetPin() const { return this->pin_; }
	virtual void SetMode(uint8_t mode);
	virtual uint8_t GetMode() const { return this->mode_; }

	virtual void InterruptCallback(uint32_t state);

	virtual uint8_t Read() { return 0; }
	virtual void Write(uint8_t value) {}

protected:
	CGpio*		gpio_;
	uint8_t		pin_;
	uint8_t		mode_;
	uint32_t	chattering_time_;
};

#endif /* CPART_H_ */
