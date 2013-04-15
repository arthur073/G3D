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

// Anim Applause
GLint AnimApplause = 1;
GLint CptApplause = 0;
GLint CptWait = 0;

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
 //  glPushMatrix();
 //  glColor3ub(118,70,185);
 //  glTranslatef(0, 0, -0.5);
 //  solidDisk(0.7, 0.1, 0.8, 30, 30);
 //  glTranslatef(0, 0, -0.3);
 //  solidDisk(1, 0.3, 0.8, 30, 30);
 //  glPopMatrix();
 

   // legs
   drawLeg(leftKnee, true);
   drawLeg(rightKnee, false);

   // feet
   drawFoot(leftKnee, true);
   drawFoot(rightKnee, false);

   // torsal
   glPushMatrix();
   glRotatef(belly, 1, 0, 0);
   glColor3ub(118,70,185);
   glTranslatef(0, 0, 0.8);
   glRotatef(180, 1, 0, 0);
   solidDisk(0.5, 0.35, 1, 30, 30);
   glPopMatrix();

   // arms
   drawArm(leftShoulder, leftElbow, leftWrist, true);
   drawArm(rightShoulder, rightElbow, rightWrist, false);

   // head
   glColor3ub(246,198,224);
   glPushMatrix();
   glRotatef(belly, 1, 0, 0);
   glRotatef(neck, 1, 0, 0);
   glTranslatef(0, 0, 1.2);
   glutSolidSphere(0.5, 30, 30);
   // hat
   glTranslatef(0, 0, 0.4);
   glColor3ub(118,70,185);
   solidCone(0.5, 0.8, 30, 30);
   solidDisk(0.7, 0.7, 0.01, 30, 30);
   glPopMatrix();


   // baton
//   glPushMatrix();
//   glTranslatef(1.5,0,0);
//   glTranslatef(0,0,0.65);
//   glTranslatef(0,0,1.35);
//   glColor3f(1,1,1);
//   glutSolidSphere(0.22, 30, 30);
//   glColor3ub(100,53,16);
//
//   glPushMatrix();
//   glTranslatef(0, 0, -0.05); 
//   glRotatef(180, 1, 0, 0);
//   solidCone(0.3, 0.6, 30, 30);
//   glPopMatrix();
//
//   glTranslatef(0,0,-1.3);
//   drawCylinder(0.05, 1.2);
//   glPopMatrix();
//   glColor3f(1,1,1);

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
   glRotatef(belly, 1, 0, 0);
   glRotatef(shoulder, 0, 0, horizontalVector);
   if (left) 
   {
      glTranslatef(-0.6, 0, 0.60);
      glRotatef(90, 0, horizontalVector, 0);
      solidDisk(0.15, 0.2, 0.6, 30, 30);
      glRotatef(elbow, -1, 0, 0);
      glRotatef(-90, 0, horizontalVector, 0);
      glTranslatef(-0.6, 0, 0);
      glRotatef(90, 0, horizontalVector, 0);
   } else {
      glTranslatef(0.6, 0, 0.60);
      glRotatef(90, 0, -horizontalVector, 0);
      solidDisk(0.15, 0.2, 0.6, 30, 30);
      glRotatef(elbow, 1, 0, 0);
      glRotatef(-90, 0, -horizontalVector, 0);
      glTranslatef(0.6, 0, 0);
      glRotatef(90, 0, -horizontalVector, 0);
   }
   solidDisk(0.2, 0.15, 0.6, 30, 30);

   // hand
   glColor3ub(246,198,224);
   glTranslatef(0, 0, -0.1);
   if (left) 
   {
      glRotatef(wrist, 0, 0.5, 1);
   } else {
      glRotatef(-wrist, 0, 0.5, 1);
   }
   glScalef(0.5,1,1);
   glutSolidCube(0.3);

   glPopMatrix();
}

void Man::drawLeg(GLfloat knee, bool left) {
   glPushMatrix();
   if (left) {
      glTranslatef(0.16, 0, -0.8);
      solidDisk(0.12, 0.2, 0.7, 30, 30);
      glRotatef(knee, 1, 0, 0);
      glTranslatef(0, 0, -0.5);
      solidDisk(0.1, 0.12, 0.5, 30, 30);
   } else {
      glTranslatef(-0.16, 0, -0.8);
      solidDisk(0.12, 0.2, 0.7, 30, 30);
      glRotatef(knee, 1, 0, 0);
      glTranslatef(0, 0, -0.5);
      solidDisk(0.1, 0.12, 0.5, 30, 30);
   
   }
   glPopMatrix();
}

void Man::drawFoot(GLfloat knee, bool left)
{
   glPushMatrix();
   glColor3f(0.2,0.2,0.2);
   glRotatef(knee, 1, 0, 0);
   glTranslatef(0, 0.1, -1.3);
   if (left) {
      glTranslatef(-0.16, 0, 0);
   } else {
      glTranslatef(0.16, 0, 0);
   } 
   glScalef(0.6,1,0.3);
   glutSolidCube(0.4);
   glPopMatrix();

} 

void Man::applause()
{
   if (AnimApplause == 1) {
      if (leftShoulder > -40) {
         leftShoulder-=0.5;
         rightShoulder+=0.5;
         leftElbow-=0.95;
         rightElbow+=0.95;
         leftWrist-=0.40;
         rightWrist+=0.40;
      } else {
         if (AnimApplause == 1) {
            // on va à la phase 2
            AnimApplause = 2;
         }
      }
   } 

   if (AnimApplause == 2) {
      // on applause
      if (leftElbow < -60) {
         leftElbow+=1;
         rightElbow-=1;
      } else {
         AnimApplause = 3;
      }
   }

   if (AnimApplause == 3) {
      if (leftElbow > -80) {
         leftElbow-=1;
         rightElbow+=1;
      } else {
         AnimApplause = 2;
         CptApplause++;
      }
   }

   if (AnimApplause == 4) {
      if (leftShoulder < 0) {
         leftShoulder+=0.5;
         rightShoulder-=0.5;
         leftElbow+=0.95;
         rightElbow-=0.95;
         leftWrist+=0.40;
         rightWrist-=0.40;
      } else {
         AnimApplause = 5;
      }
   } 

   if (AnimApplause == 5) {
      if (belly > -40) {
         belly-=1;
         neck-=0.5;
         leftShoulder+=0.6;
         rightShoulder-=0.6;

      } else {
         AnimApplause = 6;
      }
   }

   if (AnimApplause == 6) {
      if (belly > -41) {
         belly-=0.01;
      } else {
         AnimApplause = 7;
      }
   }

   if (AnimApplause == 7) {
      if (belly < 0) {
         belly+=1;
         neck+=0.5;
         leftShoulder-=0.7;
         rightShoulder+=0.7;
         leftElbow-=0.4;
         rightElbow+=0.4;
      }
   }

   if ( AnimApplause == 3 && CptApplause > 3) {
      AnimApplause = 4;
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

void Man::animate()
{
   applause();
   //walk();
}


