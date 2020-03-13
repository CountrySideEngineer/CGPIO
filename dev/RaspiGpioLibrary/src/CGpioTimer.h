/*
 * CGpioTimer.h
 *
 *  Created on: 2020/03/13
 *      Author: CountrySideEngineer
 */

#ifndef CGPIOTIMER_H_
#define CGPIOTIMER_H_
#include "CPart.h"

/**
 * @class	A class to manage timer dispatch.
 */
class CGpioTimer {
public:
	CGpioTimer();
	CGpioTimer(CPart* part, uint32_t start_time, uint32_t dispatch_time);
	virtual ~CGpioTimer();

	virtual bool IsExpires(const uint32_t current_time);

	virtual CPart* GetPart() const { return this->part_; }
	virtual uint32_t GetDispatchTime() const { return this->dispatch_time_; }
	virtual uint32_t GetStartTime() const { return this->start_time_; }
	virtual void SetStartTime(uint32_t start_time) { this->start_time_ = start_time; }

protected:
	CPart* part_;
	uint32_t start_time_;
	uint32_t dispatch_time_;
};

#endif /* CGPIOTIMER_H_ */
