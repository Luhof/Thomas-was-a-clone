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


typedef struct _walls{
	struct Wall *wall;
	struct _walls *nextWall;
	struct _walls *firstWall;
}Walls;

Walls* initWallList();
void addWall(Walls * wallsList, Wall *wall);
Wall* createWall(float width, float height, float posX, float posY);



#endif