 /******************************************************************************
 *
 * Module: LED
 *
 * File Name: led-config.h
 *
 * Description: Config file for the LED driver
 *
 * Author: Kirollos Ashraf
 *
 *******************************************************************************/

#ifndef __LED_CONFIG_H__
#define __LED_CONFIG_H__

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

/* number of leds used in the project.
 * used as a size for an array holding all initialized leds.
 * If LEDS_USED_COUNT = 1, the functions will not require the led index
 * so pin number and led logic must be set below
 */
#define LEDS_USED_COUNT						2

#if LEDS_USED_COUNT == 1

/* the pin the led is connected to
 * available only if LEDS_USED_COUNT = 1
 */
#define LED_PIN								PD4

/* the logic of the led connection
 * can be LED_POSITIVE_LOGIC or LED_NEGATIVE_LOGIC
 * available only if LEDS_USED_COUNT = 1
 */
#define LED_LOGIC							LED_NEGATIVE_LOGIC

#endif /* LEDS_USED_COUNT == 1 */

/* indicates whether to include pwm module to control brightness or not
 * if 1 => pwm will be included and you can access LED_dim() function
 * if 0 => LED_dim() function won't be supported
 */
#define PWM_FOR_DIMMING_SUPPORTED			1

/* led initial state can be
 * LED_ON
 * LED_OFF
 */
#define LED_INITIAL_STATE					LED_OFF

#endif /* __LED_CONFIG_H__ */
