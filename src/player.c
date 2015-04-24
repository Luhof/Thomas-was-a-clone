#include <stdio.h>
#include <stdlib.h>
#include "player.h"



Player* initPlayer(){
	Player* thomas = calloc(1, sizeof(Player));

    if(thomas==NULL){
        fprintf(stderr, "Error initializing player :(");
        exit(1);
    }
    return thomas;
}

void setPlayerAttr(Player * thomas, float width, float height, float posX, float posY){
	thomas->width = width;
	thomas->height = height;
	thomas->posX = posX;
	thomas->posY = posY;
	thomas->hspeed = 0;
	thomas->vspeed = 0;
}


void drawPlayer(Player * thomas){

	float width = thomas->width;
	float height = thomas->height;
	glPushMatrix();
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
	thomas->hspeed = speed;
}

void setVSpeed(Player * thomas, float speed){

	thomas->vspeed = speed;
}

int isColliding(Player * thomas, Wall * wall, float gravity){


	float coordBottomY =	thomas->posY - thomas->height/2.0;
	//float coordTopY = 		thomas->posY + thomas->height/2.0;
	float coordLeftX = 		thomas->posX - thomas->width/2.0;
	float coordRightX = 	thomas->posX + thomas->width/2.0;

	float wallTop = 		wall->posY + wall->height/2.0;
	float wallBottom = 		wall->posY - wall->height/2.0;
	float wallLeft = 		wall->posX - wall->width/2.0;
	float wallRight = 		wall->posX + wall->width/2.0;

	//vertical bottom collision
	thomas->vspeed = gravity;
	if((coordBottomY + thomas->vspeed)<= wallTop && (coordBottomY + thomas->vspeed)>=wallBottom){
		if((coordLeftX >= wallLeft && coordLeftX <= wallRight) || (coordRightX <= wallRight && coordRightX >= wallLeft)){
			//player can't move
			thomas->vspeed = 0;

			//pixel perfect collision
			if(coordBottomY>wallTop){
				float verticalDiff = coordBottomY-wallTop;
				printf("verticalDiff = %f\n", verticalDiff);
				thomas->vspeed = -verticalDiff;
			}
		}
	}

	//problem : need to check horizontal collisions and vertical collision separately
	/*horizontal collision
	if((coordLeftX + thomas->hspeed <= wallLeft)|| (coordRightX + thomas->hspeed >= wallLeft)){
		thomas->hspeed = 0;
	}*/

	return 0;
	
}

void updatePlayerPos(Player * thomas){
	thomas->posX += thomas->hspeed;
	thomas->posY += thomas->vspeed;
}
