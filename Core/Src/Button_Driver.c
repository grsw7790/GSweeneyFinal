/*
 * Button_Driver.c
 *
 *  Created on: Feb 11, 2025
 *      Author: griff
 */
#include <Button_Driver.h>

bool CheckButtonPress()
{return HAL_GPIO_ReadPin(GPIOA, BUTTON_PIN_NUM);}

void ButtonInit()
{
	GPIO_InitTypeDef button;
	button.Pin = BUTTON_PIN_NUM;
	button.Mode = GPIO_MODE_IT_RISING_FALLING;
	button.Speed = GPIO_SPEED_FREQ_MEDIUM;
	button.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA, &button);
	//HAL_NVIC_EnableIRQ(EXTI0_IRQn);
}