#include "objects/wall.h"
#include "objects/player.h"

#include <stdlib.h>
#include <stdio.h>

Walls* initWallList(){
	
	Walls *list = calloc(1, sizeof(Walls));
	
	if(list==NULL){
        fprintf(stderr, "Error initializing walls list:(");
        exit(1);
    }

    list->wall = NULL;
    list->nextWall = NULL;

    return list;
}


void addWall(Walls * wallsList, Wall *wall){

	//on créé le nouveau mur
	Walls * newWall = calloc(1, sizeof(Walls));

	if(wallsList == NULL || newWall == NULL) exit(1);

	newWall->wall = wall;
	newWall->nextWall = wallsList->firstWall;

	wallsList->firstWall = newWall;

	//on ajoute le 
	
	
		//printf("tempNode nextWall posX : %f\n", tempNode->nextWall->wall->posX);

}


Wall* createWall(float width, float height, float posX, float posY){
	Wall* newWall = calloc(1, sizeof(Wall));
	newWall->width = width;
	newWall->height = height;
	newWall->posX = posX;
	newWall->posY = posY;

	return newWall;
}

void wallsCollision(Walls * wallsList, Player * player){
		

}