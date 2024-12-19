/*
 * i2clcd.c
 *
 *  Created on: Dec 18, 2024
 *      Author: auska
 */

#include "i2clcd.h"
#include "main.h"
#include "general.h"
#include <stdio.h>
#include <string.h>
#define PCF8574_ADDR 0x27 << 1

extern I2C_HandleTypeDef hi2c1;
extern UART_HandleTypeDef huart2;

void lcd_init()
{
	  HAL_Delay(30);
	  send_cmd(0x30);
	  HAL_Delay(5);
	  send_cmd(0x30);
	  HAL_Delay(1);
	  send_cmd(0x30);
	  HAL_Delay(1);
	  send_cmd(0x20);
	  HAL_Delay(1);

	  send_cmd(0x28);
	  HAL_Delay(1);
	  send_cmd(0x08);
	  HAL_Delay(1);
	  send_cmd(0x01);
	  HAL_Delay(1);
	  send_cmd(0x06);
	  HAL_Delay(1);
	  send_cmd(0x0C);
	  HAL_Delay(1);

	  printString("Done!");
}
void clear_display()
{
	send_cmd(0x01);
	HAL_Delay(2);
}
void carriage_return()
{
	send_cmd(0xC0);
	HAL_Delay(1);
}
void send_cmd (char cmd)
{
	uint8_t t[4];
	char u, l;

	u = cmd & 0xF0;
	l = (cmd << 4) & 0xF0;
	t[0] = u | 0x0C; //rs = 0, e = 1
	t[1] = u | 0x08; // rs = 0, e = 0
	t[2] = l | 0x0C; //rs = 0, e = 1
	t[3] = l | 0x08; // rs = 0, e = 0

	if (HAL_I2C_Master_Transmit(&hi2c1, PCF8574_ADDR, t, 4, HAL_MAX_DELAY) != HAL_OK)
		Error_Handler();
}
void send_data (char data)
{
	uint8_t t[4];
	char u, l;

	u = data & 0xF0;
	l = (data << 4) & 0xF0;
	t[0] = u | 0x0D; //rs = 1, e = 1
	t[1] = u | 0x09; // rs = 1, e = 0
	t[2] = l | 0x0D; //rs = 1, e = 1
	t[3] = l | 0x09; // rs = 1, e = 0

	if (HAL_I2C_Master_Transmit(&hi2c1, PCF8574_ADDR, t, 4, HAL_MAX_DELAY) != HAL_OK)
		Error_Handler();
}
void printString(char str[])
{
	for (int i = 0; i < strlen(str); i++)
	{
		send_data(str[i]);
	}
}
