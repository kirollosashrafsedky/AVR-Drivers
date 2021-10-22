/******************************************************************************
 *
 * Module: PUSH BUTTON
 *
 * File Name: button.c
 *
 * Description: Source file for the PUSH BUTTON driver
 *
 * Author: Kirollos Ashraf
 *
 *******************************************************************************/

/*******************************************************************************
 *                                Includes	                                   *
 *******************************************************************************/

/* module header file */
#include "button.h"

/* For using dio functions for pins */
#include "../../Mcal/Dio/dio.h"

#if BUTTON_CHECK_DEBOUNCE_ENABLED == 1

/* For using delay function */
#include "../../Mcal/Timer/timer.h"

#endif /* BUTTON_CHECK_DEBOUNCE_ENABLED == 1 */

#if BUTTON_INTERRUPT_ENABLE == 1

/* for using interrupt functions */
#include "../../Mcal/External-Interrupt/external-interrupt.h"

#endif /* BUTTON_INTERRUPT_ENABLE == 1 */

/*******************************************************************************
 *                      	   Global Variables		                           *
 *******************************************************************************/

#if BUTTONS_USED_COUNT != 1

/* array to hold all initialized buttons */
static ST_Button g_buttons[BUTTONS_USED_COUNT];

#endif /* BUTTONS_USED_COUNT != 1 */

/*******************************************************************************
 *                          Functions Definition	                           *
 *******************************************************************************/

#if BUTTONS_USED_COUNT == 1

/*
 * [Function Name]: BUTTON_init
 * [Function Description]: Initializes the button
 * [Args]:
 * [in]: void
 * [Return]: void
 */
void BUTTON_init(void)
{
	/* init button pin as input */
	DIO_pinInit(BUTTON_PIN, PIN_INPUT);

	/* control internal pull of the button pin */
	DIO_controlPinInternalPull(BUTTON_PIN, BUTTON_INTERNAL_PULL);
}

/*
 * [Function Name]: BUTTON_read
 * [Function Description]: gets the button state
 * [Args]:
 * [in]: void
 * [Return]: uint8_t
 * 			 button state - pressed or released
 */
uint8_t BUTTON_read(void)
{

#if BUTTON_CHECK_DEBOUNCE_ENABLED == 1

	/* check if button is pressed for first time */
	if(DIO_readPin(BUTTON_PIN) ^ BUTTON_CONNECTION)
	{
		/* delay for some time */
		TIMER_DELAY_MS(BUTTON_CHECK_DEBOUNCE_DELAY_MS);

		/* check if button is pressed for second time */
		if (DIO_readPin(BUTTON_PIN) ^ BUTTON_CONNECTION)
		{
			return BUTTON_PRESSED;
		}
	}
	return BUTTON_RELEASED;

#else

	/* the pin value ^ with the button connection gives the pressed state */
	return DIO_readPin(BUTTON_PIN) ^ BUTTON_CONNECTION;

#endif /* BUTTON_CHECK_DEBOUNCE_ENABLED */

}

#if BUTTON_INTERRUPT_ENABLE == 1

/*
 * [Function Name]: BUTTON_attachInterrupt
 * [Function Description]: attach interrupt handler for the button
 * [Args]:
 * [in]: EN_ButtonInteruptModes a_mode
 * 		 the interrupt mode
 * [in]: volatile void (* a_handler_Ptr)(void)
 * 		 pointer to the interrupt handler function
 * [Return]: uint8_t
 * 			 returns BUTTON_INT_SUCCESS if the mood is supported on the pin
 * 			 or BUTTON_INT_ERROR otherwise
 */
uint8_t BUTTON_attachInterrupt(EN_ButtonInteruptModes a_mode, void (* volatile a_handler_Ptr)(void))
{
	uint8_t intMode;

	/* map between button int. states and ext. int. states */
	switch(a_mode)
	{
	case BUTTON_INTERRUPT_ANY_CHANGE:
		intMode = EXT_INT_ANY_CHANGE;
		break;
	case BUTTON_INTERRUPT_FALLING_EDGE:
		intMode = EXT_INT_FALLING_EDGE;
		break;
	case BUTTON_INTERRUPT_RISING_EDGE:
		intMode = EXT_INT_RISING_EDGE;
		break;
	default:
		return BUTTON_INT_ERROR;
		break;
	}

	/* enable the external interrupt if available */
	return EXT_INT_enable(BUTTON_PIN , intMode, a_handler_Ptr);
}

/*
 * [Function Name]: BUTTON_detachInterrupt
 * [Function Description]: detach interrupt handler from the button
 * [Args]:
 * [in]: void
 * [Return]: uint8_t
 * 			 returns BUTTON_INT_SUCCESS if the button has interrupt available on its pin
 * 			 or BUTTON_INT_ERROR otherwise
 */
uint8_t BUTTON_detachInterrupt(void)
{
	/* disable the external interrupt */
	return EXT_INT_disable(BUTTON_PIN);
}

#endif /* BUTTON_INTERRUPT_ENABLE == 1 */

#else

/*
 * [Function Name]: BUTTON_init
 * [Function Description]: Initializes the buttons
 * [Args]:
 * [in]: const ST_Button * a_buttons
 * 		 array of buttons structures to init
 * [Return]: void
 */
void BUTTON_init(const ST_ButtonConfig * a_buttons)
{
	uint8_t loopCounter;

	for(loopCounter = 0; loopCounter < BUTTONS_USED_COUNT; loopCounter ++)
	{
		/* copy values from a_buttons to g_buttons */
		g_buttons[loopCounter].pin = a_buttons[loopCounter].pin;
		g_buttons[loopCounter].connection = a_buttons[loopCounter].connection;

		/* init pins as input */
		DIO_pinInit(g_buttons[loopCounter].pin, PIN_INPUT);

		/* control internal pull */
		DIO_controlPinInternalPull(g_buttons[loopCounter].pin, a_buttons[loopCounter].pull);
	}
}

/*
 * [Function Name]: BUTTON_read
 * [Function Description]: gets the button state
 * [Args]:
 * [in]: uint8_t a_buttonIndex
 * 		 button index to get its state, same index used in initializing the buttons array
 * [Return]: uint8_t
 * 			 button state - pressed or released
 */
uint8_t BUTTON_read(uint8_t a_buttonIndex)
{
	if(a_buttonIndex < BUTTONS_USED_COUNT)
	{

#if BUTTON_CHECK_DEBOUNCE_ENABLED == 1

		/* check if button is pressed for first time */
		if(DIO_readPin(g_buttons[a_buttonIndex].pin) ^ g_buttons[a_buttonIndex].connection)
		{
			/* delay for some time */
			TIMER_DELAY_MS(BUTTON_CHECK_DEBOUNCE_DELAY_MS);

			/* check if button is pressed for second time */
			if (DIO_readPin(g_buttons[a_buttonIndex].pin) ^ g_buttons[a_buttonIndex].connection)
			{
				return BUTTON_PRESSED;
			}
		}
		return BUTTON_RELEASED;

#else

		/* the pin value ^ with the button connection gives the pressed state */
		return DIO_readPin(g_buttons[a_buttonIndex].pin) ^ g_buttons[a_buttonIndex].connection;

#endif /* BUTTON_CHECK_DEBOUNCE_ENABLED */

	}
	return 0;
}

#if BUTTON_INTERRUPT_ENABLE == 1

/*
 * [Function Name]: BUTTON_attachInterrupt
 * [Function Description]: attach interrupt handler for the button
 * [Args]:
 * [in]: uint8_t a_buttonIndex
 * 		 button index to enable the interrupt for
 * [in]: EN_ButtonInteruptModes a_mode
 * 		 the interrupt mode
 * [in]: volatile void (* a_handler_Ptr)(void)
 * 		 pointer to the interrupt handler function
 * [Return]: uint8_t
 * 			 returns BUTTON_INT_SUCCESS if the mood is supported on the pin
 * 			 or BUTTON_INT_ERROR otherwise
 */
uint8_t BUTTON_attachInterrupt(uint8_t a_buttonIndex, EN_ButtonInteruptModes a_mode, void (* volatile a_handler_Ptr)(void))
{
	uint8_t intMode;

	/* map between button int. states and ext. int. states */
	switch(a_mode)
	{
	case BUTTON_INTERRUPT_ANY_CHANGE:
		intMode = EXT_INT_ANY_CHANGE;
		break;
	case BUTTON_INTERRUPT_FALLING_EDGE:
		intMode = EXT_INT_FALLING_EDGE;
		break;
	case BUTTON_INTERRUPT_RISING_EDGE:
		intMode = EXT_INT_RISING_EDGE;
		break;
	default:
		return BUTTON_INT_ERROR;
		break;
	}
	/* enable the external interrupt if available */
	return EXT_INT_enable(g_buttons[a_buttonIndex].pin , intMode, a_handler_Ptr);
}

/*
 * [Function Name]: BUTTON_detachInterrupt
 * [Function Description]: detach interrupt handler from the button
 * [Args]:
 * [in]: uint8_t a_buttonIndex
 * 		 button index to disable the interrupt for
 * [Return]: uint8_t
 * 			 returns BUTTON_INT_SUCCESS if the button has interrupt available on its pin
 * 			 or BUTTON_INT_ERROR otherwise
 */
uint8_t BUTTON_detachInterrupt(uint8_t a_buttonIndex)
{
	/* disable the external interrupt */
	return EXT_INT_disable(g_buttons[a_buttonIndex].pin);
}

#endif /* BUTTON_INTERRUPT_ENABLE == 1 */

#endif /* BUTTONS_USED_COUNT == 1 */
