/**
 * @file dht22.h
 * @author Auska Wang
 * @brief Header file of dht22.c
 * 	      This file contains
 * 	      - DHT22 class with functions to get temperature and humidity data
 */

#ifndef INC_DHT22_H_
#define INC_DHT22_H_

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>

/**
 * @brief Status of DHT22 during communication process.
 */
typedef enum {
	DHT22_RESPONSE_FAIL			= 0,
	DHT22_RESPONSE_SUCCESSFUL 	= 1
} DHT22_Status;

/**
 * @brief Holds data bytes acquired from DHT22.
 */
typedef struct {
	uint8_t temp_first_byte;
	uint8_t temp_second_byte;
	uint8_t humidity_first_byte;
	uint8_t humidity_second_byte;
	uint8_t check_byte;
} DHT22_Data;

#ifdef __cplusplus
class DHT22 {
	private:
		DHT22_Status status;
		DHT22_Data data;
		void DHT22_start(void);
		void DHT22_getData();
	public:
		float getTemperatureC();
		float getTemperatureF();
		float getHumidity();
};
#endif

#endif /* INC_DHT22_H_ */


