#include "level.h"

Level * initLevel(){

	Color colors[3] = {setColor(105, 210, 231), setColor(243,134,48), setColor(155, 89, 182) };

	Level * level = calloc(1, sizeof(Level));
	level->id = 1;

	level->width = 2000.0;
	level->height = 2000.0;


	Walls* wallsList = initWallList();
	Wall * wall1 = createWall(300.0, 75.0, -250.0, 0.0);
	Wall * wall2 = createWall(25.0, 250.0, 200.0, 0.0);
	Wall * wall3 = createWall(300.0, 75.0, 100.0, -100.0);
	addWall(wallsList, wall3);
	addWall(wallsList, wall2);
	addWall(wallsList, wall1);

	//set player attributes
	Players *playersList = initPlayerList();
	Player *thomas = createPlayer(15.0, 80.0, -45.0, 100.0, -100, -37.50, 4.0, 10.0, colors[0], "./data/saut.wav");
	Player *marcel = createPlayer(70.0, 70.0, -30, 40.0, 100, 172.50, 4.0, 15.0, colors[1], "./data/saut.wav");
	Player *pouity = createPlayer(60.0, 25.0, -180, 40.0, 170, 177.50, 4.0, 10.0, colors[2], "./data/saut.wav");
	thomas->isCurrentPlayer = 1;
	addPlayer(playersList, pouity);
	addPlayer(playersList, marcel);
	addPlayer(playersList, thomas);

	level->wallsList = wallsList;
	level->playersList = playersList;

	level->cameraX = thomas->posX;
	level->cameraY = thomas->posY - 100.0;

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
		if(tempPlayer->player->isCurrentPlayer==1){
			printf("start restarting camera\n");
			level->cameraDestX = tempPlayer->player->startPosX;
			level->cameraDestY = tempPlayer->player->startPosY;
			level->isCameraMoving = 1;
			printf("done restarting camera\n");
			break;
		}
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

	level->cameraX = -tempPlayer->player->posX;
	level->cameraY = -tempPlayer->player->posY;
	/*if(tempPlayer->player->posX >0){
		if(tempPlayer->player->posX - level->cameraX > 200.0){
			//printf(">0  update camera pos X %f\n", tempPlayer->player->posX - level->cameraX);
			level->cameraX -= tempPlayer->player->hspeed;
		}
	}
	else if(tempPlayer->player->posX < 0){
			if(tempPlayer->player->posX - level->cameraX < -200.0){
			level->cameraX += -1*(tempPlayer->player->hspeed);
			//printf("<0 update camera pos X %f\n", tempPlayer->player->posX + level->cameraX);
		}
	}

	if(tempPlayer->player->posY > 0){
		if(tempPlayer->player->posY - level->cameraY > 100.0){
			level->cameraY -= tempPlayer->player->vspeed;
		}
	}
	else if(tempPlayer->player->posY < 0){
		if(tempPlayer->player->posY - level->cameraY < -100.0){
			level->cameraY += -1*(tempPlayer->player->vspeed);
		}
	}*/

}

	






void stepCamera(Level* level){

	int xDone = 0;
	int yDone = 0;

	if(level->isCameraMoving==1){
		printf("camera is moving x : %f et y %f\n to x : %f et y : %f\n", level->cameraX, level->cameraY, level->cameraDestX, level->cameraDestY);
		if(level->cameraX < level->cameraDestX){
			
				level->cameraX += 10.0;
				if(level->cameraX > level->cameraDestX){
					level->cameraX -= level->cameraX - level->cameraDestX;
					xDone = 1;
				}
		}

		else if(level->cameraX > level->cameraDestX){
			
				level->cameraX -= 10.0;
				if(level->cameraX < level->cameraDestX){
					level->cameraX += level->cameraDestX - level->cameraX;
					xDone = 1;
				}
					
			
		}

		if(level->cameraY > level->cameraDestY){

			level->cameraY -= 10.0;
			if(level->cameraY < level->cameraDestY){
				level->cameraY += level->cameraDestY - level->cameraY;
				yDone = 1;
			}
		}

		else if(level->cameraY < level->cameraDestY){

			level->cameraY += 10.0;
			if(level->cameraY > level->cameraDestY){
				level->cameraY -= level->cameraY-level->cameraDestY;
				yDone = 1;
			}
		}
	}

	if(xDone == 1 && yDone == 1)
		level->isCameraMoving = 0;

		
	
	

}