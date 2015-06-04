#include "objects/player.h"
#include "objects/wall.h"
#include "textures.h"
#include "draw.h"
#include <SDL/SDL_mixer.h>



typedef struct _level{
	int id;
	Walls * wallsList;
	Players * playersList;
	Textures * textureList;
	float width;
	float height;
	float cameraX;
	float cameraY;
	float cameraDestX;
	float cameraDestY;
	int isCameraMoving;
	Texture * background;
	Mix_Music * music;

} Level;

Level * initLevel();
int isAnyPlayerDead(Players * playersList, Level * currentLevel);
void resetLevel(Level * level);
void updateCamera(Level * level);
void stepCamera(Level* level);
void fillLevel(Level * level, int idLevel);
void emptyLevel(Level * level);
void fillLevelFromFile(Level * level, int nbStr);
void switchLevel(Level * level);
