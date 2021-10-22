/******************************************************************************
 *
 * Module: Watch Dog Timer
 *
 * File Name: watchdog.c
 *
 * Description: Source file for the AVR Watch Dog Timer driver
 *
 * Author: Kirollos Ashraf
 *
 *******************************************************************************/

/*******************************************************************************
 *                                Includes	                                   *
 *******************************************************************************/

/* module header file */
#include "watchdog.h"

/* For using mcu registers */
#include "../Mcu/mcu.h"

/*******************************************************************************
 *                          Functions Definition	                           *
 *******************************************************************************/

/*
 * [Function Name]: WATCHDOG_on
 * [Function Description]: enable the watchdog timer for the specified timeout
 * [Args]:
 * [in]: WATCHDOG_timeout timeOut
 * 		 timeout to reset the device after if the watchdog timer wasn't disabled
 * [Return]: void
 */
void WATCHDOG_on(WATCHDOG_timeout a_timeOut)
{
	if(a_timeOut >= WATCHDOG_MAX_TIMEOUTS)
		return;
	WDTCR_R |= SELECT_BIT(WDE) | a_timeOut;
}

/*
 * [Function Name]: WATCHDOG_off
 * [Function Description]: disable the watchdog timer
 * [Return]: void
 */
void WATCHDOG_off(void)
{
	WDTCR_R |= SELECT_BIT(WDTOE) | SELECT_BIT(WDE);
	WDTCR_R = 0;
}

