/*
 * log.h
 *
 *  Created on: 2020/01/26
 *      Author: CountrySideEngineer
 */

#ifndef LOG_H_
#define LOG_H_
#ifdef __cplusplus
extern "C" {
#endif

#define	LOG_LEVEL_TAG_DEBUG					("[DEBUG]")
#define	LOG_LEVEL_TAG_INFO					("[INFO ]")
#define	LOG_LEVEL_TAG_WARN					("[WARN ]")
#define	LOG_LEVEL_TAG_ERROR					("[ERROR]")
#define	LOG_LEVEL_TAG_FATAL					("[FATAL]")
#define	DLOG(fmt, ...)					\
	do {									\
		printf("%s", LOG_LEVEL_TAG_DEBUG);	\
		printf("[%s] ", __func__);			\
		printf(fmt, ## __VA_ARGS__);		\
		printf("\r\n");						\
	} while (0)

#define	ILOG(fmt, ...)					\
	do {									\
		printf("%s", LOG_LEVEL_TAG_INFO);	\
		printf("[%s] ", __func__);			\
		printf(fmt, ## __VA_ARGS__);		\
		printf("\r\n");						\
	} while (0)

#define	WLOG(fmt, ...)					\
	do {									\
		printf("%s", LOG_LEVEL_TAG_WARN);	\
		printf("[%s] ", __func__);			\
		printf(fmt, ## __VA_ARGS__);		\
		printf("\r\n");						\
	} while (0)

#define	ELOG(fmt, ...)					\
	do {									\
		printf("%s", LOG_LEVEL_TAG_FATAL);	\
		printf("[%s] ", __func__);			\
		printf(fmt, ## __VA_ARGS__);		\
		printf("\r\n");						\
	} while (0)

#define	FLOG(fmt, ...)					\
	do {									\
		printf("%s", LOG_LEVEL_TAG_FATAL);	\
		printf("[%s] ", __func__);			\
		printf(fmt, ## __VA_ARGS__);		\
		printf("\r\n");						\
	} while (0)

#ifdef __cplusplus
}
#endif
#endif /* LOG_H_ */
