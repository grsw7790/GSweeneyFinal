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
#define ROW_INDICIES    (NUM_COL - 1)   
#define COL_INDICIES    (NUM_ROW - 1) // omit above the board
#define RED             1
#define YELLOW          2
#define ZERO            0
#define ONE             1
#define DISP_ADJ        1
#define BOARD_WIDTH     (LCD_PIXEL_WIDTH - 2)
#define BOARD_HIGH      BOARD_WIDTH
#define ASCII_CONST     48

#define DISP_MULT       34  // got by 240/7 --> top of the board at 238 pixels
#define DISP_ADD        (DISP_MULT / 2)  
#define TOP             1   // row index that will be top of our board, 0 above it
#define RADIUS          15  // may use whatever <= 17
#define RED_WIN         0
#define YELLOW_WIN      1
#define TIE             2

void displayBoard(uint8_t board[][NUM_COL]);
void displayPiece(uint8_t row, uint8_t col, uint16_t color);
void startHelper();
void displayStart();
void endHelper(char word[], uint16_t color, uint32_t r_wins, uint32_t y_wins, uint32_t time);
void displayEnd(uint8_t rwywt, uint32_t r_wins, uint32_t y_wins, uint32_t time); // red win yellow win tie (which one)
 
#endif /* INC_GRAPHICS_DRIVER_H_ */