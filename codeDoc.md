# ECEN 2370 Final Project Connect 4
In this document, important functions to the Connect 4 game will be shown and explained as well as the code hierarchy which can be seen in the main branch 
(GSweeneyHierarchy.jpg). I will go in order of low on the hierarchy all the way up to main.c.

### -- HIERARCHY -- 
The coding hierarchy was part of this project that ended up getting pretty messy on my end unfortunately. I ended up writing a lot of the implementation in the main loop and 
therefore having to include many of the files I created in ApplicationCode which is not ideal. If I were to do the project over I would spend more time meticulously
planning out the hierarchy to ensure every function had a place and could easily be used up the hierarchy.

### -- LCD DRIVER --
I only added two functions to LCD_Driver; one that draws the board, just a blue rectangle without the holes, and a function that draws a rectangle.
```C
void LCD_draw_board();
void LCD_draw_rect(uint16_t p1[2], uint16_t p2[2], uint16_t color);
```
In reality I should have implemented LCD_draw_rect() first and called it in LCD_draw_board() however because I was disorganized I wrote draw board first 
and never re-wrote it to call draw rect.   <br> 
#### LCD_draw_rect() 
```C
void LCD_draw_rect(uint16_t p1[2], uint16_t p2[2], uint16_t color) 
{
  uint16_t x_range = p2[0] - p1[0];
  uint16_t y_range = p2[1] - p1[1];

  for(int x = p1[0]; x < x_range; x++)
    {
        for(int y = p1[1]; y < y_range; y++)
        {
            LCD_Draw_Pixel(x, y, color);
        }
    }
}
```
This function takes three arguments, two of which are arrays of size [2] that represent (x,y) coordinates on the LCD screen, and a 16 bit integer representing the color 
of the rectangle. Using these points it determines the bounds of the rectangle and runs through a nested for loop, calling LCD_Draw_Pixel() in order to color the pixel
specified by the coordinate the orrect color. p1 is used as the top left corner of the rectangle and p2 is used as the bottom right of the rectangle.
<br> <br>
The draw board function is essentially the same however it does not take any arguments as the bounds and color for the board are pre-defined.

### -- GRAPHICS DRIVER -- 
I wrote several functions in order to properly display the graphics on the board's LCD screen:
```C
void displayBoard(uint8_t board[][NUM_COL]);
void displayPiece(uint8_t row, uint8_t col, uint16_t color);
void startHelper();
void displayStart();
void endHelper(char word[], uint16_t color, uint32_t r_wins, uint32_t y_wins, uint32_t time);
void displayEnd(uint8_t rwywt, uint32_t r_wins, uint32_t y_wins, uint32_t time);
```
#### startHelper(), endHelper()
Both of these function's primary purpose was to display text on the LCD screen and made use of the LCD_Draw_Char() function. 
There is not much to explain functionality-wise.

#### displayPiece()
```C
void displayPiece(uint8_t row, uint8_t col, uint16_t color)
    {LCD_Draw_Circle_Fill((DISP_MULT * row + DISP_ADD + DISP_ADJ) , (82 + (DISP_MULT * col + DISP_ADD)) , RADIUS, color);}
```
This function calls LCD_Draw_Circle_Fill() in order to draw the pieces. It takes three arguments with pretty self explanatory names, one for the row
in which to display the piece (y-coordinate), one for the column in which to display the piece (x-coordinate), and one for the color. The fucntion does the 
calculations in order to find the correct coordinates on the LCD screen from coordinates relatice to the spaces on the board. 82 is the top y-pixel coordinate of 
our screen (shouldn't have used a magic number). 
##### Important defines:
```C
#define DISP_MULT       34  
#define DISP_ADD        (DISP_MULT / 2)
#define DISP_ADJ        1
```
DISP_MULT and DISP_ADD were used to find where the center of the circle should be based on the size of the board: <br>
34 = 240 / 7 (rows) <br> 
DISP_ADJ is to adjust the x and y to ensure the game is centered on the board since 240 is not perfectly divisible by 7. <br>
34 * 7 = 238

#### displayBoard()
```C
void displayBoard(uint8_t board[][NUM_COL])
{
    LCD_Clear(ZERO, LCD_COLOR_BLACK);
    LCD_draw_board(); 
    
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
```
This function iterates through our game board drawing all of the pieces and empty spaces as well as the board itself.
##### Important defines:

```C
#define NUM_ROW         7  
#define NUM_COL         7
```
The reason NUM_ROW is defined as 7 and not 6 is in order to handle the functionality of displaying the piece-to-be-dropped above the board. This
could have been done using a seperate array but I found it nicer to do it this way.

#### displayStart()
```C
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
```
This function draws two rectangles calling the aformentioned LCD function and then calls start helper to display the necessary text on the LCD.

##### Important defines:
```C
#define  LCD_PIXEL_WIDTH          ((uint16_t)240)
#define  LCD_PIXEL_HEIGHT         ((uint16_t)320)
#define  HALF_HEIGHT              ((uint16_t)(LCD_PIXEL_HEIGHT / 2))
#define  HALF_WIDTH               ((uint16_t)(LCD_PIXEL_WIDTH / 2))
```
I think ZERO is pretty self explanetory so I left that out... <br>
LCD_PIXEL_WIDTH and LCD_PIXEL_HEIGHT were both provided in the starter code and they are the width and height in pixels of the LCD respectively.
HALF_HEIGHT and HALF_WIDTH are simple half both the pixel height and width of the LCD. In combination in the displayStart() function they create 
two distinct halves of the screen for the user to make a choice (one or two player mode).

#### displayEnd()
```C
void displayEnd(uint8_t rwywt, uint32_t r_wins, uint32_t y_wins, uint32_t time)
{
    char win[5] = {'W','I','N','S','!'};
    char tie[5] = {'T','I','E','D','!'};

    switch(rwywt)
    {
        case RED_WIN:
            LCD_Clear(ZERO, LCD_COLOR_RED);
            endHelper(win, LCD_COLOR_WHITE, r_wins, y_wins, time);
            break;
        case YELLOW_WIN:
            LCD_Clear(ZERO, LCD_COLOR_YELLOW);
            endHelper(win, LCD_COLOR_BLACK, r_wins, y_wins, time);
            break;
        case TIE:
            LCD_Clear(ZERO, LCD_COLOR_WHITE);
            endHelper(tie, LCD_COLOR_BLACK, r_wins, y_wins, time);
            break;
        
        default:
            rwywt = 3; // does nothing
            break;
    }
}
```
This function is slightly more involved than displayStart() however it is still quite simple. The arguments in order represent which player won or if the game 
was a tie, the current count of red wins, the current count of yellow wins, and the time the game took. I used a switch statement in order to determine which color
won the game or if it was a time and call endHelper accordingly to display the correct information. The macros used are self explanetory and completely arbitrary
so it seems unnecessary to explain them.

### -- GAMEPLAY DRIVER --
There were three functions created in the gameplay driver, all of which being essential to clean gameplay.

#### check_valid_move()
```C
bool check_valid_move(uint8_t col_full[NUM_COL], uint8_t col)
{
    if(col_full[col] == FULL)
        return false;
    else
        return true;
}
```
This function ensures that a move a player or computer is trying to make is in fact valid by checking the intended column the drop in against
the array col_full[] that fills with 1's as the columns of the game board fill. The filling of this array happens in the move function to-be-exlpained below.  
The macro FULL just = 1. It will return true if the move is valid and false if not.

#### move()
```C
void move(uint8_t col_full[NUM_COL], uint8_t board[][NUM_COL], uint8_t color, uint8_t col) 
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
```
This function iterates through the column specified by the argument col, to find the lowest open space on the board in that column (highest index). When
it finds this it will place a value in the game board array that is the color specified the argument color. It then will check if the index it found is the top
of the board (TOP = 1 because remember we have 7 rows to display the piece-to-be-dropped) and fill the col index of the col_full[] array. It will force-exit
the for loop (by setting i = 0) once it finds and sets the free space. 

### check_win()
```C
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
```
This function iterates through nested for loops to check different win conditions. It takes a color argument as we only want to check win after
of the color that just took it's turn. There may be a way to reduce the number of for loops here however it runs as fast as needed and keeping the 
for loops seperate helps stay organized and know which win conditions you are checking when.

##### Important defines:
```C
#define ROW_INDICIES    (NUM_COL - 1)   
#define COL_INDICIES    (NUM_ROW - 1)
#define FOR_ADJ         3
```
ROW_INDICIES and COL_INDICIES are pretty self explanatory. FOR_ADJ is 3 because the way I check different win conditions it is necessary to stop
before reaching the end index of our game board as it would be trying to access outside of the board. There are also instances where you want to start
or end at index 3 in checking for diagonal wins. 

### -- BUTTON DRIVER --
Button driver is essentially the same as lab 5 however I removed the interrupt functionality as it was causing me issues and I implemented polling instead
as I was already polling for LCD touches it felt pretty natural.

### -- SCHEDULER --
Our scheduler is also largely the same just with different events. I only found the need to have one event for this project although in hidsight it may have made
my life easier to use more events to eliminate some repeatative code or something of this sort. 
```C
#define	DROP_EVENT		(1 << 0)
```
This is the only event I used for the project to prompt the program to drop a piece.

### -- APPLICATION CODE --
I wrote a few new function in application code, only three of them being worth explaining fully.

```C
void AppDispBoard(uint8_t board[][NUM_COL]); 
void AppRedMove(uint8_t col_full[NUM_COL], uint8_t board[][NUM_COL], uint8_t col);
void AppYellowMove(uint8_t col_full[NUM_COL], uint8_t board[][NUM_COL], uint8_t col);
uint8_t AI_Helper(uint8_t board[][NUM_COL], uint8_t free[][2], uint8_t index);
uint8_t App_AI_Move(uint8_t col_full[NUM_COL], uint8_t board[][NUM_COL]);
STMPE811_TouchData AppLCDpoll();
```
####  AppDispBoard(), AppRedMove(), AppYellowMove()
These three functions simply call other function from lower in the hierarchy, AppRedMove() and AppYellowMove() have the colors pre-defined as you 
might guess.

#### AI_Helper()
```C
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
```
The array free[][2] contains a pair of coordinates at "index" on the game board. This function will checks the board for neighbors of like-color
to the color the AI is playing with (in my case always yellow). It will then return the number of neighbors at the coordinates specified by the index of free[][2].

#### App_AI_Move()
```C
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
    uint8_t best_index = 3; // this is the best first move, should make game more interesting 
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
```
This function finds all possible moves on the current game board and fills a 2D array called free with said coordinates. It then iterates
through a for loop and calls the AI_Helper() function for each coordinate pair stored in free to find the open space with the most neighbors. I
initialized best_index, the number the function will return with 3, which corresponds to the best first move in Connect 4. 

#### AppLCDpoll()
```C
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
```
This function returns the (x,y) coordinates of a touch. It was used largely to hold up the program while the screen was not touched as follows:
```C
while((touch.x == ZERO) && (touch.y == ZERO))
      {touch = AppLCDpoll();}
```
This is from my main implementation which contains the larger state machine for my game. Once the while exits the program responds appropriately
depending on the state it is currently in and where the touch occured. This is the nicest way I found to poll for a touch on the start and end screens. 

### MAIN

```C
    if(players == ONE_PLAYER)
    {
      HAL_Delay(200);
      ai_move = App_AI_Move(col_full, board);

      if(check_valid_move(col_full, ai_move))
      {
        AppYellowMove(col_full, board, ai_move);
        curr_col = 3;
        temp = 0;
        for(uint8_t i = 0; i < NUM_COL; i++)
          {temp+=col_full[i];}

        if((check_win(board, YELLOW) == true) || (temp == NUM_COL))
		      state = GAME_OVER;
	      else
		      state = R_MOVE;
      }
    }
```
This code snippet shows how exactly we use App_AI_Move() in our main implementation. 

##### Important defines:
```C
#define GAME_START      0
#define RESET           1
#define ONE_PLAYER      6
#define TWO_PLAYER      7         
#define R_MOVE          3   
#define Y_MOVE          4   
#define GAME_OVER       5
```
These are defined outside of main but are mostly used in main. They are used for the state machine and general control flow of the program.
#### Game Start State:
```C
if(state == GAME_START)
  {
    // reset board
    for(uint8_t i = ZERO; i < NUM_COL; i++)
    {
      col_full[i] = 0;
      for(uint8_t j = ZERO; j < NUM_ROW; j++)
        {board[i][j] = 0;}
    }
    board[ZERO][3] = YELLOW;

    displayStart();  
    
    while((touch.x == ZERO) && (touch.y == ZERO))
      {touch = AppLCDpoll();}
    HAL_GetTick(); // start timer count
    if(touch.y >= HALF_HEIGHT) // this is weird that it works... but it does so im not messing with it
      players = ONE_PLAYER;
    else
      players = TWO_PLAYER;

    state = Y_MOVE; // enter next state after touch
    AppDispBoard(board);
  }
```
This state implements the reset after touch in the game over state and the recieving of user input on the start screen and responds correctly
to the input by setting the number of players.


#### Move State: 
```C
  if(state == R_MOVE)
  {
    if((getScheduledEvents() & DROP_EVENT) == DROP_EVENT)
    {
      removeSchedulerEvent(DROP_EVENT);
      if(check_valid_move(col_full, curr_col))
      {
        AppRedMove(col_full, board, curr_col);
        curr_col = 3;
        temp = 0;
        for(uint8_t i = 0; i < NUM_COL; i++)
          {temp+=col_full[i];}

        if((check_win(board, RED) == true) || (temp == NUM_COL))
          state = GAME_OVER;
        else
          state = Y_MOVE;
      }
    }

    if(CheckButtonPress() == BUTTON_PRESSED)
    {
      addSchedulerEvent(DROP_EVENT);
      HAL_Delay(200);
    }

    touch = AppLCDpoll();
    if((touch.x != ZERO) || (touch.y != ZERO))
    {
      if((touch.x > HALF_WIDTH) && (curr_col < ROW_INDICIES)) // make sure we dont go off board
      {
        temp = curr_col;
        curr_col += 1;
        board[ZERO][temp] = ZERO;
        board[ZERO][curr_col] = RED;
        AppDispBoard(board);
        HAL_Delay(50);
      }
      else if((touch.x < HALF_WIDTH) && (curr_col > ZERO))
      {
        temp = curr_col;
        curr_col -= 1;
        board[ZERO][temp] = ZERO;
        board[ZERO][curr_col] = RED;
        AppDispBoard(board);
        HAL_Delay(50);
      }
      else
        AppDispBoard(board);
    }
  }
```
This code snippet is a full move state from main. I think it is mostly self-explanatory although there is a bunch of random somewhat janky code happening
in here. I implemented the touch to move the piece-to-be-dropped here, as well as move validation, button polling, scheduling, etc.. There is also a state
variable here which will be set and move to the next state.

#### Game Over State:
```C
if(state == GAME_OVER)
  {
    time = HAL_GetTick();
    if(check_win(board, RED))
    {
      rwins++;
      displayEnd(RED_WIN, rwins, ywins, time);
    }
    else if(check_win(board, YELLOW))
    {
      ywins++;
      displayEnd(YELLOW_WIN, rwins, ywins, time); 
    }
    else
      displayEnd(TIE, rwins, ywins, time);
    
    while((touch.x == ZERO) && (touch.y == ZERO))
      {touch = AppLCDpoll();}
    state = GAME_START;
  }
```
The game over state counts red and yellow wins, and calls the displayEnd() function. It then polls for touch to reset the game, I decided to implement this to allow
a touch anywhere on the screen to reset the game both for simplicity and to keep the end screen clean. 


