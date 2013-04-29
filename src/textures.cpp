#include <iostream>
#include <cstdio>
using namespace std;

#include <QGLViewer/qglviewer.h>
#include "textures.h"

string TexIDSkyBox[6];
Textures::Textures()
{
	// make sure this flag is enable to use textures!
	glEnable(GL_TEXTURE_2D);
}


Textures::~Textures()
{
}


void Textures::init()
{
  initGrassPlane();
	initTree();
  initSkyBox();
}


void Textures::draw()
{
	drawGrassPlane(10.0);
  drawSkyBox(0,0,0,150,150,150);
  drawTree(4, 2, 2, 4);
  glBindTexture(GL_TEXTURE_2D, 0);
}


///////////////////////////////////////////////////////////////////////////////
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


///////////////////////////////////////////////////////////////////////////////
//   PLANE TEXTURE WITH GRASS

void Textures::initGrassPlane()
{
	// load the grass texture
	loadTexture(TEX_GRASS, "images/grass.tiff");
	
	// set its parameters
	glBindTexture(GL_TEXTURE_2D, textures[TEX_GRASS]);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}


void Textures::initTree() 
{
	// load the tree texture
	loadTexture(TEX_TREE, "images/tree.tiff");


	// set its parameters
	glBindTexture(GL_TEXTURE_2D, textures[TEX_TREE]);
	
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


void Textures::drawPlane(float s)
{
	float height = 0;

	glPushMatrix();

	glNormal3f(0.0f, 0.0f, 1.0f);
	glTranslatef(-s / 2.0, -s / 2.0, -1.35);
	
	glBegin(GL_QUADS);	
	glTexCoord2f(0, 0);
	glVertex3f(0, 0, height);
	glTexCoord2f(1, 0);
	glVertex3f(s, 0, height);
	glTexCoord2f(1, 1);
	glVertex3f(s, s, height);
	glTexCoord2f(0, 1);
	glVertex3f(0, s, height);
	glEnd();
		
	glPopMatrix();

}

void Textures::initSkyBox()
{
	int i;

	//loadTexture(TEX_SKY_BACK, "images/ZN.bmp"); // pas ok
	loadTexture(TEX_SKY_FRONT, "images/ZP.bmp"); //ok
	loadTexture(TEX_SKY_BOTTOM, "images/YN.bmp"); //ok
	loadTexture(TEX_SKY_TOP, "images/YP.bmp"); //ok
	loadTexture(TEX_SKY_LEFT, "images/XN.bmp"); // pas ok
	loadTexture(TEX_SKY_RIGHT, "images/grass.tiff"); // pas ok

  Textures::TextureId texturesMap[6] = {TEX_SKY_BACK,TEX_SKY_FRONT,TEX_SKY_BOTTOM, TEX_SKY_TOP, TEX_SKY_RIGHT, TEX_SKY_LEFT};
	
  for(i=0;i<6;i++)
	{
		glBindTexture(GL_TEXTURE_2D, texturesMap[i]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

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
  glBegin(GL_TRIANGLE_STRIP);					
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x,y,z);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y,z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x,y + height, z);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y + height, z); 
  glEnd();

  glBindTexture(GL_TEXTURE_2D, textures[TEX_SKY_TOP]);
  glBegin(GL_TRIANGLE_STRIP);			
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x,y,z + length);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x,y + height, z + length);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y, z + length);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height, z + length); 	
  glEnd();

  glBindTexture(GL_TEXTURE_2D, textures[TEX_SKY_BACK]);
  glBegin(GL_TRIANGLE_STRIP);				
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x,y,z);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x,y,	z + length);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y,z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y,z + length); 	
  glEnd();

  glBindTexture(GL_TEXTURE_2D, textures[TEX_SKY_FRONT]);
  glBegin(GL_TRIANGLE_STRIP);					
    glTexCoord2f(1.0f, 1.0f); glVertex3f(x,y + height,z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height, z);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y + height, z + length);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y + height, z + length); 	
  glEnd();


  glBindTexture(GL_TEXTURE_2D, textures[TEX_SKY_LEFT]);
  glBegin(GL_TRIANGLE_STRIP);				
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + height, z);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z + length);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + height, z + length); 
  glEnd();

  glBindTexture(GL_TEXTURE_2D, textures[TEX_SKY_RIGHT]);
  glBegin(GL_TRIANGLE_STRIP);				
    glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y, z);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y, z + length);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height, z);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y + height, z + length); 
  glEnd();

 }

/*void Textures::setFiltering()
{
	switch (filteringMode) {
	case 0:
	case 2:
	case 4:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		break;
	case 1:
	case 3:
	case 5:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		break;
	}
}*/





void Textures::drawTree(GLfloat posX, GLfloat posY, GLfloat width, GLfloat height) {

	glBindTexture(GL_TEXTURE_2D, textures[TEX_TREE]);
	glPushMatrix();
   glEnable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 

	glNormal3f(0, 0.0, 1.0);
	glTranslatef(posX, posY, -1.35);
   glRotatef(90, 1, 0, 0);
	
   glBegin(GL_QUADS);	
	glTexCoord2f(0, 0);
	glVertex3f(2, 0, 0);
	glTexCoord2f(1, 0);
	glVertex3f(2, 0, width);
	glTexCoord2f(1, 1);
	glVertex3f(2, height, width);
	glTexCoord2f(0, 1);
	glVertex3f(2, height, 0);
	glEnd();

   glDisable(GL_BLEND);
	glPopMatrix();


}

