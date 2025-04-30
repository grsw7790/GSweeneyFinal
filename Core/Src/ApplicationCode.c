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
{
	move(col_full, board, RED, col);
	//if(check_win(board, RED) == 1)
	// {
	// 		state = GAME_OVER;
	//		winner = RED;
	// }
	//else
		//state = Y_MOVE;
}

void AppYellowMove(uint8_t col_full[NUM_COL], uint8_t board[][NUM_COL], uint8_t col)
{
	move(col_full, board, YELLOW, col);
	//if(check_win(board, YELLOW) == 1)
	// {
	// 		state = GAME_OVER;
	//		winner = YELLOW;
	// }
	//else
		//state = R_MOVE;
}

uint32_t AppLCDpoll()
{
	/* If touch pressed */
	if (returnTouchStateAndLocation(&StaticTouchData) == STMPE811_State_Pressed) 
	{
		uint32_t touch = (uint16_t)(StaticTouchData.x << 16) + (uint16_t)(StaticTouchData.y);
		return touch;
	} 
	else
		return 0; // realistically we are never going to touch 0,0 so this shouldnt cause any issues
}

void LCD_Visual_Demo(void)
{
	visualDemo();
}

#if COMPILE_TOUCH_FUNCTIONS == 1
void LCD_Touch_Polling_Demo(void)
{
	LCD_Clear(0,LCD_COLOR_GREEN);
	while (1) {
		/* If touch pressed */
		if (returnTouchStateAndLocation(&StaticTouchData) == STMPE811_State_Pressed) {
			/* Touch valid */
			printf("\nX: %03d\nY: %03d\n", StaticTouchData.x, StaticTouchData.y);
			LCD_Clear(0, LCD_COLOR_RED);
		} else {
			/* Touch not pressed */
			printf("Not Pressed\n\n");
			LCD_Clear(0, LCD_COLOR_GREEN);
		}
	}
}
#endif // COMPILE_TOUCH_FUNCTIONS

void EXTI0_IRQHandler()
{
	IRQ_dis(EXTI0_IRQ_NUMBER);
	// if(check_valid_move()) // col_ful array and curr_col var as args
	// 	addSchedulerEvent(DROP_EVENT); // event should make logic pretty simple to avoid invalid moves
	IRQ_clr_PR(EXTI0_IRQ_NUMBER);
	IRQ_clr_EXTI(EXTI0_IRQ_NUMBER);
	IRQ_en(EXTI0_IRQ_NUMBER);
}
