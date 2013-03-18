#include <iostream>
#include <math.h>
using namespace std;
#include "man.h"
/*
   cylinder's drawing
   */


void Man::draw()
{

   // draw immediate 
   drawImmediate();

}

//==================== 1. Immediate method ===================================
// immediate definition of individual vertex properties
void Man::drawImmediate()
{
   // dress
   glPushMatrix();
   glTranslatef(0, 0, -1);
   solidCone(1, 1.8, 30, 30);
   glPopMatrix();

   // torsal
   glPushMatrix();
   glTranslatef(0, 0, 0.8);
   glRotatef(180, 1, 0, 0);
   solidCone(0.5, 1.5, 30, 30);
   glPopMatrix();


   // head
   glPushMatrix();
   glTranslatef(0, 0, 1.2);
   glutSolidSphere(0.5, 30, 30);
   glPopMatrix();

   // left arm
   glPushMatrix();
   glTranslatef(-0.8, 0.3, 0.2);
   glRotatef(60, 1, 0.2, 0);
   drawCylinder(0.2, 0.5);
   glPopMatrix();


   // right arm
   glPushMatrix();
   glTranslatef(0.8, 0.3, 0.2);
   glRotatef(60, 1, -0.2, 0);
   drawCylinder(0.2, 0.5);
   glPopMatrix();

   // hat
   glPushMatrix();
   glTranslatef(0, 0, 1.6);
   solidCone(0.5, 0.8, 30, 30);
   solidDisk(0.7, 0.01, 30, 30);
   glPopMatrix();

  // baton
  glPushMatrix();
  glTranslatef(1.5,0,1.03);
  glutSolidSphere(0.22, 30, 30);
  glPushMatrix();
  glTranslatef(0, 0, -0.05); 
  glRotatef(180, 1, 0, 0);
  solidCone(0.3, 0.6, 30, 30);
  glPopMatrix();
  glTranslatef(0,0,-0.8);
  drawCylinder(0.1, 0.9);
  glPopMatrix();


}

void Man::drawCylinder(float radius, float height)
{

   const float DEG2RAD = 3.14159/180;

   // le dessus
   glBegin(GL_POLYGON);
   glNormal3f(0, 0 , -1.0);
   for (int i=0; i < 360; i++)
   {
      float degInRad = i*DEG2RAD;
      glVertex3f(cos(degInRad)*radius,sin(degInRad)*radius, -height);
   }
   glEnd();

   // le dessous
   glBegin(GL_POLYGON);
   glNormal3f(0, 0, 1.0);	
   for (int i=0; i < 360; i++)
   {
      float degInRad = i*DEG2RAD;
      glVertex3f(cos(degInRad)*radius,sin(degInRad)*radius, height);
   }
   glEnd();

   // la couverture
   // nombre de côtés
   const float n = 100;
   glBegin(GL_QUAD_STRIP);
   for(int i = 0; i < 480; i += (360 / n)) {
      float a = i * DEG2RAD; // degrees to radians
      glNormal3f(cos(a), sin(a), 0); 
      glVertex3f(cos(a)*radius, sin(a)*radius, -height);
      glVertex3f(cos(a)*radius, sin(a)*radius, height);
   }
   glEnd();	
}

void Man::solidCone(GLdouble base, GLdouble height, GLint slices, GLint stacks)
{
   GLUquadricObj* quadric = gluNewQuadric();
   gluCylinder(quadric, base, 0, height, slices, stacks);
   gluDeleteQuadric(quadric);

   // le dessus
   const float DEG2RAD = 3.14159/180;
   glBegin(GL_POLYGON);
   glNormal3f(0, 0 , -1.0);
   for (int i=0; i < 360; i++)
   {
      float degInRad = i*DEG2RAD;
      glVertex3f(cos(degInRad)*base,sin(degInRad)*base, 0);
   }
   glEnd();
}


void Man::solidDisk(GLfloat base, GLfloat thickness, GLint slices, GLint stacks)
{
   GLUquadricObj* quadric = gluNewQuadric();
   gluCylinder(quadric, base, base, thickness, slices, stacks);
   gluDeleteQuadric(quadric);

   // le dessous
   const float DEG2RAD = 3.14159/180;
   glBegin(GL_POLYGON);
   glNormal3f(0, 0 , -1.0);
   for (int i=0; i < 360; i++)
   {
      float degInRad = i*DEG2RAD;
      glVertex3f(cos(degInRad)*base,sin(degInRad)*base, 0);
   }
   glEnd();

   // le dessus
   glBegin(GL_POLYGON);
   glNormal3f(0, 0 , 1.0);
   for (int i=0; i < 360; i++)
   {
      float degInRad = i*DEG2RAD;
      glVertex3f(cos(degInRad)*base,sin(degInRad)*base, thickness);
   }
   glEnd();


}
