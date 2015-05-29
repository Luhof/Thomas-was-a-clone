#include <stdio.h>
#include <stdlib.h>
#include "physics.h"
#include "level.h"
#include "objects/player.h"
#include "objects/wall.h"




Players* initPlayerList(){
	
	Players *playersList = calloc(1, sizeof(Players));
	
	if(playersList==NULL){
        fprintf(stderr, "Error initializing players list:(");
        exit(1);
    }

    playersList->player = NULL;
    playersList->nextPlayer = NULL;

    return playersList;
}

Player * createPlayer(float width, float height, float startPosX, float startPosY, float endPosX, float endPosY, float movespeed, float jumpspeed, Color color, char* son){
	Player * newPlayer = calloc(1, sizeof(Player));
	if(newPlayer==NULL) exit(1);
	newPlayer->isCurrentPlayer = 0;
	newPlayer->width = width;
	newPlayer->height = height;
	newPlayer->startPosX = startPosX;
	newPlayer->startPosY = startPosY;
	newPlayer->posX = startPosX;
	newPlayer->posY = startPosY;
	newPlayer->endPosX = endPosX;
	newPlayer->endPosY = endPosY;
	newPlayer->color = color;
	newPlayer->movespeed = movespeed;
	newPlayer->jumpspeed = jumpspeed;
	newPlayer->hspeed = 0.0;
	newPlayer->vspeed = 0.0;
	newPlayer->isHolding = NULL;
	newPlayer->son = Mix_LoadWAV(son);

	return newPlayer;

}

void addPlayer(Players *playersList, Player *player){
	
	Players * newPlayer = calloc(1, sizeof(Players));

	if(playersList == NULL || newPlayer == NULL) exit(1);

	if(playersList->firstPlayer==NULL) player->id = 0;
	else player->id = (playersList->firstPlayer->player->id) + 1;

	newPlayer->player = player;
	newPlayer->nextPlayer = playersList->firstPlayer;

	playersList->firstPlayer = newPlayer;

	

	//dealing with IDs
	
	
}

void switchCharacter(Players * playersList){

	Players * tempPlayer = playersList->firstPlayer;

		while(tempPlayer!=NULL){
			if(tempPlayer->player->isCurrentPlayer==1){
				tempPlayer->player->isCurrentPlayer = 0;
				tempPlayer = tempPlayer->nextPlayer;
				if(tempPlayer!=NULL){
					tempPlayer->player->isCurrentPlayer = 1;
					//level->isCameraMoving = 1;
					//level->cameraDestX = tempPlayer->player->posX;
					//level->cameraDestY = tempPlayer->player->posY;
					break;
				}
					playersList->firstPlayer->player->isCurrentPlayer = 1;
					//level->isCameraMoving = 1;
					//level->cameraDestX = playersList->firstPlayer->player->posX;
					//level->cameraDestY = playersList->firstPlayer->tempPlayer->player->posY;
					break;
				
			}
			tempPlayer=tempPlayer->nextPlayer;
		}

	

}

void setHSpeed(Players * playersList, int dir){
		
	Players * tempPlayer = playersList->firstPlayer;
	while(tempPlayer!=NULL){

		tempPlayer->player->hspeed = 0;

		if(tempPlayer->player->isCurrentPlayer){
			tempPlayer->player->hspeed = dir * tempPlayer->player->movespeed;
		}

		tempPlayer = tempPlayer->nextPlayer;
	}
}

void setVSpeed(Players * playersList, float gravity){

	Players * tempPlayer = playersList->firstPlayer;
	while(tempPlayer!=NULL){
		if(tempPlayer->player->vspeed > -tempPlayer->player->jumpspeed){
			tempPlayer->player->vspeed -= gravity;
		}
		tempPlayer = tempPlayer->nextPlayer;
	}
}

void isColliding(Players * playersList,  Walls * wallsList, int keyJump){

	getParents(playersList);

	Players * tempPlayer = playersList->firstPlayer;

	while(tempPlayer!=NULL){

		Player * player = tempPlayer->player;

		if(player->isHolding!=NULL && player->isCurrentPlayer!=1){
			
			Player * tempParent = player->isHolding;
				while(tempParent->isHolding!=NULL && tempParent->isCurrentPlayer!=1){
					//printf("there is a holder :o\n");
					
					playerWallCollisions(player->isHolding, wallsList, keyJump);
					playerPlayerCollisions(player->isHolding, playersList, wallsList, keyJump);
					tempParent->hspeed = tempParent->isHolding->hspeed;
					tempParent = tempParent->isHolding;
				}

			
			
			playerWallCollisions(player->isHolding, wallsList, keyJump);
			playerPlayerCollisions(player->isHolding, playersList, wallsList, keyJump);

			player->hspeed = player->isHolding->hspeed;
			//here need to add a loop for parents...
		}

		
		playerWallCollisions(player, wallsList, keyJump);
		playerPlayerCollisions(player, playersList, wallsList, keyJump);
		tempPlayer = tempPlayer->nextPlayer;
	}


	//empty list
	tempPlayer = playersList->firstPlayer;
	while(tempPlayer!=NULL){
		tempPlayer->player->isHolding = NULL;
		tempPlayer = tempPlayer->nextPlayer;
	}

	

	/*tempPlayer = playersList->firstPlayer;
	while(tempPlayer!=NULL){

		Player * player = tempPlayer->player;

		if(player->isHolding!=NULL){
			player->hspeed = player->isHolding->hspeed;
			//printf("player %d speed : %f\n", player->id, player->hspeed);
			//tempPlayer->player->isHolding=tempPlayer->player->isHolding->isHolding;
			//player->isHolding = NULL;
		}
		tempPlayer = tempPlayer->nextPlayer;
	}*/

	

}

void updatePlayersPos(Players * playersList){
	Players * tempPlayer = playersList->firstPlayer;
	while(tempPlayer!=NULL){
		updatePlayerPos(tempPlayer->player);
		tempPlayer = tempPlayer->nextPlayer;
	}
}


void updatePlayerPos(Player * thomas){
	thomas->posX += thomas->hspeed;
	thomas->posY += thomas->vspeed;
}
