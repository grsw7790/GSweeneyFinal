/*
 * Graphics_Driver.c
 *
 *  Created on: Apr 23, 2025
 *      Author: griff
 */

#include <Graphics_Driver.h>

void displayBoard(uint8_t board[][])
{
    // this will draw the full blue rectangle for the board
    for(int i = DISP_ADJ; i < BOARD_WIDTH; i++)
    {
        for(j = ZERO; j < BOARD_HIGH; j++)
        {
            LCD_Draw_Pixel(i, j, LCD_COLOR_BLUE);
        }
    }

    // this will draw all the circles necessary
    for(int i = ZERO; i < ROW_INDICIES; i++)
    {
        for(int j = ZERO; j < COL_INDICIES; j++)
        {
            if(board[i][j] == RED)
                displayPiece(i, j, LCD_COLOR_RED);
            else if(board[i][j] == YELLOW)
                displayPiece(i, j, LCD_COLOR_YELLOW);
            else
                displayPiece(i, j, LCD_COLOR_WHITE);
        }
    }
}

// in this func we are shifting right one to center the board
void diplayPiece(uint8_t row, uint8_t col, uint16_t color)
    {LCD_Draw_Circle_Fill((DISP_MULT * row + DISP_ADD + DISP_ADJ), (DISP_MULT * col + DISP_ADD), RADIUS, color);}

void displayStart()
{

}

void displayEnd()
{

}