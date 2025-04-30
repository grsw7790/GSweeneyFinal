/*
 * RNG_Driver.c
 *
 *  Created on: Apr 23, 2025
 *      Author: griff
 */

#include <RNG_Driver.h>

void RNG_Init()
{
    RNG_HandleTypeDef rng;
	rng.Instance = RNG;
}

bool RNG_isDataReady()
{

}