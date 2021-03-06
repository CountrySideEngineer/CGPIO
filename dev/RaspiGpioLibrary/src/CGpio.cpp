/*
 * CGpio.cpp
 *
 *  Created on: 2020/02/09
 *      Author: CountrySideEngineer
 */
#include <iostream>
#include <list>
#include <vector>
#include <map>
#include <assert.h>
#include "pigpio/pigpio.h"
#include "CGpio.h"
#include "CGpioTimer.h"
#include "CGpioException.h"
#include "log.h"

using namespace std;

/**
 * @brief	Default constructor
 */
CGpio::CGpio()
: spi_handle_(-1)
, spi_flgs_(0)
, is_chattering_timer_start_(false)
{
	this->isr_pin_map_.clear();
	this->critical_section_map_.clear();
	this->chattering_time_list_.clear();

	CGpio::Initialize();
}

/**
 * @brief	Destructor.
 */
CGpio::~CGpio()
{
	CGpio::Finalize();
}

/**
 * @brief	Initialize GPIO.
 */
void CGpio::Initialize()
{
	int init_result = gpioInitialise();
	if (init_result < 0) {
		WLOG("GPIO initialize failed");
	} else {
		DLOG("GPIO initialize succeeded.");
	}
}

/**
 * @brief	Finalize GPIO.
 */
void CGpio::Finalize()
{
	this->CloseSpi();

	//Remove ISR handler.
	for (auto it = this->isr_pin_map_.begin();
			it != this->isr_pin_map_.end();
			it++)
	{
		uint pin = it->first;
		gpioSetISRFunc(pin, 0, 0, NULL);
	}
	this->isr_pin_map_.clear();

	gpioTerminate();
	this->spi_handle_ = (-1);
	this->spi_flgs_ = 0;

}

/**
 * @brief	Return pointer to CGpio instance.
 * 			CGpio object is SINGLETON.
 */
CGpio* CGpio::GetInstance()
{
	static CGpio instance_;	//Static, singleton object.

	return (CGpio*)(&instance_);
}

/**
 * @brief	Set GPIO pin mode, input or output.
 * @param	pin	GPIO pin number.
 * @param	direction	GPIO access direction, input or output.
 * @return	Returns 0 if OK, otherwise return none-zero value.
 */
int CGpio::SetMode(uint8_t pin, uint8_t direction)
{
	int set_mode_result = gpioSetMode(pin, direction);
	if (0 == set_mode_result) {
		DLOG("GPIO set mode OK");
	} else {
		uint16_t err_code = GPIO_FATAL_ERROR;
		string err_message = "";
		if (PI_BAD_MODE == set_mode_result) {
			err_code = GPIO_ERROR_MODE;
			err_message = "GPIO access mode is invalid";
		} else if (PI_BAD_GPIO == set_mode_result) {
			err_code = GPIO_ERROR_GPIO;
			err_message = "GPIO access mode is invalid";
		}
		WLOG("GPIO set mode failed : 0x%04X : %s", err_code, err_message.c_str());
		throw CGpioException(err_code, err_message);
	}
	return set_mode_result;
}

/**
 * @brief	Returns the GPIO pin mode, input or output.
 * @param	pin	The GPIO pin number.
 * @return	The pin access direction, returns 0 if mode is input, 1 in output.
 */
uint8_t CGpio::GetMode(uint8_t pin)
{
	return gpioGetMode(pin);
}

/**
 * @brief	Write GPIO pin level. If the value is 0, the pin is set low,
 * 			otherwise it is set high.
 * @param	pin	GPIO pin number.
 */
void CGpio::Write(uint8_t pin, uint8_t value)
{
	uint value_to_write = 0;
	if (0 == value) {
		value_to_write = PI_LOW;
	} else {
		value_to_write = PI_HIGH;
	}
	gpioWrite(pin, value_to_write);
}

/**
 * @brief	Read GPIO pin level, low or high.
 * @param	pin	GPIO pin number.
 * @return	Returns the GPIO pin level. Returns 0 if it is low, otherwise
 * 			returns 1.
 */
uint8_t CGpio::Read(uint8_t pin)
{
	return (uint8_t)gpioRead(pin);
}

/**
 * @param	Register interrupt object called when an interrupt detected on
 * 			the GPIO pin a H/W, abstracted as CPart, part.
 * @param	edge	The change type the interrupt to be detected, hight to low
 * 					(low edge), low to high (high edge), or both.
 * @param	part	Pointer to object to handle the interrupt.
 * @return	Returns the result of regist. Returns 0 if the regist succeeded,
 * 			otherwise return none-zero value.
 * @remarks	This method calls overloaded SetIsr() inside.
 */
int CGpio::SetIsr(uint edge, CPart* part)
{
	return this->SetIsr((int)part->GetPin(), edge, part);
}

/**
 * @param	Register interrupt object called when an interrutp detected on
 * 			the GPIO pin.
 * @param	pin	GPIO pin number an interrupt to be detected.
 * @param	edge	The change type the interrupt to be detected, hight to low
 * 					(low edge), low to high (high edge), or both.
 * @param	part	Pointer to object to handle the interruption.
 * @return	Returns the result of regist. Returns 0 if the regist succeeded,
 * 			otherwise return none-zero value.
 */
int CGpio::SetIsr(uint pin, uint edge, CPart* part)
{
	assert(nullptr != part);

	int set_isr_result = GPIO_ERROR_OK;
	if (this->isr_pin_map_.end() == this->isr_pin_map_.find(pin)) {
		//The pin has not been registered as interrupt service register.
		this->isr_pin_map_.insert(make_pair(pin, part));
		this->critical_section_map_.insert(make_pair(pin, false));
		set_isr_result =
				gpioSetISRFunc(pin, edge, 0, CGpio::GpioInterruptHandle);
		if (GPIO_ERROR_OK == set_isr_result) {
			DLOG("ISR register OK : %d", pin);
		} else {
			uint16_t err_code = CGpio::GPIO_FATAL_ERROR;
			string err_message = "";
			if (PI_BAD_GPIO == set_isr_result) {
				err_code = GPIO_ERROR_GPIO;
				err_message = "GPIO pin is invalid.";
			} else if (PI_BAD_EDGE == set_isr_result) {
				err_code = GPIO_ERROR_MODE;
				err_message = "Interrupt edge is invalid.";
			} else if (PI_BAD_ISR_INIT == set_isr_result) {
				err_code = GPIO_ERROR_ISR_INIT;
				err_message = "GPIO interrrutp initialize failed.";
			}
			WLOG("Interrutp register failed : 0x%04X : %s", err_code, err_message.c_str());
			throw CGpioException(err_code, err_message);
		}
	} else {
		DLOG("The pin interrupt has been set. : %d", pin);
		set_isr_result = GPIO_ISR_ALREADY_REGISTERED;
	}
	return set_isr_result;
}

/**
 * @brief	Call back function when the interrupt is detected.
 *
 * @param	pin	GPIO pin the interrupt detected.
 * @param	level	Levle of GPIO pin the interrupt detected, LOW or HIGH.
 * @param	tick	The passed tick count
 */
void CGpio::GpioInterruptHandle(int gpio, int level, uint32_t tick)
{
	DLOG("Interrupt detected : pin = %d / level = %d", gpio, level);

	CGpio* instance = CGpio::GetInstance();
	map<uint, CPart*>& isr_pin_map = instance->GetPinMap();
	auto isr_pin_item = isr_pin_map.find(gpio);
	if (isr_pin_item == isr_pin_map.end()) {
		WLOG("Interrupt to unexpected gpio pin %d has been detected.", gpio);
	} else {
		CPart* part = isr_pin_item->second;
		if (0 == part->GetChatteringTime()) {
			part->InterruptCallback(level);
		} else {
			instance->StartChatteringTime(part);
		}
	}
}

/**
 * @brief	Seutp timer to handle chattering of H/W.
 */
void CGpio::SetupChatteringTimer()
{
	if (false == this->is_chattering_timer_start_) {
		int set_timer_result = gpioSetTimerFunc(
				CHATTERING_TIMER_ID,
				CHATTERING_TIMER_INTERVAL,
				CGpio::ChatteringTimerDispatcher);
		if (0 == set_timer_result) {
			DLOG("The chattering timer starts");

			this->is_chattering_timer_start_ = true;
		} else {
			uint16_t err_code = CGpio::GPIO_FATAL_ERROR;
			string err_message = "";
			if (PI_BAD_TIMER == set_timer_result) {
				err_code = GPIO_CHATTERING_TIMER_BAD_ID;
				err_message = "The ID of timer to handle chattering is invalid.";
			} else if (PI_BAD_MS == set_timer_result) {
				err_code = GPIO_CHATTERING_TIMER_BAD_INTERVAL;
				err_message = "The interval for chattering is invalid.";
			} else if (PI_TIMER_FAILED == set_timer_result) {
				err_code = GPIO_CHATTERING_TIMER_FAILED;
				err_message = "The timer to handle chattering can not start.";
			}
			this->is_chattering_timer_start_ = false;
			WLOG("Chattering timer failed : 0x%04X : %s",
					err_code, err_message.c_str());
			throw CGpioException(err_code, err_message);
		}
	} else {
		DLOG("The chattering timer has already started.");
	}
}

/**
 * @brief	Start time to wait while chattering.
 *
 * @param[in]	part	Pointer to CPart to wait while chattering.
 */
void CGpio::StartChatteringTime(CPart* part)
{
	if (false == this->is_chattering_timer_start_) {
		WLOG("The chattering timer is not running.");
	} else {
		if (false == this->critical_section_map_[part->GetPin()]) {
			/*
			 * The chattering has not been handled.
			 */
			this->critical_section_map_[part->GetPin()] = true;

			std::shared_ptr<CGpioTimer> timer(new CGpioTimer(part, gpioTick()));
			this->chattering_time_list_.push_back(timer);
		} else {
			WLOG("The chattering of pin %d has already been handled",
					part->GetPin());
		}
	}
}

/**
 * @brief	Callback function when the timer to check whether the chattering
 * 			time has expired or not is dispatched.
 */
void CGpio::ChatteringTimerDispatcher()
{
	CGpio* instance = CGpio::GetInstance();
	instance->ExpireChatteringTime();
}

/**
 * @brief	Call interrupt handler of CPart object whose chattering time
 * 			has expired.
 */
void CGpio::ExpireChatteringTime()
{
	uint32_t current_tick = gpioTick();
	auto it = this->chattering_time_list_.begin();
	while (it != this->chattering_time_list_.end()) {
		shared_ptr<CGpioTimer> gpio_time = *it;

		if (gpio_time->IsExpires(current_tick)) {
			auto part = gpio_time->GetPart();

			DLOG("The pin %d expired", part->GetPin());

			uint8_t pin_level = part->Read();
			part->InterruptCallback(pin_level);

			this->critical_section_map_[part->GetPin()] = false;
			it = this->chattering_time_list_.erase(it);
		} else {
			it++;
		}
	}
}

/**
 * @brief	Setup SPI by SPI configration bit flags.
 * @param	spi_config	Reference of SPI configuration.
 * @return	Returns the over 0 value, SPI handle, if the operation succeeded,
 * 			otherwise under 0, minus value.
 */
int CGpio::SetSpi(const CSpi& spi_config)
{
	uint32_t spi_flg = 0;
	spi_flg |= (spi_config.GetMode() << SPI_CONFIG_INDEX_MODE_LOW);
	spi_flg |= (spi_config.GetActiveMode0() << SPI_CONFIG_INDEX_ACTIVE_MODE_CE0);
	spi_flg |= (spi_config.GetActiveMode1() << SPI_CONFIG_INDEX_ACTIVE_MODE_CE1);
	spi_flg |= (spi_config.GetActiveMode2() << SPI_CONFIG_INDEX_ACTIVE_MODE_CE2);
	spi_flg |= (spi_config.GetChannel() << SPI_CONFIG_INDEX_SPI_CHANNEL);

	DLOG("SPI configuration : 0x%08X", spi_flg);

	return this->SetSpi(spi_config.GetClock(), spi_flg);
}

/**
 * @brief	Setup SPI by SPI configration bit flags.
 * @param	spi_clock	Source clock speed to synchronize.
 * @param	spi_flg		Bit array of SPI configuration.
 * @return	Returns the handle of SPI value.
 * 			The value larger equals than 0 means the operation succeeded.
 * @throws	CGpioException	The SPI setup operation failed.
 */
int CGpio::SetSpi(const int spi_clock, const uint32_t spi_flg)
{
	/*
	 * Deactivate Chip sElect(CE) pin before setup SPI.
	 * If the CE pin is not deactivated before the SPI setup, the receive
	 * action can not work. No data can be received.
	 */
	this->DeactivateCe(spi_flg);
	int setup_spi_result = this->spi_handle_;
	if (0 <= this->spi_handle_) {
		DLOG("SPI has already opened.");
		/*
		 * The SPI has already open.
		 * In this case, nothing to do!
		 */
	} else {
		int spi_result = spiOpen(0, spi_clock, spi_flg);
		if (0 <= spi_result) {
			DLOG("SPI open succeeded.");

			this->spi_handle_ = spi_result;
			this->spi_flgs_ = spi_flg;

			setup_spi_result = this->spi_handle_;
		} else {
			WLOG("SPI open failed.");

			/*
			 *	When opening SPI failed, reset the SPI handle.
			 */
			this->spi_flgs_ = 0;
			this->spi_handle_ = (-1);	//Reset SPI handle.

			uint16_t err_code = CGpio::GPIO_FATAL_ERROR;
			string err_message = "";
			if (PI_BAD_SPI_CHANNEL == spi_result) {
				err_code = SPI_ERROR_BAD_CHANNEL;
				err_message = string("SPI error bad channel.");
			} else if (PI_BAD_SPI_SPEED == spi_result) {
				err_code = CGpio::SPI_ERROR_BAD_CLOCK;
				err_message = string("SPI error bad speed.");
			} else if (PI_BAD_FLAGS == spi_result) {
				err_code = CGpio::SPI_ERROR_BAD_CONFIGRATION;
				err_message = string("SPI configuration has bad flags.");
			} else if (PI_NO_AUX_SPI == spi_result) {
				err_code = CGpio::SPI_ERROR_NO_AUX;
				err_message = string("SPI error aux spi.");
			} else if (PI_SPI_OPEN_FAILED == spi_result) {
				err_code = CGpio::SPI_ERROR_OPEN_FAILED;
				err_message = string("SPI error open failed.");
			} else {
				err_code = CGpio::GPIO_FATAL_ERROR;
				err_message = string("SPI fatal error.");
			}
			WLOG("SPI failed : 0x%04X : %s", err_code, err_message.c_str());
			throw CGpioException(err_code, err_message);
		}
	}
	return setup_spi_result;
}

#define	GPIO_PIN_MAIN_CE0	(8)
#define	GPIO_PIN_MAIN_CE1	(7)
#define	GPIO_PIN_AUX_CE0	(18)
#define	GPIO_PIN_AUX_CE1	(17)
#define	GPIO_PIN_AUX_CE2	(16)
/**
 * @brief	Activate or deactivate SPI CEx pin.
 * @param	spi_flg	Bit data for SPI configuration.
 */
void CGpio::DeactivateCe(const uint32_t spi_flg)
{
	int ce_pin_0 = GPIO_PIN_MAIN_CE0;
	int ce_pin_1 = GPIO_PIN_MAIN_CE1;
	int ce_pin_2 = 0;

	if (0 == (spi_flg & (0x0100))) {
		//Main channel
		ce_pin_0 = GPIO_PIN_MAIN_CE0;
		ce_pin_1 = GPIO_PIN_MAIN_CE1;

		this->DeactivateCe(ce_pin_0, spi_flg, SPI_CONFIG_INDEX_ACTIVE_MODE_CE0);
		this->DeactivateCe(ce_pin_1, spi_flg, SPI_CONFIG_INDEX_ACTIVE_MODE_CE1);
	} else {
		//AUX channel
		ce_pin_0 = GPIO_PIN_AUX_CE0;
		ce_pin_1 = GPIO_PIN_AUX_CE1;
		ce_pin_2 = GPIO_PIN_AUX_CE2;

		this->DeactivateCe(ce_pin_0, spi_flg, SPI_CONFIG_INDEX_ACTIVE_MODE_CE0);
		this->DeactivateCe(ce_pin_1, spi_flg, SPI_CONFIG_INDEX_ACTIVE_MODE_CE1);
		this->DeactivateCe(ce_pin_2, spi_flg, SPI_CONFIG_INDEX_ACTIVE_MODE_CE2);
	}
}

/**
 * @brief	Deactivate CE pin.
 * @param	pin	GPIO pin number.
 * @param	spi_flg	SPI configuration flg.
 * @param	spi_flg_index	SPI flag index.
 */
void CGpio::DeactivateCe(
		const int pin,
		const uint32_t spi_flg,
		const int spi_flg_index)
{
	gpioSetMode(pin, PI_OUTPUT);
	if (0 == (spi_flg & (1 << spi_flg_index))) {
		//	Active when low, to deactivate ce, set GPIO level high.
		gpioWrite(pin, PI_HIGH);
	} else {
		gpioWrite(pin, PI_LOW);
	}
}

/**
 * @brief	Close SPI interface.
 */
void CGpio::CloseSpi()
{
	if (0 <= this->spi_handle_) {
		spiClose(this->spi_handle_);

		this->spi_handle_ = (-1);
	} else {
		DLOG("SPI port does not open or has already been closed.");
	}
}

/**
 * @brief	Receive data via SPI interface.
 * @param	ce_pin	Pin No. of SPI CE, Chip sElection.
 * @param[in]	data	Pointer to buffer contains data to send.
 * @param	data_size	Data size in "BYTE" unit to send.
 * @return	Returns the size of data transffered if succeeded. Otherwise
 * 			returns value under 0, meaning minus.
 * @throws	CGpioException	Receiving data via SPI interface failed.
 * @remark	This method does not change CE pin level.
 */
int CGpio::SpiRead(uint8_t* data, const uint32_t data_size)
{
	assert(NULL != data);

	int read_result = GPIO_FATAL_ERROR;
	int read_byte = spiRead(this->spi_handle_, (char*)data, data_size);
	if (0 <= read_byte) {
		DLOG("SPI read data size : %d byte.", read_byte);
		read_result = read_byte;
	} else {
		uint16_t err_code = CGpio::GPIO_FATAL_ERROR;
		string err_message = "";
		if (PI_BAD_HANDLE == read_byte) {
			err_code = CGpio::SPI_ERROR_HANDLE;
			err_message = string("The handle of SPI in invalid.");
		} else if (PI_BAD_SPI_COUNT == read_byte) {
			err_code = CGpio::SPI_ERROR_BAD_DATA_SIZE;
			err_message = string("The size of SPI transfer data is invalid.");
		} else if (PI_SPI_XFER_FAILED == read_byte) {
			err_code = CGpio::SPI_ERROR_TRANSFER_FAILED;
			err_message = string("The data transfer is failed.");
		}
		WLOG("SPI read failed : 0x%04X : %s", err_code, err_message.c_str());
		throw CGpioException(err_code, err_message);
	}

	return read_result;
}

/**
 * @brief	Send data via SPI interface.
 * @param[out]	data	Pointer to buffer contains data to send.
 * @param	data_size	Size of data to send.
 * @return	Returns the size of data sent if succeeded. Otherwise
 * 			returns value under 0, meaning minus.
 * @throws	CGpioException	Sending data via SPI interface failed.
 * @remark	This method does not change CE pin level.
 */
int CGpio::SpiWrite(const uint8_t* data, const uint32_t data_size)
{
	assert(NULL != data);

	int write_result = GPIO_FATAL_ERROR;
	int write_byte = spiWrite(this->spi_handle_, (char*)data, data_size);
	if (0 <= write_byte) {
		DLOG("SPI write data size : %d byte.", write_byte);
		write_result = write_byte;
 	} else {
		uint16_t err_code = CGpio::GPIO_FATAL_ERROR;
		string err_message = "";
		if (PI_BAD_HANDLE == write_byte) {
			err_code = CGpio::SPI_ERROR_HANDLE;
			err_message = string("The handle of SPI in invalid.");
		} else if (PI_BAD_SPI_COUNT == write_byte) {
			err_code = CGpio::SPI_ERROR_BAD_DATA_SIZE;
			err_message = string("The size of SPI transfer data is invalid.");
		} else if (PI_SPI_XFER_FAILED == write_byte) {
			err_code = CGpio::SPI_ERROR_TRANSFER_FAILED;
			err_message = string("The data transfer is failed.");
		}
		WLOG("SPI read failed : 0x%04X : %s", err_code, err_message.c_str());
		throw CGpioException(err_code, err_message);
 	}
	return write_result;
}

void CGpio::EnterCriticalSection(int pin)
{
	auto it = this->critical_section_map_.find(pin);
	if (it == this->critical_section_map_.end()) {
		WLOG("Pin %d has not been ISR.", pin);
	} else {
		this->SetCriticalSection(pin, true);
	}
}

void CGpio::ExitCriticalSection(int pin)
{
	auto it = this->critical_section_map_.find(pin);
	if (it == this->critical_section_map_.end()) {
		WLOG("Pin %d has not been ISR.", pin);
	} else {
		this->SetCriticalSection(pin, false);
	}
}

void CGpio::SetCriticalSection(int pin, bool criticalSection)
{
	this->critical_section_map_[pin] = criticalSection;
}

bool CGpio::IsInCriticalSection(int pin)
{
	bool inCriticalSection = false;
	auto it = this->critical_section_map_.find(pin);
	if (it == this->critical_section_map_.end()) {
		WLOG("Pin %d has not been ISR.", pin);

		inCriticalSection = false;
	} else {
		inCriticalSection = this->critical_section_map_[pin];
	}
	return inCriticalSection;
}
