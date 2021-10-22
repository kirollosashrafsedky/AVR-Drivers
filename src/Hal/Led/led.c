/******************************************************************************
 *
 * Module: LED
 *
 * File Name: led.c
 *
 * Description: Source file for the LED driver
 *
 * Author: Kirollos Ashraf
 *
 *******************************************************************************/

/*******************************************************************************
 *                                Includes	                                   *
 *******************************************************************************/

/* module header file */
#include "led.h"

/* For using dio functions for pins */
#include "../../Mcal/Dio/dio.h"

#if PWM_FOR_DIMMING_SUPPORTED == 1

/* For using pwm for controlling led brightness */
#include "../../Mcal/Pwm/pwm.h"

#endif /* PWM_FOR_DIMMING_SUPPORTED == 1 */

/*******************************************************************************
 *                      	   Global Variables		                           *
 *******************************************************************************/

#if LEDS_USED_COUNT != 1

/* array to hold all initialized leds */
static ST_Led g_leds[LEDS_USED_COUNT];

#endif /* LEDS_USED_COUNT != 1 */

/*******************************************************************************
 *                          Functions Definition	                           *
 *******************************************************************************/

#if LEDS_USED_COUNT == 1

/*
 * [Function Name]: LED_init
 * [Function Description]: Initializes the led
 * [Args]:
 * [in]: void
 * [Return]: void
 */
void LED_init(void)
{
	DIO_pinInit(LED_PIN, PIN_OUTPUT);

#if LED_INITIAL_STATE == LED_ON

	LED_on();

#elif LED_INITIAL_STATE == LED_OFF

	LED_off();

#endif /* LED_INITIAL_STATE == LED_ON */
}

/*
 * [Function Name]: LED_on
 * [Function Description]: turns on the led
 * [Args]:
 * [in]: void
 * [Return]: void
 */
void LED_on(void)
{
	DIO_writePin(LED_PIN, LED_LOGIC);
}

/*
 * [Function Name]: LED_off
 * [Function Description]: turns off the led
 * [Args]:
 * [in]: void
 * [Return]: void
 */
void LED_off(void)
{
	DIO_writePin(LED_PIN, !LED_LOGIC);
}

/*
 * [Function Name]: LED_toggle
 * [Function Description]: toggles the led
 * [Args]:
 * [in]: void
 * [Return]: void
 */
void LED_toggle(void)
{
	DIO_togglePin(LED_PIN);
}

#if PWM_FOR_DIMMING_SUPPORTED == 1
/*
 * [Function Name]: LED_dim
 * [Function Description]: dims the led with the given brightness
 * [Args]:
 * [in]: uint8_t a_brightness
 * 		 brightness level to control the led (from 0 to 100)
 * [Return]: void
 */
void LED_dim(uint8_t a_brightness)
{
	/* make sure the brightness <= 100 */
	if(a_brightness > 100)
	{
		return;
	}
#if LED_LOGIC == LED_POSITIVE_LOGIC

	/* check if led is connected to a pin that doesn't support pwm */
	if(PWM_enable(LED_PIN, a_brightness) == PWM_ERROR)
	{
		/* write high if pwm is not supported on the pin */
		DIO_writePin(LED_PIN, HIGH);
	}

#else

	/* check if led is connected to a pin that doesn't support pwm */
	if(PWM_enable(LED_PIN, 100 - a_brightness) == PWM_ERROR)
	{
		/* write high if pwm is not supported on the pin */
		DIO_writePin(LED_PIN, LOW);
	}


#endif /* LED_LOGIC == LED_POSITIVE_LOGIC */
}

#endif /* PWM_FOR_DIMMING_SUPPORTED == 1 */

#else

/*
 * [Function Name]: LED_init
 * [Function Description]: Initializes the leds
 * [Args]:
 * [in]: const ST_Led * a_leds
 * 		 array of leds structures to init
 * [Return]: void
 */
void LED_init(const ST_Led * a_leds)
{
	uint8_t loopCounter;

	for(loopCounter = 0; loopCounter < LEDS_USED_COUNT; loopCounter ++)
	{
		/* copy values from a_leds to g_leds */
		g_leds[loopCounter] = a_leds[loopCounter];
		DIO_pinInit(g_leds[loopCounter].pin, PIN_OUTPUT);

#if LED_INITIAL_STATE == LED_ON

		LED_on(loopCounter);

#elif LED_INITIAL_STATE == LED_OFF

		LED_off(loopCounter);

#endif /* LED_INITIAL_STATE == LED_ON */

	}
}

/*
 * [Function Name]: LED_on
 * [Function Description]: turns on the led
 * [Args]:
 * [in]: uint8_t a_ledIndex
 * 		 led index to turn on, same index used in initializing the leds array
 * [Return]: void
 */
void LED_on(uint8_t a_ledIndex)
{
	if(a_ledIndex < LEDS_USED_COUNT)
	{
		DIO_writePin(g_leds[a_ledIndex].pin, g_leds[a_ledIndex].logic);
	}
}

/*
 * [Function Name]: LED_off
 * [Function Description]: turns off the led
 * [Args]:
 * [in]: uint8_t a_ledIndex
 * 		 led index to turn off, same index used in initializing the leds array
 * [Return]: void
 */
void LED_off(uint8_t a_ledIndex)
{
	if(a_ledIndex < LEDS_USED_COUNT)
	{
		DIO_writePin(g_leds[a_ledIndex].pin, !g_leds[a_ledIndex].logic);
	}
}

/*
 * [Function Name]: LED_off
 * [Function Description]: toggles the led
 * [Args]:
 * [in]: uint8_t a_ledIndex
 * 		 led index to toggle, same index used in initializing the leds array
 * [Return]: void
 */
void LED_toggle(uint8_t a_ledIndex)
{
	if(a_ledIndex < LEDS_USED_COUNT)
	{
		DIO_togglePin(g_leds[a_ledIndex].pin);
	}
}

#if PWM_FOR_DIMMING_SUPPORTED == 1
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
void LED_dim(uint8_t a_ledIndex, uint8_t a_brightness)
{
	/* make sure the brightness <= 100 and led is available */
	if(a_brightness > 100 || a_ledIndex >= LEDS_USED_COUNT)
	{
		return;
	}
	if(g_leds[a_ledIndex].logic == LED_POSITIVE_LOGIC)
	{
		/* check if led is connected to a pin that doesn't support pwm */
		if(PWM_enable(g_leds[a_ledIndex].pin, a_brightness) == PWM_ERROR)
		{
			/* write high if pwm is not supported on the pin */
			DIO_writePin(g_leds[a_ledIndex].pin, HIGH);
		}
	}
	else
	{

		/* check if led is connected to a pin that doesn't support pwm */
		if(PWM_enable(g_leds[a_ledIndex].pin, 100 - a_brightness) == PWM_ERROR)
		{
			/* write high if pwm is not supported on the pin */
			DIO_writePin(g_leds[a_ledIndex].pin, LOW);
		}
	}
}

#endif /* PWM_FOR_DIMMING_SUPPORTED == 1 */

#endif /* LEDS_USED_COUNT == 1 */
