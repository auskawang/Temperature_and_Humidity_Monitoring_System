/*
 * i2clcd.c
 *
 *  Created on: Dec 18, 2024
 *      Author: auska
 */

#include "i2clcd.h"
#include "main.h"
#include "general.h"
#include "dht22.h"
#include <stdio.h>
#include <string.h>
#define PCF8574_ADDR 0x27 << 1
#define UPPER_BITS_MASK 0xF0
#define INSTRUCTION_REGISTER_ENABLE_ON_LIGHT_ON 0x0C
#define INSTRUCTION_REGISTER_ENABLE_OFF_LIGHT_ON 0x08
#define DATA_REGISTER_ENABLE_ON_LIGHT_ON 0x0D
#define DATA_REGISTER_ENABLE_OFF_LIGHT_ON 0x09
#define INSTRUCTION_REGISTER_ENABLE_ON_LIGHT_OFF 0x04
#define INSTRUCTION_REGISTER_ENABLE_OFF_LIGHT_OFF 0x01
#define DATA_REGISTER_ENABLE_ON_LIGHT_OFF 0x05
#define DATA_REGISTER_ENABLE_OFF_LIGHT_OFF 0x01
#define BIT_MODE_4 4
extern I2C_HandleTypeDef hi2c1;
extern UART_HandleTypeDef huart2;
uint8_t light_mode = 1; //off = 0, on = 1

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
}
void clear_display()
{
	send_cmd(0x01);
	microDelay(2000);
}
void carriage_return()
{
	send_cmd(0xC0);
	microDelay(1000);
}
void send_cmd (char cmd)
{
	uint8_t t[BIT_MODE_4];
	char u, l;

	u = cmd & UPPER_BITS_MASK;
	l = (cmd << 4) & UPPER_BITS_MASK;
	t[0] = u | (light_mode ? INSTRUCTION_REGISTER_ENABLE_ON_LIGHT_ON : INSTRUCTION_REGISTER_ENABLE_ON_LIGHT_OFF); //rs = 0, e = 1
	t[1] = u | (light_mode ? INSTRUCTION_REGISTER_ENABLE_OFF_LIGHT_ON : INSTRUCTION_REGISTER_ENABLE_OFF_LIGHT_OFF); // rs = 0, e = 0
	t[2] = l | (light_mode ? INSTRUCTION_REGISTER_ENABLE_ON_LIGHT_ON : INSTRUCTION_REGISTER_ENABLE_ON_LIGHT_OFF); //rs = 0, e = 1
	t[3] = l | (light_mode ? INSTRUCTION_REGISTER_ENABLE_OFF_LIGHT_ON : INSTRUCTION_REGISTER_ENABLE_OFF_LIGHT_OFF); // rs = 0, e = 0

	if (HAL_I2C_Master_Transmit(&hi2c1, PCF8574_ADDR, t, sizeof(t), HAL_MAX_DELAY) != HAL_OK)
		Error_Handler();
}
void send_data (char data)
{
	uint8_t t[BIT_MODE_4];
	char u, l;

	u = data & UPPER_BITS_MASK;
	l = (data << 4) & UPPER_BITS_MASK;
	t[0] = u | (light_mode ? DATA_REGISTER_ENABLE_ON_LIGHT_ON : DATA_REGISTER_ENABLE_ON_LIGHT_OFF); //rs = 1, e = 1
	t[1] = u | (light_mode ? DATA_REGISTER_ENABLE_OFF_LIGHT_ON : DATA_REGISTER_ENABLE_OFF_LIGHT_OFF); // rs = 1, e = 0
	t[2] = l | (light_mode ? DATA_REGISTER_ENABLE_ON_LIGHT_ON : DATA_REGISTER_ENABLE_ON_LIGHT_OFF); //rs = 1, e = 1
	t[3] = l | (light_mode ? DATA_REGISTER_ENABLE_OFF_LIGHT_ON : DATA_REGISTER_ENABLE_OFF_LIGHT_OFF); // rs = 1, e = 0

	if (HAL_I2C_Master_Transmit(&hi2c1, PCF8574_ADDR, t, sizeof(t), HAL_MAX_DELAY) != HAL_OK)
		Error_Handler();
}
void printString(char str[])
{
	for (int i = 0; i < strlen(str); i++)
	{
		send_data(str[i]);
	}
}
void EXTI2_3_IRQHandler_Extended()
{
	light_mode = !light_mode;
	printTemperatureAndHumidityData();
	__HAL_GPIO_EXTI_CLEAR_RISING_IT(LIGHT_Button_Pin);

}
