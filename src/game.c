#include "game.h"

#include "draw.h"
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
  
  //set basic attributes
  float gravity = 0.3;

  int keyJump = 0;
  int keyLeft = 0;
  int keyRight = 0;
  int keySwitch = 0;

  Level * currLevel = initLevel();
  //fillLevel(currLevel, 1);
  fillLevelFromFile(currLevel, 1);

  /*printf("about to init texture\n");
  Texture * myTexture = initTexture("./src/background.jpg");
  printf("initialized texture \n");*/
  
  /**
  *STARTING LOOP
  **/

  int loop = 1;
  while(loop){

     

    /* temps au début de la boucle */
    Uint32 startTime = SDL_GetTicks();

    /* dessin */
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
   
    
    
    
    if(keySwitch){
      Player * newCharacter = switchCharacter(currLevel->playersList);
      currLevel->cameraX = newCharacter->posX;
      currLevel->cameraY = newCharacter->posY;
    }

      //set speed depending on gravity and player input
      setVSpeed(currLevel->playersList, gravity);
      setHSpeed(currLevel->playersList, keyLeft + keyRight);

      //use of pseudo-physics to check collisions and jumps
      isColliding(currLevel->playersList, currLevel->wallsList, keyJump);


      updatePlayersPos(currLevel->playersList);

      




      if(currLevel->isCameraMoving==0)
        updateCamera(currLevel);

      if(isAnyPlayerDead(currLevel->playersList, currLevel)==1){
        resetLevel(currLevel);
      }

     
      

      /* DRAW */
      glLoadIdentity();
     
      glPushMatrix();
        glEnable(GL_TEXTURE_2D);
        glColor3ub(255,255,255);
        drawSquareTex(currLevel->cameraX/5.0,currLevel->cameraY/5.0, currLevel->background);
        glColor3ub(255,255,255);
        //glColor3ub(255,255,255);
        
        //glColor3ub(255,255,255);
        glDisable(GL_TEXTURE_2D);




      glRotatef(1.5, 0.0,0.0,1.0);
      glTranslatef(currLevel->cameraX, currLevel->cameraY, 0);
        glEnable(GL_TEXTURE_2D);
        drawTextures(currLevel->textureList);
        glDisable(GL_TEXTURE_2D);


      glColor3ub(0.0,0.0,0.0);
      drawWalls(currLevel->wallsList);
        //printf("pos Y : %f\n", playersList->firstPlayer->player->posY);
      
      drawPlayersEndPos(currLevel->playersList);
      drawPlayers(currLevel->playersList);

     
      glPopMatrix();
      glPushMatrix();
        drawThumbnails(currLevel->playersList);
      glPopMatrix();

      if(arePlayersOnEndPos(currLevel->playersList)){
        switchLevel(currLevel);
      }

     glDisable(GL_TEXTURE_2D);


      /* END DRAW */

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
          //printf("axis used : %d\n", e.jaxis.axis);
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
              resetLevel(currLevel);
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
  Mix_FreeChunk(currLevel->playersList->firstPlayer->player->son);//Libération du son de saut

}




void launchMenu(){

  static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;

 

  //drawSquareTex(0.0,100.0,"./data/textures/menu1.png");
  //drawSquareTex(0.0,-20.0,"./data/textures/menu2.png");

  int launchedGame = 0;
  int loop = 1;
  while(loop){
    /* temps au début de la boucle */
    Uint32 startTime = SDL_GetTicks();


            /* dessin */
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();

    Texture * background = initTexture("./data/textures/backgrounds/menu.jpg");
    Texture * title      = initTexture("./data/textures/menu2.png");
    Texture * pressEnter = initTexture("./data/textures/menu1.png");

    glEnable(GL_TEXTURE_2D);
    drawSquareTex(0.0,0.0, background);
    drawSquareTex(0.0,100.0, title);
    drawSquareTex(0.0,-20.0, pressEnter);




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

        case SDL_KEYDOWN:
          switch(e.key.keysym.sym){
            case 'q' :
            case SDLK_ESCAPE :
              loop = 0;
              break;
           
            case SDLK_RETURN :
              launchedGame = 1;
              loop = 0;
            break;


            default : break;
            
          }
          break;
          
      }
    }




    Uint32 elapsedTime = SDL_GetTicks() - startTime;
    if(elapsedTime < FRAMERATE_MILLISECONDS) {
      SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
    }

  }

  if(launchedGame==1) launchGame();






}

