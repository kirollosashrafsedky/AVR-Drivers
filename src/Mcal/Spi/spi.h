/******************************************************************************
 *
 * Module: SPI
 *
 * File Name: spi.h
 *
 * Description: Header file for the AVR SPI driver
 *
 * Author: Kirollos Ashraf
 *
 *******************************************************************************/

#ifndef __SPI_H__
#define __SPI_H__

/*******************************************************************************
 *                                Includes	                                   *
 *******************************************************************************/

/* module config file */
#include "spi-config.h"

/* for using std types */
#include "../../Lib/types.h"

/* For using common defines and macros */
#include "../../Lib/common.h"

/*******************************************************************************
 *                             Types Declaration                               *
 *******************************************************************************/

/*
 * [Enum Name]: EN_SpiDataOrder
 * [Enum Description]: contains spi data order options
 */
typedef enum
{
	SPI_MSB_FIRST,
	SPI_LSB_FIRST
}EN_SpiDataOrder;

/*
 * [Enum Name]: EN_SpiDataMode
 * [Enum Description]: contains spi data modes options
 * 					   determines when the data is sampled relative to the clock
 */
typedef enum
{
	SPI_CLOCK_NOT_INVERTED_LEADING_EDGE,
	SPI_CLOCK_NOT_INVERTED_TRAILING_EDGE,
	SPI_CLOCK_INVERTED_LEADING_EDGE,
	SPI_CLOCK_INVERTED_TRAILING_EDGE
}EN_SpiDataMode;

/*
 * [Enum Name]: EN_SpiClockRate
 * [Enum Description]: contains spi clock rate options
 */
typedef enum
{
	SPI_CLOCK_4,
	SPI_CLOCK_16,
	SPI_CLOCK_64,
	SPI_CLOCK_128,
	SPI_CLOCK_2,
	SPI_CLOCK_8,
	SPI_CLOCK_32,
}EN_SpiClockRate;

/*
 * [Enum Name]: EN_SpiInterrupt
 * [Enum Description]: contains spi interrupt options
 */
typedef enum
{
	SPI_INTERRUPT_DISABLED,
	SPI_INTERRUPT_ENABLED
}EN_SpiInterrupt;

/*
 * [Struct Name]: ST_SpiMasterConfig
 * [Struct Description]: contains spi initialization (as master) config
 */
typedef struct
{

	/* data order MSB first or last */
	EN_SpiDataOrder dataOrder;

	/* data mode, clock sampling options */
	EN_SpiDataMode dataMode;

	/* spi interrupt enabled or disabled */
	EN_SpiInterrupt spiInterrupt;

	/* clock rate options */
	EN_SpiClockRate clockRate;

}ST_SpiMasterConfig;

/*
 * [Struct Name]: ST_SpiSlaveConfig
 * [Struct Description]: contains spi initialization (as slave) config
 */
typedef struct
{

	/* data order MSB first or last */
	EN_SpiDataOrder dataOrder;

	/* data mode, clock sampling options */
	EN_SpiDataMode dataMode;

	/* spi interrupt enabled or disabled */
	EN_SpiInterrupt spiInterrupt;

}ST_SpiSlaveConfig;

/*******************************************************************************
 *                           Function Prototypes                               *
 *******************************************************************************/

/*
 * [Function Name]: SPI_initMaster
 * [Function Description]: initializes the spi as master with the given configuration
 * 						   1. sets the data order
 * 						   2. sets the data mode
 * 						   3. enable/disable spi interrupts
 * 						   4. set clock speed
 * [Args]:
 * [in]: const ST_SpiMasterConfig * a_spiConfig
 * 		 the configuration of the spi master
 * [Return]: void
 */
void SPI_initMaster(const ST_SpiMasterConfig * a_spiConfig);

/*
 * [Function Name]: SPI_initSlave
 * [Function Description]: initializes the spi as slave with the given configuration
 * 						   1. sets the data order
 * 						   2. sets the data mode
 * 						   3. enable/disable spi interrupts
 * [Args]:
 * [in]: const ST_SpiSlaveConfig * a_spiConfig
 * 		 the configuration of the spi slave
 * [Return]: void
 */
void SPI_initSlave(const ST_SpiSlaveConfig * a_spiConfig);

/*
 * [Function Name]: SPI_setInterruptCallback
 * [Function Description]: sets the callback function of the spi interrupt
 * 						   should be used only if the spi interrupt is enabled.
 * 						   Otherwise it's meaningless
 * [Args]:
 * [in]: void (* volatile a_ptrToHandler)(void)
 * 		 pointer to the callback function
 * [Return]: void
 */
void SPI_setInterruptCallback(void (* volatile a_ptrToHandler)(void));

/*
 * [Function Name]: SPI_sendReceiveByteBlocking
 * [Function Description]: This function sends input data through spi
 * 						   and at the same time, it receives data.
 * 						   It uses busy wait till the data is sent/received.
 * 						   It can be used whether SPI interrupt is enabled or not.
 * 						   If SPI interrupt is enabled, it will be disabled temporarely
 * 						   during the function time then re-enabled again
 * 						   It will not generate interrupt even if spi
 * 						   interrupt is enabled
 * [Args]:
 * [in]: const uint8_t a_data
 * 		 data to be sent
 * [Return]: uint8_t
 * 			 received data
 */
uint8_t SPI_sendReceiveByteBlocking(const uint8_t a_data);

/*
 * [Function Name]: SPI_sendByteNonBlocking
 * [Function Description]: This function sends input data through spi
 * 						   without busy wait, Be aware that this function
 * 						   should be called only in callback functions when
 * 						   interrpt is enabled and after reading the value
 * 						   using SPI_receiveByteNonBlocking() function.
 * 						   or it can be used outside callback functions only
 * 						   if it's known that previous data is sent successfully
 * 						   otherwise previous data may be lost before sending
 * [Args]:
 * [in]: const uint8_t a_data
 * 		 data to be sent
 * [Return]: void
 */
void SPI_sendByteNonBlocking(const uint8_t a_data);

/*
 * [Function Name]: SPI_receiveByteNonBlocking
 * [Function Description]: This function receives data through spi
 * 						   without busy wait, Be aware that this function
 * 						   should be called only in callback functions when
 * 						   interrpt is enabled
 * [Args]:
 * [in]: void
 * [Return]: uint8_t
 * 			 received data
 */
uint8_t SPI_receiveByteNonBlocking(void);

/*
 * [Function Name]: SPI_sendString
 * [Function Description]: The function sends the given string till it reaches the null character
 * 						   It uses polling techinque "busy wait"
 * [Args]:
 * [in]: const char * a_str
 * 		 string to be sent
 * [Return]: uint8_t
 */
void SPI_sendString(const char * a_str);

/*
 * [Function Name]: SPI_receiveString
 * [Function Description]: The function receives string using busy wait
 * 						   "polling technique" till
 * 						   1. the SPI_RECEIVE_STRING_TILL is found
 * 						   	  this value can be modified in the config file
 * 						   2. reaching the maximum value a_maxSize
 * [Args]:
 * [in]: uint8_t * a_str
 * 		 array to store recived string
 * [in]: uint8_t a_maxSize
 * 		 maximum size of the passed array to receive till
 * 		 it reached
 * [Return]: void
 */
void SPI_receiveString(uint8_t * a_str, uint8_t a_maxSize);

#endif /* __SPI_H__ */
