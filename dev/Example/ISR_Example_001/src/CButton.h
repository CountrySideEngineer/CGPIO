/*
 * CButton.h
 *
 *  Created on: 2020/04/05
 *      Author: CountrySideEngineer
 */
#ifndef CBUTTON_H_
#define CBUTTON_H_
#include "cgpio/CPart.h"

class CButton : public CPart {
public:
	CButton();
	CButton(uint8_t pin, uint8_t mode, uint8_t edge, uint32_t chattering_time = 0);
	CButton(CPart* part, uint8_t pin, uint8_t mode, uint8_t edge, uint32_t chattering_time = 0);
	virtual ~CButton();

	void InterruptCallback(uint32_t state);

	virtual CPart* GetInterruptPart() const { return this->targetPart_; }
	virtual void SetInterruptPart(CPart* part) { this->targetPart_ = part; }

protected:
	CPart*	targetPart_;
};

#endif /* CBUTTON_H_ */
