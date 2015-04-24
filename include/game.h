#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#ifdef __APPLE__
  #include <OpenGL/gl.h>
  #include <OpenGL/glu.h>
#else
  #include <GL/gl.h>
  #include <GL/glu.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "basicShapes.h"
#include "wall.h"
#include "player.h"



void launchGame();