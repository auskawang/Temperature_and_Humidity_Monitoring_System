/*
 * i2clcd.h
 *
 *  Created on: Dec 18, 2024
 *      Author: auska
 */

#ifndef INC_I2CLCD_H_
#define INC_I2CLCD_H_

/* Function prototypes ------------------------------------------------------------------*/
void lcd_init();
void send_cmd(char);
void send_data(char);
void printString(char[]);
void clear_display();
void carriage_return();

#endif /* INC_I2CLCD_H_ */
