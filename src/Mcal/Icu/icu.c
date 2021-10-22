/******************************************************************************
 *
 * Module: ICU
 *
 * File Name: icu.c
 *
 * Description: Source file for the AVR ICU driver
 *
 * Author: Kirollos Ashraf
 *
 *******************************************************************************/

/*******************************************************************************
 *                                Includes	                                   *
 *******************************************************************************/

/* module header file */
#include "icu.h"

/* For using mcu registers */
#include "../Mcu/mcu.h"

/* For using DIO module */
#include "../Dio/dio.h"

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

/* Global variables to hold the address of the call back function in the application */
static void (* volatile g_callBackPtr)(void) = NULL;

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * [Function Name]: Icu_init
 * [Function Description]: initializes the ICU driver
 * 						   1. Set the required clock.
 * 						   2. Set the required edge detection.
 * 						   3. Enable the Input Capture Interrupt.
 * 						   4. Initialize Timer1 Registers
 * [Args]:
 * [in]: const ST_IcuConfig * a_icuConfig
 * 		 pointer to icu config structure
 * [Return]: void
 */
void Icu_init(const ST_IcuConfig * a_icuConfig)
{
	/* Configure ICP1/PD6 as i/p pin */
	DIO_pinInit(PD6, PIN_INPUT);

	/* Timer1 always operates in Normal Mode */
	TCCR1A_R = SELECT_BIT(FOC1A) | SELECT_BIT(FOC1B);
	TCCR1B_R = 0;
	/*
	 * insert the required edge type in ICES1 bit in TCCR1B Register
	 */
	COPY_BITS(TCCR1B_R, 0b00000001, a_icuConfig->edge, ICES1);

	/* Initial Value for Timer1 */
	TCNT1_R = 0;

	/* Initial Value for the input capture register */
	ICR1_R = 0;

	/*
	 * insert the required clock value in the first three bits (CS10, CS11 and CS12)
	 * of TCCR1B Register
	 */
	COPY_BITS(TCCR1B_R, 0b00000111, a_icuConfig->prescaler, CS10);

	/* Enable the Input Capture interrupt to generate an interrupt when edge is detected on ICP1/PD6 pin */
	TIMSK_R |= (1<<TICIE1);

}

/*
 * [Function Name]: Icu_setCallBack
 * [Function Description]: sets the Call Back function address
 * [Args]:
 * [in]: void(* volatile a_ptrToHandler)(void)
 * 		 pointer to callback function
 * [Return]: void
 */
void Icu_setCallBack(void(* volatile a_ptrToHandler)(void))
{
	/* Save the address of the Call back function in a global variable */
	g_callBackPtr = a_ptrToHandler;
}

/*
 * [Function Name]: Icu_setEdgeDetectionType
 * [Function Description]: sets the required edge detection.
 * [Args]:
 * [in]: EN_IcuEdgeType a_edgeType
 * 		 edge to set for detection
 * [Return]: void
 */
void Icu_setEdgeDetectionType(EN_IcuEdgeType a_edgeType)
{
	/*
	 * insert the required edge type in ICES1 bit in TCCR1B Register
	 */
	COPY_BITS(TCCR1B_R, 0b00000001, a_edgeType, ICES1);
}

/*
 * [Function Name]: Icu_setEdgeDetectionType
 * [Function Description]: sets the noise canceler feature of the ICU
 * [Args]:
 * [in]: EN_IcuNoiseCanceler a_noiseCanceler
 * 		 noice canceler option
 * [Return]: void
 */
void Icu_setNoiseCanceler(EN_IcuNoiseCanceler a_noiseCanceler)
{
	/*
	 * insert the required noise canceler option
	 * in ICNC1 bit in TCCR1B Register
	 */
	COPY_BITS(TCCR1B_R, 0b00000001, a_noiseCanceler, ICNC1);
}

/*
 * [Function Name]: Icu_getInputCaptureValue
 * [Function Description]: returns the Timer1 Value when the input is captured
 * [Args]:
 * [in]: void
 * [Return]: uint16_t
 * 			 the value of the input capture stored in ICR1_R
 */
uint16_t Icu_getInputCaptureValue(void)
{
	return ICR1_R;
}

/*
 * [Function Name]: Icu_clearTimerValue
 * [Function Description]: clears timer 1 value to start counting from 0
 * [Args]:
 * [in]: void
 * [Return]: void
 */
void Icu_clearTimerValue(void)
{
	TCNT1_R = 0;
}

/*
 * [Function Name]: Icu_clearTimerValue
 * [Function Description]: disables timer 1 and icu module
 * [Args]:
 * [in]: void
 * [Return]: void
 */
void Icu_deInit(void)
{
	/* Clear All Timer1 Registers */
	TCCR1A_R = 0;
	TCCR1B_R = 0;
	TCNT1_R = 0;
	ICR1_R = 0;

	/* Disable the Input Capture interrupt */
	TIMSK_R &= SELECT_INV_BIT(TICIE1);
}

/*******************************************************************************
 *                       Interrupt Service Routines                            *
 *******************************************************************************/

ISR(TIMER1_CAPT_vect)
{
	if(g_callBackPtr != NULL)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}

