#include "main.h"
#include <stdint.h>


#ifndef INC_GENERAL_H_
#define INC_GENERAL_H_

/* Defines ------------------------------------------------------------------*/
#define DHT22_Port GPIOA
#define DHT22_Pin GPIO_PIN_9

/* Function prototypes ------------------------------------------------------------------*/
void bsp_init();
void microDelay(int microseconds);
void setPinOutput(GPIO_TypeDef* GPIOx, uint16_t pin);
void setPinInput(GPIO_TypeDef* GPIOx, uint16_t pin);
uint16_t combineBytes(uint8_t left, uint8_t right);
void MX_TIM3_Init(void);
void SystemClock_Config(void);
void MX_GPIO_Init(void);
void MX_USART2_UART_Init(void);
void MX_USART1_UART_Init(void);
void RTC_Config(void);

#endif /* INC_GENERAL_H_ */
