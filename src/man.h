#ifndef _MAN_
#define _MAN_

#include "renderable.h"
#include <GL/glut.h>
#include <string>
using namespace std;

class Man : public Renderable
{
   public:
      static const string EVENT_APPLAUSE;
      static const string EVENT_WALK; 
      static string currentMove;
      void draw();
      void animate();
      static bool isAnimationEnded();

   private:
      // drawings
      void drawArm(GLfloat shoulder, GLfloat shoulder2, GLfloat elbow, GLfloat elbow2, GLfloat wrist, bool left);
      void drawLeg(GLfloat pelvis, GLfloat knee, bool left);
      void drawImmediate();
      void drawCylinder(float radius, float height);
      void drawCape();
      void solidCone(GLdouble base, GLdouble height, GLint slices, GLint stacks);
      void solidDisk(GLfloat base1, GLfloat base2, GLfloat thickness, GLint slices, GLint stacks);

      // animation 
      void applause();
      void walk();
      void capeWave();
      void solidDisk(GLfloat base, GLfloat thickness, GLint slices, GLint stacks);
};

#endif

