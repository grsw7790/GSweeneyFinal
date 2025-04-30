/*
 * RNG_Driver.h
 *
 *  Created on: Apr 23, 2025
 *      Author: griff
 */

#ifndef RNG_DRIVER_H_
#define RNG_DRIVER_H_

#include "stm32f4xx_hal.h"
#include "stdbool.h"

#define CR_CONFIG           (RNG_CR_RNGEN)
#define DATA_READY          1
#define DATA_NOT_READY      0

void RNG_Init();
bool RNG_isDataReady();
uint32_t RNG_getRN();
HAL_StatusTypeDef HAL_RNG_Init(RNG_HandleTypeDef *hrng);
HAL_StatusTypeDef HAL_RNG_GenerateRandomNumber(RNG_HandleTypeDef *hrng, uint32_t *random32bit);
uint32_t HAL_RNG_ReadLastRandomNumber(const RNG_HandleTypeDef *hrng);

#endif /* RNG_DRIVER_H_ */