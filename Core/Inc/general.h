/**
 * @file general.h
 * @author Auska Wang
 *
 * @brief Header file of general.c
 *        This file contains
 *        - macros of pins and ports for connected hardware
 *        - general purpose functions such as microsecond delays
 *        Used for other modules that require these general functions.
 */

#ifndef INC_GENERAL_H_
#define INC_GENERAL_H_

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include "stm32c0xx_hal.h"

/**
 * @brief Pins and ports for hardware for configuration purposes.
 */
#define DHT22_Port GPIOA
#define DHT22_Pin GPIO_PIN_9
#define UNITS_Button_Port GPIOA
#define UNITS_Button_Pin GPIO_PIN_7
#define ON_OFF_Button_Port GPIOB
#define ON_OFF_Button_Pin GPIO_PIN_0
#define LIGHT_Button_Pin GPIO_PIN_3
#define LIGHT_Button_Port GPIOB

/**
 * @brief Input or output for pin configuration.
 */
typedef enum {
	GPIO_INPUT 		= 0,
	GPIO_OUTPUT 	= 1
} GPIO_Mode;

/* Function prototypes ------------------------------------------------------------------*/
void hardware_init();
void micro_delay(int microseconds);
void set_pin_mode(GPIO_TypeDef* GPIOx, uint16_t pin, GPIO_Mode mode);
void Error_Handler();

#endif /* INC_GENERAL_H_ */
