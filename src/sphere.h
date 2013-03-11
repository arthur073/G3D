#ifndef _SPHERE_
#define _SPHERE_

#include "renderable.h"
#include <GL/glut.h>

class Sphere : public Renderable
{
	public:
		void draw();

	private:
		void drawImmediate();
		void drawElements();
		void drawArrays();
};

#endif

