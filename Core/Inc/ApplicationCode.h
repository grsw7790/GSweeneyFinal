/*
 * ApplicationCode.h
 *
 *  Created on: Dec 30, 2023
 *      Author: Xavion
 */

#include <Scheduler.h>
#include <Graphics_Driver.h> 
#include <LCD_Driver.h>
#include <Button_Driver.h>
#include <Gameplay_Driver.h>
#include "stdio.h"

#ifndef INC_APPLICATIONCODE_H_
#define INC_APPLICATIONCODE_H_

void ApplicationInit(void);
void AppDispBoard(uint8_t board[][NUM_COL]); // used for testing to bypass gameplay
void AppRedMove(uint8_t col_full[NUM_COL], uint8_t board[][NUM_COL], uint8_t col);
void AppYellowMove(uint8_t col_full[NUM_COL], uint8_t board[][NUM_COL], uint8_t col);
uint8_t AI_Helper(uint8_t board[][NUM_COL], uint8_t free[][2], uint8_t index);
uint8_t App_AI_Move(uint8_t col_full[NUM_COL], uint8_t board[][NUM_COL]);
STMPE811_TouchData AppLCDpoll();

#endif /* INC_APPLICATIONCODE_H_ */
