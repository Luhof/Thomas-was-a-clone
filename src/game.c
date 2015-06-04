#include "game.h"
#include "time.h"
#include "math.h"


void launchGame(){
  
	static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;

  //glClearColor(120,146,161, 1); 
  printf("game launched\n");

  /** 
  *INITIALIZING STUFF
  **/
  
//initialiser les sons 
  Mix_AllocateChannels(9);// allocation de 10 pistes pour les sons 
  //Mix_Chunk *son;
  //son = Mix_LoadWAV("./data/saut.wav");
  
  //set room attribute
  float gravity = 0.3;

  int keyJump = 0;
  int keyLeft = 0;
  int keyRight = 0;
  int keySwitch = 0;

  Level * firstLevel = initLevel();
  Players * playersList = firstLevel->playersList;
  Walls * wallsList = firstLevel->wallsList;

     
  /**
  *STARTING LOOP
  **/

  int loop = 1;
  printf("started loop\n");
  while(loop){

    

    /* temps au début de la boucle */
    Uint32 startTime = SDL_GetTicks();

    /* dessin */
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
   
    
    glLoadIdentity();
    
    if(keySwitch){
      Player * newCharacter = switchCharacter(playersList);
      firstLevel->cameraX = newCharacter->posX;
      firstLevel->cameraY = newCharacter->posY;
      printf("new character X : %f - %f\n", newCharacter->posX, newCharacter->posY);
      //firstLevel->isCameraMoving = 1;
    }
    




      //set speed depending on gravity and player input
      setVSpeed(playersList, gravity);
      
      setHSpeed(playersList, keyLeft + keyRight);

      //need to add update flags or smth like that.
      //SKETCH SHIET

      //use of pseudo-physics to check collisions and jumps
      isColliding(playersList, wallsList, keyJump);
      //isColliding(playersList, wallsList, keyJump);

      

      //printf("speeds\n%f\n%f\n%f\n***\n", thomas->hspeed, marcel->hspeed, pouity->hspeed);

      updatePlayersPos(playersList);


      

      if(arePlayersOnEndPos(playersList)) printf("you win :D\n");

      if(firstLevel->isCameraMoving==0)
        updateCamera(firstLevel);
      if(firstLevel->isCameraMoving == 1)
        stepCamera(firstLevel);

      if(isAnyPlayerDead(playersList, firstLevel)==1) resetLevel(firstLevel);
      
      glPushMatrix();

      glTranslatef(firstLevel->cameraX, firstLevel->cameraY, 1);
      
      drawPlayersEndPos(playersList);
      drawPlayers(playersList);


      glColor3ub(230,223,215);
      drawWalls(wallsList);

      glPopMatrix();

      drawThumbnails(playersList);

      //drawThumbnails(playersList);

      keyJump = 0;
      keySwitch = 0;
      

    SDL_GL_SwapBuffers();


    /****************
    EVENT HANDLER
    ******************/

    SDL_Event e;
    while(SDL_PollEvent(&e)) {
      if(e.type == SDL_QUIT) {
        loop = 0;
        break;
      }

      switch(e.type) {


        case SDL_JOYBUTTONDOWN:

          switch(e.jbutton.button)
          {
              case 4 :  //button "Start" pressed
                  loop = 0;
                  break;
              case 11 : // button "A" pressed
                  keyJump = 1; 
                  break;
          }
        break;

        case SDL_JOYAXISMOTION:
          printf("button rpesde : %d\n", e.jaxis.axis);
          switch(e.jaxis.axis){
            case 0 :

              if(e.jaxis.value < -9500){
                  keyLeft = -1;
              }

              else if(e.jaxis.value > 9500){
                  keyRight = 1;
              }
                  
              
              else{
                  keyLeft = 0;
                  keyRight = 0;
              }

              break;

          }
        break;


        case SDL_MOUSEBUTTONUP:
        break;

        case SDL_VIDEORESIZE:
        break;

        case SDL_KEYDOWN:
          switch(e.key.keysym.sym){
            case 'q' :
            case SDLK_ESCAPE :
              loop = 0;
              break;
            case 'r' :
              resetLevel(firstLevel);
              break;
            case SDLK_RIGHT :
              keyRight = 1;
              break;

            case SDLK_LEFT :
              keyLeft = -1;
              break;

            case SDLK_SPACE :
            case SDLK_UP:
              if(keyJump == 0){
                keyJump = 1;
              }
              break;
            case SDLK_TAB :
              keySwitch = 1;
            break;



            default : break;
            
          }
          break;
          


        case SDL_KEYUP:
            switch(e.key.keysym.sym){
              case SDLK_RIGHT :
                keyRight = 0;
                break;
              case SDLK_LEFT :
                keyLeft = 0;
                break;
              case SDLK_SPACE :
              case SDLK_UP:
                keyJump = 0;
                break;

              default:break;
            }
            break;

        default : break;

      }
      break;
    }

    Uint32 elapsedTime = SDL_GetTicks() - startTime;
    if(elapsedTime < FRAMERATE_MILLISECONDS) {
      SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
    }
  }

  //Libérations des bruitages  
  Mix_FreeChunk(firstLevel->playersList->firstPlayer->player->son);//Libération du son de saut

}

