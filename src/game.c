#include "game.h"

void launchGame(){
  
	static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;

  glClearColor(230,223,215, 1); 
  printf("game launched\n");

  //set room attribute
  float gravity = -1.5;

  //set player attributes
  Player *thomas = NULL;
  thomas = initPlayer(thomas);

  initPlayer(thomas);
  setPlayerAttr(thomas, 50.0, 100.0, 60.0, 40.0);
  printf("player initialized\n");
  setVSpeed(thomas, gravity);

  Wall *wall = NULL;
  wall = initWall(wall);
  setWallAttr(wall, 200.0, 25.0, 0.0, -100.0);
  printf("wall initialized\n");

  int loop = 1;
  printf("started loop\n");
  while(loop){

    /* temps au début de la boucle */
    Uint32 startTime = SDL_GetTicks();

    /* dessin */
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();
      drawRepere();

    glLoadIdentity();

      int collides = isColliding(thomas, wall, gravity);

      updatePlayerPos(thomas);
      glColor3ub(240,158,162);
      drawPlayer(thomas);

      glColor3ub(120,146,161);
      drawWall(wall);


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
              printf("right key pressed\n");
              setHSpeed(thomas, 1);
              break;

            case SDLK_LEFT :
                printf("left key pressed\n");
                setHSpeed(thomas, -1);
                break;
            default : break;
            
          }
          break;
          


        case SDL_KEYUP:
            switch(e.key.keysym.sym){
              case SDLK_RIGHT :
              case SDLK_LEFT :
                setHSpeed(thomas, 0);
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
  free(wall);

}

