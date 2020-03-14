#ifndef GPIO_STUB_H_
#define GPIO_STUB_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*-----------------------------------*/
/*----                           ----*/
/*---- Start gpioInitialise stub ----*/
/*----                           ----*/
/*-----------------------------------*/
extern void gpioInitialise_init();
extern int gpioInitialise();
extern int gpioInitialise_called_count;
extern int gpioInitialise_ret_val[];
#define	GET_GPIOINITIALISE_CALLED_COUNT()	\
	(gpioInitialise_called_count)
#define	SET_GPIOINITIALISE_CALLED_COUNT(value)	\
	(gpioInitialise_called_count = value)
#define	GET_GPIOINITIALISE_RET_VAL(idx)	\
	(gpioInitialise_ret_val[idx])
#define	SET_GPIOINITIALISE_RET_VAL(idx, value)	\
	(gpioInitialise_ret_val[idx] = value)

/*----------------------------------*/
/*----                          ----*/
/*---- Start gpioTerminate stub ----*/
/*----                          ----*/
/*----------------------------------*/
extern void gpioTerminate_init();
extern void gpioTerminate();
extern int gpioTerminate_called_count;
extern int gpioTerminate_ret_val[];
#define	GET_GPIOTERMINATE_CALLED_COUNT()	\
	(gpioTerminate_called_count)
#define	SET_GPIOTERMINATE_CALLED_COUNT(value)	\
	(gpioTerminate_called_count = value)
#define	GET_GPIOTERMINATE_RET_VAL(idx)	\
	(gpioTerminate_ret_val[idx])
#define	SET_GPIOTERMINATE_RET_VAL(idx, value)	\
	(gpioTerminate_ret_val[idx] = value)

/*--------------------------------*/
/*----                        ----*/
/*---- Start gpioSetMode stub ----*/
/*----                        ----*/
/*--------------------------------*/
extern void gpioSetMode_init();
extern int gpioSetMode(
	uint Arg1, 
	uint Arg2);
extern int gpioSetMode_called_count;
extern int gpioSetMode_ret_val[];
extern uint gpioSetMode_arg_1[];
extern uint gpioSetMode_arg_2[];
#define	GET_GPIOSETMODE_CALLED_COUNT()	\
	(gpioSetMode_called_count)
#define	SET_GPIOSETMODE_CALLED_COUNT(value)	\
	(gpioSetMode_called_count = value)
#define	GET_GPIOSETMODE_ARG_1(idx)	\
	(gpioSetMode_arg_1[idx])
#define	SET_GPIOSETMODE_ARG_1(idx, value)	\
	(gpioSetMode_arg_1[idx] = value)
#define	GET_GPIOSETMODE_ARG_2(idx)	\
	(gpioSetMode_arg_2[idx])
#define	SET_GPIOSETMODE_ARG_2(idx, value)	\
	(gpioSetMode_arg_2[idx] = value)
#define	GET_GPIOSETMODE_RET_VAL(idx)	\
	(gpioSetMode_ret_val[idx])
#define	SET_GPIOSETMODE_RET_VAL(idx, value)	\
	(gpioSetMode_ret_val[idx] = value)

/*--------------------------------*/
/*----                        ----*/
/*---- Start gpioGetMode stub ----*/
/*----                        ----*/
/*--------------------------------*/
extern void gpioGetMode_init();
extern int gpioGetMode(
	uint Arg1);
extern int gpioGetMode_called_count;
extern int gpioGetMode_ret_val[];
extern uint gpioGetMode_arg_1[];
#define	GET_GPIOGETMODE_CALLED_COUNT()	\
	(gpioGetMode_called_count)
#define	SET_GPIOGETMODE_CALLED_COUNT(value)	\
	(gpioGetMode_called_count = value)
#define	GET_GPIOGETMODE_ARG_1(idx)	\
	(gpioGetMode_arg_1[idx])
#define	SET_GPIOGETMODE_ARG_1(idx, value)	\
	(gpioGetMode_arg_1[idx] = value)
#define	GET_GPIOGETMODE_RET_VAL(idx)	\
	(gpioGetMode_ret_val[idx])
#define	SET_GPIOGETMODE_RET_VAL(idx, value)	\
	(gpioGetMode_ret_val[idx] = value)

/*-----------------------------*/
/*----                     ----*/
/*---- Start gpioRead stub ----*/
/*----                     ----*/
/*-----------------------------*/
extern void gpioRead_init();
extern int gpioRead(
	uint Arg1);
extern int gpioRead_called_count;
extern int gpioRead_ret_val[];
extern uint gpioRead_arg_1[];
#define	GET_GPIOREAD_CALLED_COUNT()	\
	(gpioRead_called_count)
#define	SET_GPIOREAD_CALLED_COUNT(value)	\
	(gpioRead_called_count = value)
#define	GET_GPIOREAD_ARG_1(idx)	\
	(gpioRead_arg_1[idx])
#define	SET_GPIOREAD_ARG_1(idx, value)	\
	(gpioRead_arg_1[idx] = value)
#define	GET_GPIOREAD_RET_VAL(idx)	\
	(gpioRead_ret_val[idx])
#define	SET_GPIOREAD_RET_VAL(idx, value)	\
	(gpioRead_ret_val[idx] = value)

/*------------------------------*/
/*----                      ----*/
/*---- Start gpioWrite stub ----*/
/*----                      ----*/
/*------------------------------*/
extern void gpioWrite_init();
extern int gpioWrite(
	uint Arg1, 
	uint Arg2);
extern int gpioWrite_called_count;
extern int gpioWrite_ret_val[];
extern uint gpioWrite_arg_1[];
extern uint gpioWrite_arg_2[];
#define	GET_GPIOWRITE_CALLED_COUNT()	\
	(gpioWrite_called_count)
#define	SET_GPIOWRITE_CALLED_COUNT(value)	\
	(gpioWrite_called_count = value)
#define	GET_GPIOWRITE_ARG_1(idx)	\
	(gpioWrite_arg_1[idx])
#define	SET_GPIOWRITE_ARG_1(idx, value)	\
	(gpioWrite_arg_1[idx] = value)
#define	GET_GPIOWRITE_ARG_2(idx)	\
	(gpioWrite_arg_2[idx])
#define	SET_GPIOWRITE_ARG_2(idx, value)	\
	(gpioWrite_arg_2[idx] = value)
#define	GET_GPIOWRITE_RET_VAL(idx)	\
	(gpioWrite_ret_val[idx])
#define	SET_GPIOWRITE_RET_VAL(idx, value)	\
	(gpioWrite_ret_val[idx] = value)

/*----------------------------*/
/*----                    ----*/
/*---- Start spiOpen stub ----*/
/*----                    ----*/
/*----------------------------*/
extern void spiOpen_init();
extern int spiOpen(
	uint Arg1, 
	uint Arg2, 
	uint Arg3);
extern int spiOpen_called_count;
extern int spiOpen_ret_val[];
extern uint spiOpen_arg_1[];
extern uint spiOpen_arg_2[];
extern uint spiOpen_arg_3[];
#define	GET_SPIOPEN_CALLED_COUNT()	\
	(spiOpen_called_count)
#define	SET_SPIOPEN_CALLED_COUNT(value)	\
	(spiOpen_called_count = value)
#define	GET_SPIOPEN_ARG_1(idx)	\
	(spiOpen_arg_1[idx])
#define	SET_SPIOPEN_ARG_1(idx, value)	\
	(spiOpen_arg_1[idx] = value)
#define	GET_SPIOPEN_ARG_2(idx)	\
	(spiOpen_arg_2[idx])
#define	SET_SPIOPEN_ARG_2(idx, value)	\
	(spiOpen_arg_2[idx] = value)
#define	GET_SPIOPEN_ARG_3(idx)	\
	(spiOpen_arg_3[idx])
#define	SET_SPIOPEN_ARG_3(idx, value)	\
	(spiOpen_arg_3[idx] = value)
#define	GET_SPIOPEN_RET_VAL(idx)	\
	(spiOpen_ret_val[idx])
#define	SET_SPIOPEN_RET_VAL(idx, value)	\
	(spiOpen_ret_val[idx] = value)

/*-----------------------------*/
/*----                     ----*/
/*---- Start spiClose stub ----*/
/*----                     ----*/
/*-----------------------------*/
extern void spiClose_init();
extern int spiClose(
	uint Arg1);
extern int spiClose_called_count;
extern int spiClose_ret_val[];
extern uint spiClose_arg_1[];
#define	GET_SPICLOSE_CALLED_COUNT()	\
	(spiClose_called_count)
#define	SET_SPICLOSE_CALLED_COUNT(value)	\
	(spiClose_called_count = value)
#define	GET_SPICLOSE_ARG_1(idx)	\
	(spiClose_arg_1[idx])
#define	SET_SPICLOSE_ARG_1(idx, value)	\
	(spiClose_arg_1[idx] = value)
#define	GET_SPICLOSE_RET_VAL(idx)	\
	(spiClose_ret_val[idx])
#define	SET_SPICLOSE_RET_VAL(idx, value)	\
	(spiClose_ret_val[idx] = value)

/*----------------------------*/
/*----                    ----*/
/*---- Start spiRead stub ----*/
/*----                    ----*/
/*----------------------------*/
extern void spiRead_init();
extern int spiRead(
	uint Arg1, 
	char* Arg2, 
	uint Arg3);
extern int spiRead_called_count;
extern int spiRead_ret_val[];
extern uint spiRead_arg_1[];
extern char* spiRead_arg_2[];
extern uint spiRead_arg_3[];
#define	GET_SPIREAD_CALLED_COUNT()	\
	(spiRead_called_count)
#define	SET_SPIREAD_CALLED_COUNT(value)	\
	(spiRead_called_count = value)
#define	GET_SPIREAD_ARG_1(idx)	\
	(spiRead_arg_1[idx])
#define	SET_SPIREAD_ARG_1(idx, value)	\
	(spiRead_arg_1[idx] = value)
#define	GET_SPIREAD_ARG_2(idx)	\
	(spiRead_arg_2[idx])
#define	SET_SPIREAD_ARG_2(idx, value)	\
	(spiRead_arg_2[idx] = value)
#define	GET_SPIREAD_ARG_3(idx)	\
	(spiRead_arg_3[idx])
#define	SET_SPIREAD_ARG_3(idx, value)	\
	(spiRead_arg_3[idx] = value)
#define	GET_SPIREAD_RET_VAL(idx)	\
	(spiRead_ret_val[idx])
#define	SET_SPIREAD_RET_VAL(idx, value)	\
	(spiRead_ret_val[idx] = value)

/*-----------------------------*/
/*----                     ----*/
/*---- Start spiWrite stub ----*/
/*----                     ----*/
/*-----------------------------*/
extern void spiWrite_init();
extern int spiWrite(
	uint Arg1, 
	char* Arg2, 
	uint Arg3);
extern int spiWrite_called_count;
extern int spiWrite_ret_val[];
extern uint spiWrite_arg_1[];
extern char* spiWrite_arg_2[];
extern uint spiWrite_arg_3[];
#define	GET_SPIWRITE_CALLED_COUNT()	\
	(spiWrite_called_count)
#define	SET_SPIWRITE_CALLED_COUNT(value)	\
	(spiWrite_called_count = value)
#define	GET_SPIWRITE_ARG_1(idx)	\
	(spiWrite_arg_1[idx])
#define	SET_SPIWRITE_ARG_1(idx, value)	\
	(spiWrite_arg_1[idx] = value)
#define	GET_SPIWRITE_ARG_2(idx)	\
	(spiWrite_arg_2[idx])
#define	SET_SPIWRITE_ARG_2(idx, value)	\
	(spiWrite_arg_2[idx] = value)
#define	GET_SPIWRITE_ARG_3(idx)	\
	(spiWrite_arg_3[idx])
#define	SET_SPIWRITE_ARG_3(idx, value)	\
	(spiWrite_arg_3[idx] = value)
#define	GET_SPIWRITE_RET_VAL(idx)	\
	(spiWrite_ret_val[idx])
#define	SET_SPIWRITE_RET_VAL(idx, value)	\
	(spiWrite_ret_val[idx] = value)

/*-----------------------------------*/
/*----                           ----*/
/*---- Start gpioSetISRFunc stub ----*/
/*----                           ----*/
/*-----------------------------------*/
extern void gpioSetISRFunc_init();
extern int gpioSetISRFunc(
	uint Arg1, 
	uint Arg2, 
	int Arg3, 
	gpioISRFunc_t Arg4);
extern int gpioSetISRFunc_called_count;
extern int gpioSetISRFunc_ret_val[];
extern uint gpioSetISRFunc_arg_1[];
extern uint gpioSetISRFunc_arg_2[];
extern int gpioSetISRFunc_arg_3[];
extern gpioISRFunc_t gpioSetISRFunc_arg_4[];
#define	GET_GPIOSETISRFUNC_CALLED_COUNT()	\
	(gpioSetISRFunc_called_count)
#define	SET_GPIOSETISRFUNC_CALLED_COUNT(value)	\
	(gpioSetISRFunc_called_count = value)
#define	GET_GPIOSETISRFUNC_ARG_1(idx)	\
	(gpioSetISRFunc_arg_1[idx])
#define	SET_GPIOSETISRFUNC_ARG_1(idx, value)	\
	(gpioSetISRFunc_arg_1[idx] = value)
#define	GET_GPIOSETISRFUNC_ARG_2(idx)	\
	(gpioSetISRFunc_arg_2[idx])
#define	SET_GPIOSETISRFUNC_ARG_2(idx, value)	\
	(gpioSetISRFunc_arg_2[idx] = value)
#define	GET_GPIOSETISRFUNC_ARG_3(idx)	\
	(gpioSetISRFunc_arg_3[idx])
#define	SET_GPIOSETISRFUNC_ARG_3(idx, value)	\
	(gpioSetISRFunc_arg_3[idx] = value)
#define	GET_GPIOSETISRFUNC_ARG_4(idx)	\
	(gpioSetISRFunc_arg_4[idx])
#define	SET_GPIOSETISRFUNC_ARG_4(idx, value)	\
	(gpioSetISRFunc_arg_4[idx] = value)
#define	GET_GPIOSETISRFUNC_RET_VAL(idx)	\
	(gpioSetISRFunc_ret_val[idx])
#define	SET_GPIOSETISRFUNC_RET_VAL(idx, value)	\
	(gpioSetISRFunc_ret_val[idx] = value)

/*-----------------------------*/
/*----                     ----*/
/*---- Start gpioTick stub ----*/
/*----                     ----*/
/*-----------------------------*/
extern void gpioTick_init();
extern uint32_t gpioTick();
extern int gpioTick_called_count;
extern int gpioTick_ret_val[];
#define	GET_GPIOTICK_CALLED_COUNT()	\
	(gpioTick_called_count)
#define	SET_GPIOTICK_CALLED_COUNT(value)	\
	(gpioTick_called_count = value)
#define	GET_GPIOTICK_RET_VAL(idx)	\
	(gpioTick_ret_val[idx])
#define	SET_GPIOTICK_RET_VAL(idx, value)	\
	(gpioTick_ret_val[idx] = value)

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* GPIO_STUB_H_ */
