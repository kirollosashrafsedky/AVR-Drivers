 /******************************************************************************
 *
 * Module: LM35 TEMPERATURE SENSOR
 *
 * File Name: lm35-config.h
 *
 * Description: Config file for the LM35 TEMPERATURE SENSOR driver
 *
 * Author: Kirollos Ashraf
 *
 *******************************************************************************/

#ifndef __LM35_CONFIG_H__
#define __LM35_CONFIG_H__

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

/* the pin, LM35 is connected to, must be a pin supporting ADC */
#define LM35_PIN							         PA0

/* maximum voltage value of the sensor */
#define LM35_MAX_VOLT_VALUE     					 1.5

/* temperature corresponding to the maximum voltage value LM35_MAX_VOLT_VALUE */
#define LM35_MAX_TEMPERATURE    					 150

#endif /* __LM35_CONFIG_H__ */
