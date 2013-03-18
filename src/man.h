#ifndef _MAN_
#define _MAN_

#include "renderable.h"
#include <GL/glut.h>

class Man : public Renderable
{
	public:
		void draw();
		void animate();

	private:
		void drawImmediate();
		void drawCylinder(float radius, float height);
      void solidCone(GLdouble base, GLdouble height, GLint slices, GLint stacks);
      void solidDisk(GLfloat base, GLfloat thickness, GLint slices, GLint stacks);
};

#endif

