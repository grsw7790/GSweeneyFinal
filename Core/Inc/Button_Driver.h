/*
 * Button_Driver.h
 *
 *  Created on: Feb 11, 2025
 *      Author: griff
 */

#ifndef BUTTON_DRIVER_H_
#define BUTTON_DRIVER_H_
 
#include <InterruptControl.h>
//#include "stm32f4xx_hal.h"
#include "stdbool.h"
 
#define BUTTON_PIN_NUM		GPIO_PIN_0
#define BUTTON_PRESSED		1
#define BUTTON_UNPRESSED	0
 
 //void ButtonInit();
bool CheckButtonPress();
void ButtonIntInit();
GPIO_PinState HAL_GPIO_ReadPin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void HAL_GPIO_Init(GPIO_TypeDef  *GPIOx, GPIO_InitTypeDef *GPIO_Init);

#endif /* BUTTON_DRIVER_H_ */
 