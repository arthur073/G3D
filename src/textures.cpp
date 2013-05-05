#include <iostream>
#include <cstdio>
using namespace std;

#include <QGLViewer/qglviewer.h>
#include "textures.h"
#include "man.h"

string TexIDSkyBox[6];
Textures::Textures()
{
   glEnable(GL_TEXTURE_2D);
}


Textures::~Textures()
{
}


void Textures::init()
{
   initGrassPlane();
   initSkyBox();
   initHead();
}
float *rotate = 0;

void Textures::draw()
{

   float translateCompletZ = Man::getTranslateCompletZ();
   glTranslatef(0,0,translateCompletZ);
   drawHead();
   glTranslatef(0,0,-translateCompletZ);

   drawGrassPlane(300.0);
   glDisable(GL_LIGHTING);
   drawSkyBox(0,0,0,300,300,300);
   glEnable(GL_LIGHTING);

   // balles
   Man::drawParametrizedBall(5, 0, 3,.5, 0.5, 0);
   Man::drawParametrizedBall(0, 5, 3,.5, 0.6, 1);
   Man::drawParametrizedBall(-5, 0, 3,.5, 0.7, 2);
   Man::drawParametrizedBall(0, -5, 3,.5, 0.8, 3);
   Man::drawParametrizedBall(0, 2.5, 3,.35, 0.4, 4);


   Man::drawBall();
   glBindTexture(GL_TEXTURE_2D, 0);
}


void Textures::loadTexture(TextureId texId, const char *filename)
{
   // generates an OpenGL texture id, and store it in the map
   GLuint id;
   glGenTextures(1, &id);
   textures[texId] = id;

   // load a texture file as a QImage
   QImage img = QGLWidget::convertToGLFormat(QImage(filename));

   // specify the texture (2D texture, rgba, single file)
   glBindTexture(GL_TEXTURE_2D, textures[texId]);
   glTexImage2D (GL_TEXTURE_2D, 0, GL_RGBA, img.width(), img.height(), 0,
         GL_RGBA, GL_UNSIGNED_BYTE, img.bits());
}


void Textures::initGrassPlane()
{
   // load the grass texture
   loadTexture(TEX_GRASS, "images/grass.tiff");

   // set its parameters
   glBindTexture(GL_TEXTURE_2D, textures[TEX_GRASS]);

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}


void Textures::initHead()
{  
   // load the face texture
   loadTexture(TEX_FACE, "images/face.jpg");

   // set its parameters
   glBindTexture(GL_TEXTURE_2D, textures[TEX_FACE]);

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}

void Textures::drawGrassPlane(float s)
{
   // use the grass texture
   glBindTexture(GL_TEXTURE_2D, textures[TEX_GRASS]);
   // draw a plane
   drawPlane(s);
}

void Textures::drawHead() {

   // positionnement
   float belly = Man::getBelly();
   float neck = Man::getNeck();
   //glColor3ub(246,198,224);
   glPushMatrix();
   glRotatef(belly, 1, 0, 0);
   glRotatef(neck, 1, 0, 0);
   glRotatef(180, 0, 0, 1);
   glTranslatef(0, 0, 1.2);
   glScalef(0.85,1,1);
   //glutSolidSphere(0.5, 30, 30);

   // dessin
   GLUquadric *qobj = gluNewQuadric(); 
   gluQuadricTexture(qobj,GL_TRUE); 
   //glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D, textures[TEX_FACE]);
   gluSphere(qobj,0.5,50,50); 
   gluDeleteQuadric(qobj); 

   glPopMatrix();
}


void Textures::drawPlane(float s)
{
   float height = 0;

   glPushMatrix();

   glNormal3f(0.0f, 1.0f, 1.0f);
   glTranslatef(-s / 2.0, -s / 2.0, -1.35);

   glBegin(GL_QUADS);	
   glTexCoord2f(0, 0);
   glVertex3f(0, 0, height);
   glTexCoord2f(100, 0);
   glVertex3f(s, 0, height);
   glTexCoord2f(100, 100);
   glVertex3f(s, s, height);
   glTexCoord2f(0, 100);
   glVertex3f(0, s, height);
   glEnd();

   glPopMatrix();

}

void Textures::initSkyBox()
{
   loadTexture(TEX_SKY_TOP, "images/YP.bmp"); //ok
   loadTexture(TEX_SKY_RIGHT, "images/XP.bmp"); //ok
   loadTexture(TEX_SKY_BACK, "images/ZN.bmp"); // ok
   loadTexture(TEX_SKY_FRONT, "images/ZP.bmp"); //ok
   loadTexture(TEX_SKY_LEFT, "images/XN.bmp"); //ok
   loadTexture(TEX_SKY_BOTTOM, "images/YN.bmp"); //ok

   Textures::TextureId texturesMap[6] = {TEX_SKY_BACK,TEX_SKY_FRONT,TEX_SKY_BOTTOM, TEX_SKY_TOP, TEX_SKY_RIGHT, TEX_SKY_LEFT};

   for(int i=0;i<6;i++)
   {
      glBindTexture(GL_TEXTURE_2D, texturesMap[i]);
      glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
      glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);

      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
   }
}

void Textures::drawSkyBox(float x, float y, float z, float width, float height, float length)
{
   x = x - width  / 2;  // Calcul l'emplacement d'un coin du cube
   y = y - height / 2;
   z = z - length / 2;

   glBindTexture(GL_TEXTURE_2D, textures[TEX_SKY_BOTTOM]);
   glBegin(GL_QUADS);	
   glNormal3f(0.0, 0.0, -1.0);  
   glTexCoord2f(0.0f, 0.0f); glVertex3f(x,y,z);
   glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y,z);
   glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width,y + height, z);
   glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + height, z); 
   glEnd();

   glBindTexture(GL_TEXTURE_2D, textures[TEX_SKY_TOP]);
   glBegin(GL_QUADS);			
   glTexCoord2f(0.0f, 0.0f); glVertex3f(x,y,z + length);
   glTexCoord2f(0.0f, 1.0f); glVertex3f(x,y + height, z + length);
   glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y + height, z + length);
   glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y, z + length); 	
   glEnd();

   glBindTexture(GL_TEXTURE_2D, textures[TEX_SKY_BACK]);
   glBegin(GL_QUADS);				
   glTexCoord2f(1.0f, 1.0f); glVertex3f(x,y,z);
   glTexCoord2f(1.0f, 0.0f); glVertex3f(x,y,	z + length);
   glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y,z + length);
   glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y,z); 	
   glEnd();

   glBindTexture(GL_TEXTURE_2D, textures[TEX_SKY_FRONT]);
   glBegin(GL_QUADS);					
   glTexCoord2f(1.0f, 1.0f); glVertex3f(x,y + height,z);
   glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height, z);
   glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y + height, z + length);
   glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y + height, z + length); 	
   glEnd();


   glBindTexture(GL_TEXTURE_2D, textures[TEX_SKY_LEFT]);
   glBegin(GL_QUADS);				
   glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y, z);
   glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + height, z);
   glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y + height, z + length);
   glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z + length); 
   glEnd();

   glBindTexture(GL_TEXTURE_2D, textures[TEX_SKY_RIGHT]);
   glBegin(GL_QUADS);				
   glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y, z);
   glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y, z + length);
   glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y + height, z + length);
   glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height, z); 
   glEnd();

}
