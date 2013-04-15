#ifndef _MAN_
#define _MAN_

#include "renderable.h"
#include <GL/glut.h>

class Man : public Renderable
{
   public:
      void draw();
      void animate();
      void applause();

   private:
      // drawings
      void drawArm(GLfloat shoulder, GLfloat elbow, GLfloat wrist, bool left);
      void drawFoot(GLfloat knee, bool left);
      void drawLeg(GLfloat knee, bool left);
      void drawImmediate();
      void drawCylinder(float radius, float height);
      void solidCone(GLdouble base, GLdouble height, GLint slices, GLint stacks);
      void solidDisk(GLfloat base1, GLfloat base2, GLfloat thickness, GLint slices, GLint stacks);

      // animation 
      void walk();
      void solidDisk(GLfloat base, GLfloat thickness, GLint slices, GLint stacks);
};

#endif

