 /******************************************************************************
 *
 * Module: Watch Dog Timer
 *
 * File Name: watchdog.h
 *
 * Description: Header file for the AVR Watch Dog Timer driver
 *
 * Author: Kirollos Ashraf
 *
 *******************************************************************************/

#ifndef __WATCHDOG_H__
#define __WATCHDOG_H__

/*******************************************************************************
 *                                Includes	                                   *
 *******************************************************************************/

/* For using std types */
#include "../../Lib/types.h"

/* For using common defines and macros */
#include "../../Lib/common.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define WATCHDOG_MAX_TIMEOUTS	8

/*******************************************************************************
 *                             Types Declaration                               *
 *******************************************************************************/

/*
 * [Enum Name]: WATCHDOG_timeout
 * [Enum Description]: contain timeouts for watchdog timer
 */

typedef enum
{
	/* Time-out at Vcc = 3v => 17.1ms, at Vcc = 5v => 16.3ms */
	WATCHDOG_TIMEOUT_16ms = 0,
	/* Time-out at Vcc = 3v => 34.3ms, at Vcc = 5v => 32.5ms */
	WATCHDOG_TIMEOUT_32ms,
	/* Time-out at Vcc = 3v => 68.5ms, at Vcc = 5v => 65ms */
	WATCHDOG_TIMEOUT_65ms,
	/* Time-out at Vcc = 3v => 0.14s, at Vcc = 5v => 0.13s */
	WATCHDOG_TIMEOUT_130ms,
	/* Time-out at Vcc = 3v => 0.27s, at Vcc = 5v => 0.26s */
	WATCHDOG_TIMEOUT_260ms,
	/* Time-out at Vcc = 3v => 0.55s, at Vcc = 5v => 0.52s */
	WATCHDOG_TIMEOUT_520ms,
	/* Time-out at Vcc = 3v => 1.1s, at Vcc = 5v => 1.0s */
	WATCHDOG_TIMEOUT_1s,
	/* Time-out at Vcc = 3v => 2.2s, at Vcc = 5v => 21s */
	WATCHDOG_TIMEOUT_2s,
}WATCHDOG_timeout;

/*******************************************************************************
 *                           Function Prototypes                               *
 *******************************************************************************/

/*
 * [Function Name]: WATCHDOG_on
 * [Function Description]: enable the watchdog timer for the specified timeout
 * [Args]:
 * [in]: WATCHDOG_timeout timeOut
 * 		 timeout to reset the device after if the watchdog timer wasn't disabled
 * [Return]: void
 */
void WATCHDOG_on(WATCHDOG_timeout a_timeOut);

/*
 * [Function Name]: WATCHDOG_off
 * [Function Description]: disable the watchdog timer
 * [Return]: void
 */
void WATCHDOG_off(void);

#endif /* __WATCHDOG_H__ */
