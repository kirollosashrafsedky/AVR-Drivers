 /******************************************************************************
 *
 * Module: PUSH BUTTON
 *
 * File Name: button-config.h
 *
 * Description: Config file for the PUSH BUTTON driver
 *
 * Author: Kirollos Ashraf
 *
 *******************************************************************************/

#ifndef __BUTTON_CONFIG_H__
#define __BUTTON_CONFIG_H__

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

/* number of push buttons used in the project.
 * used as a size for an array holding all initialized buttons.
 * If BUTTONS_USED_COUNT = 1, the functions will not require the button index
 * so button config must be set below
 */
#define BUTTONS_USED_COUNT								2

#if BUTTONS_USED_COUNT == 1

/* the pin the push button is connected to
 * available only if BUTTONS_USED_COUNT = 1
 */
#define BUTTON_PIN										PD2

/* describes the connection of the push button
 * can be BUTTON_ACTIVE_HIGH => conneccts to high when pressed
 * or BUTTON_ACTIVE_LOW => conneccts to low when pressed
 */
#define BUTTON_CONNECTION								BUTTON_ACTIVE_LOW

/* describes the button internal pull
 * can be BUTTON_NO_PULL, BUTTON_PULL_UP, BUTTON_PULL_DOWN
 * note that BUTTON_PULL_UP and BUTTON_PULL_DOWN must be supported on the mcu to use them
 */
#define BUTTON_INTERNAL_PULL							BUTTON_PULL_UP

#endif /* BUTTONS_USED_COUNT == 1 */

/* if BUTTON_CHECK_DEBOUNCE_ENABLED = 1 => the module will add a delay
 * of BUTTON_CHECK_DEBOUNCE_DELAY_MS to prevent debounce effect,
 * if BUTTON_CHECK_DEBOUNCE_ENABLED = 0, the module won't check for debounces
 */
#define BUTTON_CHECK_DEBOUNCE_ENABLED					0

/* only used if BUTTON_CHECK_DEBOUNCE_ENABLED = 1, used to specify
 * the time in ms used in check debounce delay
 */
#define BUTTON_CHECK_DEBOUNCE_DELAY_MS					30

/* enable or disable interrupt functions for the button
 * if BUTTON_INTERRUPT_ENABLE = 1, then EXT_INT module is required
 */
#define BUTTON_INTERRUPT_ENABLE							1

#endif /* __BUTTON_CONFIG_H__ */
