/*
 * Graphics_Driver.c
 *
 *  Created on: Apr 23, 2025
 *      Author: griff
 */

#include <Graphics_Driver.h>


// in this func we are shifting right one to center the board
void displayPiece(uint8_t row, uint8_t col, uint16_t color)
    {LCD_Draw_Circle_Fill((DISP_MULT * row + DISP_ADD + DISP_ADJ), (DISP_MULT * col + DISP_ADD), RADIUS, color);}

void displayBoard(uint8_t board[][NUM_COL])
{
    LCD_draw_board();
    
    // this will draw all the circles necessary
    for(uint8_t i = ZERO; i < ROW_INDICIES; i++)
    {
        for(int8_t j = ZERO; j < COL_INDICIES; j++)
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

void startHelper()
{
    uint16_t top_mid = (uint16_t)(HALF_HEIGHT / 2);
    uint16_t bot_mid = (uint16_t)(HALF_WIDTH / 2);

    LCD_SetTextColor(LCD_COLOR_BLACK);
	LCD_SetFont(&Font16x24);

    LCD_DisplayChar(72,top_mid, 'S');
	LCD_DisplayChar(97,top_mid, 'I');
	LCD_DisplayChar(112,top_mid, 'N');
    // 120
	LCD_DisplayChar(127,top_mid, 'G');
	LCD_DisplayChar(142,top_mid, 'L');
    LCD_DisplayChar(157,top_mid, 'E');

    LCD_DisplayChar(105,bot_mid, 'T');
	LCD_DisplayChar(120,bot_mid, 'W');
	LCD_DisplayChar(135,bot_mid, 'O');
}


void displayStart()
{
    uint16_t top_left[2] = {ZERO, HALF_HEIGHT};
    uint16_t bot_right[2] = {HALF_WIDTH, ZERO};

    // split top and bottom half visually 
    LCD_Clear(ZERO, LCD_COLOR_GREEN);
    LCD_draw_rect(top_left, bot_right, LCD_COLOR_MAGENTA);

    // player choices
    startHelper();
}

void endHelper(char word[], uint16_t color) // this is expandable
{
    LCD_SetTextColor(color);
	LCD_SetFont(&Font16x24);

    // win or tie
	LCD_DisplayChar(90,140, word[0]);
	LCD_DisplayChar(105,140, word[1]);
	LCD_DisplayChar(120,140, word[2]);
	LCD_DisplayChar(135,140, word[3]);
	LCD_DisplayChar(150,140, word[4]);

    // we can do num wins and time here as well.
}

void displayEnd(uint8_t rwywt)
{
    char win[5] = {'W','I','N','S','!'};
    char tie[5] = {'T','I','E','D','!'};

    switch(rwywt)
    {
        case RED_WIN:
            LCD_Clear(ZERO, LCD_COLOR_RED);
            endHelper(win, LCD_COLOR_WHITE);
            break;
        case YELLOW_WIN:
            LCD_Clear(ZERO, LCD_COLOR_YELLOW);
            endHelper(win, LCD_COLOR_BLACK);
            break;
        case TIE:
            LCD_Clear(ZERO, LCD_COLOR_WHITE);
            endHelper(tie, LCD_COLOR_BLACK);
            break;
        
        default:
            rwywt = 3; // does nothing
            break;
    }
}