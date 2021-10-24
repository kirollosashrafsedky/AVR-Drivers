/******************************************************************************
 *
 * Module: SPI
 *
 * File Name: spi-config.h
 *
 * Description: Config file for the AVR SPI driver
 *
 * Author: Kirollos Ashraf
 *
 *******************************************************************************/

#ifndef __SPI_CONFIG_H__
#define __SPI_CONFIG_H__

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

/* used as default data when sending,
 * just to receive new data
 */
#define SPI_DEFAULT_DATA_VALUE 			0xFF

/* used in SPI_RECEIVE_STRING_TILL function to receive string
 * till this character is found before reaching the maximum size of the array
 */
#define SPI_RECEIVE_STRING_TILL			'\r'

/* Define F_CPU if not defined to calculate spi clock correctly */
#ifndef F_CPU
#define F_CPU 							1000000UL
#endif /* F_CPU */


#endif /* __SPI_CONFIG_H__ */
