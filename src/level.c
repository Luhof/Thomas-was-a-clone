#include "level.h"

Level * initLevel(){

	Color colors[3] = {setColor(105, 210, 231), setColor(243,134,48), setColor(155, 89, 182) };

	Level * level = calloc(1, sizeof(Level));
	level->id = 1;

	level->width = 2000.0;
	level->height = 2000.0;


	Walls* wallsList = initWallList();
	Wall * wall1 = createWall(300.0, 75.0, -250.0, -100.0);
	Wall * wall2 = createWall(25.0, 250.0, 200.0, -100.0);
	Wall * wall3 = createWall(300.0, 75.0, 100.0, -100.0);
	addWall(wallsList, wall3);
	addWall(wallsList, wall2);
	addWall(wallsList, wall1);

	//set player attributes
	Players *playersList = initPlayerList();
	Player *thomas = createPlayer(15.0, 80.0, -45.0, 100.0, -100, -37.50, 4.0, 10.0, colors[0], "./data/saut.wav");
	Player *marcel = createPlayer(70.0, 70.0, -30, 40.0, 100, 172.50, 4.0, 15.0, colors[1], "./data/saut.wav");
	Player *pouity = createPlayer(25.0, 50.0, -100, 40.0, 170, 177.50, 4.0, 10.0, colors[2], "./data/saut.wav");
	thomas->isCurrentPlayer = 1;
	addPlayer(playersList, pouity);
	addPlayer(playersList, marcel);
	addPlayer(playersList, thomas);

	level->wallsList = wallsList;
	level->playersList = playersList;

	level->cameraX = 0;
	level->cameraY = 0;

	//level->cameraDestX = thomas->startPosX;

	return level;
}


int isAnyPlayerDead(Players * playersList, Level * currentLevel){

	Players * tempPlayer = playersList->firstPlayer;
	while(tempPlayer!=NULL){
		if(		tempPlayer->player->posX < currentLevel->width/2.0*-1
			||	tempPlayer->player->posX > currentLevel->width/2.0
			||	tempPlayer->player->posY < currentLevel->height/2.0*-1
			||	tempPlayer->player->posY > currentLevel->height/2.0){
			return 1;
		}
		tempPlayer = tempPlayer->nextPlayer;
	}
	return 0;

}


void resetLevel(Level * level){

	Players * tempPlayer = level->playersList->firstPlayer;
	while(tempPlayer!=NULL){
		tempPlayer->player->posX = tempPlayer->player->startPosX;
		tempPlayer->player->posY = tempPlayer->player->startPosY;
		tempPlayer = tempPlayer->nextPlayer;
	}

}

void updateCamera(Level * level){
	Players * tempPlayer = level->playersList->firstPlayer;
	while(tempPlayer!=NULL){
		if(tempPlayer->player->isCurrentPlayer == 1){
			break;
		}
		tempPlayer = tempPlayer->nextPlayer;
	}

	if(tempPlayer->player->posX >0){
		if(tempPlayer->player->posX - level->cameraX > 200.0){
			//printf(">0  update camera pos X %f\n", tempPlayer->player->posX - level->cameraX);
			level->cameraX -= tempPlayer->player->hspeed;
		}
	}
	else if(tempPlayer->player->posX < 0){
			if(tempPlayer->player->posX - level->cameraX < -200.0){
			level->cameraX += -1*(tempPlayer->player->hspeed);
			//printf("<0 update camera pos X %f\n", tempPlayer->player->posX + level->cameraX);
			
			//level->cameraY = -1*tempPlayer->player->posY;
		}
	}

}

	






void stepCamera(Level* level){

	/*
	if(level->cameraX != level->cameraDestX){
		if(level->cameraX < level->cameraDestX){
			
				level->cameraX += 3;
		}
		if(level->cameraX > level->cameraDestX){
			
				level->cameraX -= 3;
			
		}
	}
	*/

}