#include <stdio.h>
#include <stdlib.h>
#include "physics.h"
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

Player * createPlayer(float width, float height, float posX, float posY, float movespeed, float jumpspeed, Color color){
	Player * newPlayer = calloc(1, sizeof(Player));
	if(newPlayer==NULL) exit(1);
	newPlayer->isCurrentPlayer = 0;
	newPlayer->width = width;
	newPlayer->height = height;
	newPlayer->posX = posX;
	newPlayer->posY = posY;
	newPlayer->color = color;
	newPlayer->movespeed = movespeed;
	newPlayer->jumpspeed = jumpspeed;
	newPlayer->hspeed = 0.0;
	newPlayer->vspeed = 0.0;

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

void setHSpeed(Player * thomas, int dir){
		
		thomas->hspeed = dir * thomas->movespeed;

}

void setVSpeed(Player * thomas, float speed){
	if(thomas->vspeed > -thomas->jumpspeed){
		thomas->vspeed -= speed;
	}
}

void isColliding(Players * playersList,  Walls * wallsList, int keyJump){

	Players * tempPlayer = playersList->firstPlayer;

	while(tempPlayer!=NULL){

		Player * player = tempPlayer->player;


		//COLLISION WITH WALLS

		playerWallCollisions(player, wallsList, keyJump);
		playerPlayerCollisions(player, playersList, keyJump);

		tempPlayer = tempPlayer->nextPlayer;
	}

	

}

void updatePlayerPos(Player * thomas){
	thomas->posX += thomas->hspeed;
	thomas->posY += thomas->vspeed;
}
