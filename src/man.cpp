#include <iostream>
#include <unistd.h>
#include <math.h>
#include<unistd.h>
#include "man.h"
/*
   cylinder's drawing
   */

/* free angles */
GLfloat belly = 0;
GLfloat neck = 0;
GLfloat leftElbow = 0;
GLfloat leftElbow2 = 0;
GLfloat rightElbow = 0;
GLfloat rightElbow2 = 0;
GLfloat leftShoulder = 0;
GLfloat rightShoulder = 0;
GLfloat leftShoulder2 = 0;
GLfloat rightShoulder2 = 0;
GLfloat leftWrist = 0;
GLfloat rightWrist = 0;
GLfloat leftKnee = 0;
GLfloat rightKnee = 0;
GLfloat leftPelvis = 0;
GLfloat rightPelvis = 0;
int horizontalVector = 1;

bool reverseAnim = false;
bool reverseAnimWalk = false;

const string Man::EVENT_APPLAUSE = "applause";
const string Man::EVENT_WALK = "walk";

string Man::currentMove = "";

// Anim Applause
GLint AnimApplause = 1;
GLint AnimWalk = 0;
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
   drawLeg(leftPelvis, leftKnee, true);
   drawLeg(rightPelvis, rightKnee, false);


   // torsal
   glPushMatrix();
   glRotatef(belly, 1, 0, 0);
   glColor3ub(118,70,185);
   glTranslatef(0, 0, 0.8);
   glRotatef(180, 1, 0, 0);
   solidDisk(0.5, 0.35, 1, 30, 30);
   glPopMatrix();

   // arms
   drawArm(leftShoulder, leftShoulder2,  leftElbow, leftElbow2, leftWrist, true);
   drawArm(rightShoulder, rightShoulder2, rightElbow, rightElbow2, rightWrist, false);

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

   //cape
   drawCape();


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



void Man::drawArm(GLfloat shoulder, GLfloat shoulder2, GLfloat elbow, GLfloat elbow2, GLfloat wrist, bool left) 
{
   // arm
   glPushMatrix();
   glColor3ub(118,70,185);
   glRotatef(belly, 1, 0, 0);
   glRotatef(shoulder, 0, 0, horizontalVector);
   if (left) 
   {
      glTranslatef(-0.25, 0, 0.60);
      glRotatef(shoulder2, 0, horizontalVector, 0);
      glTranslatef(-0.25, 0, 0);
      glRotatef(90, 0, horizontalVector, 0);
      solidDisk(0.15, 0.2, 0.6, 30, 30);
      glRotatef(elbow, -1, 0, 0);
      glRotatef(elbow2, 0, 1, 0);
      glRotatef(-90, 0, horizontalVector, 0);
      glTranslatef(-0.6, 0, 0);
      glRotatef(90, 0, horizontalVector, 0);
   } else {
      glTranslatef(0.2, 0, 0.60);
      glRotatef(shoulder2, 0, horizontalVector, 0);
      glTranslatef(0.3, 0, 0);
      glRotatef(90, 0, -horizontalVector, 0);
      solidDisk(0.15, 0.2, 0.6, 30, 30);
      glRotatef(elbow, 1, 0, 0);
      glRotatef(elbow2, 0, 1, 0);
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

void Man::drawLeg(GLfloat pelvis, GLfloat knee, bool left) {
   glPushMatrix();
   glColor3ub(118,70,185);
   if (left) {
      glRotatef(pelvis, 1, 0, 0);
      glTranslatef(0.16, 0, -0.8);
      solidDisk(0.12, 0.2, 0.7, 30, 30);
      glRotatef(knee, 1, 0, 0);
      glTranslatef(0, 0, -0.5);
      solidDisk(0.1, 0.12, 0.5, 30, 30);
      glTranslatef(0, 0.1, 0);
      glScalef(0.6,1,0.3);
      glColor3f(0.2,0.2,0.2);
      glutSolidCube(0.4);
   } else {
      glRotatef(pelvis, 1, 0, 0);
      glTranslatef(-0.16, 0, -0.8);
      solidDisk(0.12, 0.2, 0.7, 30, 30);
      glRotatef(knee, 1, 0, 0);
      glTranslatef(0, 0, -0.5);
      solidDisk(0.1, 0.12, 0.5, 30, 30);
      glTranslatef(0, 0.1, 0);
      glScalef(0.6,1,0.3);
      glColor3f(0.2,0.2,0.2);
      glutSolidCube(0.4);
   
   }
   glPopMatrix();
}

int wiggle_count = 0;
GLfloat hold;

float capePoints[ 50 ][ 50 ] [ 3 ];
float xRotation = 80;
float yRotation = 0;
float zRotation = 0;

void Man::drawCape()
{
  glPushMatrix();

  glColor3f(1,0,0);
  //placement de la cape
  glTranslatef(1.2f,-0.4f,1.05f);
  glRotatef(xRotation,1.0f,0.0f,0.0f);
  glRotatef(yRotation, 0.0f, 1.0f, 0.0f);
  glRotatef(zRotation, 0.0f, 0.0f, 1.0f);

  //init du tableau des points de la cape
  for(int x=0;x<50; x++)
  {
    for(int y=0;y<50;y++)
    {
        capePoints[x][y][0] = (x/60.0f)-1.5f;
        capePoints[x][y][1] = (y/40.0f)-1.5f;
        capePoints[x][y][2] = sin((((x/2.0f)*25.0f)/360.0f)*3.141592654*2.0f)/15.0f;
      }
  }

  //glBindTexture(GL_TEXTURE_2D, texture[0]);       // Select Our Texture

  glBegin(GL_QUADS);
  for(int x = 0; x < 49; x++ )                // Loop Through The X Plane (44 Points)
  {
    for(int y = 0; y < 49; y++ )            // Loop Through The Y Plane (44 Points)
    {
     
     // float_x = float(x)/14.0f;       // Create A Floating Point X Value
     // float_y = float(y)/14.0f;       // Create A Floating Point Y Value
     // float_xb = float(x+1)/14.0f;        // Create A Floating Point Y Value+0.0227f
     // float_yb = float(y+1)/14.0f;        // Create A Floating Point Y Value+0.0227fi

    //  glTexCoord2f( float_x, float_y);    // First Texture Coordinate (Bottom Left)
      glVertex3f( capePoints[x][y][0], capePoints[x][y][1], capePoints[x][y][2] );
     //   glTexCoord2f( float_x, float_yb );  // Second Texture Coordinate (Top Left)
      glVertex3f( capePoints[x][y+1][0], capePoints[x][y+1][1], capePoints[x][y+1][2] );
         
      //  glTexCoord2f( float_xb, float_yb ); // Third Texture Coordinate (Top Right)
      glVertex3f( capePoints[x+1][y+1][0], capePoints[x+1][y+1][1], capePoints[x+1][y+1][2] );
         
      //  glTexCoord2f( float_xb, float_y );  // Fourth Texture Coordinate (Bottom Right)
      glVertex3f( capePoints[x+1][y][0], capePoints[x+1][y][1], capePoints[x+1][y][2] );
    }
  }
  glEnd();
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
      } else {
         AnimApplause = 8 ;
      }
   }

   if ( AnimApplause == 3 && CptApplause > 3) {
      AnimApplause = 4;
   }
} 


void Man::walk() 
{
  //only for changing the move
  if (AnimWalk == 2) {
    AnimWalk = 1;
  }
   if (AnimWalk == 0) {
      if (leftShoulder2 > -30) {
         leftShoulder2 -= 1;
         rightShoulder2 += 1;
      }
      if (leftElbow2 > -40) {
         leftElbow2 -= 1;
         rightElbow2 += 1;
      } else {
         AnimWalk = 1;
      }
   }


   if (AnimWalk == 1) {
     if( leftKnee == 0 ) {
        AnimWalk = 2;
     }
   if (reverseAnimWalk == false) 
   {
      if (leftKnee < 15) {
         leftKnee+=0.5;
         leftPelvis+=0.5;
         rightKnee-=0.5;
         rightPelvis-=0.5;
         leftElbow+=0.4;
         rightElbow+=0.4;
      } else {
         reverseAnimWalk = true;
      }
   } else {
      if (leftKnee > -10) {
         leftKnee-=0.5;
         leftPelvis-=0.5;
         rightKnee+=0.5;
         rightPelvis+=0.5;
         leftElbow-=0.4;
         rightElbow-=0.4;
      } else {
         reverseAnimWalk = false;
      }
   }
   }
}

void Man::capeWave()
{
  //on ralenti le movement
  if( wiggle_count == 2 )
  {
    for( int y = 0; y < 49; y++ )
    {
        //on garde le 1er point sur la gauche (1)
        hold=capePoints[0][y][2];
        for( int x = 0; x < 49; x++)
        {
            // on decale d'un cran
          capePoints[x][y][2] = capePoints[x+1][y][2];
        }
        //on le met dans le point à droite (2)
        capePoints[49][y][2]=hold;
    }
    wiggle_count = 0;
  }
  wiggle_count++;
  //xRotation+=0.3f;
  //yRotation+=0.2f;
  //zRotation+=0.4f;
}

void Man::animate()
{
  //la cape bouge tout le temps
  capeWave();
  drawImmediate();
  //  //on traite le nouveau mouvement
  if( Man::currentMove == Man::EVENT_APPLAUSE )
  {
    applause();
  }
  else if ( Man::currentMove == Man::EVENT_WALK )
  {
    walk();
  }
  
}

bool Man::isAnimationEnded()
{
  if( Man::currentMove == Man::EVENT_APPLAUSE )
  {
    return ( AnimApplause == 8 ? true : false );
  }
  else if ( Man::currentMove == Man::EVENT_WALK )
  {
    return ( AnimWalk == 2 ? true : false );
  }
  else
  {
    return true;
  }
}


