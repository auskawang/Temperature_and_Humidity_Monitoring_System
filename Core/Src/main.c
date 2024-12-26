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

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "dht22.h"
#include "general.h"
#include "i2clcd.h"
#include <stdio.h>
#include <string.h>
#define DHT22_READ_DELAY_MS 2000 //required 2 second delay between readings
/**
 * @brief main
 *
 * This function serves as the entry point of the program
 *
 * @param None
 * @return None
 */
static void system_init()
{
	bsp_init();	//initializes the hardware of STM32 NUCLEOC031C6
	lcd_init(); //initializes the lcd
}
int main(void)
{
	system_init();
    while (1)
    {
    	printTemperatureAndHumidityData();	//prints temperature and humidity data through serial
		HAL_Delay(DHT22_READ_DELAY_MS);	//wait for 2 seconds
    }
}

/**
 * @brief Error Handler
 *
 * This function handles errors where the program is forced into an endless loop
 *
 * @param None
 * @return None
 */
void Error_Handler(void)
{

  __disable_irq();
  while (1)
  {
  }

}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
