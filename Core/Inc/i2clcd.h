/*
 * i2clcd.h
 *
 *  Created on: Dec 18, 2024
 *      Author: auska
 */

#ifndef INC_I2CLCD_H_
#define INC_I2CLCD_H_

#include <stdint.h>
/* Function prototypes ------------------------------------------------------------------*/
//void lcd_init();
//void send_data(char, uint8_t);
//void printString(char[], uint8_t);
//void clear_display();
//void carriage_return();
//void display_off();
//void display_on();
//void EXTI2_3_IRQHandler_Extended();

#ifdef __cplusplus
class I2CLCD {
	private:
		uint8_t lightmode = 1;
		void send_cmd (char cmd);
	public:
		void lcd_init();
		void clear_display();
		void carriage_return();
		void printString(char str[]);
};
#endif

#endif /* INC_I2CLCD_H_ */
