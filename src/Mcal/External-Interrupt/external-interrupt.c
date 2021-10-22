/******************************************************************************
 *
 * Module: External Interrupt
 *
 * File Name: external-interrupt.c
 *
 * Description: Source file for the AVR External Interrupt driver
 *
 * Author: Kirollos Ashraf
 *
 *******************************************************************************/

/*******************************************************************************
 *                                Includes	                                   *
 *******************************************************************************/

/* module header file */
#include "external-interrupt.h"

/* For using mcu registers */
#include "../Mcu/mcu.h"

/* For using Dio module */
#include "../Dio/dio.h"

/*******************************************************************************
 *                            Global Variables		                           *
 *******************************************************************************/

static void (* volatile g_int0Handler_ptr)(void) = NULL;
static void (* volatile g_int1Handler_ptr)(void) = NULL;
static void (* volatile g_int2Handler_ptr)(void) = NULL;

/*******************************************************************************
 *                          Functions Definition	                           *
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
uint8_t EXT_INT_enable(uint8_t a_pin, EXT_INT_Modes a_mode, void (* volatile a_handler_Ptr)(void))
{
	switch(a_pin)
	{
	case INT0_PIN:
		DIO_pinInit(INT0_PIN, PIN_INPUT);
		if(a_mode < EXT_INTO_MODES_NO)
		{
			/* Fill bits ISC00 and ISC01 with the mood */
			COPY_BITS(MCUCR_R, 0b00000011, a_mode, ISC00);

			/* Enable INT 0 */
			SET_BIT(GICR_R, INT0);

			g_int0Handler_ptr = a_handler_Ptr;
		}
		break;
	case INT1_PIN:
		DIO_pinInit(INT1_PIN, PIN_INPUT);
		if(a_mode < EXT_INT1_MODES_NO)
		{
			/* Fill bits ISC10 and ISC11 with the mood */
			COPY_BITS(MCUCR_R, 0b00000011, a_mode, ISC10);

			/* Enable INT 1 */
			SET_BIT(GICR_R, INT1);

			g_int1Handler_ptr = a_handler_Ptr;
		}
		break;
	case INT2_PIN:
		DIO_pinInit(INT2_PIN, PIN_INPUT);
		if(a_mode == EXT_INT_FALLING_EDGE || a_mode == EXT_INT_RISING_EDGE)
		{
			/* Fill bit ISC2 with the mood */
			COPY_BITS(MCUCSR_R, 0b00000001, a_mode, ISC2);

			/* Enable INT 2 */
			SET_BIT(GICR_R, INT2);

			g_int2Handler_ptr = a_handler_Ptr;
		}
		else
		{
			return EXT_INT_FAILURE;
		}
		break;
	default:
		/* Pin doesn't have support for external interrupts */
		return EXT_INT_FAILURE;
		break;
	}
	return EXT_INT_SUCCESS;

}

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
uint8_t EXT_INT_disable(uint8_t a_pin)
{
	switch(a_pin)
	{
	case INT0_PIN:
		/* Disable INT 0 */
		CLEAR_BIT(GICR_R, INT0);
		break;
	case INT1_PIN:
		/* Disable INT 1 */
		CLEAR_BIT(GICR_R, INT1);
		break;
	case INT2_PIN:
		/* Disable INT 2 */
		CLEAR_BIT(GICR_R, INT2);
		break;
	default:
		/* Pin doesn't have support for external interrupts */
		return EXT_INT_FAILURE;
		break;
	}
	return EXT_INT_SUCCESS;
}

/*******************************************************************************
 *                       Interrupt Service Routines                            *
 *******************************************************************************/

/* ISR for INT 0 */
ISR(INT0_vect)
{
	if(g_int0Handler_ptr != NULL)
	{
		(*g_int0Handler_ptr)();
	}
}

/* ISR for INT 1 */
ISR(INT1_vect)
{
	if(g_int1Handler_ptr != NULL)
	{
		(*g_int1Handler_ptr)();
	}
}

/* ISR for INT 2 */
ISR(INT2_vect)
{
	if(g_int2Handler_ptr != NULL)
	{
		(*g_int2Handler_ptr)();
	}
}
