/*
 * CSpi.h
 *
 *  Created on: 2020/02/16
 *      Author: KENSUKE
 */

#ifndef CSPI_H_
#define CSPI_H_

class CSpi {
public:
	/**
	 * Enum for SPI channel, main and aux.
	 */
	typedef enum _SPI_CHANNEL {
		MAIN = 0u,
		AUX,
		MAX
	} SPI_CHANNEL;

	/**
	 * Enum for SPI mode, mode 0 to 3.
	 */
	typedef enum _SPI_MODE {
		MODE_0 = 0u,
		MODE_1,
		MODE_2,
		MODE_3,
		MODE_MAX
	} SPI_MODE;

	/**
	 * Enum for SPI active mode, active when GPIO pin level is low or high.
	 */
	typedef enum _SPI_ACTIVE_MODE {
		ACTIVE_LOW = 0u,
		ACTIVE_HIGH,
		ACTIVE_MAX
	} SPI_ACTIVE_MODE;

	/**
	 * Enum for SPI communication speed by clock.
	 * For raspberry pi, the speed can set any integer value, but, in this
	 * library, the speed limits to make it use easy.
	 */
	typedef enum _SPI_CLOCK {
		CLOCK_125K = 125u * 1000u,
		CLOCK_250K = 250u * 1000u,
		CLOCK_500K = 500u * 1000u,
		CLOCK_1M = 1u * 1000u * 1000u,
		CLOCK_10M = 10u * 1000u * 1000u
	} SPI_CLOCK;

public:
	CSpi();
	CSpi(SPI_CHANNEL channel,
			SPI_MODE mode,
			SPI_ACTIVE_MODE active_mode_ce0,
			SPI_ACTIVE_MODE active_mode_ce1,
			SPI_ACTIVE_MODE active_mode_ce2,
			SPI_CLOCK spi_clock);
	virtual ~CSpi();

	SPI_CHANNEL			GetChannel() const { return this->channel_; }
	SPI_MODE			GetMode() const { return this->mode_; }
	SPI_ACTIVE_MODE 	GetActiveMode0() const { return this->active_mode_ce0_; }
	SPI_ACTIVE_MODE 	GetActiveMode1() const { return this->active_mode_ce1_; }
	SPI_ACTIVE_MODE 	GetActiveMode2() const { return this->active_mode_ce2_; }
	SPI_CLOCK			GetClock() const { return this->comm_clock_; }

protected:
	SPI_CHANNEL		channel_;
	SPI_MODE		mode_;
	SPI_ACTIVE_MODE	active_mode_ce0_;
	SPI_ACTIVE_MODE active_mode_ce1_;
	SPI_ACTIVE_MODE active_mode_ce2_;
	SPI_CLOCK		comm_clock_;
};

#endif /* CSPI_H_ */
