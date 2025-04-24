/*
 * Graphics_Driver.h
 *
 *  Created on: Apr 23, 2025
 *      Author: griff
 */

#ifndef INC_GRAPHICS_DRIVER_H_
#define INC_GRAPHICS_DRIVER_H_

#include <LCD_Driver.h>

// game board values
#define NUM_ROW         7               // because the top I will count as a row to display the piece-to-be-dropped
#define NUM_COL         7
#define ROW_INDICIES    (NUM_ROW - 1)   // to properly do for loop w/o magic numbers
#define COL_INDICIES    (NUM_COL - 1)
#define RED             1
#define YELLOW          2
#define WHITE           0
#define ZERO            0
#define DISP_ADJ        1
#define BOARD_WIDTH     (LCD_PIXEL_WIDTH - 2)
#define BOARD_HIGH      BOARD_WIDTH

#define DISP_MULT       34  // got by 240/7 --> top of the board at 238 pixels
#define DISP_ADD        (DISP_MULT / 2)  
#define TOP             6   // outside our max rows indicies of the actual board
#define RADIUS          15  // may use whatever <= 17

void displayBoard(uint8_t board[][]);
void diplayPiece(uint8_t row, uint8_t col, uint16_t color);
void displayStart();
void displayEnd();
 
#endif /* INC_GRAPHICS_DRIVER_H_ */