
#include "draw.h"

void drawThumbnails(Players * playersList){
	  
	glPushMatrix();
		glColor3ub(100,50,20);
		glBegin(GL_QUADS);
		glVertex2f(-50.0, -50.0);
		glVertex2f(50.0, -50.0);
		glVertex2f(15.0, 15.0);
		glVertex2f(-15.0, 15.0);
		glEnd();
	glPopMatrix();
}

void drawPlayers(Players * playersList){
	Players * tempPlayer = playersList->firstPlayer;
	while(tempPlayer!=NULL){
		drawPlayer(tempPlayer->player);
		tempPlayer = tempPlayer->nextPlayer;
	}
}



void drawWalls(Walls * wallsList){
	Walls * tempWall = wallsList->firstWall;
	while(tempWall!=NULL){
		drawWall(tempWall->wall);
		tempWall = tempWall->nextWall;
	}
}

void drawPlayer(Player * thomas){

		float width = thomas->width;
		float height = thomas->height;

		glPushMatrix();
		glColor3ub(thomas->color.r,thomas->color.g,thomas->color.b);
		glTranslatef(thomas->posX, thomas->posY, 0);
		glBegin(GL_QUADS);
		glVertex2f(-(width/2.0), -(height/2.0));
		glVertex2f((width/2.0), -(height/2.0));
		glVertex2f((width/2.0), (height/2.0));
		glVertex2f(-(width/2.0), (height/2.0));
		glEnd();
		glPopMatrix();

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