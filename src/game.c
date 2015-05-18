#include "game.h"

void launchGame(){
  
	static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;

  glClearColor(120,146,161, 1); 
  printf("game launched\n");


  /** 
  *INITIALIZING STUFF
  **/

  //set room attribute
  float gravity = 0.3;

  //set player attributes
  Player *thomas = NULL;
  thomas = initPlayer(thomas);

  initPlayer(thomas);
  setPlayerAttr(thomas, 50.0, 100.0, 60.0, 40.0);
  printf("player initialized\n");

  Wall* walls[3];
  walls[0] = initWall(walls[0]);
  setWallAttr(walls[0], 150.0, 25.0, 0.0, -100.0);
  walls[1] = initWall(walls[1]);
  setWallAttr(walls[1], 25.0, 150.0, 100.0, -50.0);
  walls[2] = initWall(walls[2]);
  setWallAttr(walls[2], 150.0, 25.0, 100.0, 150.0);
  
  printf("wall initialized\n");

  int keyJump = 0;
  int keyLeft = 0;
  int keyRight = 0;


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
    
      thomas->dir = keyLeft + keyRight;
      setVSpeed(thomas, gravity);
      setHSpeed(thomas, thomas->dir*thomas->movespeed);
 
     isColliding(thomas, walls, keyJump);
    
      updatePlayerPos(thomas);
      glColor3ub(240,158,162);
      drawPlayer(thomas);

      glColor3ub(230,223,215);
      drawWall(walls[0]);
      drawWall(walls[1]);
      drawWall(walls[2]);


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

            case SDLK_RIGHT :
              keyRight = 1;
              break;

            case SDLK_LEFT :
              keyLeft = -1;
              break;

            case SDLK_SPACE : 
              keyJump = 1;
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

  free(thomas);
  free(walls[0]);
  free(walls[1]);

}

