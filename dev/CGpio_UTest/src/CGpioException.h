/*
 * CGpioException.h
 *
 *  Created on: 2020/03/14
 *      Author: CountrySideEngineer
 */

#ifndef CGPIOEXCEPTION_H_
#define CGPIOEXCEPTION_H_
#include <iostream>
#include <string>
#include <exception>

using namespace std;

#define	STUB_BUFF_SIZE		(100)

/**
 * @class Stub class of CGpioException.
 */
class CGpioException : public exception {
public:
	static void InitStub();

public:
	CGpioException();
	CGpioException(uint16_t code, string message);
	virtual ~CGpioException();

	virtual uint16_t GetCode() const { return this->code_; }
	virtual string	GetMessage() const { return this->message_; }

public:
	static uint32_t	default_constructor_called_count;
	static uint32_t	constructor_with_argument_called_count;

protected:
	uint16_t	code_;
	string		message_;
};

#endif /* CGPIOEXCEPTION_H_ */
