#include "objects/player.h"
#include "objects/wall.h"



typedef struct _level{
	int id;
	Walls * wallsList;
	Players * playersList;
	float width;
	float height;
	float cameraX;
	float cameraY;
	float cameraDestX;
	float cameraDestY;
	int isCameraMoving;
} Level;

Level * initLevel();
int isAnyPlayerDead(Players * playersList, Level * currentLevel);
void resetLevel(Level * level);
void updateCamera(Level * level);
void stepCamera(Level* level);