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
GLfloat leftKnee = 0;
GLfloat rightKnee = 0;
int horizontalVector = 1;

bool reverseAnim = false;
bool reverseAnimWalk = false;

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
   glColor3ub(118,70,185);
   glTranslatef(0, 0, -0.8);
   solidCone(1, 1.6, 30, 30);
   glPopMatrix();

   // feet
   drawFoot(leftKnee, true);
   drawFoot(rightKnee, false);

   // torsal
   glPushMatrix();
   glColor3ub(118,70,185);
   glTranslatef(0, 0, 0.8);
   glRotatef(180, 1, 0, 0);
   solidCone(0.5, 1.5, 30, 30);
   glPopMatrix();

   // arms
   drawArm(leftShoulder, leftElbow, leftWrist, true);
   drawArm(rightShoulder, rightElbow, rightWrist, false);

 
   // hat
   glPushMatrix();
   glColor3ub(118,70,185);
   glTranslatef(0, 0, 1.6);
   solidCone(0.5, 0.8, 30, 30);
   solidDisk(0.7, 0.7, 0.01, 30, 30);
   glPopMatrix();


   // head
   glColor3ub(246,198,224);
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


void Man::solidDisk(GLfloat base1, GLfloat base2, GLfloat thickness, GLint slices, GLint stacks)
{
   GLUquadricObj* quadric = gluNewQuadric();
   gluCylinder(quadric, base1, base2, thickness, slices, stacks);
   gluDeleteQuadric(quadric);

   // le dessous
   const float DEG2RAD = 3.14159/180;
   glBegin(GL_POLYGON);
   glNormal3f(0, 0 , -1.0);
   for (int i=0; i < 360; i++)
   {
      float degInRad = i*DEG2RAD;
      glVertex3f(cos(degInRad)*base1,sin(degInRad)*base1, 0);
   }
   glEnd();

   // le dessus
   glBegin(GL_POLYGON);
   glNormal3f(0, 0 , 1.0);
   for (int i=0; i < 360; i++)
   {
      float degInRad = i*DEG2RAD;
      glVertex3f(cos(degInRad)*base2,sin(degInRad)*base2, thickness);
   }
   glEnd();
}



void Man::drawArm(GLfloat shoulder, GLfloat elbow, GLfloat wrist, bool left) 
{
   // arm
   glPushMatrix();
   glColor3ub(118,70,185);
   glRotatef(shoulder, 0, 0, horizontalVector);
   if (left) 
   {
      glTranslatef(-1.2, 0, 0.65);
      glRotatef(90, 0, horizontalVector, 0);
   } else {
      glTranslatef(1.2, 0, 0.65);
      glRotatef(90, 0, -horizontalVector, 0);
   }
   solidCone(0.2, 1.2, 30, 30);
   glPopMatrix();


   // hand
   glColor3ub(246,198,224);
   glPushMatrix();
   glRotatef(shoulder, 0, 0, horizontalVector);
   if (left) {
      glTranslatef(-1.2, 0, 0.65);
      glRotatef(90, 0, horizontalVector, 0);
   } else {
      glTranslatef(1.2, 0, 0.65);
      glRotatef(90, 0, -horizontalVector, 0);
   } 
   glTranslatef(0, 0, -0.1);
   glScalef(0.5,1,1);
   glutSolidCube(0.3);
   glPopMatrix();
}

void Man::drawFoot(GLfloat knee, bool left)
{
   glPushMatrix();
   glColor3f(0.5,0.5,0.5);
   glRotatef(knee, 1, 0, 0);
   glTranslatef(0, 0, -0.9);
   if (left) {
      glTranslatef(-0.5, 0, 0);
   } else {
      glTranslatef(0.5, 0, 0);
   } 
   glScalef(1,2,0.5);
   glutSolidCube(0.4);
   glPopMatrix();

} 

void Man::animate()
{
  animateArmsHorizontal();
  //animateArmsVertical();

  walk();
}

void Man::animateArmsHorizontal() 
{
   //belly+=1;
   //neck+=1;
  horizontalVector = 1;
  if( reverseAnim == false )
  {
   if (leftShoulder > -70) {
      leftShoulder-=1;
      rightShoulder+=1;
   }
   else {
     reverseAnim = true;
   }

   if (rightWrist > -90) {
      rightWrist-=1;
   }
   else {
     reverseAnim = true;
   }
  }
  else
  {
   if (leftShoulder < 0) {
      leftShoulder+=1;
      rightShoulder-=1;
   }
   else {
     reverseAnim = false;
   }

   if (rightWrist < 0) {
      rightWrist+=1;
   }
   else {
     reverseAnim = false;
   }
  }
}


void Man::animateArmsVertical() 
{
   //belly+=1;
   //neck+=1;
  horizontalVector = 0;
  if( reverseAnim == false )
  {
   if (leftShoulder > -70) {
      leftShoulder-=1;
      rightShoulder+=1;
   }
   else {
     reverseAnim = true;
   }

   if (rightWrist > -90) {
      rightWrist-=1;
   }
   else {
     reverseAnim = true;
   }
  }
  else
  {
   if (leftShoulder < 0) {
      leftShoulder+=1;
      rightShoulder-=1;
   }
   else {
     reverseAnim = false;
   }

   if (rightWrist < 0) {
      rightWrist+=1;
   }
   else {
     reverseAnim = false;
   }
  }

}


void Man::walk() 
{
   if (reverseAnimWalk == false) 
   {
      if (leftKnee < 15) {
         leftKnee+=0.3;
         rightKnee-=0.3;
      } else {
         reverseAnimWalk = true;
      }
   } else {
      if (leftKnee > -10) {
         leftKnee-=0.3;
         rightKnee+=0.3;
      } else {
         reverseAnimWalk = false;
      }
   }
}
