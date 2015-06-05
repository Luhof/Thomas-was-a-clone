#define LINE_BUFFER_SIZE 2000
#include "level.h"
#include <unistd.h>

Level * initLevel(){

	Level * level = calloc(1, sizeof(Level));
	level->id = 0;

	level->width = 0;
	level->height = 0;

	level->cameraX = 0;
	level->cameraY = 0;


	return level;
}

void fillLevel(Level * level, int idLevel){


}

void switchLevel(Level * level){
	int nextId = level->id +1;
	emptyLevel(level);
	fillLevelFromFile(level, nextId);
}

void fillLevelFromFile(Level * level, int nbStr){
	
	Walls* wallsList = initWallList();
	Players *playersList = initPlayerList();
	Textures * textureList = initTexturesList();
	level->wallsList = wallsList;
	level->playersList = playersList;
	level->textureList = textureList;
	//temp
	level->id = nbStr;
	level->width = 2000.0;
	level->height = 2000.0;

	//get file name
	char buf[12];
	sprintf(buf, "%d", nbStr);


	char * levelStr = "./data/levels/level";
	char * extStr = ".txt";
	char * result = malloc(strlen(levelStr)+nbStr+strlen(extStr)+1);//+1 for the zero-terminator
   	if(result==NULL) exit(1);

    strcpy(result, levelStr);
    strcat(result, buf);
    strcat(result, extStr);

    //load file and data
    FILE * f;
    int currLine = 0;
    int charCount = 0;
    char firstchar;
  	char buffer[LINE_BUFFER_SIZE];
  	char buffercomments[LINE_BUFFER_SIZE];
  	int scanfres;

  	Wall * tempWall;
  	float wallWidth, wallHeight, wallX, wallY;
  	//char myString[1000];
  	Player * tempPlayer;
  	float playerWidth, playerHeight, playerStartPosX, playerStartPosY, playerEndPosX, playerEndPosY, playerSpeed, playerJump;
  	int pr, pg, pb, isCurr;
  	Color tempColor;

  	float lvlWidth, lvlHeight;
  	char musicFile[100];
  	char background[100];

  	char textureFile[100];
  	float textureX, textureY;
  	Texture * tempTexture;
  	int isFront = 0;
  	

  	f = fopen(result, "r");
 	if(f == NULL)
  	{
    	printf("Error loading file %s\n", result);
    	exit(1);
  	}
  	


  	/* Cross all lines of the file */
  	do{

    fgets(buffer, LINE_BUFFER_SIZE, f);
    ++currLine;
    /* Check for empty line */
    scanfres = sscanf(buffer, "%s", buffercomments);
    if (scanfres != 1) continue;

    /* Check for comments */
    scanfres = sscanf(buffer, " %c", &firstchar);
    if (scanfres == 1 && firstchar == '#') continue;

    /* Check for level data */
    scanfres = sscanf(buffer, "%c %f %f %s %s%n", &firstchar, &lvlWidth, &lvlHeight, musicFile, background, &charCount);
    if (scanfres == 5 && firstchar == 'S')
    {	
    	
    	level->music = Mix_LoadMUS(musicFile); // on charge la zikmu yo !
  		if(level->music==NULL) {
    		printf("ça ne charge pas la musique  \n");
 		 }
 		Mix_PlayMusic(level->music, -1);// on joue la musique à l'infini 
    	//printf("texture name : %s \n", background);
    	level->background = initTexture(background);
    	level->width = lvlWidth;
    	level->height = lvlHeight;
      continue;
    }

    /* Check for walls setting lines */
    scanfres = sscanf(buffer, " %c %f %f %f %f %n", &firstchar, &wallWidth, &wallHeight, &wallX, &wallY, &charCount);
    if (scanfres == 5 && firstchar == 'W')
    {

      tempWall = createWall(wallWidth, wallHeight, wallX, wallY);
      addWall(level->wallsList, tempWall);
      continue;
    }

    /*if (scanfres != 5)
    {
    
      fprintf(stderr, "Error reading line %d : %s", currLine, buffer);
      continue;
    }*/

    /* Check for charecter setting lines */
    scanfres = sscanf(buffer, "%c %f %f %f %f %f %f %f %f %d %d %d %d %n", &firstchar, &playerWidth, &playerHeight, &playerStartPosX, &playerStartPosY, &playerEndPosX, &playerEndPosY, &playerSpeed, &playerJump, &pr, &pg, &pb, &isCurr, &charCount);
    if (scanfres == 13 && firstchar == 'P')
    {
    	tempColor = setColor(pr, pg, pb);

    	tempPlayer = createPlayer(playerWidth, playerHeight, playerStartPosX, playerStartPosY, playerEndPosX, playerEndPosY, playerSpeed, playerJump, tempColor);
    	if(isCurr == 1) tempPlayer->isCurrentPlayer = 1;
    	addPlayer(level->playersList, tempPlayer);
      continue;
    }

    /* Check for textures */
    scanfres = sscanf(buffer, " %c %f %f %s %d%n", &firstchar, &textureX, &textureY, textureFile, &isFront, &charCount);
    if (scanfres == 5 && firstchar == 'T')
    {	
    	//tempTexture = initTexturesList();
    	tempTexture = initTexture(textureFile);
    	tempTexture->textureX = textureX;
    	tempTexture->textureY = textureY;
    	if(isFront == 1)tempTexture->isFront = 1;
    	addTexture(level->textureList, tempTexture);
    	//level->textureList = tempTexture->firstTexture;
    
    	
      continue;
    }





  } while (!feof(f));

   /* closing file*/
  if(fclose(f) == EOF) {
    printf("Closing error with %s", result);
   	exit(1);
  }


}

void emptyLevel(Level * level){

	Walls * tempWalls = NULL;
	while(level->wallsList!=NULL){
		tempWalls = level->wallsList->nextWall;
		free(level->wallsList->wall);
		free(level->wallsList);
		level->wallsList = tempWalls;
	}

	Players * tempPlayers = NULL;
	while(level->playersList!=NULL){
		tempPlayers = level->playersList->nextPlayer;
		free(level->playersList->player);
		free(level->playersList);
		level->playersList = tempPlayers;
	}

	level->background = NULL;
	Mix_PauseMusic();
	//Mix_FreeMusic(level->music);

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
			
			level->cameraX = tempPlayer->player->startPosX;
			level->cameraY = tempPlayer->player->startPosY;
			//level->isCameraMoving = 1;
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

	if(level->isCameraMoving == 0){
		level->cameraX = -tempPlayer->player->posX;
		level->cameraY = -tempPlayer->player->posY;
	}

	//basic code for smoother camera, following character
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
		//printf("camera is moving x : %f et y %f\n to x : %f et y : %f\n", level->cameraX, level->cameraY, level->cameraDestX, level->cameraDestY);
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

		else xDone = 1;

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

		else yDone = 1;
	}

	if(xDone == 1 && yDone == 1)
		level->isCameraMoving = 0;

		
	
	

}

