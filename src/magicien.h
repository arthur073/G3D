#ifndef _MAGICIAN_
#define _MAGICIAN_

#include "renderable.h"
#include <GL/glut.h>
#include "cube.h"
#include "cylinder.h"
#include "sphere.h"

class Magicien : public Renderable
{
	public:
		Magicien();
     ~Magicien();
  void draw();
};

#endif

