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

/* Includes */
#include "main.h"
#include "general.h"
#include "lcd_data_display.h"
#include <stdio.h>
#include <string.h>

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
	hardware_init();
	print_temp_and_humidity_data();
    while (1)
    {
    }
}



