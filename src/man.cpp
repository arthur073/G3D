#include <iostream>
#include <unistd.h>
#include <math.h>
#include<unistd.h>
using namespace std;
#include "man.h"
/*
   cylinder's drawing
   */

/* free angles */
GLfloat belly = 0;
GLfloat neck = 0;
GLfloat leftElbow = 0;
GLfloat rightElbow = 0;
GLfloat leftShoulder = 0;
GLfloat rightShoulder = 0;
GLfloat leftWrist = 0;
GLfloat rightWrist = 0;

void Man::draw()
{
   // draw immediate 
   drawImmediate();
}

//==================== 1. Immediate method ===================================
// immediate definition of individual vertex properties
void Man::drawImmediate()
{
   glColor3ub(118,70,185);

   // dress
   glPushMatrix();
   glTranslatef(0, 0, -1);
   solidCone(1, 1.8, 30, 30);
   glPopMatrix();

   // torsal
   glPushMatrix();
   glTranslatef(0, 0, 0.8);
   //glRotatef(belly, 1, 0, 0);
   glRotatef(180, 1, 0, 0);
   solidCone(0.5, 1.5, 30, 30);
   glPopMatrix();

   // arms
   drawArm(leftShoulder, leftElbow, leftWrist, true);
   drawArm(rightShoulder, rightElbow, rightWrist, false);

 
   // hat
   glPushMatrix();
   glTranslatef(0, 0, 1.6);
   solidCone(0.5, 0.8, 30, 30);
   solidDisk(0.7, 0.01, 30, 30);
   glPopMatrix();


   glColor3ub(246,198,224);
   // head
   glPushMatrix();
   glRotatef(neck, 1, 0, 0);
   glTranslatef(0, 0, 1.2);
   glutSolidSphere(0.5, 30, 30);
   glPopMatrix();

 
 


   // baton
   glPushMatrix();
   glRotatef(rightShoulder, 0, 0, 1);
   glTranslatef(1.5,0,0);
   glTranslatef(0,0,0.65);
   glRotatef(rightWrist, 1, 0, 0);
   glTranslatef(0,0,1.35);
   glColor3f(1,1,1);
   glutSolidSphere(0.22, 30, 30);
   glColor3ub(100,53,16);

   glPushMatrix();
   glTranslatef(0, 0, -0.05); 
   glRotatef(180, 1, 0, 0);
   solidCone(0.3, 0.6, 30, 30);
   glPopMatrix();
   
   glTranslatef(0,0,-1.3);
   drawCylinder(0.05, 1.2);
   glPopMatrix();
   glColor3f(1,1,1);

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



void drawArm(GLfloat shoulder, GLfloat elbow, GLfloat wrist, bool left) 
{
   // left arm
   glPushMatrix();
   glRotatef(shoulder, 0, 0, 1);
   if (left) 
   {
      glTranslatef(-1.2, 0, 0.65);
      glRotatef(90, 0, 1, 0);
   } else {
      glTranslatef(1.2, 0, 0.65);
      glRotatef(90, 0, -1, 0);
   }
   solidCone(0.2, 1.2, 30, 30);
   glPopMatrix();


   // left hand
   glPushMatrix();
   glRotatef(shoulder, 0, 0, 1);
   if (left) {
      glTranslatef(-1.2, 0, 0.65);
      glRotatef(90, 0, 1, 0);
   } else {
      glTranslatef(1.2, 0, 0.65);
      glRotatef(90, 0, -1, 0);
   } 
   glTranslatef(0, 0, -0.1);
   glScalef(0.5,1,1);
   glutSolidCube(0.3);
   glPopMatrix();
}



void Man::animate() 
{
   //belly+=1;
   //neck+=1;
   if (leftShoulder > -70) {
      leftShoulder-=1;
      rightShoulder+=1;
   }
   if (rightWrist > -90) {
      rightWrist-=1;
   }
}
