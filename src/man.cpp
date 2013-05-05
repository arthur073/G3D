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

GLfloat ballZ = 0;
GLfloat ballY = 0;
GLfloat ballYLength = 0;
GLfloat ballSize = 0;
GLfloat alphaBall = 0;
GLfloat Light0Power = 1.5;
GLfloat Light1Power = 0.0;

float translateCompletZ = 0.0f;

int horizontalVector = 1;

bool reverseAnim = false;
bool reverseAnimWalk = false;

const string Man::EVENT_APPLAUSE = "applause";
const string Man::EVENT_WALK = "walk";
const string Man::EVENT_SPELL = "spell";
const string Man::EVENT_DISAPPEAR = "disappear";

string Man::currentMove = "";

// Anim Applause
GLint AnimApplause = 1;
GLint AnimWalk = 0;
GLint AnimSpell = 0;
GLint AnimDisappear = 0;
GLint CptApplause = 0;
GLint CptWait = 0;
GLint cptWalk = 0;


void Man::draw()
{
   // draw immediate 
   drawImmediate();
}

//==================== 1. Immediate method ===================================
// immediate definition of individual vertex properties
void Man::drawImmediate()
{
   glEnable(GL_LIGHT1);
   glTranslatef(0,0,translateCompletZ);

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
   //glutSolidSphere(0.5, 30, 30);
   // hat
   glTranslatef(0, 0, 0.4);
   glColor3ub(118,70,185);
   solidCone(0.5, 0.8, 30, 30);
   solidDisk(0.7, 0.7, 0.01, 30, 30);
   glPopMatrix();



   //fog
   drawFog();

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

void Man::drawBall() 
{

   // Lumière ambiante
   float fTemp0[4] = { Light0Power, Light0Power, Light0Power, 1.0f };
   glLightfv(GL_LIGHT0, GL_DIFFUSE, fTemp0);

   glPushMatrix();
   glEnable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
   
   glRotatef(ballY, 0, 0, 1);

   // Lumière de la balle
   GLfloat light1_position[] = { 0.0f, 1.5f, 0.7f, 0.3f };
   float fTemp1[4] = { Light1Power, Light1Power, Light1Power, 1.0f };
   glLightfv(GL_LIGHT1, GL_DIFFUSE, fTemp1);
   glLightfv(GL_LIGHT1, GL_POSITION, light1_position); 


   glTranslatef(0,1.5+ballYLength,0.9+ballZ/200);
   glColor4f(1,1,1,alphaBall);
   glScalef(ballSize/40,ballSize/40,ballSize/40);
   glutSolidSphere(0.3, 30, 30);
   glDisable(GL_BLEND);
   glPopMatrix();
}

float fogDensity = 0.0f;

void Man::drawFog()
{
  GLfloat fogColor[4] = { 0.5f, 0.5f, 0.5f, 1.0f };
  glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

  glFogi(GL_FOG_MODE, GL_EXP);
  glFogfv(GL_FOG_COLOR, fogColor);
  glFogf(GL_FOG_DENSITY, fogDensity);
  glHint(GL_FOG_HINT, GL_DONT_CARE);
  glFogf(GL_FOG_START, 1.0f);
  glFogf(GL_FOG_END, 5.0f);
  glEnable(GL_FOG);

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
         cptWalk++;
      }
      if (cptWalk == 6) {
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

   if (AnimWalk == 2) {
      // On remonte au point de départ
      if (leftShoulder2 < 0) {
         leftShoulder2 += 1;
         rightShoulder2 -= 1;
      }
      if (leftElbow2 < 0) {
         leftElbow2 += 1;
         rightElbow2 -= 1;
      } else {
         AnimWalk = 3;
      }
   }
}

void Man::spell() 
{

   if (AnimSpell == 0) {
      if (leftShoulder2 < 20) {
         leftShoulder-=0.5;
         leftShoulder2+=0.35;
         rightShoulder2-=0.35;
         rightShoulder+=0.5;
         Light0Power-=0.017;
      } else {
         AnimSpell = 1;
      }   
      if (leftElbow2 < 10) {
         leftElbow2++;
         rightElbow2--;
      }
   }

   if (AnimSpell == 1) {
      if (leftShoulder2 < 25) {
         leftShoulder2+=0.05;
         rightShoulder2-=0.05;
      } else {
         AnimSpell = 2;
      }   
      if (leftElbow2 < 15) {
         leftElbow2+=0.1;
         rightElbow2-=0.1;
      }
   }

   if (AnimSpell == 2) {
         if (ballSize < 20) {
            alphaBall+=0.03;
            ballZ++;
            ballSize++;
            Light1Power+=0.03;
         } else {
            AnimSpell = 3;
         }
   }

   if (AnimSpell == 3) {
         if (ballZ < 100) {
            ballZ++;
            neck+=0.1;
            leftShoulder2+=0.1;
            rightShoulder2-=0.1;
         } else {
            AnimSpell = 4;
         }
   }

   if (AnimSpell == 4) {
      if (ballY < 90) {
         ballZ+=0.1;
         ballY++;
      } else {
         AnimSpell = 5;
      }
   } 

  if (AnimSpell == 5) {
      if (ballY < 3600) {
         ballY= ballY + (ballY/100);
         Light1Power+=0.009;
      } else {
         AnimSpell = 6;
      }
   } 

  if ( AnimSpell == 6) {
      if (ballY < 7200) {
         ballY= ballY + ((7250 - ballY)/100);
         ballSize+=0.1;
      } else {
         AnimSpell = 7;
      }
      if (ballY > 7100) {
         belly+=0.1;
      }
  }

  if (AnimSpell == 7) {
      
     if (belly < 20) {
         belly+=0.1;
         leftShoulder2-=0.1;
         rightShoulder2+=0.1;
         Light1Power+=0.1;
      } else {
         AnimSpell = 8;
      }
  } 

  if (AnimSpell == 8) {
      // lancé de la boule
      if (belly > -20) {
         belly -=3;
         leftShoulder2+=0.5;
         rightShoulder2-=0.5;
      } else {
         AnimSpell = 9;
      }  
      if (ballYLength < 100 && belly < -10) {
         ballYLength+=0.1;
      } 
  }

  if (AnimSpell == 9) {
     if (ballYLength < 10) {
         ballYLength+=0.2;
     } else {
        AnimSpell = 10;
      }
  }

   if (AnimSpell == 10) {
      // insérer ici une explosion de la boule
      if (Light1Power < 20) {
         Light1Power+=0.5;
         ballSize+=0.3;
         alphaBall-=0.2;
      } else {
         AnimSpell = 11;
      }
   }

   if (AnimSpell == 11) {
      Light1Power= 0;
      AnimSpell = 12;
   }

   if (AnimSpell == 12) {
      if (Light0Power < 1) {
         Light0Power+=0.01;
      }
      if (leftShoulder2 >0) {
         leftShoulder2--;
         rightShoulder2++;
      }
      if (leftElbow2>0) {
         leftElbow2--;
         rightElbow2++;
      }
      if (neck>0) {
         neck-=0.1;
      } else {
         AnimSpell = 13;
      }
      if (leftShoulder<0) {
         leftShoulder++;
         rightShoulder--;
      }
      if (belly < 0) {
         belly++;
      }
   }

}
int cptTimer = 0;
void Man::disappear()
{
  if( AnimDisappear == 0 ) {
    if( fogDensity < 0.300f ) {
      fogDensity += 0.002f;
    } else {
      AnimDisappear = 1;
    }
  } else if( AnimDisappear == 1 ) {
    //faire disparaitre le bonhomme
    //translateCompletZ = 1200;
    AnimDisappear = 2;
  } else if( AnimDisappear == 2 ) {
    if( fogDensity > 0.0f ) {
      fogDensity -= 0.002f;
    } else {
      fogDensity = 0;
      AnimDisappear = 3;
    }
  } else if( AnimDisappear == 3 ) {
    if( cptTimer > 150 ) {
      AnimDisappear = 4;
    } else {
      cptTimer++;
    }
  }
}




void Man::animate()
{

   //on fait reapparaitre le bonhomme au cas ou
   if( Man::currentMove != Man::EVENT_DISAPPEAR )
     translateCompletZ = 0;

   //on traite le nouveau mouvement
   if( Man::currentMove == Man::EVENT_APPLAUSE )
   {
      applause();
   }
   else if ( Man::currentMove == Man::EVENT_WALK )
   {
      walk();
   }
   else if ( Man::currentMove == Man::EVENT_SPELL )
   {
      spell();
   }
   else if( Man::currentMove == Man::EVENT_DISAPPEAR )
   {
     disappear();
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
      return ( AnimWalk == 3 ? true : false );
   }
   else if ( Man::currentMove == Man::EVENT_SPELL )
   {
      return ( AnimSpell == 13 ? true : false );
   }
   else if ( Man::currentMove == Man::EVENT_DISAPPEAR )
   {
     return ( AnimDisappear == 4 ? true : false );
   }
   else
   {
      return true;
   }
}


void Man::resetAnim() {
   AnimWalk = 0;
   AnimApplause = 1;
   AnimSpell = 0;
   AnimDisappear = 0;
   CptApplause = 0;
   CptWait = 0;
   cptWalk = 0;
   AnimSpell = 0;
   ballZ= 0;
   ballY= 0;
   ballYLength = 0;
   ballSize = 0;
   alphaBall = 0;
}


float Man::getBelly()
{
   return belly;
}

float Man::getNeck()
{
   return neck;
}
