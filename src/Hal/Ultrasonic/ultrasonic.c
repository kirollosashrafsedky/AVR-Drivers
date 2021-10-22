/******************************************************************************
 *
 * Module: LCD
 *
 * File Name: lcd.c
 *
 * Description: Source file for the LCD driver
 *
 * Author: Kirollos Ashraf
 *
 *******************************************************************************/

/*******************************************************************************
 *                                Includes	                                   *
 *******************************************************************************/

/* module header file */
#include "ultrasonic.h"

/* for using DIO functions */
#include "../../Mcal/Dio/dio.h"

/* For using delay function */
#include "../../Mcal/Timer/timer.h"

/* For using ICU function */
#include "../../Mcal/Icu/icu.h"

/*******************************************************************************
 *                     		   Global Variables	                       	       *
 *******************************************************************************/

/* global variable carrying the number of edges
 * if 0 => the next edge is the rising one
 * if 1 => the next edge is the falling edge
 * if 2 => indication that there's new pulseWidth value to read (new data flag)
 */
static volatile uint8_t g_edgeNumber = 0;

/* global variable carrying the icu value, the pulse width */
static volatile uint16_t g_pulseWidth = 0;

/*******************************************************************************
 *                      Static Functions Prototypes	                           *
 *******************************************************************************/

/*
 * [Function Name]: ULTRASONIC_trigger
 * [Function Description]: Send the Trigger pulse to the ultrasonic.
 * [Args]:
 * [in]: void
 * [Return]: void
 */
static void ULTRASONIC_trigger(void);

/*******************************************************************************
 *                          Functions Definition	                           *
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
void ULTRASONIC_init(void)
{

	/* configure the icu module
	 * 1. clock = F_CPU / 8
	 * 2. edge = Rising edge
	 */
	ST_IcuConfig icuConfig = {
			ICU_PRESCALER_8, ICU_RISING_EDGE
	};
	Icu_init(&icuConfig);

	/* set icu callback function */
	Icu_setCallBack(ULTRASONIC_edgeProcessing);

	/* set the trigger pin as output */
	DIO_pinInit(ULTRASONIC_TRIGGER_PIN, PIN_OUTPUT);
}

/*
 * [Function Name]: ULTRASONIC_readDistance
 * [Function Description]: 1. Send the trigger pulse
 * 						   2. Start the measurements by the ICU
 * [Args]:
 * [in]: void
 * [Return]: void
 */
uint16_t ULTRASONIC_readDistance(void)
{
	uint16_t distance;

	/* trigger the ultrasonic */
	ULTRASONIC_trigger();

	/* wait till pulse is sent and recieved */
	while(g_edgeNumber != 2);

	/* make g_edgeNumber = 0 for next calls of the functions */
	g_edgeNumber = 0;

	/* calculate the distance */
	distance = (uint16_t)(g_pulseWidth / (F_CPU / ((float64_t)ULTRASONIC_SOUND_SPEED_CM_DIV_2 * ULTRASONIC_ICU_PRESCALER)));

	/* subtract the calibration value only in case that the result is not negative */
	if((int32_t)distance - ULTRASONIC_CALIBRATION_VALUE > 0)
	{
		return distance - ULTRASONIC_CALIBRATION_VALUE;
	}
	return  distance;
}

/*
 * [Function Name]: ULTRASONIC_edgeProcessing
 * [Function Description]: 1. callback for the icu driver.
 * 						   2. calculates the high time for the echo signal
 * [Args]:
 * [in]: void
 * [Return]: void
 */
void ULTRASONIC_edgeProcessing(void)
{
	/* if 0 then the rising edge is captured */
	if(g_edgeNumber == 0)
	{
		/* clear the timer value */
		Icu_clearTimerValue();

		/* wait for nest falling edge */
		Icu_setEdgeDetectionType(ICU_FALLING_EDGE);

		/* increase edge number */
		g_edgeNumber ++;
	}
	else if(g_edgeNumber == 1)
	{
		/* read ICU value */
		g_pulseWidth = Icu_getInputCaptureValue();

		/* wait for next rising edge */
		Icu_setEdgeDetectionType(ICU_RISING_EDGE);

		/* make edge count = 2 to indicate data is available */
		g_edgeNumber = 2;
	}
}

/*
 * [Function Name]: ULTRASONIC_trigger
 * [Function Description]: Send the Trigger pulse to the ultrasonic.
 * [Args]:
 * [in]: void
 * [Return]: void
 */
static void ULTRASONIC_trigger(void)
{
	/* send high pulse for 10us or more */
	DIO_writePin(ULTRASONIC_TRIGGER_PIN, HIGH);
	TIMER_DELAY_MS(1);
	DIO_writePin(ULTRASONIC_TRIGGER_PIN, LOW);
}
