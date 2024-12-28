#include "main.h"
#include <stdint.h>


#ifndef INC_GENERAL_H_
#define INC_GENERAL_H_

/* Defines ------------------------------------------------------------------*/
#define DHT22_Port GPIOA
#define DHT22_Pin GPIO_PIN_9
#define EXTI_Button_Port GPIOA
#define EXTI_Button_Pin GPIO_PIN_7
#define ON_OFF_Button_Port GPIOB
#define ON_OFF_Button_Pin GPIO_PIN_0
#define LIGHT_Button_Pin GPIO_PIN_3
#define LIGHT_Button_Port GPIOB


/* Function prototypes ------------------------------------------------------------------*/
void bsp_init();
void microDelay(int microseconds);
void setPinOutput(GPIO_TypeDef* GPIOx, uint16_t pin);
void setPinInput(GPIO_TypeDef* GPIOx, uint16_t pin);
uint16_t combineBytes(uint8_t left, uint8_t right);
static void MX_TIM3_Init(void);
static void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
//static void MX_USART1_UART_Init(void);
//static void RTC_Config(void);

#endif /* INC_GENERAL_H_ */
