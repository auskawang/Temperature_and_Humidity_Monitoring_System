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

/* Function prototypes ------------------------------------------------------------------*/
void DHT22_start();
int DHT22_response();
uint8_t DHT22_read();
void DHT22_getData();
void printData();
float getTemperatureC(uint8_t t1, uint8_t t2);
float getTemperatureF(uint8_t t1, uint8_t t2);
float getHumidity(uint8_t h1, uint8_t h2);


#endif /* INC_DHT22_H_ */
