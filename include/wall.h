#ifdef __APPLE__
  #include <OpenGL/gl.h>
  #include <OpenGL/glu.h>
#else
  #include <GL/gl.h>
  #include <GL/glu.h>
#endif

#ifndef _WALL_H_
#define _WALL_H_

typedef struct Wall{
	float width;
	float height;
	float posX;
	float posY;
}Wall;

Wall* initWall();
void setWallAttr(Wall * wall, float width, float height, float posX, float posY);
void drawWall(Wall * wall);

#endif