/******************************************************************************
 *
 * Module: LM35 TEMPERATURE SENSOR
 *
 * File Name: lm35.c
 *
 * Description: Source file for the LM35 TEMPERATURE SENSOR driver
 *
 * Author: Kirollos Ashraf
 *
 *******************************************************************************/

/*******************************************************************************
 *                                Includes	                                   *
 *******************************************************************************/

/* module header file */
#include "lm35.h"

/* for using ADC module */
#include "../../Mcal/Adc/adc.h"

/*******************************************************************************
 *                          Functions Definition	                           *
 *******************************************************************************/

/*
 * [Function Name]: LM35_getTemperature
 * [Function Description]: calculate the temperature
 * [Args]:
 * [in]: void
 * [Return]: uint8_t
 * 			 measured temperature
 */
uint8_t LM35_getTemperature(void)
{
	uint16_t adcResult, temp_value = 0;

	/* Read ADC channel where the temperature sensor is connected */
	adcResult = ADC_readChannelPolling(LM35_PIN);

	/* Calculate the temperature from the ADC value*/
	temp_value = (uint8_t)(((uint32_t)adcResult * LM35_MAX_TEMPERATURE * ADC_REF_VOLT_VALUE) / (ADC_MAXIMUM_VALUE * LM35_MAX_VOLT_VALUE));

	return temp_value;
}
