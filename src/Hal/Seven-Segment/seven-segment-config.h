 /******************************************************************************
 *
 * Module: SEVEN SEGMENT DECODER
 *
 * File Name: seven-segment-config.h
 *
 * Description: Config file for the SEVEN SEGMENT DECODER driver
 *
 * Author: Kirollos Ashraf
 *
 *******************************************************************************/

#ifndef __SEVEN_SEGMENT_CONFIG_H__
#define __SEVEN_SEGMENT_CONFIG_H__

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

/* number of 7 segments connected to the decoder,
 * and the number of enable pins connected to the mcu
 */
#define SEGMENTS_USED_COUNT								4

/* put it equal to TRUE if the data pins are connected
 * in order in the same port, otherwise put it equal to FALSE
 */
#define SEGMENTS_USE_SINGLE_PORT						TRUE

#if SEGMENTS_USE_SINGLE_PORT == TRUE

/* the port of the data pins
 * used only if SEGMENTS_USE_SINGLE_PORT = TRUE
 */
#define SEGMENTS_DATA_PORT								PORTC

/* the start pin - the pin connected to Data-0 of the decoder
 * used only if SEGMENTS_USE_SINGLE_PORT = TRUE
 */
#define SEGMENTS_DATA_START_PIN							PC0

#else

/* seven segment decoder data pins */
#define SEVENT_SEGMENT_D0								PC0
#define SEVENT_SEGMENT_D1								PC1
#define SEVENT_SEGMENT_D2								PC2
#define SEVENT_SEGMENT_D3								PC3

#endif /* SEGMENTS_USE_SINGLE_PORT == TRUE */

#endif /* __SEVEN_SEGMENT_CONFIG_H__ */
