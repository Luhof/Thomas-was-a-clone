#include <stdio.h>
#include <stdlib.h>
#
#include "objects/player.h"



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
		thomas->movespeed = 6.0;
		thomas->jumpspeed = 10.0;
		thomas->hspeed = 0.0;
		thomas->vspeed = 0.0;
		thomas->dir = 0;
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
		if(thomas->vspeed > -thomas->jumpspeed){
			thomas->vspeed -= speed;
		}

	}

	void isColliding(Player * thomas, Wall ** walls, int keyJump){


		int i;

		float coordBottomY =	thomas->posY - thomas->height/2.0;
		float coordTopY = 		thomas->posY + thomas->height/2.0;
		float coordLeftX = 		thomas->posX - thomas->width/2.0;
		float coordRightX = 	thomas->posX  + thomas->width/2.0;


		for(i=0; i<3; i++){

			float verticalDiff = 0.0;
			float horizontalDiff = 0.0;
			float wallTop = 		walls[i]->posY + walls[i]->height/2.0;
			float wallBottom = 		walls[i]->posY - walls[i]->height/2.0;
			float wallLeft = 		walls[i]->posX - walls[i]->width/2.0;
			float wallRight = 		walls[i]->posX + walls[i]->width/2.0;

			if(		coordBottomY+thomas->vspeed+0.01 < wallTop
				&&	coordTopY+thomas->vspeed > wallBottom
				&&	coordRightX > wallLeft
				&&	coordLeftX < wallRight)
			{
				thomas->vspeed = (keyJump * thomas->jumpspeed);	
			}

			//horizontal collision
			if(	coordBottomY < wallTop
				&&	coordTopY > wallBottom
				&&	coordRightX+thomas->hspeed >= wallLeft
				&&  coordLeftX+thomas->hspeed <= wallRight
				)
			{
				//if player is going RIGHT
				if(thomas->hspeed > 0){
					horizontalDiff = -1*(coordRightX - wallLeft);
				}
				//else if player is going LEFT
				else if(thomas->hspeed < 0){
					horizontalDiff = wallRight - coordLeftX;
				}
				thomas->hspeed = horizontalDiff;
			}

			//vertical collision
			if(	thomas->vspeed != 0
				&&	coordBottomY+thomas->vspeed < wallTop
				&&	coordTopY+thomas->vspeed > wallBottom
				&&	coordRightX > wallLeft
				&&	coordLeftX < wallRight)
			{
				//if player is FALLING
				if(thomas->vspeed < 0){
					verticalDiff =  (coordBottomY - wallTop);
					printf("verticalDiff = %f\n", verticalDiff);
				}
				//else if he is JUMPING
				else if(thomas->vspeed > 0){
					verticalDiff =  -1*(coordTopY - wallBottom);
				}
				thomas->posY += verticalDiff;
				thomas->vspeed = 0;
				
			}
		}

	}

	void updatePlayerPos(Player * thomas){
		thomas->posX += thomas->hspeed;
		thomas->posY += thomas->vspeed;
	}
