/******************************************************************************
 *
 * Module: ULTRASONIC
 *
 * File Name: ultrasonic-config.h
 *
 * Description: Config file for the ULTRASONIC driver
 *
 * Author: Kirollos Ashraf
 *
 *******************************************************************************/

#ifndef __ULTRASONIC_CONFIG_H__
#define __ULTRASONIC_CONFIG_H__

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

/* it's a value minused from the distance, used for calibration
 * it can be positive or negative */
#define ULTRASONIC_CALIBRATION_VALUE				-1

/* the trigger pin of the ultrasonic */
#define ULTRASONIC_TRIGGER_PIN						PB5

/* the echo pin of the ultrasonic
 * this pin must have ICU supported on it
 */
#define ULTRASONIC_ECHO_PIN							PD6

/* making sure F_CPU is defined */
#ifndef F_CPU
#define F_CPU										(1000000U)
#endif /* F_CPU */

#endif /* __ULTRASONIC_CONFIG_H__ */
