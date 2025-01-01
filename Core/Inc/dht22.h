/**
 * @file dht22.h
 * @author Auska Wang
 * @brief Header file of dht22.c
 * 	      This file contains
 * 	      - the functions necessary to extract
 * 	      temperature and humidity readings from DHT22 sensor.
 * 	      - DHT22_Data struct to consolidate
 * 	      data bytes, making the process of obtaining data bytes
 * 	      more intuitive for other modules.
 */

#ifndef INC_DHT22_H_
#define INC_DHT22_H_

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>

/**
 * @brief Status of DHT22 used during communication process.
 */
typedef enum {
	DHT22_RESPONSE_FAIL			= 0,
	DHT22_RESPONSE_SUCCESSFUL 	= 1
} DHT22_Status;

/**
 * @brief Holds data bytes sent by DHT22.
 */
typedef struct {
	uint8_t temp_first_byte;
	uint8_t temp_second_byte;
	uint8_t humidity_first_byte;
	uint8_t humidity_second_byte;
	uint8_t check_byte;
} DHT22_Data;

/* Function prototypes ------------------------------------------------------------------*/
void DHT22_getData(DHT22_Data* data);
float getTemperatureC(uint8_t, uint8_t);
float getTemperatureF(uint8_t, uint8_t);
float getHumidity(uint8_t, uint8_t);

#endif /* INC_DHT22_H_ */
