/**
 * @file dht22.c
 * @brief Functions for interfacing with the DHT22 temperature and humidity sensor
 * @author Auska Wang
 * @date August 2024
 */

/* Includes ------------------------------------------------------------------*/
#include <string.h>
#include <stdio.h>
#include "dht22.h"
#include "main.h"
#include "general.h"
#include "i2clcd.h"

#define LCD_DISPLAY_LENGTH 16
#define BITS_IN_BYTE 8
#define HUMIDITY_MEASUREMENT_OFFSET -7.0
extern UART_HandleTypeDef huart2;


//variables for extreme temp measurements
//float highTemp = 0.0f;
//float lowTemp = 100.0f;
//float highHumidity = 0.0f;
//float lowHumidity = 100.0f;
//uint8_t highTempHour, highTempMin, lowTempHour, lowTempMin, highHumidityHour, highHumidityMin, lowHumidityHour, lowHumidityMin;

uint8_t h1, 	//first byte of humidity data
		h2, 	//second byte of humidity data
		t1, 	//first byte of temperature data
		t2, 	//second byte of temperature data
		check;	//checksum byte to ensure data integrity

uint8_t temp_units = 0;
/**
 * @brief Initializes the DHT22 sensor.
 *
 * This function sends the start signal to the DHT22 sensor and switches the GPIO pin to input mode.
 *
 * @param None
 * @return None
 */
static void DHT22_start()
{
	setPinOutput(DHT22_Port, DHT22_Pin);

	//MCU pulls the data line low for at least 1 - 10 ms
	HAL_GPIO_WritePin(DHT22_Port, DHT22_Pin, 0);
	microDelay(5000); //5 ms delay

	//MCU pulls the data line high and waits 20 - 40 us for DHT22 response
	HAL_GPIO_WritePin(DHT22_Port, DHT22_Pin, 1);
	microDelay(30);	//30 us delay

	setPinInput(DHT22_Port, DHT22_Pin);	//switch to input mode to detect response from DHT22 sensor
}

/**
 * @brief Confirms the responsiveness of DHT22 sensor.
 *
 * This function waits and senses for the response from DHT22 sensor.
 *
 * @param None
 * @return int response
 */
static DHT22_Status DHT22_response()
{
	DHT22_Status response = DHT22_RESPONSE_FAIL;	//flag that shows whether responsiveness of DHT22 sensor, 0 if failed, 1 if successful

	//sensor will pull the data line low for 80 us
	microDelay(40);	//40 us delay

	//check if data line is low with 40 us left of pulling the data line low
	if (!HAL_GPIO_ReadPin(DHT22_Port, DHT22_Pin))
	{
		//sensor will then pull the data line high for 80 us
		microDelay(80);	//delay 80 us

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
 * @brief Acquisition of data bytes
 *
 * This function interprets sensor voltage values and stores and returns byte data
 *
 * @param None
 * @return uint8_t byte
 */
static uint8_t DHT22_read()
{
	uint8_t byte = 0;	//create byte 00000000

	//process bit by bit, for a total of 8 bits, or 1 byte
	for (int i = 0; i < BITS_IN_BYTE; i++)
	{
		//sensor will pull low, wait for high data line for data
		while (!HAL_GPIO_ReadPin(DHT22_Port, DHT22_Pin))
		{}

		//26 - 28 us high means bit value of 0, 70 us high means bit value of 1
		microDelay(40);	//wait for 40 us

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
 * @brief Gets temperature in Celsius
 *
 * This function calculates the temperature in Celsius from two bytes of temperature data
 *
 * @param uint8_t t1, uint8_t t2
 * @return float
 */
float getTemperatureC(uint8_t t1, uint8_t t2)
{
	return combineBytes(t1, t2) / 10.0;	//temperature value should be divided by 10 to get real value
}

/**
 * @brief Gets temperature in Farenheit
 *
 * This function calculates the temperature in Farenheit by converting C to F
 *
 * @param uint8_t t1, uint8_t t2
 * @return float
 */
static float getTemperatureF(uint8_t t1, uint8_t t2)
{
	return 9.0 / 5.0 * (combineBytes(t1, t2) / 10.0) + 32;	//C = 9/5 * F + 32
}

/**
 * @brief Gets humidity
 *
 * This function calculates the humidity in %
 *
 * @param uint8_t h1, uint8_t h2
 * @return float
 */
static float getHumidity(uint8_t h1, uint8_t h2)
{
	return combineBytes(h1, h2) / 10.0;	//humidity value should be divided by 10 to get real value
}

/**
 * @brief Get data from DHT22
 *
 * This function encapsulates the process of initializing and gathering data from sensor, and stores the data into parameters
 *
 * @param uint8_t* h1, uint8_t* h2, uint8_t* t1, uint8_t* t2, uint8_t* check
 * @return none
 */
static void DHT22_getData()
{
	DHT22_start();	//begin process of reading from sensor

	//if sensor is responsive
	if (DHT22_response() == DHT22_RESPONSE_SUCCESSFUL)
	{
	  h1 = DHT22_read();	//first byte from sensor is first byte of humidity data
	  h2 = DHT22_read();	//second byte from sensor is second byte of humidity data
	  t1 = DHT22_read();	//third byte from sensor is first byte of temperature data
	  t2 = DHT22_read();	//fourth byte from sensor is second byte of humidity data
	  check = DHT22_read();//fifth byte from sensor is check sum data
	}

	//if sensor is not responding, give error
	else
	  Error_Handler();
}

/**
 * @brief Print data
 *
 * This function prints out the temperature and humidity data through serial. Optimization is lowest to prevent parameters and variables from being optimized out
 *
 * @param uint8_t* h1, uint8_t* h2, uint8_t* t1, uint8_t* t2
 * @return none
 */

void printTemperatureAndHumidityData()
{
	DHT22_getData();
	volatile float temperature = (temp_units) ? getTemperatureF(t1, t2) : getTemperatureC(t1, t2);
	volatile float humidity = getHumidity(h1, h2) + HUMIDITY_MEASUREMENT_OFFSET;	//software calibration
//	HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
//	HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);



//	if (temperature > highTemp)
//	{
//		highTemp = temperature;
//		highTempHour = sTime.Hours;
//		highTempMin = sTime.Minutes;
//	}
//
//	if (temperature < lowTemp)
//	{
//		lowTemp = temperature;
//		lowTempHour = sTime.Hours;
//		lowTempMin = sTime.Minutes;
//	}
//
//	if (humidity > highHumidity)
//	{
//		highHumidity = humidity;
//		highHumidityHour = sTime.Hours;
//		highHumidityMin = sTime.Minutes;
//	}
//
//	if (humidity < lowHumidity)
//	{
//		lowHumidity = humidity;
//		lowHumidityHour = sTime.Hours;
//		lowHumidityMin = sTime.Minutes;
//	}

	char buffer[LCD_DISPLAY_LENGTH] = {0};
//	snprintf(buffer, sizeof(buffer), "%.2f,%.2f,%.2f,%02d,%02d,%.2f,%02d,%02d,%.2f,%02d,%02d,%.2f,%02d,%02d\n", temperature, humidity, highTemp, highTempHour, highTempMin, lowTemp, lowTempHour, lowTempMin, highHumidity, highHumidityHour, highHumidityMin, lowHumidity, lowHumidityHour, lowHumidityMin);
	clear_display();
	snprintf(buffer, sizeof(buffer), "Temp: %.2f", temperature);
	buffer[strlen(buffer)] = 0xDF;
	buffer[strlen(buffer)] = temp_units ? 'F' : 'C';
	printString(buffer);
	carriage_return();
	snprintf(buffer, sizeof(buffer), "Humidity: %.2f", humidity);
	buffer[strlen(buffer)] = '%';
	printString(buffer);

//	HAL_UART_Transmit(&huart2, (const uint8_t*)buffer, strlen(buffer), HAL_MAX_DELAY);	//send data through serial


}

void HAL_GPIO_EXTI_Rising_Callback(uint16_t GPIO_Pin) {
	temp_units = !temp_units;
	__HAL_GPIO_EXTI_CLEAR_RISING_IT(GPIO_Pin);
}

