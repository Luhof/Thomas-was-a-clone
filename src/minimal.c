#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>

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


  if(-1 == SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK)) {
    fprintf(stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
    return EXIT_FAILURE;
  }

  SDL_Joystick *joystick; // attention, c'est bien un pointeur !
  joystick = SDL_JoystickOpen(0);

  SDL_JoystickEventState(SDL_ENABLE);

  
  Mix_Music *musique;// initialisation du pointeur sur la musique 
 
  
  //antialiasing
  SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS,1);
  SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES,6);

  setVideoMode(ratio, windowWidth, windowHeight);

  SDL_WM_SetCaption("Thomas was a Clone", NULL);

  glPointSize(4);

//Charger les sons 
 if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) //Initialisation de l'API Mixer
   {
      printf("%s", Mix_GetError());
   }


  musique = Mix_LoadMUS("./data/musik.wav"); // on charge la zikmu yo !
  if(musique==NULL) {
    printf("ça ne charge pas la musique  \n");
  }
  Mix_PlayMusic(musique, -1);// on joue la musique à l'infini 

if(Mix_PlayingMusic()==1) {

  printf("ça joue de la musique !!! \n");
}
else {
  printf("la musique ne se joue pas \n");
}



  launchGame();

  SDL_JoystickClose(joystick);

  Mix_FreeMusic(musique);
  Mix_CloseAudio(); //Fermeture de l'API
  
  SDL_Quit();
  return EXIT_SUCCESS;
}
