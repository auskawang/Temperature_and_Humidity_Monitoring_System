/**
 * @file lcd_data_display.c
 * @author Auska Wang
 * @brief Contains function that prints data to LCD.
 */

#include <string.h>
#include <stdio.h>
#include "lcd_data_display.h"
#include "general.h"
#include "i2clcd.h"
#include "dht22.h"

/* Defines */
#define LCD_DISPLAY_LENGTH 16
#define HUMIDITY_MEASUREMENT_OFFSET -7.0


/* Variables */
extern TIM_HandleTypeDef htim14;

TEMP_UNITS temp_units = FAHRENHEIT;
DISPLAY_MODE display_mode = ON;
uint8_t light_mode = 1; //off = 0, on = 1

/**
 * @brief Prints temperature and humidity data to LCD.
 *
 * @param None
 * @return none
 */
void print_temp_and_humidity_data()
{
	DHT22_Data data;
	DHT22_getData(&data);
	volatile float temperature = (temp_units == FAHRENHEIT) ? getTemperatureF(data.temp_first_byte, data.temp_second_byte) : getTemperatureC(data.temp_first_byte, data.temp_second_byte);
	volatile float humidity = getHumidity(data.humidity_first_byte, data.humidity_second_byte) + HUMIDITY_MEASUREMENT_OFFSET;	//software calibration

	char buffer[LCD_DISPLAY_LENGTH] = {0};
	clear_display();
	snprintf(buffer, sizeof(buffer), "Temp: %.2f", temperature);
	buffer[strlen(buffer)] = 0xDF;
	buffer[strlen(buffer)] = (temp_units == FAHRENHEIT) ? 'F' : 'C';
	printString(buffer, light_mode);
	carriage_return();
	snprintf(buffer, sizeof(buffer), "Humidity: %.2f", humidity);
	buffer[strlen(buffer)] = '%';
	printString(buffer, light_mode);
}

/**
 * @brief ISR for TIM14
 *
 * Timer is set so that every two seconds, LCD updates temperature and humidity information.
 * @param None
 * @return none
 */
void TIM14_IRQHandler_Extended()
{
	print_temp_and_humidity_data();
	HAL_TIM_IRQHandler(&htim14);

}

/**
 * @brief ISR for EXTI2_3 interrupts
 *
 * An interrupt will toggle the back light of the LCD, linked to PB3, rising edge
 * @param None
 * @return none
 */
void EXTI2_3_IRQHandler_Extended()
{
	micro_delay(50000); //debouncing
	micro_delay(50000); //debouncing
	micro_delay(50000); //debouncing

	light_mode = !light_mode;
	print_temp_and_humidity_data();
	__HAL_GPIO_EXTI_CLEAR_RISING_IT(LIGHT_Button_Pin);
}

/**
 * @brief ISR for EXTI4_15 interrupts
 *
 * An interrupt will toggle the units for temperature, linked to PA7, rising edge
 * @param None
 * @return none
 */
void EXTI4_15_IRQHandler_Extended()
{
	micro_delay(50000); //debouncing
	micro_delay(50000); //debouncing
	micro_delay(50000); //debouncing

	if (display_mode == ON)
	{
		temp_units = (temp_units == FAHRENHEIT) ? CELSIUS : FAHRENHEIT;
		print_temp_and_humidity_data();
	}

	__HAL_GPIO_EXTI_CLEAR_RISING_IT(UNITS_Button_Pin);
}
