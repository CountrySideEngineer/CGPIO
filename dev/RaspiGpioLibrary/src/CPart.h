/*
 * CPart.h
 *
 *  Created on: 2020/02/09
 *      Author: KENSUKE
 */

#ifndef CPART_H_
#define CPART_H_
#include "pigpio/pigpio.h"
#include "CSpi.h"

class CPart {
public:
	CPart();
	CPart(uint8_t pin, uint8_t mode);
	virtual ~CPart();

	uint8_t		GetPin() const { return this->pin_; }
	void		SetPin(uint8_t pin) { this->pin_ = pin; }
	uint8_t		GetMode() const { return this->mode_; }
	void		SetMode(uint8_t mode) { this->mode_ = mode; }

	virtual	void		InterruptCallback(uint32_t state);

	virtual	uint32_t	SetSpi(CSpi* spi_config);

	uint32_t	Read();
	void		Write(uint32_t value);


protected:
	uint8_t		pin_;
	uint8_t		mode_;
	uint32_t	chattering_time_;
};

#endif /* CPART_H_ */
