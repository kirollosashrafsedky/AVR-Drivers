/******************************************************************************
 *
 * Module: SPI
 *
 * File Name: spi.c
 *
 * Description: Source file for the AVR SPI driver
 *
 * Author: Kirollos Ashraf
 *
 *******************************************************************************/

/*******************************************************************************
 *                                Includes	                                   *
 *******************************************************************************/

/* module header file */
#include "spi.h"

/* For using mcu registers */
#include "../Mcu/mcu.h"

/* For using DIO module */
#include "../Dio/dio.h"

/*******************************************************************************
 *                            Global Variables	                               *
 *******************************************************************************/

/* pointer to spi interrupt handler */
static void (* volatile g_spiPtrToHandler)(void) = NULL;

/*******************************************************************************
 *                          Functions Definition	                           *
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
void SPI_initMaster(const ST_SpiMasterConfig * a_spiConfig)
{
	/******** Configure SPI Master Pins *********
	 * SS(PB4)   	--> 	Output
	 * MOSI(PB5) 	--> 	Output
	 * MISO(PB6) 	--> 	Input
	 * SCK(PB7) 	--> 	Output
	 ********************************************/
	DIO_pinInit(PB4, PIN_OUTPUT);
	DIO_pinInit(PB5, PIN_OUTPUT);
	DIO_pinInit(PB6, PIN_INPUT);
	DIO_pinInit(PB7, PIN_OUTPUT);

	SPCR_R = 0;

	/* insert the value of spi interrupt in SPIE */
	COPY_BITS(SPCR_R, 0x01, a_spiConfig->spiInterrupt, SPIE);

	/* insert the value of data order in DORD */
	COPY_BITS(SPCR_R, 0x01, a_spiConfig->dataOrder, DORD);

	/* insert the value of data mode in CPOL, CPHA */
	COPY_BITS(SPCR_R, 0x03, a_spiConfig->dataMode, CPHA);

	/* insert the first two bits of clock rate in SPR1, SPR0 */
	COPY_BITS(SPCR_R, 0x03, a_spiConfig->clockRate, SPR0);

	/* insert the third bit of clock rate in SPI2X */
	if(BIT_IS_SET(a_spiConfig->clockRate, 2))
	{
		SET_BIT(SPSR_R, SPI2X);
	}
	else
	{
		CLEAR_BIT(SPSR_R, SPI2X);
	}

	/************************** SPCR Description **************************
	 * SPE     = 1 Enable SPI Driver
	 * MSTR    = 1 Enable Master
	 ***********************************************************************/
	SPCR_R |= SELECT_BIT(SPE) | SELECT_BIT(MSTR);
}

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
void SPI_initSlave(const ST_SpiSlaveConfig * a_spiConfig)
{
	/******** Configure SPI Slave Pins *********
	 * SS(PB4)   	--> 	Input
	 * MOSI(PB5) 	--> 	Input
	 * MISO(PB6) 	--> 	Output
	 * SCK(PB7) 	--> 	Input
	 ********************************************/
	DIO_pinInit(PB4, PIN_INPUT);
	DIO_pinInit(PB5, PIN_INPUT);
	DIO_pinInit(PB6, PIN_OUTPUT);
	DIO_pinInit(PB7, PIN_INPUT);

	SPCR_R = 0;

	/* insert the value of spi interrupt in SPIE */
	COPY_BITS(SPCR_R, 0x01, a_spiConfig->spiInterrupt, SPIE);

	/* insert the value of data order in DORD */
	COPY_BITS(SPCR_R, 0x01, a_spiConfig->dataOrder, DORD);

	/* insert the value of data mode in CPOL, CPHA */
	COPY_BITS(SPCR_R, 0x03, a_spiConfig->dataMode, CPHA);

	/* Clear the SPI2X bit in SPSR to Choose SPI clock = Fosc/4 */
	CLEAR_BIT(SPSR_R, SPI2X);

	/************************** SPCR Description **************************
	 * SPE     = 1 Enable SPI Driver
	 * MSTR    = 0 Enable Slave
	 ***********************************************************************/
	SPCR_R |= SELECT_BIT(SPE);
}

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
void SPI_setInterruptCallback(void (* volatile a_ptrToHandler)(void))
{
	/* save the interrupt pointer to callback */
	g_spiPtrToHandler = a_ptrToHandler;
}

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
uint8_t SPI_sendReceiveByteBlocking(const uint8_t a_data)
{
	uint8_t data;
	boolean interruptEnabled = FALSE;

	/* check if the spi interrput is enabled */
	if(BIT_IS_SET(SPCR_R, SPIE))
	{
		/* disable it temporarely */
		CLEAR_BIT(SPCR_R, SPIE);
		interruptEnabled = TRUE;
	}

	/* Initiate the communication and send data by SPI */
	SPDR_R = a_data;

	/* wait till data is transferred */
	while(BIT_IS_CLEAR(SPSR_R ,SPIF));

	/*
	 * Read the received data
	 * The SPIF flag will be cleared after read the data
	 */
	data = SPDR_R;

	/* re-enable spi enterrupt if it was enabled before entering the function */
	if(interruptEnabled == TRUE)
	{
		/* re-enable it */
		SET_BIT(SPCR_R, SPIE);
	}

	return data;
}

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
void SPI_sendByteNonBlocking(const uint8_t a_data)
{
	/* send data by putting it in SPDR_R */
	SPDR_R = a_data;
}

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
uint8_t SPI_receiveByteNonBlocking(void)
{
	/* read the received data */
	return SPDR_R;
}

/*
 * [Function Name]: SPI_sendString
 * [Function Description]: The function sends the given string till it reaches the null character
 * 						   It uses polling techinque "busy wait"
 * [Args]:
 * [in]: const char * a_str
 * 		 string to be sent
 * [Return]: uint8_t
 */
void SPI_sendString(const char * a_str)
{
	while(*a_str)
	{
		/* send char by char */
		SPI_sendReceiveByteBlocking(*a_str);

		/* increment the pointer */
		a_str ++;
	}
}

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
void SPI_receiveString(uint8_t * a_str, uint8_t a_maxSize)
{
	/* counter to keep track of the size */
	uint8_t counter = 0;

	/* return if size is 0 or 1 */
	if(a_maxSize == 0)
	{
		return;
	}
	else if(a_maxSize == 1)
	{
		*a_str = '\0';
		return;
	}

	/* get the first character */
	*a_str = SPI_sendReceiveByteBlocking(SPI_DEFAULT_DATA_VALUE);

	/* loop till the SPI_RECEIVE_STRING_TILL is found */
	while(*a_str != SPI_RECEIVE_STRING_TILL)
	{
		/* increment the counter and the pointer */
		counter ++;
		a_str ++;

		/* break the loop if the length reached the max size - 1 to leave space for '\0' */
		if(counter >= a_maxSize - 1) break;

		/* get the next character */
		*a_str = SPI_sendReceiveByteBlocking(SPI_DEFAULT_DATA_VALUE);
	}

	/* add null terminator */
	*a_str = '\0';
}

/*******************************************************************************
 *                       Interrupt Service Routines                            *
 *******************************************************************************/

/* ISR for spi */
ISR(SPI_STC_vect)
{
	if(g_spiPtrToHandler != NULL)
	{
		(*g_spiPtrToHandler)();
	}
}
