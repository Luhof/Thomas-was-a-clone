#include "objects/wall.h"

#include <stdlib.h>
#include <stdio.h>

Wall* initWall(){
	Wall *wall = calloc(1, sizeof(Wall));

    if(wall==NULL){
        fprintf(stderr, "Error initializing wall :(");
        exit(1);
    }

    return wall;
}

void setWallAttr(Wall * wall, float width, float height, float posX, float posY){
	wall->width = width;
	wall->height = height;
	wall->posX = posX;
	wall->posY = posY;
}

void drawWall(Wall * wall){

	float width = wall->width;
	float height = wall->height;
	glPushMatrix();
		glTranslatef(wall->posX, wall->posY, 0);
		glBegin(GL_QUADS);
			glVertex2f(-(width/2.0), -(height/2.0));
			glVertex2f((width/2.0), -(height/2.0));
			glVertex2f((width/2.0), (height/2.0));
			glVertex2f(-(width/2.0), (height/2.0));
		glEnd();
	glPopMatrix();
}