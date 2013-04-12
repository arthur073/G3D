#include <iostream>
#include <cstdio>
using namespace std;

#include <QGLViewer/qglviewer.h>
#include "textures.h"



Textures::Textures()
{
	// make sure this flag is enable to use textures!
	glEnable(GL_TEXTURE_2D);
	filteringMode = 0;
}


Textures::~Textures()
{
}


void Textures::init()
{
	// load and init all the textures used in this practical
	initGrassPlane();
//	initCrate();
// 	initMipmap();
//	initMultiTexturing();
//	initBillBoard();
}


void Textures::draw()
{
// [un]comment these functions when required with the questions...

	drawGrassPlane(10.0);
//	drawCrate(2.0);
// 	drawMipmap();
// 	drawMultiTexturing();
// 	drawBillBoard();
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
	// use filtering option (toogled with 'f' key)
	setFiltering();

	// draw a plane
	drawPlane(s);
}


void Textures::drawPlane(float s)
{
	glNormal3f(0.0, 0.0, 1.0);
	float height = 0;

	glPushMatrix();
	glTranslatef(-s / 2.0, -s / 2.0, 0.0);
	
	// Qu 1: the all texture is directly mapped to the quad angles
	//       => glTexCoord2f(0,1),(1,1),(1,0),(0,0)

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


///////////////////////////////////////////////////////////////////////////////
//   CRATE

void Textures::initCrate()
{
	// TODO!
	loadTexture(TEX_CRATE, "images/crate.tiff");
	
	// set its parameters
	glBindTexture(GL_TEXTURE_2D, textures[TEX_CRATE]);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}

void Textures::drawCrate(float size)
{
	// TODO : define the texture coordinates to map the crate.tiff
	// texture on each face

	// ...

	// use the grass texture
	glBindTexture(GL_TEXTURE_2D, textures[TEX_CRATE]);
	// use filtering option (toogled with 'f' key)
	setFiltering();
	glBegin(GL_QUADS);

	glTexCoord3f(0, 0, 1);
	glVertex3f(0, 0, 0);
	glTexCoord3f(1, 0, 1);
	glVertex3f(size, 0, 0);
	glTexCoord3f(1, 0, 1);
	glVertex3f(size, 0, size);
	glTexCoord3f(0, 0, 1);
	glVertex3f(0, 0, size);

	glTexCoord3f(1, 0, 1);
	glVertex3f(size, 0, 0);
	glTexCoord3f(1, 1, 1);
	glVertex3f(size, size, 0);
	glTexCoord3f(1, 1, 1);
	glVertex3f(size, size, size);
	glTexCoord3f(1, 0, 1);
	glVertex3f(size, 0, size);

	glTexCoord3f(1, 1, 1);
	glVertex3f(size, size, 0);
	glTexCoord3f(0, 1, 1);
	glVertex3f(0, size, 0);
	glTexCoord3f(0, 1, 1);
	glVertex3f(0, size, size);
	glTexCoord3f(1, 1, 1);
	glVertex3f(size, size, size);

	glTexCoord3f(0, 1, 1);
	glVertex3f(0, size, 0);
	glTexCoord3f(0, 0, 1);
	glVertex3f(0, 0, 0);
	glTexCoord3f(0, 0, 1);
	glVertex3f(0, 0, size);
	glTexCoord3f(0, 1, 1);
	glVertex3f(0, size, size);

	glTexCoord3f(0, 0, 1);
	glVertex3f(0, 0, size);
	glTexCoord3f(1, 0, 1);
	glVertex3f(size, 0, size);
	glTexCoord3f(1, 1, 1);
	glVertex3f(size, size, size);
	glTexCoord3f(0, 1, 1);
	glVertex3f(0, size, size);

	glEnd();

}



///////////////////////////////////////////////////////////////////////////////
//   MIPMAP

void Textures::initMipmap()
{
	// TODO!
}

void Textures::drawMipmap()
{
	// TODO!
}




///////////////////////////////////////////////////////////////////////////////
//   MULTI-TEXTURING

void Textures::initMultiTexturing()
{
	// TODO!
}


void Textures::drawMultiTexturing()
{
	// TODO!
}



///////////////////////////////////////////////////////////////////////////////
//   BILLBOARDS

void Textures::initBillBoard()
{
	// TODO!
}

void Textures::drawBillBoard()
{
	// TODO!
}



///////////////////////////////////////////////////////////////////////////////
// CONTROLS 

// filteringMode (for GL_TEXTURE_MIN_FILTER) can be 
//	GL_NEAREST, GL_LINEAR, 
//	GL_NEAREST_MIPMAP_NEAREST,GL_LINEAR_MIPMAP_NEAREST, 
//	GL_NEAREST_MIPMAP_LINEAR, GL_LINEAR_MIPMAP_LINEAR

void Textures::toogleFiltering()
{
	filteringMode = ++filteringMode % 6;
	cout << "filteringMode = " << filteringMode << endl;
}

void Textures::setFiltering()
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
}

void Textures::setFilteringMipmap()
{
	// MIN FILTER
	switch (filteringMode) {
	case 0:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		break;
	case 1:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		break;
	case 2:
		// nearest ds les levels, puis nearest
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
		break;
	case 3:
		// interp ds les levels, puis nearest
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
		break;
	case 4:
		// nearest ds les levels, puis interpolation
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
		break;
	case 5:
		// interp ds les levels, puis interpolation
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		break;
	default:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	}

	// MAG FILTER
	switch (filteringMode) {
	case 0:
	case 2:
	case 4:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		break;
	case 1:
	case 3:
	case 5:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		break;
	}
}

