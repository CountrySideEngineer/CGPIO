/*
 * CSpiUTest.cpp
 *
 *  Created on: 2020/02/22
 *      Author: CountrySideEngineer
 */
#include <iostream>
#include "gtest/gtest.h"
#include "CSpi.h"

using namespace std;

TEST(CSpi, Constructor_001)
{
	CSpi spi;

	ASSERT_EQ(0, spi.GetChannel());
	ASSERT_EQ(0, spi.GetMode());
	ASSERT_EQ(0, spi.GetActiveMode0());
	ASSERT_EQ(0, spi.GetActiveMode1());
	ASSERT_EQ(0, spi.GetActiveMode2());
	ASSERT_EQ(1000000, spi.GetClock());
}

TEST(CSpi, Constructor_002)
{
	CSpi spi(CSpi::SPI_CHANNEL::AUX,
			CSpi::SPI_MODE::MODE_2,
			CSpi::SPI_ACTIVE_MODE::ACTIVE_HIGH,
			CSpi::SPI_ACTIVE_MODE::ACTIVE_LOW,
			CSpi::SPI_ACTIVE_MODE::ACTIVE_MAX,
			CSpi::SPI_CLOCK::CLOCK_10M);

	ASSERT_EQ(1, spi.GetChannel());
	ASSERT_EQ(2, spi.GetMode());
	ASSERT_EQ(1, spi.GetActiveMode0());
	ASSERT_EQ(0, spi.GetActiveMode1());
	ASSERT_EQ(2, spi.GetActiveMode2());
	ASSERT_EQ(10000000, spi.GetClock());
}
