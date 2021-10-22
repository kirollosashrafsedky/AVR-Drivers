 /******************************************************************************
 *
 * Module: LM35 TEMPERATURE SENSOR
 *
 * File Name: lm35.h
 *
 * Description: Header file for the LM35 TEMPERATURE SENSOR driver
 *
 * Author: Kirollos Ashraf
 *
 *******************************************************************************/

#ifndef __LM35_H__
#define __LM35_H__

/*******************************************************************************
 *                                Includes	                                   *
 *******************************************************************************/

/* module config file */
#include "lm35-config.h"

/* For using std types */
#include "../../Lib/types.h"

/* For using common defines and macros */
#include "../../Lib/common.h"

/*******************************************************************************
 *                           Function Prototypes                               *
 *******************************************************************************/

/*
 * [Function Name]: LM35_getTemperature
 * [Function Description]: calculate the temperature
 * [Args]:
 * [in]: void
 * [Return]: uint8_t
 * 			 measured temperature
 */
uint8_t LM35_getTemperature(void);

#endif /* __LM35_H__ */
