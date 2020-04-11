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
#include <memory>
#include "CPart.h"
#include "CSpi.h"
#include "CGpioTimer.h"

class CPart;

using namespace std;

class CGpio {
public:
	const uint16_t GPIO_ERROR_OK = (0x0000);
	const uint16_t GPIO_ERROR_GPIO = (0x0003);
	const uint16_t GPIO_ERROR_MODE = (0x0004);
	const uint16_t GPIO_ERROR_ISR_INIT = (0x0005);
	const uint16_t SPI_ERROR_BAD_CHANNEL = (0x0010);
	const uint16_t SPI_ERROR_BAD_CLOCK = (0x0011);
	const uint16_t SPI_ERROR_BAD_CONFIGRATION = (0x0012);
	const uint16_t SPI_ERROR_NO_AUX = (0x0013);
	const uint16_t SPI_ERROR_OPEN_FAILED = (0x0014);
	const uint16_t SPI_ERROR_HANDLE = (0x0015);
	const uint16_t SPI_ERROR_BAD_DATA_SIZE = (0x0016);
	const uint16_t SPI_ERROR_TRANSFER_FAILED = (0x0017);
	const uint16_t GPIO_ISR_ALREADY_REGISTERED = (0x0021);
	const uint16_t GPIO_ISR_BAD_EDGE = (0x0022);
	const uint16_t GPIO_CHATTERING_TIMER_BAD_ID = (0x0030);
	const uint16_t GPIO_CHATTERING_TIMER_BAD_INTERVAL = (0x0031);
	const uint16_t GPIO_CHATTERING_TIMER_FAILED = (0x0032);
	const uint16_t GPIO_FATAL_ERROR = (0xFFFF);

protected:
	enum {
		SPI_CONFIG_INDEX_SPI_MODE_LOW = 0,
		SPI_CONFIG_INDEX_SPI_MODE_HIGH,
	};
	enum {
		SPI_CONFIG_INDEX_MODE_LOW = 0,
		SPI_CONFIG_INDEX_MODE_HIGH,
		SPI_CONFIG_INDEX_ACTIVE_MODE_CE0,
		SPI_CONFIG_INDEX_ACTIVE_MODE_CE1,
		SPI_CONFIG_INDEX_ACTIVE_MODE_CE2,
		SPI_CONFIG_INDEX_RESERVED_CE0,
		SPI_CONFIG_INDEX_RESERVED_CE1,
		SPI_CONFIG_INDEX_RESERVED_CE2,
		SPI_CONFIG_INDEX_SPI_CHANNEL,
		SPI_CONFIG_INDEX_MAX,
	};

	const uint32_t SPI_CONFIG_FLG_MODE = (3 << SPI_CONFIG_INDEX_MODE_LOW);
	const uint32_t SPI_CONFIG_FLG_ACTIVE_MODE_CE0_HIGH =
			(1 << SPI_CONFIG_INDEX_ACTIVE_MODE_CE0);
	const uint32_t SPI_CONFIG_FLG_ACTIVE_MODE_CE1_HIGH =
			(1 << SPI_CONFIG_INDEX_ACTIVE_MODE_CE1);
	const uint32_t SPI_CONFIG_FLG_ACTIVE_MODE_CE2_HIGH =
			(1 << SPI_CONFIG_INDEX_ACTIVE_MODE_CE2);
	const uint32_t SPI_CONFIG_FLG_CE0_RESERVED_FOR_SPI =
			(1 << SPI_CONFIG_INDEX_RESERVED_CE0);
	const uint32_t SPI_CONFIG_FLG_CE1_RESERVED_FOR_SPI =
			(1 << SPI_CONFIG_INDEX_RESERVED_CE1);
	const uint32_t SPI_CONFIG_FLG_CE2_RESERVED_FOR_SPI =
			(1 << SPI_CONFIG_INDEX_RESERVED_CE2);
	const uint32_t SPI_CONFIG_FLG_SPI_CHANNEL =
			(1 << SPI_CONFIG_INDEX_SPI_CHANNEL);
	const uint CHATTERING_TIMER_ID = 0;		//ID for chattering timer.
	const uint CHATTERING_TIMER_INTERVAL = 10;	//10 milli sec.

protected:
	CGpio();

public:
	virtual ~CGpio();

public:
	static CGpio* GetInstance();
	static void Interrupt(int pin, int level, uint32_t tick);
	static void ChatteringTimerDispatcher();

	virtual int SetMode(uint8_t pin, uint8_t direction);
	virtual uint8_t GetMode(uint8_t pin);
	virtual void Write(uint8_t pin, uint8_t value);
	virtual uint8_t Read(uint8_t pin);
	virtual int SetIsr(uint edge, CPart* part);
	virtual int SetIsr(uint pin, uint edge, CPart* part);
	virtual int SetSpi(const CSpi& spi_config);
	virtual int SetSpi(const int spi_clock, const uint32_t spi_flg);
	virtual void CloseSpi();
	virtual int SpiRead(uint8_t* data, const uint32_t data_size);
	virtual int SpiWrite(const uint8_t* data, const uint32_t data_size);
	virtual void Initialize();
	virtual void Finalize();

	virtual int GetSpiHandle() const { return this->spi_handle_; }
	virtual uint32_t GetSpiFlg() const { return this->spi_flgs_; }
	virtual map<uint, CPart*>& GetPinMap() { return this->isr_pin_map_; }
	virtual vector<shared_ptr<CGpioTimer>>& GetChatteringTimeList() { return this->chattering_time_list_; }

	virtual void SetupChatteringTimer();
	virtual void StartChatteringTime(CPart* part);
	virtual void ExpireChatteringTime();

protected:
	static void GpioInterruptHandle(int gpio, int level, uint32_t tick);

	virtual void DeactivateCe(const uint32_t spi_flg);
	virtual void DeactivateCe(
			const int pin,
			const uint32_t spi_flg,
			const int spi_flg_index);
	virtual void EnterCriticalSection(int pin);
	virtual void ExitCriticalSection(int pin);
	virtual void SetCriticalSection(int pin, bool ciritcalSection);
	virtual bool IsInCriticalSection(int pin);

protected:
	CGpio*		gpio_;
	int			spi_handle_;
	uint32_t	spi_flgs_;

	bool		is_chattering_timer_start_;
	map<uint, CPart*> isr_pin_map_;
	map<uint, bool> critical_section_map_;
	vector<std::shared_ptr<CGpioTimer>> chattering_time_list_;
};

#endif /* CGPIO_H_ */
