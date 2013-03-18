#ifndef _MAN_
#define _MAN_

#include "renderable.h"
#include <GL/glut.h>

class Man : public Renderable
{
	public:
		void draw();

	private:
		void drawImmediate();
};

#endif

