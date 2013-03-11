#include <iostream>
#include <math.h>
using namespace std;
#include "cylinder.h"

/*
   cylinder's drawing
   */


void Cylinder::draw()
{

   // draw immediate (center cylinder)
   glPushMatrix();
   drawImmediate(0.5, 0.5);
   //bras 
   glTranslatef(0.5, 0.5, 0);
   glRotatef(-45, -0.1, 0.5, 0);
   drawImmediate(0.15, 0.35); 
   glPopMatrix();
   //bras
   glPushMatrix();
   glTranslatef(0.5, -0.5, 0);
   glRotatef(-45, 0.1, 0.5, 0);
   drawImmediate(0.15, 0.35);
   glPopMatrix();

   //jambe droite
   glPushMatrix();
   glTranslatef(0, 0.25, -0.8);
   drawImmediate(0.15, 0.35);
   glPopMatrix();

   //jambe gauche
   glPushMatrix();
   glTranslatef(0, -0.25, -0.8);
   drawImmediate(0.15, 0.35);
   glPopMatrix();
}

//==================== 1. Immediate method ===================================
// immediate definition of individual vertex properties

void Cylinder::drawImmediate(float rad, float taille)
{

   const float DEG2RAD = 3.14159/180;
   const float radius = rad;

   // le dessus
   glBegin(GL_POLYGON);

   glNormal3f(0.0, 0.0, -1.0);
   for (int i=0; i < 360; i++)
   {
      float degInRad = i*DEG2RAD;
      glVertex3f(cos(degInRad)*radius,sin(degInRad)*radius, -taille);
   }

   glEnd();

   // le dessous
   glBegin(GL_POLYGON);

   glNormal3f(0.0, 0.0, 1.0);	
   for (int i=0; i < 360; i++)
   {
      float degInRad = i*DEG2RAD;
      glVertex3f(cos(degInRad)*radius,sin(degInRad)*radius, taille);
   }

   glEnd();


   // la couverture
   // nombre de côtés
   const float n = 100;
   glBegin(GL_QUAD_STRIP);
   for(int i = 0; i < 480; i += (360 / n)) {
      float a = i * DEG2RAD; // degrees to radians
      glNormal3f(cos(a), sin(a), 0); // TODO: to change
      glVertex3f(cos(a)*radius, sin(a)*radius, -taille);
      glVertex3f(cos(a)*radius, sin(a)*radius, taille);
   }
   glEnd();	
}



//==================== 2. Arrays - drawArrays ================================
// - store vertex-related data (coordinates, normals, colors, etc) in arrays
//   => reduces the number of function calls

void Cylinder::drawArrays()
{	

   // on définit les variables globales et les tableaux
   const float DEG2RAD = 3.14159/180;
   const float radius = 0.5;
   GLfloat allVertices[1080];
   GLfloat allNormals[1080];
   GLfloat allVertices2[1080];
   GLfloat allNormals2[1080];
   GLfloat allVertices3[960];
   GLfloat allNormals3[960];
   int curV = 0;
   int curN = 0;


   // Remplissage des tableaux
   // le dessus
   for (int i=0; i < 360; i++)
   {
      float degInRad = i*DEG2RAD;
      allVertices[curV++] = cos(degInRad)*radius;
      allVertices[curV++] = sin(degInRad)*radius;
      allVertices[curV++] = -0.5;
      allNormals[curN++] = 0.0;
      allNormals[curN++] = 0.0;
      allNormals[curN++] = -1.0;
   }


   // le dessous
   curV = 0;
   curN = 0;
   for (int i=0; i < 360; i++)
   {
      float degInRad = i*DEG2RAD;
      allVertices2[curV++] = cos(degInRad)*radius;
      allVertices2[curV++] = sin(degInRad)*radius;
      allVertices2[curV++] = 0.5;
      allNormals2[curN++] = 0.0;
      allNormals2[curN++] = 0.0;
      allNormals2[curN++] = 1.0;

   }


   // la couverture
   // nombre de côtés
   curV = 0;
   curN = 0;
   const float n = 100;
   for(int i = 0; i < 480; i += (360 / n)) {
      float a = i * DEG2RAD; // degrees to radians
      //	glVertex3f(cos(a)*radius, sin(a)*radius, -0.5);
      //	glVertex3f(cos(a)*radius, sin(a)*radius, 0.5);
      allVertices3[curV++] = cos(a)*radius;
      allVertices3[curV++] = sin(a)*radius;
      allVertices3[curV++] = -0.5;
      allVertices3[curV++] = cos(a)*radius;
      allVertices3[curV++] = sin(a)*radius;
      allVertices3[curV++] = 0.5;

      allNormals3[curN++] = cos(a);
      allNormals3[curN++] = sin(a);
      allNormals3[curN++] = 0;
      allNormals3[curN++] = cos(a);
      allNormals3[curN++] = sin(a);
      allNormals3[curN++] = 0;


   }


   // Utilisation des tableaux

   // activate the use of GL_VERTEX_ARRAY and GL_NORMAL_ARRAY
   glEnableClientState(GL_NORMAL_ARRAY);
   glEnableClientState(GL_VERTEX_ARRAY);
   // specify the arrays to use
   // le haut
   glNormalPointer(GL_FLOAT, 0, allNormals);
   glVertexPointer(3, GL_FLOAT, 0 , allVertices);
   glDrawArrays(GL_POLYGON, 0, 360); 

   // le bas
   glNormalPointer(GL_FLOAT, 0, allNormals2);
   glVertexPointer(3, GL_FLOAT, 0 , allVertices2);
   glDrawArrays(GL_POLYGON, 0, 360); 

   // la couverture
   glNormalPointer(GL_FLOAT, 0, allNormals3);
   glVertexPointer(3, GL_FLOAT, 0 , allVertices3);
   glDrawArrays(GL_QUAD_STRIP, 0, 320); 

   // disable the use of arrays (do not forget!)
   glDisableClientState(GL_VERTEX_ARRAY);
   glDisableClientState(GL_NORMAL_ARRAY);
}
