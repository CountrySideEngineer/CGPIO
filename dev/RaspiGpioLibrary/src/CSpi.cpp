/*
 * CSpi.cpp
 *
 *  Created on: 2020/02/16
 *      Author: KENSUKE
 */

#include "CSpi.h"

/**
 * @brief	Default constructor.
 * @remark	Set default value into each menber variable.
 * 			The default value is 0.
 */
CSpi::CSpi()
: channel_(SPI_CHANNEL::MAIN)
, mode_(SPI_MODE::MODE_0)
, active_mode_ce0_(SPI_ACTIVE_MODE::ACTIVE_LOW)
, active_mode_ce1_(SPI_ACTIVE_MODE::ACTIVE_LOW)
, active_mode_ce2_(SPI_ACTIVE_MODE::ACTIVE_LOW)
, comm_clock_(SPI_CLOCK::CLOCK_1M)
{}

/**
 * @brief	Constructor with argument.
 */
CSpi::CSpi(SPI_CHANNEL channel,
		SPI_MODE mode,
		SPI_ACTIVE_MODE active_mode_0,
		SPI_ACTIVE_MODE active_mode_1,
		SPI_ACTIVE_MODE active_mode_2,
		SPI_CLOCK comm_clock)
: channel_(channel)
, mode_(mode)
, active_mode_ce0_(active_mode_0)
, active_mode_ce1_(active_mode_1)
, active_mode_ce2_(active_mode_2)
, comm_clock_(comm_clock)
{}

/**
 * @brief	Destructor.
 */
CSpi::~CSpi() {}

