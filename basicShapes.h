#include <SDL/SDL.h>

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

void drawSquare(int filled);
void drawRepere();
void drawCircle(int filled);
void drawRoundSquare(int filled);
void drawMainArm();
void drawManipArm();
void drawBatteur();