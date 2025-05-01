/*
 * ApplicationCode.h
 *
 *  Created on: Dec 30, 2023
 *      Author: Xavion
 */

#include <Scheduler.h>
#include <Graphics_Driver.h> // final version should comment this out. here for testing now (maybe not)
#include <LCD_Driver.h>
#include <Button_Driver.h>
#include <Gameplay_Driver.h>
//#include "stm32f4xx_hal.h"
//#include "stm32f4xx_hal_rng.h"
#include "stdio.h"

#ifndef INC_APPLICATIONCODE_H_
#define INC_APPLICATIONCODE_H_

// bit masks to determine coords of touch
#define TOUCH_Y     0xFFFF
#define TOUCH_X     (TOUCH_Y << 16)

void ApplicationInit(void);
//void LCD_Visual_Demo(void);

void AppDispBoard(uint8_t board[][NUM_COL]); // used for testing to bypass gameplay
void AppRedMove(uint8_t col_full[NUM_COL], uint8_t board[][NUM_COL], uint8_t col);
void AppYellowMove(uint8_t col_full[NUM_COL], uint8_t board[][NUM_COL], uint8_t col);
uint8_t AI_Helper(uint8_t board[][NUM_COL], uint8_t free[][2], uint8_t index);
uint8_t App_AI_Move(uint8_t col_full[NUM_COL], uint8_t board[][NUM_COL]);
STMPE811_TouchData AppLCDpoll();

// #if (COMPILE_TOUCH_FUNCTIONS == 1)
// void LCD_Touch_Polling_Demo(void);
// #endif // (COMPILE_TOUCH_FUNCTIONS == 1)

#endif /* INC_APPLICATIONCODE_H_ */
