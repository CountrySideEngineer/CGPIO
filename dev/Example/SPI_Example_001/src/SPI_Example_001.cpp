//============================================================================
// Name        : SPI_Example_001.cpp
// Author      : CountrySideEngineer
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <unistd.h>
#include "cgpio/CSpi.h"
#include "cgpio/CPart.h"
#include "cgpio/CGpio.h"
#include "pigpio/pigpio.h"
#include "log.h"

using namespace std;

#define	PIN_SPI0_CE0		(8)
#define	PIN_SPI0_CE1		(9)
#define	SPI_BUFF_SIZE		(10)
#define	SPI_TX_BUFF_SIZE	(SPI_BUFF_SIZE)
#define	SPI_RX_BUFF_SIZE	(SPI_BUFF_SIZE)

/**
 * @brief	Main function of SPI communication.
 * @detail	Main function using SPI interface as MASTER to communicate with@n
 * 			slave device.@n
 * 			In this sample application, the slave device is arduino nano.
 */
int main() {
	CSpi spi(CSpi::SPI_CHANNEL::MAIN,
			CSpi::SPI_MODE::MODE_0,
			CSpi::SPI_ACTIVE_MODE::ACTIVE_LOW,
			CSpi::SPI_ACTIVE_MODE::ACTIVE_LOW,
			CSpi::SPI_ACTIVE_MODE::ACTIVE_LOW,
			CSpi::SPI_CLOCK::CLOCK_125K);
	CGpio* instance = CGpio::GetInstance();
	unsigned int handle = instance->SetSpi(spi);
	DLOG("SPI handle = %d", handle);

	uint ce_pin = PIN_SPI0_CE0;
	CPart spi_part(ce_pin, CPart::GPIO_PIN_OUTPUT);

	uint8_t tx_buff[SPI_TX_BUFF_SIZE] = { 0 };
	for (int index = 0; index < SPI_TX_BUFF_SIZE; index++) {
		tx_buff[index] = 0x00;
	}
	uint8_t rx_buff[SPI_RX_BUFF_SIZE] = { 0 };
	for (int index = 0; index < SPI_RX_BUFF_SIZE; index++) {
		rx_buff[index] = 0xFF;
	}

	//Setup send data.
	for (int index = 0; index < 10; index++) {
		/*
		 * Setup send data.
		 * The data changes every time to make it be able to check
		 * the data received in the slave device.
		 */
		for (int sub_index = 0; sub_index < SPI_TX_BUFF_SIZE; sub_index++) {
			tx_buff[sub_index] = (uint8_t)(index + sub_index);
		}
		DLOG("Loop count - %3d", index);
		DLOG("Send data - 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X",
				tx_buff[0], tx_buff[1], tx_buff[2], tx_buff[3], tx_buff[4],
				tx_buff[5], tx_buff[6], tx_buff[7], tx_buff[8], tx_buff[9]);

		spi_part.Write(CPart::GPIO_PIN_LOW);	//Activate SPI.
		spi_part.Send(&tx_buff[0], SPI_TX_BUFF_SIZE);
		usleep(10 * 1000);
		uint32_t recv_data_size = spi_part.Recv(&rx_buff[0], 3);
		spi_part.Write(CPart::GPIO_PIN_HIGH);	//Deactivate SPI.

		DLOG("Recv data size - %d", recv_data_size);
		DLOG("Recv data - 0x%02X 0x%02X 0x%02X",
				rx_buff[0], rx_buff[1], rx_buff[2]);

		usleep(600 * 1000);	//Wait a second.
	}

	return 0;
}
