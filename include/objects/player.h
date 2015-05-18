#ifndef _PLAYER_H_
#define _PLAYER_H_

#ifdef __APPLE__
  #include <OpenGL/gl.h>
  #include <OpenGL/glu.h>
#else
  #include <GL/gl.h>
  #include <GL/glu.h>
#endif



#include "wall.h"


typedef struct _player{
	float width;
	float height;
	float movespeed;
	float jumpspeed;
	float hspeed;
	float vspeed;
	float posX;
	float posY;
	int dir;
} Player;

Player* initPlayer();
void setPlayerAttr(Player * thomas, float width, float height, float posX, float posY);
void freePlayer(Player * thomas);

void drawPlayer(Player * thomas);

void setHSpeed(Player * thomas, float speed);
void setVSpeed(Player * thomas, float speed);

void isColliding(Player * thomas, Wall ** walls, int keyJump);

void updatePlayerPos(Player * thomas);

#endif