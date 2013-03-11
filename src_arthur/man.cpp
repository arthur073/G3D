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
   // torsal
	glPushMatrix();
   drawCylinder(0.7, 0.7);
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


   // right leg
	glPushMatrix();
	glTranslatef(0.4, 0, -1);
   drawCylinder(0.25, 0.6);
	glPopMatrix();

   // left leg
	glPushMatrix();
	glTranslatef(-0.4, 0, -1);
   drawCylinder(0.25, 0.6);
	glPopMatrix();

   // right foot 
	glPushMatrix();
	glTranslatef(0.4, 0, -1.6);
   glRotatef(90, 1, 0, 0);
   glutSolidSphere(0.5, 2, 3);
	glPopMatrix();

   // left foot 
	glPushMatrix();
	glTranslatef(-0.4, 0, -1.6);
   glRotatef(90, 1, 0, 0);
   glutSolidSphere(0.5, 2, 3);
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
			         glNormal3f(cos(a), sin(a), 0); // TODO: to change
            		glVertex3f(cos(a)*radius, sin(a)*radius, -height);
            		glVertex3f(cos(a)*radius, sin(a)*radius, height);
        	}
	glEnd();	
}

