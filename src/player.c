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
	thomas->hspeed = 0;
	thomas->vspeed = 0;
}

void freePlayer(Player * thomas){
	thomas = NULL;
}

void drawPlayer(Player * thomas){

	float width = thomas->width;
	float height = thomas->height;
	//printf("posX = %f // hspeed = %f", thomas->posX, thomas->hspeed);
	glPushMatrix();
	//printf("%f\n", thomas->posX);
		glTranslatef(thomas->posX, thomas->posY, 0);

		glBegin(GL_QUADS);
			glVertex2f(-(width/2.0), -(height/2.0));
			glVertex2f((width/2.0), -(height/2.0));
			glVertex2f((width/2.0), (height/2.0));
			glVertex2f(-(width/2.0), (height/2.0));
		glEnd();
	glPopMatrix();
}

void setHSpeed(Player * thomas, float speed){
	//printf("speed : %f\n", speed);
	thomas->hspeed = speed;
	//printf("hspeed : %f\n", thomas->hspeed);
}

void updatePlayerPos(Player * thomas){
	printf("speed : %f\n", thomas->hspeed);
	thomas->posX += thomas->hspeed;
	printf("%f\n", thomas->posX);
}
