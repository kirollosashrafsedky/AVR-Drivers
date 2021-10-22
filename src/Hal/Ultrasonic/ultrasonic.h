/******************************************************************************
 *
 * Module: ULTRASONIC
 *
 * File Name: ultrasonic.h
 *
 * Description: Header file for the ULTRASONIC driver
 *
 * Author: Kirollos Ashraf
 *
 *******************************************************************************/

#ifndef __ULTRASONIC_H__
#define __ULTRASONIC_H__

/*******************************************************************************
 *                                Includes	                                   *
 *******************************************************************************/

/* module config file */
#include "ultrasonic-config.h"

/* for using std types */
#include "../../Lib/types.h"

/* For using common defines and macros */
#include "../../Lib/common.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

/* used precaler for the ultrasonic */
#define ULTRASONIC_ICU_PRESCALER					8

/* the speed of sound divided by 2 */
#define ULTRASONIC_SOUND_SPEED_CM_DIV_2				17150

/*******************************************************************************
 *                           Function Prototypes                               *
 *******************************************************************************/

/*
 * [Function Name]: ULTRASONIC_init
 * [Function Description]: initializes the ultrasonic sensor
 * 						   1. Initialize the ICU driver.
 * 						   2. Setup the ICU call back function
 * 						   3. Setup the direction for the trigger pin.
 * [Args]:
 * [in]: void
 * [Return]: void
 */
void ULTRASONIC_init(void);

/*
 * [Function Name]: ULTRASONIC_readDistance
 * [Function Description]: 1. Send the trigger pulse
 * 						   2. Start the measurements by the ICU
 * [Args]:
 * [in]: void
 * [Return]: void
 */
uint16_t ULTRASONIC_readDistance(void);

/*
 * [Function Name]: ULTRASONIC_edgeProcessing
 * [Function Description]: 1. callback for the icu driver.
 * 						   2. calculates the high time for the echo signal
 * [Args]:
 * [in]: void
 * [Return]: void
 */
void ULTRASONIC_edgeProcessing(void);

#endif /* __ULTRASONIC_H__ */
