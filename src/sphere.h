#ifndef _SPHERE_
#define _SPHERE_

#include "renderable.h"
#include <GL/glut.h>

class Sphere : public Renderable
{
	public:
      Sphere(float taille, int nb_morceaux);
      ~Sphere();

	private:
      void drawImmediate(float taille, int nb_morceaux);
};

#endif

