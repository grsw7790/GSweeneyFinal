/*
 * Gameplay_Driver.c
 *
 *  Created on: Apr 23, 2025
 *      Author: griff
 */

#include <Gameplay_Driver.h>

void move(uint8_t col_full[], uint8_t board[][], uint8_t color, uint8_t col)
{
    for(int i = COL_INDICIES; i > ZERO; i--)
    {
        if(board[i][col] == ZERO)
        {
            board[i][col] = color;
            if(i == ZERO)
                col_full[col] = FULL;
        }
    }
    displayBoard(board);
}

bool check_win(uint8_t board[][], uint8_t color)
{
    // Check Horizontal
    for(int i = ZERO; i < COL_INDICIES-FOR_ADJ; i++)
    {
        for(int j = ZERO; j < ROW_INDICIES; j++)
        {
            if(board[i][j] == color && board[i][j+1] == color && board[i][j+2] == color board[i][j+3] == color) // 4 in a row cond
                return true
        }
    }

    // Check Verticle
    for(int i = ZERO; i < ROW_INDICIES; i++)
    {
        for(int j = ZERO; j < COL_INDICIES-FOR_ADJ; j++)
        {
            if(board[i][j] == color && board[i+1][j] == color && board[i+2][j] == color && board[i+3][j] == color)
                return true;
        }
    }

    // Check Diagonal Ascending
    for(int i = FOR_ADJ; i < COL_INDICIES; i++)
    {
        for(int j = ZERO; j < ROW_INDICIES-FOR_ADJ; j++)
        {
            if(board[i][j] == color && board[i-1][j+1] == color && board[i-2][j+2] == color && board[i-3][j+3] == color)
                return true;
        }
    }

    // Check Diagonal Descending
    for(int i = FOR_ADJ; i < COL_INDICIES-FOR_ADJ; i++)
    {
        for(int j = FOR_ADJ; j < ROW_INDICIES; j++)
        {
            if(board[i][j] == color && board[i-1][j-1] == color && board[i-2][j-2] == color && board[i-3][j-3] == color)
                return true;          
        }
    }
}

bool check_valid_move(uint8_t col_full[], uint8_t col)
{
    if(col_full[col] == FULL)
        return FALSE;
    else
        return TRUE;
}