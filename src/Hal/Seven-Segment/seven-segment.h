 /******************************************************************************
 *
 * Module: SEVEN SEGMENT DECODER
 *
 * File Name: seven-segment.h
 *
 * Description: Header file for the SEVEN SEGMENT DECODER driver
 *
 * Author: Kirollos Ashraf
 *
 *******************************************************************************/

#ifndef __SEVEN_SEGMENT_H__
#define __SEVEN_SEGMENT_H__

/*******************************************************************************
 *                                Includes	                                   *
 *******************************************************************************/

/* module config file */
#include "seven-segment-config.h"

/* For using std types */
#include "../../Lib/types.h"

/* For using common defines and macros */
#include "../../Lib/common.h"

/*******************************************************************************
 *                           Function Prototypes                               *
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
void SEVEN_SEGMENT_init(uint8_t * a_enablePins);

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
void SEVEN_SEGMENT_write(uint8_t a_enablePinIndex, uint8_t a_data);

/*
 * [Function Name]: SEVEN_SEGMENT_clearAll
 * [Function Description]: disable all seven segments enables
 * [Args]:
 * [in]: void
 * [Return]: void
 */
void SEVEN_SEGMENT_clearAll(void);

#endif /* __SEVEN_SEGMENT_H__ */
