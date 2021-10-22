 /******************************************************************************
 *
 * Module: External Interrupt
 *
 * File Name: external-interrupt.h
 *
 * Description: Header file for the AVR External Interrupt driver
 *
 * Author: Kirollos Ashraf
 *
 *******************************************************************************/

#ifndef __EXTERNAL_INTERRUPT_H__
#define __EXTERNAL_INTERRUPT_H__

/*******************************************************************************
 *                                Includes	                                   *
 *******************************************************************************/

/* For using std types */
#include "../../Lib/types.h"

/* For using common defines and macros */
#include "../../Lib/common.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

/* success or failure indicating interrupt availablity on the passed pin */
#define EXT_INT_SUCCESS 		1
#define EXT_INT_FAILURE 		0

/* No of modes for each interrupt */
#define EXT_INTO_MODES_NO 		4
#define EXT_INT1_MODES_NO 		4
#define EXT_INT2_MODES_NO 		2

/*******************************************************************************
 *                             Types Declaration                               *
 *******************************************************************************/

/*
 * [Enum Name]: EXT_INT_Modes
 * [Enum Description]: contain modes for external interrupt 0, 1, or 2
 */

typedef enum
{
	/* External Interrupt modes for interrupt 0, 1, or 2 */
	/* The first two modes works only with interrupt 0 and 1 */
	EXT_INT_LOW_LEVEL = 0,
	EXT_INT_ANY_CHANGE,
	EXT_INT_FALLING_EDGE,
	EXT_INT_RISING_EDGE,
}EXT_INT_Modes;

/*******************************************************************************
 *                           Function Prototypes                               *
 *******************************************************************************/

/*
 * [Function Name]: EXT_INT_enable
 * [Function Description]: enable external interrupt on a specific pin if
 * 						   available with the passed mode
 * [Args]:
 * [in]: uint8_t a_pin
 * 		 the pin number to enable the external interrupt for
 * [in]: EXT_INT_Modes a_mode
 * 		 the mode of the external interrupt
 * [in]: void (* a_handler_Ptr)(void)
 * 		 pointer to the isr handler
 * [Return]: uint8_t
 * 			 returns EXT_INT_SUCCESS if the pin has external interrupt available
 * 			 or EXT_INT_Failure if not
 */
uint8_t EXT_INT_enable(uint8_t a_pin, EXT_INT_Modes a_mode, void (* volatile a_handler_Ptr)(void));

/*
 * [Function Name]: EXT_INT_disable
 * [Function Description]: disable external interrupt on a specific pin if
 * 						   available
 * [Args]:
 * [in]: uint8_t a_pin
 * 		 the pin number to disable the external interrupt for
 * [Return]: uint8_t
 * 			 returns EXT_INT_SUCCESS if the pin has external interrupt available
 * 			 or EXT_INT_Failure if not
 */
uint8_t EXT_INT_disable(uint8_t a_pin);

#endif /* __EXTERNAL_INTERRUPT_H__ */
