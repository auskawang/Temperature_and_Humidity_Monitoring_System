/**
 * @file dht22.c
 * @author Auska Wang
 * @brief Functions for gathering useful with the DHT22 sensor
 */

/* Includes */
#include <string.h>
#include <stdio.h>
#include "dht22.h"
#include "stm32c0xx_hal.h"
#include "general.h"

/* Defines */
#define BITS_IN_BYTE 8 //the number of bits in a byte

/* Variables */
extern UART_HandleTypeDef huart2;
extern TIM_HandleTypeDef htim14;

/**
 * @brief Initializes the DHT22 sensor and prepares for reading from sensor.
 *
 * @param None
 * @return Status of DHT22 after initialization process, which is either success or fail.
 */
static DHT22_Status DHT22_start(void)
{
	set_pin_mode(DHT22_Port, DHT22_Pin, GPIO_OUTPUT);

	//MCU pulls the data line low for at least 1 - 10 ms
	HAL_GPIO_WritePin(DHT22_Port, DHT22_Pin, 0);
	micro_delay(5000); //5 ms delay

	//MCU pulls the data line high and waits 20 - 40 us for DHT22 response
	HAL_GPIO_WritePin(DHT22_Port, DHT22_Pin, 1);
	micro_delay(30);	//30 us delay

	set_pin_mode(DHT22_Port, DHT22_Pin, GPIO_INPUT);	//switch to input mode to detect response from DHT22 sensor

	DHT22_Status response = DHT22_RESPONSE_FAIL;	//flag that shows whether responsiveness of DHT22 sensor, 0 if failed, 1 if successful

		//sensor will pull the data line low for 80 us
		micro_delay(40);	//40 us delay

		//check if data line is low with 40 us left of pulling the data line low
		if (!HAL_GPIO_ReadPin(DHT22_Port, DHT22_Pin))
		{
			//sensor will then pull the data line high for 80 us
			micro_delay(80);	//delay 80 us

			//if successful, data line should still be high since at this moment program is in the middle of sensor pulling data line high
			if (HAL_GPIO_ReadPin(DHT22_Port, DHT22_Pin))
				response = DHT22_RESPONSE_SUCCESSFUL;	//assign response with 1 since response of sensor is successful
		}

		//wait until data line pulls low, where acquisition of data will start
		while (HAL_GPIO_ReadPin(DHT22_Port, DHT22_Pin))
		{}

		return response;
}

/**
 * @brief Reads a byte of data from DHT22.
 *
 * @param None
 * @return Byte of data received from sensor
 */
static uint8_t DHT22_read(void)
{
	uint8_t byte = 0;	//create byte 00000000

	//process bit by bit, for a total of 8 bits, or 1 byte
	for (int i = 0; i < BITS_IN_BYTE; i++)
	{
		//sensor will pull low, wait for high data line for data
		while (!HAL_GPIO_ReadPin(DHT22_Port, DHT22_Pin))
		{}

		//26 - 28 us high means bit value of 0, 70 us high means bit value of 1
		micro_delay(40);	//wait for 40 us

		//if data line is still high, this means that bit value must be 1
		if (HAL_GPIO_ReadPin(DHT22_Port, DHT22_Pin))
			byte |= 1 << (BITS_IN_BYTE - 1 - i);	//place bit value 1 in corresponding position

		//if data line is still high, wait until data line is low
		while (HAL_GPIO_ReadPin(DHT22_Port, DHT22_Pin))
		{}
	}

	return byte;
}

/**
 * @brief Gives decimal value after combining given upper and bottom bytes
 *
 *
 * @param upper Upper byte, lower Lower byte
 * @return Decimal value after combining upper and lower bytes
 */
uint16_t combineBytes(uint8_t upper, uint8_t lower)
{
	return (uint16_t)upper << 8 | (uint16_t)lower;
}

/**
 * @brief Gets temperature in Celsius given two bytes of temperature data
 *
 * @param t1 Upper temperature byte, t2 Lower temperature byte
 * @return The temperature in Celsius
 * @note DHT22 sends temperature to MCU by giving 2 bytes.
 *       If t1 = 0000 0001 and t2 = 0101 1111, combine them to get 0000 0001 0101 1111 = 351,
 *       and finally divide by 10 -> 351 / 10 = 35.1 Celsius
 */
float getTemperatureC(uint8_t t1, uint8_t t2)
{
	return combineBytes(t1, t2) / 10.0;
}

/**
 * @brief Gets temperature in Fahrenheit
 *
 * This function calculates the temperature in Fahrenheit by converting C to F
 *
 * @param t1 Upper temperature byte, t2 Lower temperature byte
 * @return Temperature expressed in Fahrenheit
 */
float getTemperatureF(uint8_t t1, uint8_t t2)
{
	return 9.0 / 5.0 * getTemperatureC(t1, t2) + 32;
}

/**
 * @brief Calculates humidity given upper and lower humidity bytes
 *
 * @param h1 Upper humidity byte, h2 Lower humidity byte
 * @return Humidity value expressed in %
 * @note DHT22 sends humidity value to MCU by giving 2 bytes.
 *       If h1 = 0000 0010 and h2 = 1000 1100, combine them to get 0000 0010 1000 1100 = 652,
 *       and finally divide by 10 -> 652 / 10 = 65.2%
 */
float getHumidity(uint8_t h1, uint8_t h2)
{
	return combineBytes(h1, h2) / 10.0;
}

/**
 * @brief Get data from DHT22
 *
 * This function encapsulates the process of initializing and gathering data from sensor, and stores the data into data struct
 *
 * @param data Pointer to DHT22_Data struct where information will be stored in
 * @return none
 */
void DHT22_getData(DHT22_Data* data)
{
	//if sensor is responsive
	if (DHT22_start() == DHT22_RESPONSE_SUCCESSFUL)
	{
	  data->humidity_first_byte = DHT22_read();	//first byte from sensor is first byte of humidity data
	  data->humidity_second_byte = DHT22_read();	//second byte from sensor is second byte of humidity data
	  data->temp_first_byte = DHT22_read();	//third byte from sensor is first byte of temperature data
	  data->temp_second_byte = DHT22_read();	//fourth byte from sensor is second byte of temperature data
	  data->check_byte = DHT22_read(); //fifth byte from sensor is check sum data
	}

	//if sensor is not responding, give error
	else
	  Error_Handler();
}
