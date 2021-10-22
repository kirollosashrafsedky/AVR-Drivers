/******************************************************************************
 *
 * Module: LED
 *
 * File Name: led.h
 *
 * Description: Header file for the LED driver
 *
 * Author: Kirollos Ashraf
 *
 *******************************************************************************/

#ifndef __LED_H__
#define __LED_H__

/*******************************************************************************
 *                                Includes	                                   *
 *******************************************************************************/

/* module config file */
#include "led-config.h"

/* For using std types */
#include "../../Lib/types.h"

/* For using common defines and macros */
#include "../../Lib/common.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

/* led states */
#define LED_ON			 			 1
#define LED_OFF			 			 0

/*******************************************************************************
 *                             Types Declaration                               *
 *******************************************************************************/

/*
 * [Enum Name]: EN_LedLogic
 * [Enum Description]: contains led's connection (logic) states
 */
typedef enum
{
	LED_NEGATIVE_LOGIC,
	LED_POSITIVE_LOGIC
}EN_LedLogic;

#if LEDS_USED_COUNT != 1

/*
 * [Struct Name]: ST_Led
 * [Struct Description]: contains led's configuration
 */
typedef struct
{
	/* pin led is connected to */
	uint8_t pin;

	/* connection of the led */
	EN_LedLogic logic;
}ST_Led;

#endif /* LEDS_USED_COUNT != 1 */

/*******************************************************************************
 *                           Function Prototypes                               *
 *******************************************************************************/

/************** LED_init ****************/

#if LEDS_USED_COUNT == 1

/*
 * [Function Name]: LED_init
 * [Function Description]: Initializes the led
 * [Args]:
 * [in]: void
 * [Return]: void
 */
void LED_init(void);

#else

/*
 * [Function Name]: LED_init
 * [Function Description]: Initializes the leds
 * [Args]:
 * [in]: const ST_Led * a_leds
 * 		 array of leds structures to init
 * [Return]: void
 */
void LED_init(const ST_Led * a_leds);

#endif /* LEDS_USED_COUNT == 1 */

/************** LED_on ****************/

#if LEDS_USED_COUNT == 1

/*
 * [Function Name]: LED_on
 * [Function Description]: turns on the led
 * [Args]:
 * [in]: void
 * [Return]: void
 */
void LED_on(void);

#else

/*
 * [Function Name]: LED_on
 * [Function Description]: turns on the led
 * [Args]:
 * [in]: uint8_t a_ledIndex
 * 		 led index to turn on, same index used in initializing the leds array
 * [Return]: void
 */
void LED_on(uint8_t a_ledIndex);

#endif /* LEDS_USED_COUNT == 1 */

/************** LED_off ****************/

#if LEDS_USED_COUNT == 1

/*
 * [Function Name]: LED_off
 * [Function Description]: turns off the led
 * [Args]:
 * [in]: void
 * [Return]: void
 */
void LED_off(void);

#else

/*
 * [Function Name]: LED_off
 * [Function Description]: turns off the led
 * [Args]:
 * [in]: uint8_t a_ledIndex
 * 		 led index to turn off, same index used in initializing the leds array
 * [Return]: void
 */
void LED_off(uint8_t a_ledIndex);

#endif /* LEDS_USED_COUNT == 1 */

/************** LED_toggle ****************/

#if LEDS_USED_COUNT == 1

/*
 * [Function Name]: LED_toggle
 * [Function Description]: toggles the led
 * [Args]:
 * [in]: void
 * [Return]: void
 */
void LED_toggle(void);

#else

/*
 * [Function Name]: LED_off
 * [Function Description]: toggles the led
 * [Args]:
 * [in]: uint8_t a_ledIndex
 * 		 led index to toggle, same index used in initializing the leds array
 * [Return]: void
 */
void LED_toggle(uint8_t a_ledIndex);

#endif /* LEDS_USED_COUNT == 1 */

/************** LED_dim ****************/

#if PWM_FOR_DIMMING_SUPPORTED == 1

#if LEDS_USED_COUNT == 1

/*
 * [Function Name]: LED_dim
 * [Function Description]: dims the led with the given brightness
 * [Args]:
 * [in]: uint8_t a_brightness
 * 		 brightness level to control the led (from 0 to 100)
 * [Return]: void
 */
void LED_dim(uint8_t a_brightness);

#else

/*
 * [Function Name]: LED_dim
 * [Function Description]: dims the led with the given brightness
 * [Args]:
 * [in]: uint8_t a_ledIndex
 * 		 led index to dim, same index used in initializing the leds array
 * [in]: uint8_t a_brightness
 * 		 brightness level to control the led (from 0 to 100)
 * [Return]: void
 */
void LED_dim(uint8_t a_ledIndex, uint8_t a_brightness);

#endif /* LEDS_USED_COUNT == 1 */

#endif /* PWM_FOR_DIMMING_SUPPORTED == 1 */

#endif /* __LED_H__ */
