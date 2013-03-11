#ifndef _MAGICIEN_
#define _MAGICIEN_

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
};

#endif

