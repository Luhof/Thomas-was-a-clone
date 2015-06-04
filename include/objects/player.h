
#ifndef _PLAYER_H_
#define _PLAYER_H_
#include <SDL/SDL_mixer.h>

#ifdef __APPLE__
  #include <OpenGL/gl.h>
  #include <OpenGL/glu.h>
#else
  #include <GL/gl.h>
  #include <GL/glu.h>
#endif

#include "../colors.h"
#include "wall.h"
//#include "level.h"


typedef struct _player{
	int id;
	int isCurrentPlayer;
	struct _player * isHolding;
	float width;
	float height;
	float movespeed;
	float jumpspeed;
	float hspeed;
	float vspeed;
	float startPosX;
	float startPosY;
	float posX;
	float posY;
	float endPosX;
	float endPosY;
	Color color;
	Mix_Chunk *son;
} Player;

typedef struct _players{
	struct _player *player;
	struct _players *nextPlayer;
	struct _players *firstPlayer;
} Players;


Players* initPlayerList();
Player * createPlayer(float width, float height, float startPosX, float startPosY, float endPosX, float endPosY, float movespeed, float jumpspeed, Color color);

void addPlayer(Players *playersList, Player *player);
Player * switchCharacter(Players * playersList);
void setHSpeed(Players * playersList, int dir);
void setVSpeed(Players * playersList, float gravity);

void isColliding(Players * playersList, Walls * wallsList, int keyJump);

void updatePlayersPos(Players * playersList);
void updatePlayerPos(Player * thomas);


#endif