#ifndef _DYNAMIC_SYSTEM_H_
#define _DYNAMIC_SYSTEM_H_

#include <QGLViewer/vec.h>
#include <QGLViewer/manipulatedFrame.h>
using namespace qglviewer;

#include <GL/glut.h>
#include <vector>
using namespace std;

#include "spring.h"
#include "particle.h"
#include "renderable.h"

/*
 * This class represents a dynamic system made of particles
 * linked together with damped springs, within a medium with
 * gravity and viscosity.
 * Particles a represented by small spheres, with a radius and a mass.
 * The initial scene is composed of a fixed plane, a static particle
 * that can be controlled by the mouse, and a dynamic particle.
 */
class DynamicSystem : public Renderable
{

   private:
      // system
      vector<Particle *> particles;
      vector<Spring *> springs;
      int partNumber;

      // System parameters (common)
      Vec defaultGravity;
      Vec gravity;			// gravity used in simulation
      double defaultMediumViscosity;
      double mediumViscosity;		// viscosity used in simulation
      double dt;			// time step
      bool handleCollisions;

      // Collisions parameters
      Vec groundPosition;
      Vec groundNormal;
      double rebound;	// 0 = pure absorption; 1 = pure elastic impact

      // Parameters shared by all particles
      double particleMass;
      double particleRadius;
      double distanceBetweenParticles;

      // Parameters shared by all springs
      double springStiffness;
      double springInitLength;
      double springDamping;


   public:
      DynamicSystem();	
      virtual ~DynamicSystem();

      // Position of the firt particle ca be set through mouse movements
      const Vec &getFixedParticlePosition() const;
      void setFixedParticlePosition(const Vec &pos);

      // Activate/desactivate gravity during the simulation
      void setGravity(bool onOff);
      // Activate/desactivate viscosity during the simulation
      void setViscosity(bool onOff);
      // Activate/desactivate contacts during the simulation
      void setCollisionsDetection(bool onOff);

   private:
      // Reset the scene (remove all particles and springs)
      void clear();

      // Compute collision between a sphere and the fixed) ground
      void collisionParticleGround(Particle *p);

      void collisionParticleBack(Particle *p);

      void createSystemScene();
      void createTestCollisions();

      void animWind();

      // Renderable methods
   public:
      // Init the particle-spring system
      void init();

      // Draw the particle-spring system
      void draw();

      // Update positions and velocities of dynamic objects
      void animate();

};

#endif
