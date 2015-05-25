
#include "draw.h"

void drawThumbnails(Players * playersList){
	float ratio = 1200.0/600.0;
	int i = 0;
	Players * tempPlayer = playersList->firstPlayer;

	while(tempPlayer != NULL){
		glPushMatrix();
			glTranslatef((-250.0*ratio)+15+(30*i), -235.0, 0);
			glColor3ub(tempPlayer->player->color.r,tempPlayer->player->color.g,tempPlayer->player->color.b);
			glBegin(GL_QUADS);
			glVertex2f(-15.0, -15.0);
			glVertex2f(15.0, -15.0);
			glVertex2f(15.0, 15.0);
			glVertex2f(-15.0, 15.0);
			glEnd();
		glPopMatrix();
		
		if(tempPlayer->player->isCurrentPlayer){
			glPushMatrix();
				glTranslatef((-250.0*ratio)+15+(30*i), -205.0, 0);
				glColor3ub(255,255,255);
				glBegin(GL_TRIANGLES);
				glVertex2f(-10, 10);
				glVertex2f(10, 10);
				glVertex2f(0, -7.50);
			glEnd();
			glPopMatrix();
		}
		i++;
		tempPlayer = tempPlayer->nextPlayer;
	}
	
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