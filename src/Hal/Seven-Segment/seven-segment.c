/******************************************************************************
 *
 * Module: SEVEN SEGMENT DECODER
 *
 * File Name: seven-segment.c
 *
 * Description: Source file for the SEVEN SEGMENT DECODER driver
 *
 * Author: Kirollos Ashraf
 *
 *******************************************************************************/

/*******************************************************************************
 *                                Includes	                                   *
 *******************************************************************************/

/* module header file */
#include "seven-segment.h"

/* For using dio functions for pins */
#include "../../Mcal/Dio/dio.h"

/*******************************************************************************
 *                      	   Global Variables		                           *
 *******************************************************************************/

/* array to save all enables pins */
static uint8_t g_sevenSegmentEnables[SEGMENTS_USED_COUNT];

/*******************************************************************************
 *                          Functions Definition	                           *
 *******************************************************************************/

/*
 * [Function Name]: SEVEN_SEGMENT_init
 * [Function Description]: init the seven segment decoder and enable pins
 * [Args]:
 * [in]: uint8_t * a_enablePins
 * 		 array of enable pins connected to the decoder,
 * 		 its size must be equal to SEGMENTS_USED_COUNT
 * [Return]: void
 */
void SEVEN_SEGMENT_init(uint8_t * a_enablePins)
{
	uint8_t loopCounter;

	/* init data pins of the decoder as outputs */
#if SEGMENTS_USE_SINGLE_PORT == TRUE

	DIO_portInitPartial(SEGMENTS_DATA_PORT, PORT_OUTPUT, 0x0F, SEGMENTS_DATA_START_PIN);

#else

	DIO_pinInit(SEVENT_SEGMENT_D0, PIN_OUTPUT);
	DIO_pinInit(SEVENT_SEGMENT_D1, PIN_OUTPUT);
	DIO_pinInit(SEVENT_SEGMENT_D2, PIN_OUTPUT);
	DIO_pinInit(SEVENT_SEGMENT_D3, PIN_OUTPUT);

#endif /* SEGMENTS_USE_SINGLE_PORT == TRUE */

	for(loopCounter = 0; loopCounter < SEGMENTS_USED_COUNT; loopCounter ++)
	{
		/* save passed enable pins to g_sevenSegmentEnables */
		g_sevenSegmentEnables[loopCounter] = a_enablePins[loopCounter];

		/*  init enable pins as output */
		DIO_pinInit(g_sevenSegmentEnables[loopCounter], PIN_OUTPUT);
	}
	SEVEN_SEGMENT_clearAll();
}

/*
 * [Function Name]: SEVEN_SEGMENT_write
 * [Function Description]: write data to a specific seven segment through the decoder
 * [Args]:
 * [in]: uint8_t a_enablePinIndex
 * 		 enable pin index of the seven segment to write to
 * [in]: uint8_t a_data
 * 		 data to write to the decoder
 * [Return]: void
 */
void SEVEN_SEGMENT_write(uint8_t a_enablePinIndex, uint8_t a_data)
{
	/* make sure the index is smaller than the segments count */
	if(a_enablePinIndex < SEGMENTS_USED_COUNT)
	{
		/* clear all enables first */
		SEVEN_SEGMENT_clearAll();

		/* write data to the decoder */
#if SEGMENTS_USE_SINGLE_PORT == TRUE

		DIO_writePortPartial(SEGMENTS_DATA_PORT, a_data, 0x0F, SEGMENTS_DATA_START_PIN);

#else

		DIO_writePin(SEVENT_SEGMENT_D0, GET_BIT(a_data, 0));
		DIO_writePin(SEVENT_SEGMENT_D1, GET_BIT(a_data, 1));
		DIO_writePin(SEVENT_SEGMENT_D2, GET_BIT(a_data, 2));
		DIO_writePin(SEVENT_SEGMENT_D3, GET_BIT(a_data, 3));

#endif /* SEGMENTS_USE_SINGLE_PORT == TRUE */

		/* write high to the selected enable pin */
		DIO_writePin(g_sevenSegmentEnables[a_enablePinIndex], HIGH);
	}
}

/*
 * [Function Name]: SEVEN_SEGMENT_clearAll
 * [Function Description]: disable all seven segments enables
 * [Args]:
 * [in]: void
 * [Return]: void
 */
void SEVEN_SEGMENT_clearAll(void)
{
	uint8_t loopCounter;

	for(loopCounter = 0; loopCounter < SEGMENTS_USED_COUNT; loopCounter ++)
	{
		/* write zeros to all enable pins */
		DIO_writePin(g_sevenSegmentEnables[loopCounter], LOW);
	}
}
