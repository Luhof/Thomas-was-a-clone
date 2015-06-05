
#include "draw.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

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
	tempPlayer = playersList->firstPlayer;
	while(tempPlayer!= NULL){
		if(tempPlayer->player->isCurrentPlayer==1) drawPlayerArrow(tempPlayer->player);
		tempPlayer = tempPlayer->nextPlayer;
	}
}

void drawPlayersEndPos(Players * playersList){
	Players * tempPlayer = playersList->firstPlayer;
	while(tempPlayer!=NULL){
		drawPlayerEndPos(tempPlayer->player);
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

void drawPlayerArrow(Player * thomas){
		glPushMatrix();
			glColor4f(1,1,1,0.5);
			glTranslatef(thomas->posX, thomas->posY+thomas->height/2.0+10.0,0);
			glBegin(GL_TRIANGLES);
			glVertex2f(-7,7);
			glVertex2f(7, 7);
			glVertex2f(0,-7);
			glEnd();
		glPopMatrix();
}

void drawPlayerEndPos(Player * thomas){
		float width = thomas->width;
		float height = thomas->height;

		glPushMatrix();
		glColor3ub(thomas->color.r,thomas->color.g, thomas->color.b);
		glTranslatef(thomas->endPosX, thomas->endPosY, 0);
		if(isPlayerOnEndPos(thomas)){
			glColor3ub(255, 255, 255);
			glBegin(GL_QUADS);
		}
		else glBegin(GL_LINE_LOOP);
		glVertex2f(-(width/2.0), -(height/2.0));
		glVertex2f((width/2.0), -(height/2.0));
		glVertex2f((width/2.0), (height/2.0));
		glVertex2f(-(width/2.0), (height/2.0));
		glEnd();
		glPopMatrix();
}



void drawWall(Wall * wall){
glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);


	float width = wall->width;
	float height = wall->height;
	
	glPushMatrix();
		glColor4f(0,0,0,0.2);
		glTranslatef(wall->posX-30.0, wall->posY-30, 0);
		glBegin(GL_QUADS);
			glVertex2f(-(width/2.0), -(height/2.0));
			glVertex2f((width/2.0), -(height/2.0));
			glVertex2f((width/2.0), (height/2.0));
			glVertex2f(-(width/2.0), (height/2.0));
		glEnd();
	glPopMatrix();

	glPushMatrix();
		//glColor4f(0.5,0.3,0.6,0.5);
		glTranslatef(wall->posX-wall->width/2.0, wall->height/2.0+wall->posY, 0);
		glBegin(GL_TRIANGLES);
			glVertex2f(0, 0);
			glVertex2f(0.0, -30.0);
			glVertex2f(-30.0, -30.0);
		glEnd();
	glPopMatrix();

	glPushMatrix();
		//glColor4f(0.5,0.3,0.6,0.5);
		glTranslatef(wall->posX+wall->width/2.0, wall->posY-wall->height/2.0, 0);
		glBegin(GL_TRIANGLES);
			glVertex2f(0, 0);
			glVertex2f(-30.0, -30.0);
			glVertex2f(-30.0, 0.0);
		glEnd();
	glPopMatrix();

	glPushMatrix();
		glColor3ub(255,255,255);
		glTranslatef(wall->posX, wall->posY, 0);
		glBegin(GL_QUADS);
			glVertex2f(-(width/2.0), -(height/2.0));
			glVertex2f((width/2.0), -(height/2.0));
			glVertex2f((width/2.0), (height/2.0));
			glVertex2f(-(width/2.0), (height/2.0));
		glEnd();
	glPopMatrix();
}

void drawTextures(Textures * textureList, int isFront){
	Textures * tempTexture = textureList->firstTexture;
	while(tempTexture!=NULL){
		
		if(isFront==tempTexture->myTexture->isFront)
			drawSquareTex(tempTexture->myTexture->textureX, tempTexture->myTexture->textureY, tempTexture->myTexture);
		
		tempTexture = tempTexture->nextTexture;

	}
	
}

void drawSquareTex(float x, float y, Texture * myTexture){

glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_BLEND);
    
    //SDL_FreeSurface(myTexture->texture); // Image contenu sur GPU
	//printf("w : %f h : %f\n", (float)myTexture->texture->w, (float)myTexture->texture->h);


 glBindTexture(GL_TEXTURE_2D, myTexture->textureId);


glPushMatrix();
glTranslatef(x,y,1);

float w = (float)myTexture->texture->w;
float h = (float)myTexture->texture->h;
glBegin(GL_QUADS);
			
			glTexCoord2f(0,1);
			glVertex2f(-w/2.0, -h/2.0);
			
			glTexCoord2f(1,1);
			glVertex2f(w/2.0, -h/2.0);
			
			glTexCoord2f(1,0);
			glVertex2f(w/2, h/2);

			glTexCoord2f(0,0);
			glVertex2f(-w/2, h/2);

		glEnd();

glPopMatrix();

//glBindTexture(GL_TEXTURE_2D,0);

//glDeleteTextures(1, &textureId);
}