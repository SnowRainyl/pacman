typedef enum {
    GAME_PAUSE,
    GAME_RUNNING,
    GAME_OVER,
    GAME_WIN
} GameState;

// ????
typedef enum {
    DIR_NONE=0,
    DIR_LEFT=1,
    DIR_RIGHT=2,
    DIR_UP=3,
    DIR_DOWN=4
} Direction;

// ???????
typedef struct {
    int x;
    int y;
    Direction dir;
	  Direction  nextDir;
} PacMan;

typedef struct {
    uint8_t maze[SCREEN_WIDTH/CELL_SIZE][MAZE_HEIGHT/CELL_SIZE];  // 0:??, 1:?, 2:????, 3:???
    PacMan pacman;
    int score;
    int lives;
    int remainingTime;
    GameState state;
    int remainingPills;
} Game;