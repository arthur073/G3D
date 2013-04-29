#include <iostream>
#include <cstdio>
using namespace std;

#include <QGLViewer/qglviewer.h>
#include "textures.h"



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
	// load and init all the textures used in this practical
	initGrassPlane();
}


void Textures::draw()
{
	drawGrassPlane(10.0);
 // drawSkyDome();
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

void Textures::drawGrassPlane(float s)
{
	// use the grass texture
	glBindTexture(GL_TEXTURE_2D, textures[TEX_GRASS]);
	// draw a plane
	drawPlane(s);
  glBindTexture(GL_TEXTURE_2D, 0);
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

void Textures::drawSkyDome()
{
  int radius = 200;
  double phi, theta;
  double x, y, z;
  double PI = 3.141592;
  glPushMatrix();
  for (phi = 0.0; phi <= 80.0; phi += 10.0) {
        glBegin(GL_TRIANGLE_STRIP);
            for (theta = -180.0; theta <= 180.0; theta += 10.0) {
                x = radius * sin(PI/180 * theta) * cos(PI/180 * phi);
                y = radius * cos(PI/180 * theta) * cos(PI/180 * phi);
                z = radius * sin(PI/180 * phi);
                glVertex3d (x,y,z);
                x = radius * sin(PI/180 * theta) * cos(PI/180 * (phi + 10.0));
                y = radius * cos(PI/180 * theta) * cos(PI/180 * (phi + 10.0));
                z = radius * sin(PI/180 * (phi + 10.0));
                glVertex3d (x,y,z);
           }
         glEnd();
  }
  glPopMatrix();
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

