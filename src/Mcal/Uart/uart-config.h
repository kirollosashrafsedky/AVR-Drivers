/******************************************************************************
 *
 * Module: UART
 *
 * File Name: uart-config.h
 *
 * Description: Config file for the AVR UART driver
 *
 * Author: Kirollos Ashraf
 *
 *******************************************************************************/

#ifndef __UART_CONFIG_H__
#define __UART_CONFIG_H__

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

/* used in UART_receiveString function to recieve string
 * till this character is found before reaching the maximum size of the array
 */
#define UART_RECIEVE_STRING_TILL			'\r'

#endif /* __UART_CONFIG_H__ */
