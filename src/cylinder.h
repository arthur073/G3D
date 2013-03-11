#ifndef _CYLINDER_
#define _CYLINDER_

#include "renderable.h"
#include <GL/glut.h>

class Cylinder : public Renderable
{
	public:
		void draw();

	private:
		void drawImmediate(float rad, float taille);
		void drawElements();
		void drawArrays();
};

#endif

