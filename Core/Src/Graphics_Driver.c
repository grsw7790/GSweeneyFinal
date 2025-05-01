/*
 * Graphics_Driver.c
 *
 *  Created on: Apr 23, 2025
 *      Author: griff
 */

#include <Graphics_Driver.h>

/*
    TOP LEFT BOARD (x,y) = (0,0)
    BOTTOM RIGHT BOARD (x,y) = (240,320)
*/
// in this func we are shifting right one to center the board
void displayPiece(uint8_t row, uint8_t col, uint16_t color)
    {LCD_Draw_Circle_Fill((DISP_MULT * row + DISP_ADD + DISP_ADJ) , (82 + (DISP_MULT * col + DISP_ADD)) , RADIUS, color);}

void displayBoard(uint8_t board[][NUM_COL])
{
    LCD_Clear(ZERO, LCD_COLOR_BLACK);
    LCD_draw_board(); // needs work
    
    // this will draw all the circles necessary
    for(uint8_t y = ZERO; y < NUM_ROW; y++)
    {
        for(int8_t x = ZERO; x < NUM_COL; x++)
        {
            if(board[y][x] == RED)
                displayPiece(x, y, LCD_COLOR_RED);
            else if(board[y][x] == YELLOW)
                displayPiece(x, y, LCD_COLOR_YELLOW);
            else
                displayPiece(x, y, LCD_COLOR_BLACK);
        }
    }
}

void startHelper()
{
    uint16_t top_mid = (uint16_t)(HALF_HEIGHT / 2);
    uint16_t bot_mid = top_mid + (uint16_t)(HALF_HEIGHT);

    LCD_SetTextColor(LCD_COLOR_BLACK);
	LCD_SetFont(&Font16x24);

    LCD_DisplayChar(82,top_mid, 'S');
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
    uint16_t top_left1[2] = {ZERO, ZERO};
    uint16_t bot_right1[2] = {LCD_PIXEL_WIDTH, HALF_HEIGHT};

    uint16_t top_left2[2] = {ZERO, HALF_HEIGHT};
    uint16_t bot_right2[2] = {LCD_PIXEL_WIDTH, LCD_PIXEL_HEIGHT};

    // split top and bottom half visually 
    LCD_draw_rect(top_left2, bot_right2, LCD_COLOR_GREEN);
    LCD_draw_rect(top_left1, bot_right1, LCD_COLOR_MAGENTA);

    // player choices
    startHelper();
}

void endHelper(char word[], uint16_t color, uint32_t r_wins, uint32_t y_wins) // this is expandable
{
    LCD_SetTextColor(color);
	LCD_SetFont(&Font16x24);

    // win or tie
	LCD_DisplayChar(90,100, word[0]);
	LCD_DisplayChar(105,100, word[1]);
	LCD_DisplayChar(120,100, word[2]);
	LCD_DisplayChar(135,100, word[3]);
	LCD_DisplayChar(150,100, word[4]);

    LCD_DisplayChar(90,130, 'R');
	LCD_DisplayChar(90,155, 'Y');
	LCD_DisplayChar(105,130, ':');
	LCD_DisplayChar(105,155, ':');
	LCD_DisplayChar(120,130, ((char)r_wins + ASCII_CONST));
    LCD_DisplayChar(120,155, ((char)y_wins + ASCII_CONST));

    // we can do num wins and time here as well.
}

void displayEnd(uint8_t rwywt, uint32_t r_wins, uint32_t y_wins)
{
    char win[5] = {'W','I','N','S','!'};
    char tie[5] = {'T','I','E','D','!'};

    switch(rwywt)
    {
        case RED_WIN:
            LCD_Clear(ZERO, LCD_COLOR_RED);
            endHelper(win, LCD_COLOR_WHITE, r_wins, y_wins);
            break;
        case YELLOW_WIN:
            LCD_Clear(ZERO, LCD_COLOR_YELLOW);
            endHelper(win, LCD_COLOR_BLACK, r_wins, y_wins);
            break;
        case TIE:
            LCD_Clear(ZERO, LCD_COLOR_WHITE);
            endHelper(tie, LCD_COLOR_BLACK, r_wins, y_wins);
            break;
        
        default:
            rwywt = 3; // does nothing
            break;
    }
}