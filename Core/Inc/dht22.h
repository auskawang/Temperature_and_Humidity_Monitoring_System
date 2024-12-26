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

/* Function prototypes ------------------------------------------------------------------*/
static void DHT22_start();
static DHT22_Status DHT22_response();
static uint8_t DHT22_read();
static void DHT22_getData();
void printTemperatureAndHumidityData();
static float getTemperatureC(uint8_t t1, uint8_t t2);
static float getTemperatureF(uint8_t t1, uint8_t t2);
static float getHumidity(uint8_t h1, uint8_t h2);


#endif /* INC_DHT22_H_ */
