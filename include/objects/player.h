

#ifndef _PLAYER_H_
#define _PLAYER_H_

#ifdef __APPLE__
  #include <OpenGL/gl.h>
  #include <OpenGL/glu.h>
#else
  #include <GL/gl.h>
  #include <GL/glu.h>
#endif

#include "../colors.h"
#include "wall.h"



typedef struct _player{
	int id;
	int isCurrentPlayer;
	int isHolding;
	float width;
	float height;
	float movespeed;
	float jumpspeed;
	float hspeed;
	float vspeed;
	float posX;
	float posY;
	Color color;

} Player;

typedef struct _players{
	struct _player *player;
	struct _players *nextPlayer;
	struct _players *firstPlayer;
} Players;


Players* initPlayerList();
Player * createPlayer(float width, float height, float posX, float posY, float movespeed, float jumpspeed, Color color);

void addPlayer(Players *playersList, Player *player);
void switchCharacter(Players * playersList);
void setHSpeed(Players * playersList, int dir);
void setVSpeed(Players * playersList, float gravity);

void isColliding(Players * playersList, Walls * wallsList, int keyJump);

void updatePlayerPos(Player * thomas);

#endif