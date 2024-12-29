/**
 * @file dht22.h
 * @brief Header file of dht22.c
 * @author Auska Wang
 * @date August 2024
 */

#ifndef INC_DHT22_H_
#define INC_DHT22_H_

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>

typedef enum {
	DHT22_RESPONSE_FAIL = 0,
	DHT22_RESPONSE_SUCCESSFUL = 1
} DHT22_Status;

typedef enum {
	FAHRENHEIT = 0,
	CELSIUS = 1
} TEMP_UNITS;

typedef enum {
	OFF = 0,
	ON = 1
} DISPLAY_MODE;

/* Function prototypes ------------------------------------------------------------------*/
void printTemperatureAndHumidityData();
void TIM14_IRQHandler_Extended();
void EXTI0_1_IRQHandler_Extended();
void EXTI4_15_IRQHandler_Extended();


#endif /* INC_DHT22_H_ */
