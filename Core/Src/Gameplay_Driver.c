/*
 * Gameplay_Driver.c
 *
 *  Created on: Apr 23, 2025
 *      Author: griff
 */

#include <Gameplay_Driver.h>

void move(uint8_t col_full[NUM_COL], uint8_t board[][NUM_COL], uint8_t color, uint8_t col) // we have to call 2d array differently
{
    for(int i = NUM_ROW - 1; i >= TOP; i--)
    {
        if(board[i][col] == ZERO)
        {
            board[i][col] = color;
            if(i == TOP)
                col_full[col] = FULL;
            
            board[0][col] = ZERO;
            col = 3;

            if(color == RED)
                board[0][col] = YELLOW; 
            else 
                board[0][col] = RED;
            i = 0;
        }
    }   
    displayBoard(board);
}

bool check_win(uint8_t board[][NUM_COL], uint8_t color)// i=x j=y
{
    // Check Horizontal
    for(int i = ZERO; i <= ROW_INDICIES-FOR_ADJ; i++) 
    {
        for(int j = ONE; j <= COL_INDICIES; j++)
        {
            if(board[j][i] == color && board[j][i+1] == color && board[j][i+2] == color && board[j][i+3] == color) // 4 in a row cond
                return true;
        }
    }

    // Check Verticle
    for(int i = ZERO; i <= ROW_INDICIES; i++)
    {
        for(int j = ONE; j <= COL_INDICIES-FOR_ADJ; j++)
        {
            if((board[j][i] == color) && (board[j+1][i] == color) && (board[j+2][i] == color) && (board[j+3][i] == color))
                return true;
        }
    }

    // Check Diagonal Ascending
    for(int i = ZERO; i <= ROW_INDICIES - FOR_ADJ; i++)
    {
        for(int j = FOR_ADJ; j <= COL_INDICIES; j++)
        {
            if((board[j][i] == color) && (board[j-1][i+1] == color) && (board[j-2][i+2] == color) && (board[j-3][i+3] == color))
                return true;
        }
    }

    // Check Diagonal Descending
    for(int i = ZERO; i <= COL_INDICIES - FOR_ADJ; i++)
    {
        for(int j = ZERO; j <= ROW_INDICIES - FOR_ADJ; j++)
        {
            if((board[j][i] == color) && (board[j+1][i+1] == color) && (board[j+2][i+2] == color) && (board[j+3][i+3] == color))
                return true;          
        }
    }
    return false;
}

bool check_valid_move(uint8_t col_full[NUM_COL], uint8_t col)
{
    if(col_full[col] == FULL)
        return false;
    else
        return true;
}