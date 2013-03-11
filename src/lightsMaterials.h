#ifndef _LIGHTS_MATERIALS_
#define _LIGHTS_MATERIALS_

#include "renderable.h"
#include <GL/glut.h>

class LightsMaterials : public Renderable
{
	public:
		LightsMaterials();
		virtual void draw();
		virtual void init();

	private:
		// some basic colors...
		static GLfloat black[];
		static GLfloat white[];
		static GLfloat red[];
		static GLfloat blue[];
		static GLfloat green[];
		static GLfloat yellow[];
		static GLfloat magenta[];
		static GLfloat cyan[];

		// draw 12 spheres with different materials set with glMaterial*
		// Exemple adapted from the OpenGL Programming Guide (The Red Book)
		void exampleMaterial();
		
		// Another way to set up materials with glColorMaterial*
		void exampleColorMaterial();

		// Two spheres with blendind
		void exampleBlending();

    //modify position of the lights
    void setLightPosition();
};

#endif

