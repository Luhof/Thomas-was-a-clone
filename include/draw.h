#include "objects/wall.h"
#include "objects/player.h"
#include "textures.h"
#include "physics.h"
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

//no comments on these prototypes
//their name should be enough :)
void drawWalls(Walls * wallsList);
void drawPlayers(Players * playersList);
void drawPlayersEndPos(Players * playersList);
void drawPlayer(Player * thomas);
void drawWall(Wall * wall);
void drawThumbnails(Players * playersList);
void drawPlayerEndPos(Player * thomas);
void drawSquareTex(float x, float y, Texture * myTexture);
void drawPlayerArrow(Player * thomas);
void drawTextures(Textures * textureList, int isFront);