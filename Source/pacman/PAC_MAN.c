#include "PAC_MAN.h"
#include <stdio.h>   // Convert numbers to strings
#include <string.h>  //Convert numbers to strings
Game gameState; 
int score = 0;    //show current scores in the screen
int scoreflag=0; //use to update remain lives
int victory=0;    //Whether the game is a winning state or not
/*
0:passage
1:walls
2:standard pills
3:power pills
4:door
*/
const uint8_t MAZE_ARRAY[31][28] = {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,2,2,2,2,2,2,2,2,2,2,2,2,1,1,2,2,2,2,2,2,2,2,2,2,2,2,1},
    {1,2,1,1,1,1,2,1,1,1,1,1,2,1,1,2,1,1,1,1,1,2,1,1,1,1,2,1},
    {1,2,1,0,0,1,2,1,0,0,0,1,2,1,1,2,1,0,0,0,1,2,1,0,0,1,2,1},
    {1,2,1,1,1,1,2,1,1,1,1,1,2,1,1,2,1,1,1,1,1,2,1,1,1,1,2,1},
    {1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1},
    {1,2,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,2,1},
    {1,2,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,2,1},
    {1,2,2,2,2,2,2,1,1,2,2,2,2,1,1,2,2,2,2,1,1,2,2,2,2,2,2,1},
    {1,1,1,1,1,1,2,1,1,1,1,1,0,1,1,0,1,1,1,1,1,2,1,1,1,1,1,1},
    {1,1,1,1,1,1,2,1,1,1,1,1,0,1,1,0,1,1,1,1,1,2,1,1,1,1,1,1},
    {1,1,1,1,1,1,2,1,1,0,0,0,0,0,0,0,0,0,0,1,1,2,1,1,1,1,1,1},
    {1,1,1,1,1,1,2,1,1,0,1,1,1,4,4,1,1,1,0,1,1,2,1,1,1,1,1,1},
    {1,1,1,1,1,1,2,1,1,0,1,0,0,0,0,0,0,1,0,1,1,2,1,1,1,1,1,1},
    {0,0,0,0,0,0,2,0,0,0,1,0,0,0,0,0,0,1,0,0,0,2,0,0,0,0,0,0},
    {1,1,1,1,1,1,2,1,1,0,1,0,0,0,0,0,0,1,0,1,1,2,1,1,1,1,1,1},
    {1,1,1,1,1,1,2,1,1,0,1,1,1,1,1,1,1,1,0,1,1,2,1,1,1,1,1,1},
    {1,1,1,1,1,1,2,1,1,0,0,0,0,0,0,0,0,0,0,1,1,2,1,1,1,1,1,1},
    {1,1,1,1,1,1,2,1,1,0,1,1,1,1,1,1,1,1,0,1,1,2,1,1,1,1,1,1},
    {1,1,1,1,1,1,2,1,1,0,1,1,1,1,1,1,1,1,0,1,1,2,1,1,1,1,1,1},
    {1,0,2,2,2,2,2,2,2,2,2,2,2,1,1,2,2,2,2,2,2,2,2,2,2,2,0,1},
    {1,2,1,1,1,1,2,1,1,1,1,1,2,1,1,2,1,1,1,1,1,2,1,1,1,1,2,1},
    {1,2,1,1,1,1,2,1,1,1,1,1,2,1,1,2,1,1,1,1,1,2,1,1,1,1,2,1},
    {1,2,2,2,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,2,2,2,1},
    {1,1,1,2,1,1,2,1,1,2,1,1,1,1,1,1,1,1,2,1,1,2,1,1,2,1,1,1},
    {1,1,1,2,1,1,2,1,1,2,1,1,1,1,1,1,1,1,2,1,1,2,1,1,2,1,1,1},
    {1,0,1,2,2,2,2,1,1,2,2,2,2,1,1,2,2,2,2,1,1,2,2,2,2,2,2,1},
    {1,2,1,1,1,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,2,1},
    {1,2,1,1,1,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,2,1},
    {1,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};
/*
initGame():
Initialize the maze, initialize the initial position and direction of the pacman,
pause the state of the game, the initial status of remain lives is 0, the game score is 0,
the state of victory is 0, and the generation function of powerpills is called.
*/
void initGame(Game* game) {
   
    for(int x = 0; x < 31; x++) {
        for(int y = 0; y < 28; y++) {
            game->maze[x][y] = MAZE_ARRAY[x][y];
            
        }
    }
		game->pacman.x = 14;  
    game->pacman.y = 17;  
    game->pacman.dir = DIR_LEFT;
		game->isPaused=1;
		game->lives=1;
		score=0;
    generatePowerPills(game);
		
		victory=0;
		if(game->isPaused)
		{
				disable_timer(2);
				disable_RIT();
        GUI_Text(100, 133, (uint8_t *)"PAUSE", Red, Black);
		}
}
/*
generatePowerPills():
Randomly generate powerpills and replace them with normal pills
*/
void generatePowerPills(Game* game) {
    int powerPillsPlaced = 0;
    while(powerPillsPlaced < 6) {
				int test=getSysTickRandom();
        int x = getSysTickRandom() % (SCREEN_WIDTH/CELL_SIZE);
        int y = getSysTickRandom() % (MAZE_HEIGHT/CELL_SIZE);
			
        if(game->maze[x][y] == 2) {  
            game->maze[x][y] = 3;     
            powerPillsPlaced++;
        }
    }
}
/*
erasePill():
When the pacman is moved, the position it is moved to is exactly the location where the pills 
are present or the power pills are present, and the pills need to be eaten and erased.
*/
void erasePill(Game* game, int x, int y) {
		if(game->maze[y][x] == 2 ) 
		{  
        
       game->maze[y][x] = 0;  
        
			 LCD_SetPoint(
                        x * CELL_SIZE + SCREEN_OFFSET_X + CELL_SIZE/2,
                        y * CELL_SIZE + SCREEN_OFFSET_Y + CELL_SIZE/2,
                        Black
                    );
        
    }
		else if(game->maze[y][x] == 3)
		{
				for(int yi = -1; yi <= 1; yi++) {
                        for(int xi = -1; xi <= 1; xi++) {
                            LCD_SetPoint(
                                x * CELL_SIZE + SCREEN_OFFSET_X + CELL_SIZE/2 + xi,
                                y * CELL_SIZE + SCREEN_OFFSET_Y + CELL_SIZE/2 + yi,
                                POWER_PILL_COLOR
                            );
                        }
                    }
		}
		

}
/*
erasepacman():
When moving the joystick, erase the pacman image of the previous pacman position
*/

void erasepacman(Game* game,int x, int y)
{
	 int screenX = game->pacman.x * CELL_SIZE + SCREEN_OFFSET_X;
    int screenY = game->pacman.y * CELL_SIZE + SCREEN_OFFSET_Y;
    int size = CELL_SIZE - 2;
    
		for(int yi = -2; yi <= 3; yi++) {
                        for(int xi = -2; xi <= 3; xi++) {
                            LCD_SetPoint(
                                screenX + CELL_SIZE/2 + xi,
                                screenY + CELL_SIZE/2 + yi,
                                Black
                            );
                        }
                    }
}

/*
updatePacMan():
When using a joystick, I update the position of the pacman, 
the game score, determine whether all the pills have been eaten, 
and plot the position change of the pacman
*/

void updatePacMan(Game* game) 
{
	
		if((g_nextDirection!=DIR_NONE )&&(g_directionChanged!=0))
	{
				Direction old_direction=game->pacman.dir;
				game->pacman.dir=g_nextDirection;
				int newx=game->pacman.x;
				int newy=game->pacman.y;
				switch(game->pacman.dir) 
				{
						case DIR_NONE:  break;
						case DIR_RIGHT: newx++; break;
						case DIR_LEFT:  newx--; break;
						case DIR_UP:    newy--; break;
						case DIR_DOWN:  newy++; break;
				}
				if(canMove(game,newx,newy))
				{
					erasepacman(game,game->pacman.x,game->pacman.y);
					update_score(game,newx,newy);
					game->pacman.x=newx;
					game->pacman.y=newy;
					/*
					The edge area of the middle row can be teleported
					*/
					if(game->pacman.x==27&&game->pacman.y==14)
					{
						game->pacman.x=1;
						game->pacman.y=14;
					}
					if(game->pacman.x==0&&game->pacman.y==14)
					{
						game->pacman.x=26;
						game->pacman.y=14;
					}
					
				}
				else
				{
					game->pacman.dir=old_direction;
				}
				if(!victory){drawPacMan(game);}
				
	}
}
/*
update_score():
The game score is judged according to the pills eaten, and when all the pills are eaten, the game ends and the victory is output.
*/
void update_score(Game* game, int x, int y)
{
		if(game->maze[y][x]==2)
		{
			clear_score(140,15);
			score=score+10;
			scoreflag=scoreflag+10;
			game->maze[y][x]=0;
			if(scoreflag>=1000)
			{
				scoreflag=scoreflag-1000;
				game->lives = game->lives +1;
				updatelives(game->lives);
			}
			char str[20];
			sprintf(str, "%d", score); 
			GUI_Text(140, 15, (uint8_t *)str, White, 0);
			
		}
		else if(game->maze[y][x]==3)
		{
			clear_score(140,15);
			score=score+100;
			scoreflag=scoreflag+100;
			game->maze[y][x]=0;
			if(scoreflag>=1000)
			{
				scoreflag=scoreflag-1000;
				game->lives = game->lives +1;
				updatelives(game->lives);
			}
			char str[20];
			sprintf(str, "%d", score); 
			GUI_Text(140, 15, (uint8_t *)str, White, 0);
		}
		if(score==2940)
		{
			LCD_Clear(Black);
			GUI_Text(89, 150, (uint8_t *) "VICTORY!!", Yellow, 0);
			disable_timer(2);
			disable_RIT();
			victory=1;
		}
}
/*
updatelives():
update the remain lives, initial remain lives is 1
One is added every time the score reaches 1000
*/
void updatelives(int x)
{
		//reflash remain lives region using black
	   for(int yi = 0; yi <= 10; yi++) {
       for(int xi = 0; xi < 100; xi++) {
           LCD_SetPoint(130 + xi, 276 + yi, Black);
       }
   }
   //Update the latest remain lives
   char str[2];
   sprintf(str, "%d", x);
   GUI_Text(130, 276, (uint8_t *)str, White, 0);
}
/*
canMove():
If the pacman encounters a wall, or if it is outside the maze range, he will not be able to continue moving
*/
uint8_t canMove(const Game* game, int x, int y)
{
    if (x < 0 || x >= 28 || y < 0 || y >= 31) return 0;
		else if(game->maze[y][x]==1) return 0;
    return 1;
}

/*
drawMaze():
Draw a maze based on an array of mazes
*/
void drawMaze(const Game* game){
    for(int y = 0; y < MAZE_SIZE; y++) {
        for(int x = 0; x < MAZE_SIZE; x++) {
            switch(game->maze[y][x]) {
							  case 0:
									//passage
										break;
                case 1:
									//wall
                    drawCell(x, y, WALL_COLOR);
                    break;
                    
                case 2:
                    // standard pills
                    LCD_SetPoint(
                        x * CELL_SIZE + SCREEN_OFFSET_X + CELL_SIZE/2,
                        y * CELL_SIZE + SCREEN_OFFSET_Y + CELL_SIZE/2,
                        PILL_COLOR
                    );
                    break;
                    
                case 3:
                    // superpower(2x2)
                    for(int yi = -1; yi <= 1; yi++) {
                        for(int xi = -1; xi <= 1; xi++) {
                            LCD_SetPoint(
                                x * CELL_SIZE + SCREEN_OFFSET_X + CELL_SIZE/2 + xi,
                                y * CELL_SIZE + SCREEN_OFFSET_Y + CELL_SIZE/2 + yi,
                                POWER_PILL_COLOR
                            );
                        }
                    }
                    break;
								case 4:
									//A door reserved for ghosts in the central area to come out
									drawCell(x, y, Magenta);
									break;
            }
        }
    }  
}
/*
drawPacMan():
Draw an image of the Pacman based on x,y
*/
void drawPacMan(const Game* game) {
    int screenX = game->pacman.x * CELL_SIZE + SCREEN_OFFSET_X;
    int screenY = game->pacman.y * CELL_SIZE + SCREEN_OFFSET_Y;
    int size = CELL_SIZE - 2;
    
		for(int yi = -1; yi <= 3; yi++) {
                        for(int xi = -1; xi <= 3; xi++) {
                            LCD_SetPoint(
                                screenX + CELL_SIZE/2 + xi,
                                screenY + CELL_SIZE/2 + yi,
                                Cyan
                            );
                        }
                    }
    
}
/*
drawCell():It acts as an enlarged pixel with a magnification of cell_size.
The basic function that implements the display of a Pac-Man game, and is used to draw: walls, doors 
*/
void drawCell(int x, int y, uint16_t color) {
    int screenX = x * CELL_SIZE + SCREEN_OFFSET_X;
    int screenY = y * CELL_SIZE + SCREEN_OFFSET_Y;
    
   
    if(screenX >= 0 && screenX + CELL_SIZE < 240 && 
       screenY >= STATUS_BAR_HEIGHT && screenY + CELL_SIZE < 320) {
        for(int yi = 0; yi < CELL_SIZE; yi++) {
            for(int xi = 0; xi < CELL_SIZE; xi++) {
                LCD_SetPoint(screenX + xi, screenY + yi, color);
            }
        }
    }
}

/*
clear_score():
Used to erase old scores before updating scores
*/
void clear_score(int x,int y)
{
	  for(int yi = -1; yi <= 1; yi++) {
                        for(int xi = -1; xi <= 1; xi++) {
                            LCD_SetPoint(
                                x * CELL_SIZE + SCREEN_OFFSET_X + CELL_SIZE/2 + xi,
                                y * CELL_SIZE + SCREEN_OFFSET_Y + CELL_SIZE/2 + yi,
                                Black
                            );
                        }
                    }
}
