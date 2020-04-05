/*
 * CGpio.h
 *
 *  Created on: 2020/02/09
 *      Author: CountrySideEngineer
 */

#ifndef CGPIO_H_
#define CGPIO_H_
#include <map>
#include <vector>

using namespace std;

class CGpio {
public:
	static void InitStub();

public:
	enum {
		CGPIO_STUB_BUFF_SIZE = 100
	};

public:
	CGpio() {}
	virtual ~CGpio() {}

public:
	static CGpio* GetInstance();

	int SetMode(uint8_t pin, uint8_t direction);
	uint8_t GetMode(uint8_t pin);
	void Write(uint8_t pin, uint8_t value);
	uint8_t Read(uint8_t pin);
	int SpiRead(uint8_t* data, const uint32_t data_size);
	int SpiWrite(const uint8_t* data, const uint32_t data_size);

public:
	static uint32_t GetInstance_called_count;
	static CGpio* GetInstance_ret_val[CGPIO_STUB_BUFF_SIZE];
	static uint32_t SetMode_called_count;
	static uint8_t SetMode_arg1[CGPIO_STUB_BUFF_SIZE];
	static uint8_t SetMode_arg2[CGPIO_STUB_BUFF_SIZE];
	static int SetMode_ret_val[CGPIO_STUB_BUFF_SIZE];
	static uint32_t GetMode_called_count;
	static uint8_t GetMode_arg1[CGPIO_STUB_BUFF_SIZE];
	static uint16_t GetMode_ret_val[CGPIO_STUB_BUFF_SIZE];
	static uint32_t SpiRead_called_count;
	static uint8_t* SpiRead_arg1[CGPIO_STUB_BUFF_SIZE];
	static uint32_t SpiRead_arg2[CGPIO_STUB_BUFF_SIZE];
	static int SpiRead_ret_val[CGPIO_STUB_BUFF_SIZE];
	static uint32_t SpiWrite_called_count;
	static uint8_t* SpiWrite_arg1[CGPIO_STUB_BUFF_SIZE];
	static uint32_t SpiWrite_arg2[CGPIO_STUB_BUFF_SIZE];
	static int SpiWrite_ret_val[CGPIO_STUB_BUFF_SIZE];

	static uint32_t Read_called_count;
	static uint8_t Read_arg1[CGPIO_STUB_BUFF_SIZE];
	static uint8_t Read_ret_val[CGPIO_STUB_BUFF_SIZE];
	static uint32_t Write_called_count;
	static uint8_t Write_arg1[CGPIO_STUB_BUFF_SIZE];
	static uint8_t Write_arg2[CGPIO_STUB_BUFF_SIZE];
};

#endif /* CGPIO_H_ */
