/**
 * @file lcd_data_display.h
 * @author Auska Wang
 *
 * @brief Header file of lcd_data_display.c
 *        This file contains
 *        - Enums for flag naming purposes
 *        - ISR for EXTI interrupts through button presses
 *        - ISR for recurring timer interrupts
 */

#ifndef LCD_DATA_DISPLAY_H_
#define LCD_DATA_DISPLAY_H_

/**
 * @brief Display on or off.
 */
typedef enum {
	OFF 		= 0,
	ON 			= 1
} DISPLAY_MODE;

/**
 * @brief Temperature unit displayed on LCD.
 */
typedef enum {
	FAHRENHEIT 		= 0,
	CELSIUS 		= 1
} TEMP_UNITS;

/* Function prototypes ------------------------------------------------------------------*/
void print_temp_and_humidity_data();
void TIM14_IRQHandler_Extended();
void EXTI0_1_IRQHandler_Extended();
void EXTI2_3_IRQHandler_Extended();
void EXTI4_15_IRQHandler_Extended();

#endif /* LCD_DATA_DISPLAY_H_ */
