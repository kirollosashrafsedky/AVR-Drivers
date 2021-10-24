#include "app.h"
#include "../Mcal/Dio/dio.h"
#include "../Mcal/Timer/timer.h"
#include "../Mcal/Pwm/pwm.h"
#include "../Mcal/External-Interrupt/external-interrupt.h"
#include "../Mcal/WatchDog/watchdog.h"
#include "../Mcal/Adc/adc.h"
#include "../Mcal/Uart/uart.h"
#include "../Mcal/Spi/spi.h"

#include "../Hal/DC-Motor/dc-motor.h"
#include "../Hal/Led/led.h"
#include "../Hal/Button/button.h"
#include "../Hal/Seven-Segment/seven-segment.h"
#include "../Hal/Lcd/lcd.h"
#include "../Hal/LM35/lm35.h"
#include "../Hal/Keypad/keypad.h"

//uint8_t buffer[20], bufferIndex = 0;

void app_init()
{
	/*volatile uint32_t i;*/
	/* Dio and ext. interrupt test */

	/*DIO_pinInit(PA0, PIN_OUTPUT);
	DIO_enablePinInternalPullUp(PD3);
	EXT_INT_enable(PD3, EXT_INT_FALLING_EDGE, interruptHandler);*/
	//	ENABLE_GLOBAL_INTERRUPT();

	/* watch dog timer test */
	/*DIO_pinInit(PA0, PIN_OUTPUT);
	DIO_writePin(PA0, LOW);
	for(i = 0; i < 10000; i++);
	DIO_writePin(PA0, HIGH);*/

	/* timer 0 ovf test */
	/*DIO_pinInit(PA0, PIN_OUTPUT);
	uint32_t ticks = TIME_MS_TO_TICKS(1024, 1000);
	TIMER_config timerConfig = {TIMER_0, TIMER_0_CTC, TIMER_0_PRESCALER_1024, ticks, interruptHandler};
	TIMER_init(&timerConfig);
	TIMER_start(TIMER_0);*/

	/* timer 2 ovf test */
	/*DIO_pinInit(PA0, PIN_OUTPUT);
	uint32_t ticks = TIME_MS_TO_TICKS(1024, 1500);
	TIMER_config timerConfig = {TIMER_2, TIMER_2_OVF, TIMER_2_PRESCALER_1024, ticks, interruptHandler};
	TIMER_init(&timerConfig);
	TIMER_start(TIMER_2);*/

	/* timer 1 ovf test */
	/*DIO_pinInit(PA0, PIN_OUTPUT);
	uint32_t ticks = TIME_MS_TO_TICKS(1, 10000);
	TIMER_config timerConfig = {TIMER_1, TIMER_1_OVF, TIMER_1_PRESCALER_1, ticks, interruptHandler};
	TIMER_init(&timerConfig);
	TIMER_start(TIMER_1);*/

	/* timer 0 ctc test */
	/*DIO_pinInit(PA0, PIN_OUTPUT);
	uint32_t ticks = TIME_MS_TO_TICKS(1024, 1);
	TIMER_config timerConfig = {TIMER_0, TIMER_0_CTC_TOGGLE_OC0, TIMER_0_PRESCALER_1024, ticks, interruptHandler};
	TIMER_init(&timerConfig);
	TIMER_start(TIMER_0);*/

	/* timer 2 ctc test */
	/*DIO_pinInit(PA0, PIN_OUTPUT);
	uint32_t ticks = TIME_MS_TO_TICKS(32, 150);
	TIMER_config timerConfig = {TIMER_2, TIMER_2_CTC_TOGGLE_OC2, TIMER_2_PRESCALER_32, ticks, interruptHandler};
	TIMER_init(&timerConfig);
	TIMER_start(TIMER_2);*/

	/* timer 1 ctc test */
	/*DIO_pinInit(PA0, PIN_OUTPUT);
	uint32_t ticks = TIME_MS_TO_TICKS(1024, 1000);
	TIMER_config timerConfig = {TIMER_1, TIMER_1_CTC_TOGGLE_OC1A_OC1B, TIMER_1_PRESCALER_1024, ticks, interruptHandler};
	TIMER_init(&timerConfig);
	TIMER_start(TIMER_1);*/

	//	ENABLE_GLOBAL_INTERRUPT();
	//	DIO_pinInit(PA0, PIN_OUTPUT);

	/* motor test */
	/*DCMOTOR_init(&motor1);*/

	//	LED_init(PD5, LED_OFF, LED_POSITIVE_LOGIC);
	//	LED_init(PD4, LED_OFF, LED_NEGATIVE_LOGIC);

	/*ST_Led leds[LEDS_USED_COUNT] = {
			{PD5, LED_POSITIVE_LOGIC},
			{PD4, LED_NEGATIVE_LOGIC}
	};
	LED_init(leds);*/

	//	ST_ButtonConfig buttons[BUTTONS_USED_COUNT] = {
	//			{PA0, BUTTON_ACTIVE_LOW, BUTTON_PULL_UP},
	//			{PA1, BUTTON_ACTIVE_HIGH, BUTTON_NO_PULL}
	//	};
	/*BUTTON_init();
	ENABLE_GLOBAL_INTERRUPT();*/
	//	TIMER_DELAY_MS(5000);
	//	BUTTON_detachInterrupt();
	//	LED_dim(0, 25);
	//	LED_dim(1, 75);

	//	LED_init();
	//	LED_on();
	//	LED_off();
	//	LED_toggle();
	//	LED_dim(70);

	/* motor test */
	/*ST_DCMOTOR dcMotor[] = {
			{PC0, PC1, PD4},
			{PC2, PC3, PD5},
	};
	DCMOTOR_init(dcMotor);*/

	/* 7 segment init */
	//	uint8_t sevenSegmentPins[] = {PD4, PD5, PD6, PD7};
	/*uint8_t sevenSegmentPins[] = {PD7, PD6, PD5, PD4};
	SEVEN_SEGMENT_init(sevenSegmentPins);*/
	//	DIO_portInitPartial(PORTA, PORT_OUTPUT, 0xff);
	//	DIO_writePortPartial(PORTA, 0b00001001, 0b00111100, PA1);
	//	DIO_togglePin(PA5);

	/*ST_AdcConfig adcConfig = {
			ADC_AREF, ADC_PRESCALER_8, ADC_INTERRUPT_OFF
	};

	LCD_init();
	ADC_init(&adcConfig);*/
	//	DIO_pinInit(PA0, PIN_INPUT);
	//	KEYPAD_init();

//	LCD_init();
//
//	ST_UartConfig uartConfig = {
//			UART_8_BITS,
//			UART_PARITY_DISABLED,
//			UART_STOP_BIT_1,
//			9600,
//			UART_TX_INTERRUPT_ENABLED,
//			UART_RX_INTERRUPT_ENABLED
//	};
//	UART_init(&uartConfig);
//	DIO_pinInit(PA0, PIN_OUTPUT);
//	UART_setRxInterruptCallback(interruptHandlerRx);
//	UART_setTxInterruptCallback(interruptHandlerTx);
//	ENABLE_GLOBAL_INTERRUPT();
}

void app_update()
{
	/* watch dog timer test */
	/*WATCHDOG_on(WATCHDOG_TIMEOUT_2s);
		for(volatile uint32_t i = 0; i < 200000; i++);
		WATCHDOG_off();*/

	//	DIO_togglePin(PA0);
	//	TIMER_DELAY_MS(1);

	/* pwm test */
	/*PWM_enable(PD4, 80);
	PWM_enable(PD5, 25);
	TIMER_DELAY_MS(1000);*/

	/* motor test */
	/*DCMOTOR_start(&motor1, MOTOR_FORWARD, 20);
	TIMER_DELAY_MS(1000);
	DCMOTOR_stop(&motor1);
	TIMER_DELAY_MS(1000);
	DCMOTOR_start(&motor1, MOTOR_REVERSE, 80);
	TIMER_DELAY_MS(1000);
	DCMOTOR_stop(&motor1);
	TIMER_DELAY_MS(1000);*/

	/* led test */
	//	LED_toggle(PA0);
	//	LED_toggle(PB0);
	//	TIMER_DELAY_MS(200);
	//	LED_dim(PD7, 100);
	//			LED_dim(PD5, 100);
	//	LED_dim(PB3, 99);
	//	LED_dim(PD7, 99);
	//	LED_dim(PB3, 100);
	//	LED_dim(PD7, 100);
	//	TIMER_DELAY_MS(1000);
	//	uint8_t i;
	//			LED_dim(PD4, 0);
	//			LED_dim(PD5, 0);
	//	for(i = 0; i <= 100; i++)
	//	{
	//		LED_dim(PD4, i);
	//		LED_dim(PD5, i);
	//		TIMER_DELAY_MS(5);
	//	}
	////	LED_dim(PD7, 100);
	////	TIMER_DELAY_MS(100);
	//	for(i = 100; i >= 0; i--)
	//	{
	//		LED_dim(PD4, i);
	//		LED_dim(PD5, i);
	//		TIMER_DELAY_MS(5);
	//		if(i == 0) break;
	//	}
	//	TIMER_DELAY_MS(100);

	/* motor test */
	/*DCMOTOR_start(0, DCMOTOR_FORWARD, 100);
	DCMOTOR_start(1, DCMOTOR_REVERSE, 100);
	TIMER_DELAY_MS(2000);
	DCMOTOR_stop(0);
	DCMOTOR_stop(1);
	TIMER_DELAY_MS(2000);
	DCMOTOR_start(0, DCMOTOR_REVERSE, 30);
	DCMOTOR_start(1, DCMOTOR_FORWARD, 30);
	TIMER_DELAY_MS(2000);*/

	/* button test */
	//	if(BUTTON_read(0) == BUTTON_PRESSED)
	//	{
	//		LED_on(0);
	//	}
	//	else
	//	{
	//		LED_off(0);
	//	}
	//	if(BUTTON_read(1) == BUTTON_RELEASED)
	//	{
	//		LED_on(1);
	//	}
	//	else
	//	{
	//		LED_off(1);
	//	}
	/* 7 segment test */
	/*for(uint8_t i = 0; i < 4; i++)
	{
		for(uint8_t j = 0; j < 10; j++)
		{
			SEVEN_SEGMENT_write(i, j);
			TIMER_DELAY_MS(200);
		}
	}
	SEVEN_SEGMENT_clearAll();
	TIMER_DELAY_MS(1000);*/
	/*uint16_t value;
	value = LM35_getTemperature();
	LCD_setCursor(0, 0);
	LCD_sendInteger(value);
	LCD_sendStr("   ");*/


//	uint8_t str[20];
//	UART_receiveString(str, 20);
//	LCD_sendCommand(LCD_CLEAR_SCREEN);
//	LCD_sendStrAt(0, 0, buffer);
//	UART_sendByteBlocking('k');
//	TIMER_DELAY_MS(500);
	//	value = UART_recieveBytePolling();
	//	LCD_sendCharAt(0, 0, value);
	//	TIMER_DELAY_MS(200);
	//	UART_sendBytePolling(value);
}

//void interruptHandlerRx()
//{
//	buffer[bufferIndex] = UART_recieveByteNonBlocking();
//	bufferIndex ++;
//	buffer[bufferIndex] = '\0';
//}
//
//void interruptHandlerTx()
//{
//	DIO_togglePin(PA0);
//}
