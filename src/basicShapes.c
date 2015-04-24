#include "basicShapes.h"

void drawSquare(int filled){
  if(filled == 1){
    glBegin(GL_QUADS);
  }
  else{
    glBegin(GL_LINE_LOOP);
  }
  glVertex2f(-0.5,0.5);
  glVertex2f(0.5,0.5);
  glVertex2f(0.5,-0.5);
  glVertex2f(-0.5,-0.5);
  glEnd();
}


void drawRepere(){
  glBegin(GL_LINES);
  glColor3ub(255,0,0);
  glVertex2f(0,0);
  glVertex2f(0,100);
  glColor3ub(0,255,0);
  glVertex2f(0,0);
  glVertex2f(100,0);
  glEnd();

}

void drawCircle(int filled){

  int i;
  int preciseLevel = 360;

  if(filled == 1){
    glBegin(GL_POLYGON);
  }
  else{
      glBegin(GL_LINE_LOOP);
  }

  for(i=1; i<preciseLevel; i++){
    glVertex2f(cos(i*2*M_PI/preciseLevel)/2, sin(i*2*M_PI/preciseLevel)/2);

  }
  glEnd();

}