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
#include "game.h"

static const unsigned int BIT_PER_PIXEL = 32;

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

  launchGame();

  SDL_Quit();

  return EXIT_SUCCESS;
}
