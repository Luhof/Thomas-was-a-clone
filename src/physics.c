#include "physics.h"
#include <stdio.h>

int placeMeeting(int top1, int right1, int bottom1, int left1, int top2, int right2, int bottom2, int left2){
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
			placeMeeting(coordTopY+player->vspeed, coordRightX, coordBottomY+player->vspeed-1, coordLeftX, wallTop, wallRight, wallBottom, wallLeft)==1)
			{

			//if player is FALLING, he is on the floor
			if(player->vspeed < 0){
				verticalDiff = (coordBottomY - wallTop);
				//Since the player is on the ground he can jump !!
				if(player->isCurrentPlayer==1)
					player->vspeed = (keyJump * player->jumpspeed);
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
		if(placeMeeting(coordTopY+player->vspeed, coordRightX+player->hspeed,coordBottomY+player->vspeed, coordLeftX+player->hspeed, wallTop, wallRight, wallBottom, wallLeft)){

			//if player is going RIGHT
			if(player->hspeed > 0){
				horizontalDiff = -1*(coordRightX - wallLeft);
			}
			//else if player is going LEFT
			else if(player->hspeed < 0){
				horizontalDiff = wallRight - coordLeftX;
			}

			player->hspeed = horizontalDiff;
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
				**	horizontal collision
				**/
				if(placeMeeting(coordTopY+player->vspeed, coordRightX+player->hspeed,coordBottomY, coordLeftX+player->hspeed, coordTopY2+player2->vspeed, coordRightX2+player2->hspeed, coordBottomY2+player2->vspeed, coordLeftX2+player2->hspeed))
				{
					

					//if player is going RIGHT
					if(player->hspeed > 0){
						horizontalDiff = -1*(coordRightX - coordLeftX2);
					}
					//else if player is going LEFT
					else if(player->hspeed < 0){
						horizontalDiff = coordRightX2 - coordLeftX;
					}
					player->hspeed = horizontalDiff;
				}

				/**
				** vertical collision
				**/
				if(player->vspeed!=0 &&
				placeMeeting(coordTopY+player->vspeed, coordRightX+player->hspeed, coordBottomY+player->vspeed-1, coordLeftX, coordTopY2, coordRightX2, coordBottomY2, coordLeftX2)==1)
				{
									
					printf("collides with player\n**\n");	
					//if player is FALLING, he is on the top of the bottom player (player2)...	
					if(player->vspeed < 0){
						verticalDiff = (coordBottomY - coordTopY2);
							
						//Since the player is on the ground he can jump !!
						if(player->isCurrentPlayer==1){
							player->vspeed = (keyJump * player->jumpspeed);
						}
						else player->vspeed = 0;
						
						/*playerPlayerCollisions(player, playersList, wallsList, keyJump);
						playerWallCollisions(player, wallsList, keyJump);*/
					}

					//else if he is JUMPING
					else if(player->vspeed > 0){
						verticalDiff =  -1*(coordBottomY2 - coordTopY);
						player->vspeed = 0;
						player2->vspeed = player->vspeed;
					}

					player->posY -= verticalDiff; 
								
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
				if(placeMeeting(coordTopY+player->vspeed, coordRightX+player->hspeed, coordBottomY+player->vspeed-1, coordLeftX, coordTopY2, coordRightX2, coordBottomY2, coordLeftX2)==1)
				{
										
					//if player is FALLING, he is on the top of the bottom player (player2)...	
					if(player->vspeed < 0){

						player->isHolding = player2;
						printf("player %d parent : %d\n", player->id, player->isHolding->id);
					}

					//else if he is JUMPING
					else if(player->vspeed > 0){
						player2->isHolding = player;
						printf("player %d parent : %d\n", player2->id, player->id);
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













