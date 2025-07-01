// pacman.h
#ifndef __PACMAN_H
#define __PACMAN_H

#include "LPC17xx.h"
#include "GLCD.h"
#include "timer.h"
#include "RIT.h"

#define SCREEN_WIDTH     240   //landtiger simulator SCREEN_WIDTH
#define SCREEN_HEIGHT    320   //landtiger simulator SCREEN_HEIGHT

#define STATUS_HEIGHT    40   // top 40 height shows Game Over In and SCORE
#define LIVES_HEIGHT     30   // bottom 30 height shows remain lives
#define MAZE_HEIGHT      (SCREEN_HEIGHT - STATUS_HEIGHT - LIVES_HEIGHT)  //maze heitght

// pills size and pacman size
#define PILL_SIZE       2     // for() function draw it, standard pills size
#define POWER_PILL_SIZE 6     // for() function draw it, power pills size
#define PACMAN_SIZE     8     // for() function draw it, pacman size


#define WALL_COLOR Blue2
#define PILL_COLOR White
#define POWER_PILL_COLOR Yellow
#define PACMAN_COLOR Yellow
#define BACKGROUND_COLOR Black
#define TEXT_COLOR White


// pacman direction 
typedef enum {
    DIR_NONE=0,
    DIR_LEFT=1,
    DIR_RIGHT=2,
    DIR_UP=3,
    DIR_DOWN=4
} Direction;

//pacman struct
typedef struct {
    int x;
    int y;
    Direction dir;
	  Direction  nextDir;
} PacMan;
//whole game struct
typedef struct {
    uint8_t maze[SCREEN_WIDTH/CELL_SIZE][MAZE_HEIGHT/CELL_SIZE];  //0:passage,1:walls,2:standard pills,3:power pills,4:door
    PacMan pacman;
    int score;  //show in screen the current score
    int lives; //remain lives
    int remainingPills;
		int isPaused;
} Game;

extern Game gameState;     //whole game struct
extern int score;         //show in screen
extern int last_second;  //60s
extern volatile Direction g_nextDirection;
extern volatile int g_directionChanged;

void initGame(Game* game);
void drawMaze(const Game* game);
void generatePowerPills(Game* game);
uint8_t canMove(const Game* game, int x, int y);
void drawPacMan(const Game* game);
void updatePacMan(Game* game);
void update_score(Game* game, int x, int y);
void clear_score(int x,int y);
void updatelives(int x);
#endif
