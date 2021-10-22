/******************************************************************************
 *
 * Module: ICU
 *
 * File Name: icu.h
 *
 * Description: Header file for the AVR ICU driver
 *
 * Author: Kirollos Ashraf
 *
 *******************************************************************************/

#ifndef __ICU_H__
#define __ICU_H__

/*******************************************************************************
 *                                Includes	                                   *
 *******************************************************************************/

/* For using std types */
#include "../../Lib/types.h"

/* For using common defines and macros */
#include "../../Lib/common.h"

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/

/*
 * [Enum Name]: EN_IcuPrescaler
 * [Enum Description]: contains ICU prescalers(clocks)
 */
typedef enum
{
	NO_CLOCK,
	ICU_PRESCALER_1,
	ICU_PRESCALER_8,
	ICU_PRESCALER_64,
	ICU_PRESCALER_256,
	ICU_PRESCALER_1024
}EN_IcuPrescaler;

/*
 * [Enum Name]: EN_IcuEdgeType
 * [Enum Description]: contains ICU edge trigger types
 */
typedef enum
{
	ICU_FALLING_EDGE,
	ICU_RISING_EDGE
}EN_IcuEdgeType;

/*
 * [Enum Name]: EN_IcuNoiseCanceler
 * [Enum Description]: contains ICU noise canceler options
 */
typedef enum
{
	ICU_NOISE_CANCELER_DISABLE,
	ICU_NOISE_CANCELER_ENABLE
}EN_IcuNoiseCanceler;

/*
 * [Enum Name]: ST_IcuConfig
 * [Enum Description]: contains ICU config
 */
typedef struct
{
	EN_IcuPrescaler prescaler;
	EN_IcuEdgeType edge;
}ST_IcuConfig;

/*******************************************************************************
 *                      Functions Prototypes                                   *
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
void Icu_init(const ST_IcuConfig * a_icuConfig);

/*
 * [Function Name]: Icu_setCallBack
 * [Function Description]: sets the Call Back function address
 * [Args]:
 * [in]: void(* volatile a_ptrToHandler)(void)
 * 		 pointer to callback function
 * [Return]: void
 */
void Icu_setCallBack(void(* volatile a_ptrToHandler)(void));

/*
 * [Function Name]: Icu_setEdgeDetectionType
 * [Function Description]: sets the required edge detection.
 * [Args]:
 * [in]: EN_IcuEdgeType a_edgeType
 * 		 edge to set for detection
 * [Return]: void
 */
void Icu_setEdgeDetectionType(EN_IcuEdgeType a_edgeType);

/*
 * [Function Name]: Icu_setEdgeDetectionType
 * [Function Description]: sets the noise canceler feature of the ICU
 * [Args]:
 * [in]: EN_IcuNoiseCanceler a_noiseCanceler
 * 		 noice canceler option
 * [Return]: void
 */
void Icu_setNoiseCanceler(EN_IcuNoiseCanceler a_noiseCanceler);

/*
 * [Function Name]: Icu_getInputCaptureValue
 * [Function Description]: returns the Timer1 Value when the input is captured
 * [Args]:
 * [in]: void
 * [Return]: uint16_t
 * 			 the value of the input capture stored in ICR1_R
 */
uint16_t Icu_getInputCaptureValue(void);

/*
 * [Function Name]: Icu_clearTimerValue
 * [Function Description]: clears timer 1 value to start counting from 0
 * [Args]:
 * [in]: void
 * [Return]: void
 */
void Icu_clearTimerValue(void);

/*
 * [Function Name]: Icu_clearTimerValue
 * [Function Description]: disables timer 1 and icu module
 * [Args]:
 * [in]: void
 * [Return]: void
 */
void Icu_deInit(void);

#endif /* __ICU_H__ */
