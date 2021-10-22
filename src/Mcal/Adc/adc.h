/******************************************************************************
 *
 * Module: ADC
 *
 * File Name: adc.h
 *
 * Description: Header file for the AVR ADC driver
 *
 * Author: Kirollos Ashraf
 *
 *******************************************************************************/

#ifndef __ADC_H__
#define __ADC_H__

/*******************************************************************************
 *                                Includes	                                   *
 *******************************************************************************/

/* Module config file */
#include "adc-config.h"

/* For using std types */
#include "../../Lib/types.h"

/* For using common defines and macros */
#include "../../Lib/common.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

/* maximum value of the 10-bit adc */
#define ADC_MAXIMUM_VALUE    							1023

/*******************************************************************************
 *                             External Variables                              *
 *******************************************************************************/

/* global variable to hold the adc result when using adc interrupt */
extern volatile uint16_t g_adcResult;

/*******************************************************************************
 *                             Types Declaration                               *
 *******************************************************************************/

/*
 * [Enum Name]: EN_AdcReferenceVolatge
 * [Enum Description]: contains adc reference voltage options,
 * 					   note that the value of ADC_REF_VOLT_VALUE in the config file
 * 					   should be modified as well for modules using ADC to behave properly
 */
typedef enum
{
	/* the reference voltage is connected to the external AREF pin */
	ADC_AREF,

	/* AVCC with external capacitor at AREF pin */
	ADC_AVCC,

	/* Internal 2.56V Voltage Reference with external capacitor at AREF pin */
	ADC_INTERNAL = 3,
}EN_AdcReferenceVolatge;

/*
 * [Enum Name]: EN_AdcPrescaler
 * [Enum Description]: contains adc prescaler clock options used to operate the adc,
 * 					   ADC must operate in range 50-200Khz
 */
typedef enum
{
	ADC_PRESCALER_2 = 1,
	ADC_PRESCALER_4,
	ADC_PRESCALER_8,
	ADC_PRESCALER_16,
	ADC_PRESCALER_32,
	ADC_PRESCALER_64,
	ADC_PRESCALER_128,
}EN_AdcPrescaler;

/*
 * [Enum Name]: EN_AdcInterruptMode
 * [Enum Description]: contains adc prescaler clock options used to operate the adc
 */
typedef enum
{
	ADC_INTERRUPT_OFF,
	ADC_INTERRUPT_ON
}EN_AdcInterruptMode;

/*
 * [Enum Name]: EN_AdcAutoTriggerSource
 * [Enum Description]: contains adc auto trigger sources
 */
typedef enum
{
	ADC_ATC_FREE_RUNNING_MODE,
	ADC_ATC_FREE_ANALOG_COMPARATOR,
	ADC_ATC_FREE_EXT_INT_0,
	ADC_ATC_FREE_TIMER_0_CTC,
	ADC_ATC_FREE_TIMER_0_OVF,
	ADC_ATC_FREE_TIMER_1_CTCB,
	ADC_ATC_FREE_TIMER_1_OVF,
	ADC_ATC_FREE_TIMER_1_ICU,
}EN_AdcAutoTriggerSource;

/*
 * [Struct Name]: ST_AdcConfig
 * [Struct Description]: contains adc config data used for initialization
 */
typedef struct
{
	/* reference voltage of the adc */
	EN_AdcReferenceVolatge a_referenceVoltage;

	/* adc prescaler clock value */
	EN_AdcPrescaler a_prescaler;

	/* whether adc interrupt is on or off */
	EN_AdcInterruptMode a_interruptMode;
}ST_AdcConfig;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * [Function Name]: ADC_init
 * [Function Description]: responsible for initialize the ADC driver
 * [Args]:
 * [in]: const ADC_Config * a_adcConfig
 * 		 pointer to adc config struct
 * [Return]: void
 */
void ADC_init(const ST_AdcConfig * a_adcConfig);

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
uint16_t ADC_readChannelPolling(uint8_t a_channelPin);

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
void ADC_readChannelInterrupt(uint8_t a_channelPin);

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
void ADC_setCallBack(void (* volatile a_handler_Ptr)(void));

/*
 * [Function Name]: ADC_enableAutoTriggerSource
 * [Function Description]: used to enable auto trigger source, ADC conversions occur when the selected source
 * 						   happens, you can return to the default settings of manually starting the conversion
 * 						   at any time by calling ADC_disableAutoTriggerSource, or re-init the adc
 * [Args]:
 * [in]: EN_AdcAutoTriggerSource a_autoTriggerSource
 * 		 pointer to interrupt handler function
 * [Return]: void
 */
void ADC_enableAutoTriggerSource(EN_AdcAutoTriggerSource a_autoTriggerSource);

/*
 * [Function Name]: ADC_enableAutoTriggerSource
 * [Function Description]: disables the auto trigger source.
 * 						   ADC conversion happens only manually
 * [Args]:
 * [in]: void
 * [Return]: void
 */
void ADC_disableAutoTriggerSource(void);

#endif /* __ADC_H__ */
