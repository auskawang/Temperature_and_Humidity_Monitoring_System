/**
 * @file i2clcd.c
 * @author Auska Wang
 * @brief Provides functions to interface with LCD.
 */

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "i2clcd.h"
#include "main.h"
#include "general.h"
#include <stdio.h>
#include <string.h>

/* Defines */
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
extern uint8_t light_mode;

/**
 * @brief Initializes LCD display in 4-bit mode according to HD44780 datasheet.
 *
 * @return None
 */
void I2CLCD::lcd_init()
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

/**
 * @brief Clears display of LCD.
 *
 * @return None
 */
void I2CLCD::clear_display()
{
	send_cmd(0x01);
	micro_delay(2000);
}

/**
 * @brief Moves cursor to second line of the LCD.
 *
 * @return None
 */
void I2CLCD::carriage_return()
{
	send_cmd(0xC0);
	micro_delay(1000);
}

/**
 * @brief Turns the LCD display off.
 *
 * @return None
 */
//void display_off()
//{
//	send_cmd(0x08, light_mode);
//	micro_delay(40);
//}

/**
 * @brief Turns the LCD display on.
 *
 * @return None
 */
//void display_on()
//{
//	send_cmd(0x0C, light_mode);
//	micro_delay(40);
//}

/**
 * @brief Sends data to instruction register of LCD.
 *
 * @param cmd Instruction byte to be sent, light_mode Backlight on or off
 * @return None
 */
void I2CLCD::send_cmd (char cmd)
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

/**
 * @brief Sends data to data register of LCD.
 *
 * @param cmd Instruction byte to be sent, light_mode Backlight on or off
 * @return None
 */
void send_data (char data, uint8_t light_mode)
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

/**
 * @brief Prints a given string to the LCD.
 *
 * @param str[] Char array/string to be printed, light_mode Backlight on or off
 * @return None
 */
void I2CLCD::print_string(char str[])
{
	for (int i = 0; i < (uint8_t)strlen(str); i++)
	{
		send_data(str[i], light_mode);
	}
}

#ifdef __cplusplus
}
#endif
