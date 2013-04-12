#ifndef _TEXTURES_H_
#define _TEXTURES_H_

#include <map>
using namespace std;
#include <QImage>

#include "renderable.h"


class Textures : public Renderable
{

public:
	Textures();
	virtual ~Textures();

// Renderable methods
public:
	void init();
	void draw();

private:
	// id of all textures used in this practical
	enum TextureId {
		TEX_GRASS,
		TEX_CRATE, 
		TEX_MIPMAP,
		TEX_FLOWERS,
		TEX_LIGHT,
		TEX_TREE
	};

	// association bewteen a TextureId and its OpenGL texture id
	// (generated with glGenTextures. cf the loadTexture method)
	map<TextureId, GLuint> textures;

	// load a single texture file to associate with a Textureid
	void loadTexture(TextureId id, const char *filename);
	
	// draw a quad centered in the XY place (z=0), of size s
	void drawPlane(float s = 10.0);
	

// METHODS TO IMPLEMENT / MODIFY IN THE PRATICAL SESSION

	// init and draw a plane with the grass texture
	void initGrassPlane();
	void drawGrassPlane(float size);

	// init and draw a crate with texture on each face
	void initCrate();
	void drawCrate(float size);

	// use mipmaps
	void initMipmap();
	void drawMipmap();

	// use multi-texturing
	void initMultiTexturing();
	void drawMultiTexturing();

	// use billboards
	void initBillBoard();
	void drawBillBoard();

public:
	// activated by the 'f' key
	GLint filteringMode;
	void toogleFiltering();
	void setFiltering();
	void setFilteringMipmap();
};

#endif
