#include <stdio.h>
#include "pigpio/pigpio.h"
#define GPIO_STUB_BUF_SIZE			(100)

/*-----------------------------------*/
/*----                           ----*/
/*---- Start gpioInitialise stub ----*/
/*----                           ----*/
/*-----------------------------------*/
int gpioInitialise_called_count;
int gpioInitialise_ret_val[GPIO_STUB_BUF_SIZE];
int gpioInitialise()
{
	int ret_val =
		gpioInitialise_ret_val
		[gpioInitialise_called_count];


	gpioInitialise_called_count++;

	return (ret_val);
}
void gpioInitialise_init()
{
	int idx = 0;

	gpioInitialise_called_count = 0;
	for (idx = 0; idx < GPIO_STUB_BUF_SIZE; idx++) {
		gpioInitialise_ret_val[idx] = 0;
	}
}

/*----------------------------------*/
/*----                          ----*/
/*---- Start gpioTerminate stub ----*/
/*----                          ----*/
/*----------------------------------*/
int gpioTerminate_called_count;
int gpioTerminate_ret_val[GPIO_STUB_BUF_SIZE];
void gpioTerminate()
{

	gpioTerminate_called_count++;
}
void gpioTerminate_init()
{
	int idx = 0;

	gpioTerminate_called_count = 0;
	for (idx = 0; idx < GPIO_STUB_BUF_SIZE; idx++) {
		gpioTerminate_ret_val[idx] = 0;
	}
}

/*--------------------------------*/
/*----                        ----*/
/*---- Start gpioSetMode stub ----*/
/*----                        ----*/
/*--------------------------------*/
int gpioSetMode_called_count;
uint gpioSetMode_arg_1[GPIO_STUB_BUF_SIZE];
uint gpioSetMode_arg_2[GPIO_STUB_BUF_SIZE];
int gpioSetMode_ret_val[GPIO_STUB_BUF_SIZE];
int gpioSetMode(
	uint gpio,
	uint mode)
{
	int ret_val =
		gpioSetMode_ret_val
		[gpioSetMode_called_count];

	gpioSetMode_arg_1
		[gpioSetMode_called_count] =
			gpio;
	gpioSetMode_arg_2
		[gpioSetMode_called_count] =
			mode;

	gpioSetMode_called_count++;

	return (ret_val);
}
void gpioSetMode_init()
{
	int idx = 0;

	gpioSetMode_called_count = 0;
	for (idx = 0; idx < GPIO_STUB_BUF_SIZE; idx++) {
		gpioSetMode_arg_1[idx] = 0;
		gpioSetMode_arg_2[idx] = 0;
		gpioSetMode_ret_val[idx] = 0;
	}
}

/*--------------------------------*/
/*----                        ----*/
/*---- Start gpioGetMode stub ----*/
/*----                        ----*/
/*--------------------------------*/
int gpioGetMode_called_count;
uint gpioGetMode_arg_1[GPIO_STUB_BUF_SIZE];
int gpioGetMode_ret_val[GPIO_STUB_BUF_SIZE];
int gpioGetMode(
	uint gpio)
{
	int ret_val =
		gpioGetMode_ret_val
		[gpioGetMode_called_count];

	gpioGetMode_arg_1
		[gpioGetMode_called_count] =
			gpio;

	gpioGetMode_called_count++;

	return (ret_val);
}
void gpioGetMode_init()
{
	int idx = 0;

	gpioGetMode_called_count = 0;
	for (idx = 0; idx < GPIO_STUB_BUF_SIZE; idx++) {
		gpioGetMode_arg_1[idx] = 0;
		gpioGetMode_ret_val[idx] = 0;
	}
}

/*-----------------------------*/
/*----                     ----*/
/*---- Start gpioRead stub ----*/
/*----                     ----*/
/*-----------------------------*/
int gpioRead_called_count;
uint gpioRead_arg_1[GPIO_STUB_BUF_SIZE];
int gpioRead_ret_val[GPIO_STUB_BUF_SIZE];
int gpioRead(
	uint gpio)
{
	int ret_val =
		gpioRead_ret_val
		[gpioRead_called_count];

	gpioRead_arg_1
		[gpioRead_called_count] =
			gpio;

	gpioRead_called_count++;

	return (ret_val);
}
void gpioRead_init()
{
	int idx = 0;

	gpioRead_called_count = 0;
	for (idx = 0; idx < GPIO_STUB_BUF_SIZE; idx++) {
		gpioRead_arg_1[idx] = 0;
		gpioRead_ret_val[idx] = 0;
	}
}

/*------------------------------*/
/*----                      ----*/
/*---- Start gpioWrite stub ----*/
/*----                      ----*/
/*------------------------------*/
int gpioWrite_called_count;
uint gpioWrite_arg_1[GPIO_STUB_BUF_SIZE];
uint gpioWrite_arg_2[GPIO_STUB_BUF_SIZE];
int gpioWrite_ret_val[GPIO_STUB_BUF_SIZE];
int gpioWrite(
	uint gpio,
	uint level)
{
	int ret_val =
		gpioWrite_ret_val
		[gpioWrite_called_count];

	gpioWrite_arg_1
		[gpioWrite_called_count] =
			gpio;
	gpioWrite_arg_2
		[gpioWrite_called_count] =
			level;

	gpioWrite_called_count++;

	return (ret_val);
}
void gpioWrite_init()
{
	int idx = 0;

	gpioWrite_called_count = 0;
	for (idx = 0; idx < GPIO_STUB_BUF_SIZE; idx++) {
		gpioWrite_arg_1[idx] = 0;
		gpioWrite_arg_2[idx] = 0;
		gpioWrite_ret_val[idx] = 0;
	}
}

/*----------------------------*/
/*----                    ----*/
/*---- Start spiOpen stub ----*/
/*----                    ----*/
/*----------------------------*/
int spiOpen_called_count;
uint spiOpen_arg_1[GPIO_STUB_BUF_SIZE];
uint spiOpen_arg_2[GPIO_STUB_BUF_SIZE];
uint spiOpen_arg_3[GPIO_STUB_BUF_SIZE];
int spiOpen_ret_val[GPIO_STUB_BUF_SIZE];
int spiOpen(
	uint spiChan,
	uint baud,
	uint spiFlags)
{
	int ret_val =
		spiOpen_ret_val
		[spiOpen_called_count];

	spiOpen_arg_1
		[spiOpen_called_count] =
			spiChan;
	spiOpen_arg_2
		[spiOpen_called_count] =
			baud;
	spiOpen_arg_3
		[spiOpen_called_count] =
			spiFlags;

	spiOpen_called_count++;

	return (ret_val);
}
void spiOpen_init()
{
	int idx = 0;

	spiOpen_called_count = 0;
	for (idx = 0; idx < GPIO_STUB_BUF_SIZE; idx++) {
		spiOpen_arg_1[idx] = 0;
		spiOpen_arg_2[idx] = 0;
		spiOpen_arg_3[idx] = 0;
		spiOpen_ret_val[idx] = 0;
	}
}

/*-----------------------------*/
/*----                     ----*/
/*---- Start spiClose stub ----*/
/*----                     ----*/
/*-----------------------------*/
int spiClose_called_count;
uint spiClose_arg_1[GPIO_STUB_BUF_SIZE];
int spiClose_ret_val[GPIO_STUB_BUF_SIZE];
int spiClose(
	uint handle)
{
	int ret_val =
		spiClose_ret_val
		[spiClose_called_count];

	spiClose_arg_1
		[spiClose_called_count] =
			handle;

	spiClose_called_count++;

	return (ret_val);
}
void spiClose_init()
{
	int idx = 0;

	spiClose_called_count = 0;
	for (idx = 0; idx < GPIO_STUB_BUF_SIZE; idx++) {
		spiClose_arg_1[idx] = 0;
		spiClose_ret_val[idx] = 0;
	}
}

/*----------------------------*/
/*----                    ----*/
/*---- Start spiRead stub ----*/
/*----                    ----*/
/*----------------------------*/
int spiRead_called_count;
uint spiRead_arg_1[GPIO_STUB_BUF_SIZE];
char* spiRead_arg_2[GPIO_STUB_BUF_SIZE];
uint spiRead_arg_3[GPIO_STUB_BUF_SIZE];
int spiRead_ret_val[GPIO_STUB_BUF_SIZE];
int spiRead(
	uint handle,
	char *buf,
	uint count)
{
	int ret_val =
		spiRead_ret_val
		[spiRead_called_count];

	spiRead_arg_1
		[spiRead_called_count] =
			handle;
	spiRead_arg_2
		[spiRead_called_count] =
			buf;
	spiRead_arg_3
		[spiRead_called_count] =
			count;

	spiRead_called_count++;

	return (ret_val);
}
void spiRead_init()
{
	int idx = 0;

	spiRead_called_count = 0;
	for (idx = 0; idx < GPIO_STUB_BUF_SIZE; idx++) {
		spiRead_arg_1[idx] = 0;
		spiRead_arg_2[idx] = NULL;
		spiRead_arg_3[idx] = 0;
		spiRead_ret_val[idx] = 0;
	}
}

/*-----------------------------*/
/*----                     ----*/
/*---- Start spiWrite stub ----*/
/*----                     ----*/
/*-----------------------------*/
int spiWrite_called_count;
uint spiWrite_arg_1[GPIO_STUB_BUF_SIZE];
char* spiWrite_arg_2[GPIO_STUB_BUF_SIZE];
uint spiWrite_arg_3[GPIO_STUB_BUF_SIZE];
int spiWrite_ret_val[GPIO_STUB_BUF_SIZE];
int spiWrite(
	uint handle,
	char *buf,
	uint count)
{
	int ret_val =
		spiWrite_ret_val
		[spiWrite_called_count];

	spiWrite_arg_1
		[spiWrite_called_count] =
			handle;
	spiWrite_arg_2
		[spiWrite_called_count] =
			buf;
	spiWrite_arg_3
		[spiWrite_called_count] =
			count;

	spiWrite_called_count++;

	return (ret_val);
}
void spiWrite_init()
{
	int idx = 0;

	spiWrite_called_count = 0;
	for (idx = 0; idx < GPIO_STUB_BUF_SIZE; idx++) {
		spiWrite_arg_1[idx] = 0;
		spiWrite_arg_2[idx] = NULL;
		spiWrite_arg_3[idx] = 0;
		spiWrite_ret_val[idx] = 0;
	}
}

/*-----------------------------------*/
/*----                           ----*/
/*---- Start gpioSetISRFunc stub ----*/
/*----                           ----*/
/*-----------------------------------*/
int gpioSetISRFunc_called_count;
uint gpioSetISRFunc_arg_1[GPIO_STUB_BUF_SIZE];
uint gpioSetISRFunc_arg_2[GPIO_STUB_BUF_SIZE];
int gpioSetISRFunc_arg_3[GPIO_STUB_BUF_SIZE];
gpioISRFunc_t gpioSetISRFunc_arg_4[GPIO_STUB_BUF_SIZE];
int gpioSetISRFunc_ret_val[GPIO_STUB_BUF_SIZE];
int gpioSetISRFunc(
	uint gpio,
	uint edge,
	int timeout,
	gpioISRFunc_t f)
{
	int ret_val =
		gpioSetISRFunc_ret_val
		[gpioSetISRFunc_called_count];

	gpioSetISRFunc_arg_1
		[gpioSetISRFunc_called_count] =
			gpio;
	gpioSetISRFunc_arg_2
		[gpioSetISRFunc_called_count] =
			edge;
	gpioSetISRFunc_arg_3
		[gpioSetISRFunc_called_count] =
			timeout;
	gpioSetISRFunc_arg_4
		[gpioSetISRFunc_called_count] =
			f;

	gpioSetISRFunc_called_count++;

	return (ret_val);
}
void gpioSetISRFunc_init()
{
	int idx = 0;

	gpioSetISRFunc_called_count = 0;
	for (idx = 0; idx < GPIO_STUB_BUF_SIZE; idx++) {
		gpioSetISRFunc_arg_1[idx] = 0;
		gpioSetISRFunc_arg_2[idx] = 0;
		gpioSetISRFunc_arg_3[idx] = 0;
		gpioSetISRFunc_arg_4[idx] = 0;
		gpioSetISRFunc_ret_val[idx] = 0;
	}
}
