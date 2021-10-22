 /******************************************************************************
 *
 * Module: PUSH BUTTON
 *
 * File Name: button.h
 *
 * Description: Header file for the PUSH BUTTON driver
 *
 * Author: Kirollos Ashraf
 *
 *******************************************************************************/

#ifndef __BUTTON_H__
#define __BUTTON_H__

/*******************************************************************************
 *                                Includes	                                   *
 *******************************************************************************/

/* module config file */
#include "button-config.h"

/* For using std types */
#include "../../Lib/types.h"

/* For using common defines and macros */
#include "../../Lib/common.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

/* button states */
#define BUTTON_PRESSED				1
#define BUTTON_RELEASED				0

/* button interrupt states */
#define BUTTON_INT_SUCCESS			1
#define BUTTON_INT_ERROR			0

/*******************************************************************************
 *                             Types Declaration                               *
 *******************************************************************************/

/*
 * [Enum Name]: EN_ButtonConnection
 * [Enum Description]: contains button's connection method
 */
typedef enum
{
	BUTTON_ACTIVE_HIGH,
	BUTTON_ACTIVE_LOW
}EN_ButtonConnection;

/*
 * [Enum Name]: EN_ButtonInternalPull
 * [Enum Description]: contains button's internal pull states,
 * 					   using BUTTON_PULL_UP or BUTTON_PULL_DOWN, does nothing
 * 					   if they are not supported by the mcu
 */
typedef enum
{
	BUTTON_NO_PULL,
	BUTTON_PULL_UP,
	BUTTON_PULL_DOWN
}EN_ButtonInternalPull;

#if BUTTON_INTERRUPT_ENABLE == 1

/*
 * [Enum Name]: EN_ButtonInteruptModes
 * [Enum Description]: contains general modes of interrupts that can be attached to the
 * 					   button, may not be supported on all pins in all mcus
 */
typedef enum
{
	BUTTON_INTERRUPT_ANY_CHANGE,
	BUTTON_INTERRUPT_FALLING_EDGE,
	BUTTON_INTERRUPT_RISING_EDGE,
}EN_ButtonInteruptModes;

#endif /* BUTTON_INTERRUPT_ENABLE == 1 */

#if BUTTONS_USED_COUNT != 1

/*
 * [Struct Name]: ST_ButtonConfig
 * [Struct Description]: contains button's configuration
 */
typedef struct
{
	/* pin push button is connected to */
	uint8_t pin;

	/* connection of the push button */
	EN_ButtonConnection connection;

	/* push button internal pull state */
	EN_ButtonInternalPull pull;

}ST_ButtonConfig;

/*
 * [Struct Name]: ST_Button
 * [Struct Description]: same as ST_ButtonConfig but contain data needed to be stored only
 * 						 i.e. used inside the driver only
 */
typedef struct
{
	/* pin push button is connected to */
	uint8_t pin;

	/* connection of the push button */
	EN_ButtonConnection connection;

}ST_Button;

#endif /* BUTTONS_USED_COUNT != 1 */

/*******************************************************************************
 *                           Function Prototypes                               *
 *******************************************************************************/

/************** BUTTON_init ****************/

#if BUTTONS_USED_COUNT == 1

/*
 * [Function Name]: BUTTON_init
 * [Function Description]: Initializes the button
 * [Args]:
 * [in]: void
 * [Return]: void
 */
void BUTTON_init(void);

#else

/*
 * [Function Name]: BUTTON_init
 * [Function Description]: Initializes the buttons
 * [Args]:
 * [in]: const ST_ButtonConfig * a_buttons
 * 		 array of buttons config structures to init
 * [Return]: void
 */
void BUTTON_init(const ST_ButtonConfig * a_buttons);

#endif /* BUTTONS_USED_COUNT == 1 */

/************** BUTTON_read ****************/

#if BUTTONS_USED_COUNT == 1

/*
 * [Function Name]: BUTTON_read
 * [Function Description]: gets the button state
 * [Args]:
 * [in]: void
 * [Return]: uint8_t
 * 			 button state - pressed or released
 */
uint8_t BUTTON_read(void);

#else

/*
 * [Function Name]: BUTTON_read
 * [Function Description]: gets the button state
 * [Args]:
 * [in]: uint8_t a_buttonIndex
 * 		 button index to get its state, same index used in initializing the buttons array
 * [Return]: uint8_t
 * 			 button state - pressed or released
 */
uint8_t BUTTON_read(uint8_t a_buttonIndex);

#endif /* BUTTONS_USED_COUNT == 1 */


#if BUTTON_INTERRUPT_ENABLE == 1

/************** BUTTON_attachInterrupt ****************/

#if BUTTONS_USED_COUNT == 1

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
uint8_t BUTTON_attachInterrupt(EN_ButtonInteruptModes a_mode, void (* volatile a_handler_Ptr)(void));

#else

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
uint8_t BUTTON_attachInterrupt(uint8_t a_buttonIndex, EN_ButtonInteruptModes a_mode, void (* volatile a_handler_Ptr)(void));

#endif /* BUTTONS_USED_COUNT == 1 */

/************** BUTTON_detachInterrupt ****************/

#if BUTTONS_USED_COUNT == 1

/*
 * [Function Name]: BUTTON_detachInterrupt
 * [Function Description]: detach interrupt handler from the button
 * [Args]:
 * [in]: void
 * [Return]: uint8_t
 * 			 returns BUTTON_INT_SUCCESS if the button has interrupt available on its pin
 * 			 or BUTTON_INT_ERROR otherwise
 */
uint8_t BUTTON_detachInterrupt(void);

#else

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
uint8_t BUTTON_detachInterrupt(uint8_t a_buttonIndex);

#endif /* BUTTONS_USED_COUNT == 1 */

#endif /* BUTTON_INTERRUPT_ENABLE == 1 */

#endif /* __BUTTON_H__ */
