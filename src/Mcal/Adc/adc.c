/******************************************************************************
 *
 * Module: ADC
 *
 * File Name: adc.c
 *
 * Description: Source file for the AVR ADC driver
 *
 * Author: Kirollos Ashraf
 *
 *******************************************************************************/

/*******************************************************************************
 *                                Includes	                                   *
 *******************************************************************************/

/* module header file */
#include "adc.h"

/* For using mcu registers */
#include "../Mcu/mcu.h"

/*******************************************************************************
 *                         Global Variables                             	   *
 *******************************************************************************/

/* global variable to hold the adc result when using adc interrupt */
volatile uint16_t g_adcResult;

/* pointer to the callback function */
static void (* volatile g_adcInterruptHandler)(void) = NULL;

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * [Function Name]: ADC_init
 * [Function Description]: responsible for initialize the ADC driver
 * [Args]:
 * [in]: const ADC_Config * a_adcConfig
 * 		 pointer to adc config struct
 * [Return]: void
 */
void ADC_init(const ST_AdcConfig * a_adcConfig)
{
	/* ADMUX Register Bits Description:
	 * REFS1, REFS0 = a_adcConfig->a_referenceVoltage
	 * ADLAR   		= 0 right adjusted
	 * MUX4:0  		= 00000 to choose channel 0 as initialization
	 */
	COPY_BITS(ADMUX_R, 0b00111111, 0, MUX0);
	COPY_BITS(ADMUX_R, 0b00000011, a_adcConfig->a_referenceVoltage, REFS0);

	/* ADCSRA Register Bits Description:
	 * ADEN    = 1 Enable ADC
	 * ADIE    = a_adcConfig->a_interruptMode
	 * ADATE   = 0 Disable Auto Trigger
	 * ADPS2:0 = a_adcConfig->a_prescaler
	 */
	ADCSRA_R = 0;
	COPY_BITS(ADCSRA_R, 0b00000111, a_adcConfig->a_prescaler, ADPS0);
	COPY_BITS(ADCSRA_R, 0b00000001, a_adcConfig->a_interruptMode, ADIE);
	SET_BIT(ADCSRA_R, ADEN);
}

/*
 * [Function Name]: ADC_readChannelPolling
 * [Function Description]: responsible for read analog data from a certain ADC channel
 * 						   and convert it to digital using the ADC driver.
 * 						   It's a busy wait function, it won't procced till the
 * 						   adc value is obtained.
 * 						   This function can be used in both cases, when adc interrupt is on or off,
 * 						   but it doesn't excute an interrupt when it's called, it disables the
 * 						   interrupt temporarly
 * [Args]:
 * [in]: uint8_t a_channelPin
 * 		 from PA0 to PA7
 * 		 or, any other 5-bit value (differential input) look datasheet
 * [Return]: uint16_t
 * 			 the adc value
 */
uint16_t ADC_readChannelPolling(uint8_t a_channelPin)
{
	uint8_t channelNum, isInterruptEnabled = 0;

	/* get the channel number from the pin number */
	channelNum = GET_PIN_NO(a_channelPin);

	/* modify the first 5 bits in ADMUX_R to match the channel number */
	COPY_BITS(ADMUX_R, 0b00011111, channelNum, MUX0);

	/* check if the interrupt is enabled to disable it temporarly */
	if(BIT_IS_SET(ADCSRA_R, ADIE))
	{
		isInterruptEnabled = 1;
		CLEAR_BIT(ADCSRA_R, ADIE);
	}

	/* Start conversion write '1' to ADSC */
	SET_BIT(ADCSRA_R, ADSC);

	/* Wait for conversion to complete, ADIF becomes 1 */
	while(BIT_IS_CLEAR(ADCSRA_R, ADIF));

	/* Clear ADIF by write '1' to it */
	SET_BIT(ADCSRA_R, ADIF);

	/* re-enable the interrupt if it was enabled before calling the function */
	if(isInterruptEnabled)
	{
		SET_BIT(ADCSRA_R, ADIE);
	}

	/* Read the digital value from the data register */
	return ADC_R;
}

/*
 * [Function Name]: ADC_readChannelPolling
 * [Function Description]: responsible for read analog data from a certain ADC channel
 * 						   and convert it to digital using the ADC driver.
 * 						   It doesn't return any value, the user must check the global
 * 						   variable g_adcResult.
 * 						   Be sure when reading this variable just after calling this function, it may return
 * 						   an old value. the best way is to call ADC_setCallBack() function and read the variable
 * 						   in this callback function to be sure that adc has finished conversion.
 * 						   This function should only be used when enabling the adc interrupt, or it will not
 * 						   give interrupt
 * [Args]:
 * [in]: uint8_t a_channelPin
 * 		 from PA0 to PA7
 * 		 or, any other 5-bit value (differential input) look datasheet
 * [Return]: void
 */
void ADC_readChannelInterrupt(uint8_t a_channelPin)
{
	uint8_t channelNum;

	/* get the channel number from the pin number */
	channelNum = GET_PIN_NO(a_channelPin);

	/* modify the first 5 bits in ADMUX_R to match the channel number */
	COPY_BITS(ADMUX_R, 0b00011111, channelNum, MUX0);

	/* Start conversion write '1' to ADSC */
	SET_BIT(ADCSRA_R, ADSC);
}

/*
 * [Function Name]: ADC_readChannelPolling
 * [Function Description]: used to assign the callback function when the adc interrupt occurs
 * 						   This function should be used only when enabling the adc interrupt.
 * 						   You can safely read the global variable g_adcResult in the callback function
 * [Args]:
 * [in]: void (* volatile a_handler_Ptr)(void)
 * 		 pointer to interrupt handler function
 * [Return]: void
 */
void ADC_setCallBack(void (* volatile a_handler_Ptr)(void))
{
	g_adcInterruptHandler = a_handler_Ptr;
}

/*
 * [Function Name]: ADC_enableAutoTriggerSource
 * [Function Description]: used to enable auto trigger source, ADC conversions occur when the selected source
 * 						   happens, you can return to the default settings of manually starting the conversion
 * 						   at any time by calling ADC_disableAutoTriggerSource, or re-init the adc
 * [Args]:
 * [in]: ADC_AutoTriggerSource a_autoTriggerSource
 * 		 pointer to interrupt handler function
 * [Return]: void
 */
void ADC_enableAutoTriggerSource(EN_AdcAutoTriggerSource a_autoTriggerSource)
{
	/* set the ADATE bit to enable Auto Trigger Source mode */
	SET_BIT(ADCSRA_R, ADATE);

	/* add the trigger source to bits5:7 in SFIOR register */
	COPY_BITS(SFIOR_R, 0b00000111, a_autoTriggerSource, ADTS0);
}

/*
 * [Function Name]: ADC_enableAutoTriggerSource
 * [Function Description]: disables the auto trigger source.
 * 						   ADC conversion happens only manually
 * [Args]:
 * [in]: void
 * [Return]: void
 */
void ADC_disableAutoTriggerSource(void)
{
	/* clear the ADATE bit to disable Auto Trigger Source mode */
	CLEAR_BIT(ADCSRA_R, ADATE);
}

/* ADC ISR */
ISR(ADC_vect)
{
	/* Read ADC Data after conversion complete */
	g_adcResult = ADC_R;

	/* excute the callback function if not null */
	if(g_adcInterruptHandler != NULL)
	{
		(*g_adcInterruptHandler)();
	}
}
