/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

#ifdef __cplusplus
extern "C" {
#endif

/* Includes */
#include "main.h"
#include "general.h"
#include "dht22.h"
#include "i2clcd.h"
#include <stdio.h>
#include <string.h>


DHT22 dht22;
I2CLCD i2clcd;
/**
 * @brief main
 *
 * This function serves as the entry point of the program
 *
 * @param None
 * @return None
 */
int main(void)
{
	hardware_init(); //contains hardware initialization for this specific board
	i2clcd.lcd_init();	//initializes LCD
    while (1)
    {
    	float temperature = dht22.getTemperatureF();
    	char buffer[16];
    	snprintf(buffer, 16, "%.2f", temperature);
		i2clcd.clear_display();
    	i2clcd.printString(buffer);
    	HAL_Delay(2000);
    }
}

#ifdef __cplusplus
}
#endif



