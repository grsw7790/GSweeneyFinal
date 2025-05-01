/*
 * Gameplay_Driver.h
 *
 *  Created on: Apr 23, 2025
 *      Author: griff
 */

#ifndef INC_GAMEPLAY_DRIVER_H_
#define INC_GAMEPLAY_DRIVER_H_

#include <Graphics_Driver.h>

#define FULL            1
#define FOR_ADJ         3

// gameplay states
#define GAME_START      0
#define RESET           1
#define ONE_PLAYER      6
#define TWO_PLAYER      7         
#define R_MOVE          3   
#define Y_MOVE          4   
#define GAME_OVER       5   // lots to do in this sate. cap timer display end screen. count win/ties. allow for reset

void move(uint8_t col_full[NUM_COL], uint8_t board[][NUM_COL], uint8_t color, uint8_t col);
bool check_win(uint8_t board[][NUM_COL], uint8_t color); // this will assume the game board size is properly initialized
bool check_valid_move(uint8_t col_full[NUM_COL], uint8_t col);

#endif /* INC_GAMEPLAY_DRIVER_H_ */
