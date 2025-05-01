/*
 * ApplicationCode.c
 *
 *  Created on: Dec 30, 2023 (updated 11/12/2024) Thanks Donavon! 
 *      Author: Xavion
 */

#include <ApplicationCode.h>

/* Static variables */


extern void initialise_monitor_handles(void); 

#if COMPILE_TOUCH_FUNCTIONS == 1
static STMPE811_TouchData StaticTouchData;
#endif // COMPILE_TOUCH_FUNCTIONS

void ApplicationInit(void)
{
	initialise_monitor_handles(); // Allows printf functionality
    LTCD__Init();
    LTCD_Layer_Init(0);
    LCD_Clear(0,LCD_COLOR_WHITE);

    #if COMPILE_TOUCH_FUNCTIONS == 1
	InitializeLCDTouch();

	// This is the orientation for the board to be direclty up where the buttons are vertically above the screen
	// Top left would be low x value, high y value. Bottom right would be high x value, low y value.
	StaticTouchData.orientation = STMPE811_Orientation_Portrait_2;

	#endif // COMPILE_TOUCH_FUNCTIONS
}

void AppDispBoard(uint8_t board[][NUM_COL])
	{displayBoard(board);}

void AppRedMove(uint8_t col_full[NUM_COL], uint8_t board[][NUM_COL], uint8_t col)
	{move(col_full, board, RED, col);}

void AppYellowMove(uint8_t col_full[NUM_COL], uint8_t board[][NUM_COL], uint8_t col)
	{move(col_full, board, YELLOW, col);}

	uint8_t AI_Helper(uint8_t board[][NUM_COL], uint8_t free[][2], uint8_t index)
	{
		uint8_t num_neighbors = 0;
		uint8_t x = free[index][0];
		uint8_t y = free[index][1];
	
		// Left
		if (x > 0 && board[y][x - 1] == YELLOW)
			num_neighbors++;
	
		// Right
		if (x < NUM_COL - 1 && board[y][x + 1] == YELLOW)
			num_neighbors++;
	
		// Below
		if (y < NUM_ROW - 1 && board[y + 1][x] == YELLOW)
			num_neighbors++;
	
		// Bottom-left
		if (x > 0 && y < NUM_ROW - 1 && board[y + 1][x - 1] == YELLOW)
			num_neighbors++;
	
		// Bottom-right
		if (x < NUM_COL - 1 && y < NUM_ROW - 1 && board[y + 1][x + 1] == YELLOW)
			num_neighbors++;
	
		// Top-left
		if (x > 0 && y > 0 && board[y - 1][x - 1] == YELLOW)
			num_neighbors++;
	
		// Top-right
		if (x < NUM_COL - 1 && y > 0 && board[y - 1][x + 1] == YELLOW)
			num_neighbors++;
	
		return num_neighbors;
	}
	

uint8_t App_AI_Move(uint8_t col_full[NUM_COL], uint8_t board[][NUM_COL]) // AI move will always be yellow
{
	uint8_t free[NUM_COL][2];
	uint8_t num_free = 0;
	for(uint8_t i = ZERO; i <= ROW_INDICIES; i++)
	{
		for(uint8_t j = COL_INDICIES; j >= ONE; j--)
		{
			if(col_full[i])
				i++;
			if(board[j][i] == ZERO)
			{
				free[num_free][0] = i;
				free[num_free][1] = j; //store x,y into free moves
				num_free++; // count num free moves
				i++; // makes sure we can only see one free per column
			}
		}
	}

	// count neighbors for each free move
    uint8_t max_neighbors = 0;
    uint8_t best_index = 2; // making it 2 1st should hopefully lead to more interesting games than 0
    for (uint8_t n = 0; n < num_free; n++)
    {
        uint8_t neighbors = AI_Helper(board, free, n);
        if (neighbors > max_neighbors)
        {
            max_neighbors = neighbors;
            best_index = n;
        }
    }
    uint8_t best_x = free[best_index][0];
	return best_x;
}

STMPE811_TouchData AppLCDpoll()
{
	/* If touch pressed */
	if (returnTouchStateAndLocation(&StaticTouchData) == STMPE811_State_Pressed) 
		return StaticTouchData; 
	else
	{
		StaticTouchData.x = ZERO;
		StaticTouchData.y = ZERO;
		return StaticTouchData;
	}
		 
}
