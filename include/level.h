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

//Check if any player is out of levels boundaries
int isAnyPlayerDead(Players * playersList, Level * currentLevel);
//reset all players positions and camera.
void resetLevel(Level * level);
//the view follows the player
void updateCamera(Level * level);
//UNUSED FOR NOW : move smoothly the camera
void stepCamera(Level* level);
//fill level by hand (in case there is no file)
void fillLevel(Level * level, int idLevel);
//clean one level
void emptyLevel(Level * level);
//use level from file level+nbStr+.txt
void fillLevelFromFile(Level * level, int nbStr);
//go to level id+1.
void switchLevel(Level * level);
