#include <stdio.h>
#include <stdlib.h>
#include "player.h"


void initPlayer(Player * thomas){
	thomas = calloc(1, sizeof(Player));

    if(thomas==NULL){
        fprintf(stderr, "Error initializing player :(");
        exit(1);
    }
}

void setPlayerAttr(Player * thomas, float width, float height, float posX, float posY){
	thomas->width = width;
	thomas->height = height;
	thomas->posX = posX;
	thomas->posY = posY;
}

void freePlayer(Player * thomas){
	thomas = NULL;
}

void drawPlayer(Player * thomas){

	float width = thomas->width;
	float height = thomas->height;
	glPushMatrix();
	glBegin(GL_QUADS);
		glVertex2f(-(width/2.0), -(height/2.0));
		glVertex2f((width/2.0), -(height/2.0));
		glVertex2f((width/2.0), (height/2.0));
		glVertex2f(-(width/2.0), (height/2.0));
	glEnd();
	glPopMatrix();
}















