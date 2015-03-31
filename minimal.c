#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#ifdef __APPLE__
  #include <OpenGL/gl.h>
  #include <OpenGL/glu.h>
#else
  #include <GL/gl.h>
  #include <GL/glu.h>
#endif

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "basicShapes.h"
#include "player.h"


static const unsigned int BIT_PER_PIXEL = 32;
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;

void reshape(float ratio, int winWidth, int winHeight) {
  glViewport(0, 0, winWidth, winHeight);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(-250.0*ratio, 250.0*ratio, -250.0, 250.0);
}


void setVideoMode(float ratio, int winWidth, int winHeight) {
  if(NULL == SDL_SetVideoMode(winWidth, winHeight, BIT_PER_PIXEL, SDL_OPENGL)) {
    fprintf(stderr, "Impossible d'ouvrir la fenetre. Fin du programme.\n");
    exit(EXIT_FAILURE);
  }
  reshape(ratio, winWidth,winHeight);
}

int main(int argc, char** argv) {

  unsigned int windowWidth  = 1200;
  unsigned int windowHeight = 600;
  float ratio = windowWidth/(float)windowHeight;



  if(-1 == SDL_Init(SDL_INIT_VIDEO)) {
    fprintf(stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
    return EXIT_FAILURE;
  }

  //antialiasing
  SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS,1);
  SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES,6);

  setVideoMode(ratio, windowWidth, windowHeight);

  SDL_WM_SetCaption("Thomas was a Clone", NULL);

  glPointSize(4);

  int loop = 1;
  while(loop) {

    /* temps au début de la boucle */
    Uint32 startTime = SDL_GetTicks();

    /* dessin */
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();

      Player thomas;
      initPlayer(&thomas);
      setPlayerAttr(&thomas, 100.0, 200.0, 0, -100);

      //main arm
      glScalef(50,100,1);


      glLoadIdentity();
      drawRepere();
      glLoadIdentity();
      drawPlayer(&thomas);

      freePlayer(&thomas);




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
            default : break;
          }
          break;

        default:
          break;
      }
    }

    Uint32 elapsedTime = SDL_GetTicks() - startTime;
    if(elapsedTime < FRAMERATE_MILLISECONDS) {
      SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
    }
  }

  SDL_Quit();

  return EXIT_SUCCESS;
}
