/*
 * CGpio.h
 *
 *  Created on: 2020/02/09
 *      Author: CountrySideEngineer
 */

#ifndef CGPIO_H_
#define CGPIO_H_
#include <map>
#include "pigpio/pigpio.h"

using namespace std;

class CGpio {
public:
	const int GPIO_ERROR_OK = (0);
	const int GPIO_ERROR_GPIO = (-3);
	const int GPIO_ERROR_MODE = (-4);
	const int SPI_ERROR_BAD_CHANNEL = (-5);
	const int SPI_ERROR_BAD_SPEED = (-6);
	const int SPI_ERROR_BAD_FLGS = (-7);
	const int SPI_ERROR_AUX_SPI = (-8);
	const int SPI_ERROR_OPEN_FAILED = (-9);
	const int GPIO_FATAL_ERROR = (int)(0xFFFF);

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
		SPI_CONFIG_INDEX_SPI_MODE,
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
	const uint32_t SPI_CONFIG_FLG_SPI_MODE =
			(1 << SPI_CONFIG_INDEX_SPI_MODE);

protected:
	CGpio();

public:
	virtual ~CGpio();

public:
	static void Initialize();
	static void Finalize();
	static CGpio* GetInstance();

	int		SetMode(uint8_t pin, uint8_t direction);
	uint8_t	GetMode(uint8_t pin);
	virtual	int		SetSpi(const CSpi* spi_config);
	virtual	int		SetSpi(const int spi_clock, const uint32_t spi_flg);

protected:
	virtual	void DeactivateCe(const uint32_t spi_flg);
	virtual	void DeactivateCe(
			const int pin,
			const uint32_t spi_flg,
			const int spi_flg_index);

protected:
	int			spi_handle_;
	uint32_t	spi_flgs_;
};

#endif /* CGPIO_H_ */
