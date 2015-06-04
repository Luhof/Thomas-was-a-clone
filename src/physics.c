#include "physics.h"
#include <stdio.h>

int placeMeeting(float top1, float right1, float bottom1, float left1, float top2, float right2, float bottom2, float left2){
	if(		bottom1 < top2
		&&	top1 > bottom2
		&&	right1 > left2
		&&	left1 < right2){
		return 1;
	}

	else{
		return 0;
	}
}

void playerWallCollisions(Player * player, Walls * wallsList, int keyJump){
	
	float verticalDiff = 0.0;
	float horizontalDiff = 0.0;
	Walls * tempWall = wallsList->firstWall;
	tempWall = wallsList->firstWall;

	float coordBottomY =	player->posY - player->height/2.0;
	float coordTopY = 		player->posY + player->height/2.0;
	float coordLeftX = 		player->posX - player->width/2.0;
	float coordRightX = 	player->posX  + player->width/2.0;
	
	while(tempWall!=NULL){

		float wallTop = 		tempWall->wall->posY + tempWall->wall->height/2.0;
		float wallBottom = 		tempWall->wall->posY - tempWall->wall->height/2.0;
		float wallLeft = 		tempWall->wall->posX - tempWall->wall->width/2.0;
		float wallRight = 		tempWall->wall->posX + tempWall->wall->width/2.0;
		
		/**
		**	vertical collision
		**/
		if(player->vspeed!=0 &&
			placeMeeting(coordTopY+player->vspeed, coordRightX, coordBottomY+player->vspeed, coordLeftX, wallTop, wallRight, wallBottom, wallLeft)==1)
			{

			//if player is FALLING, he is on the floor
			if(player->vspeed < 0){
				verticalDiff = (coordBottomY - wallTop);
				//Since the player is on the ground he can jump !!
				if(player->isCurrentPlayer==1){
					player->vspeed = (keyJump * player->jumpspeed);
					if(keyJump == 1) Mix_PlayChannel(1, player->son, 0);
				}
				
				else player->vspeed = 0;
			}

			//else if he is JUMPING
			else if(player->vspeed > 0){
				verticalDiff =  -1*(wallBottom - coordTopY);
				player->vspeed = 0;
			}
			player->posY -= verticalDiff;			
		}

		/**
		**	horizontal collision
		**/
		if(placeMeeting(coordTopY, coordRightX+player->hspeed,coordBottomY, coordLeftX+player->hspeed, wallTop, wallRight, wallBottom, wallLeft)){
				if(player->isHolding!=NULL && player->isHolding->isCurrentPlayer ==1){
					player->hspeed = 0;
					player->vspeed = 0;
				}	
			//if player is going RIGHT
			if(player->hspeed > 0){
				horizontalDiff = (coordRightX - wallLeft);
			}
			//else if player is going LEFT
			else if(player->hspeed < 0){
				horizontalDiff = -1*(wallRight - coordLeftX);
			}
			player->hspeed = 0;
			player->posX -= horizontalDiff;
		}		
		
		tempWall = tempWall->nextWall;
	}


}

void playerPlayerCollisions(Player * player, Players *playersList, Walls * wallsList, int keyJump){
		/* CHECK COLLISION WITH OTHER PLAYERS */
		
		//ok should be done for everyone :(
		float verticalDiff = 0.0;
		float horizontalDiff = 0.0;
		float coordBottomY =	player->posY - player->height/2.0;
		float coordTopY = 		player->posY + player->height/2.0;
		float coordLeftX = 		player->posX - player->width/2.0;
		float coordRightX = 	player->posX + player->width/2.0;

		Players * tempPlayer2 = playersList->firstPlayer;
		while(tempPlayer2!=NULL){

			verticalDiff = 0.0;
			horizontalDiff = 0.0;
			Player * player2 = tempPlayer2->player;
			
			
			if(player2->id != player->id){
				float coordBottomY2 =	player2->posY - player2->height/2.0;
				float coordTopY2 = 		player2->posY + player2->height/2.0;
				float coordLeftX2 = 	player2->posX - player2->width/2.0;
				float coordRightX2 = 	player2->posX  + player2->width/2.0;


				/**
				** vertical collision
				**/
				if(player->vspeed!=0 &&
				placeMeeting(coordTopY+player->vspeed, coordRightX, coordBottomY+player->vspeed, coordLeftX, coordTopY2, coordRightX2, coordBottomY2, coordLeftX2)==1)
				{
									
					//if player is FALLING, he is on the top of the bottom player (player2)...	
					if(player->vspeed < 0){
						//printf("collision from top\n");
						verticalDiff = (coordBottomY - coordTopY2);
						player->posY -= verticalDiff; 
						//Since the player is on the ground he can jump !!
						if(player->isCurrentPlayer==1){
							player->vspeed = (keyJump * player->jumpspeed);
							if(keyJump == 1) Mix_PlayChannel(1, player->son, 0);

						}
						else player->vspeed = 0;
						
						/*playerPlayerCollisions(player, playersList, wallsList, keyJump);
						playerWallCollisions(player, wallsList, keyJump);*/
					}

					//else if he is JUMPING
					else if(player->vspeed > 0){
						verticalDiff =  -1*(coordBottomY2 - coordTopY);
						//printf("collision from bottom\n");
						//player->hspeed = 0;
						player->vspeed = 0;
						//player->hspeed = 0;
						if(player2->isHolding!=NULL && player2->isHolding->isCurrentPlayer ==1){
							//player2->hspeed = 0;
							player2->vspeed = 0;
							//player->hspeed = 0;
							player->vspeed = 0;

						}
						//player2->vspeed = 0;
						player->posY-=verticalDiff;
					}
					//else player->vspeed = 0;

					
								
				}

				/**
				**	horizontal collision
				**/
				if(placeMeeting(coordTopY, coordRightX+player->hspeed,coordBottomY, coordLeftX+player->hspeed, coordTopY2, coordRightX2, coordBottomY2, coordLeftX2))
				{
					//printf("collision from side\n");
					//if player is going RIGHT
					if(player->hspeed > 0){
						horizontalDiff = (coordRightX - coordLeftX2);
					}
					//else if player is going LEFT
					else if(player->hspeed < 0){
						horizontalDiff = -1*(coordRightX2 - coordLeftX);
					}
					player->hspeed = horizontalDiff; 
				}


				
			}

			tempPlayer2 = tempPlayer2->nextPlayer;
		
		}


}

void getParents(Players * playersList){

	Players * tempPlayer = playersList->firstPlayer;
	Player * player;
	Player * player2;
	while(tempPlayer!=NULL){
		player = tempPlayer->player;

		float coordBottomY =	player->posY - player->height/2.0;
		float coordTopY = 		player->posY + player->height/2.0;
		float coordLeftX = 		player->posX - player->width/2.0;
		float coordRightX = 	player->posX + player->width/2.0;
		

		Players * tempPlayer2 = playersList->firstPlayer;
		while(tempPlayer2!=NULL){
				player2 = tempPlayer2->player;
				if(player2->id != player->id){
				float coordBottomY2 =	player2->posY - player2->height/2.0;
				float coordTopY2 = 		player2->posY + player2->height/2.0;
				float coordLeftX2 = 	player2->posX - player2->width/2.0;
				float coordRightX2 = 	player2->posX  + player2->width/2.0;
				if(placeMeeting(coordTopY+player->vspeed, coordRightX, coordBottomY+player->vspeed, coordLeftX, coordTopY2, coordRightX2, coordBottomY2, coordLeftX2)==1)
				{
										
					//if player is FALLING, he is on the top of the bottom player (player2)...	
					if(player->vspeed < 0){
						//printf("player %d is holding %d\n", player->id, player2->id);
						player->isHolding = player2;
						//printf("player %d parent : %d\n", player->id, player->isHolding->id);
					}

					//else if he is JUMPING
					else if(player->vspeed > 0){
						player2->isHolding = player;
						//printf("player %d is holding %d\n", player2->id, player->id);
						//printf("player %d parent : %d\n", player2->id, player->id);
					}

					else{
						/*player->isHolding = NULL;
						player2->isHolding = NULL;*/
					}			
				}

					
				}
				tempPlayer2 = tempPlayer2->nextPlayer;


			}
				tempPlayer = tempPlayer->nextPlayer;

		
	}

	

}


int isPlayerOnEndPos(Player * player){

	float coordBottomY =	player->posY - player->height/2.0;
	float coordTopY = 		player->posY + player->height/2.0;
	float coordLeftX = 		player->posX - player->width/2.0;
	float coordRightX = 	player->posX + player->width/2.0;

	float endCoordBottomY =		player->endPosY - player->height/2.0;
	float endCoordTopY = 		player->endPosY + player->height/2.0;
	float endCoordLeftX = 		player->endPosX - player->width/2.0;
	float endCoordRightX = 		player->endPosX + player->width/2.0;
	return placeMeeting(coordTopY, coordRightX, coordBottomY, coordLeftX, endCoordTopY, endCoordRightX, endCoordBottomY, endCoordLeftX);

}

int arePlayersOnEndPos(Players * playersList){
	int result = 1;
	Players * tempPlayer = playersList->firstPlayer;
	while(tempPlayer!=NULL){
		result *= isPlayerOnEndPos(tempPlayer->player);
		tempPlayer = tempPlayer->nextPlayer;
	}
	return result;
}












