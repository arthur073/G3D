#include <cmath>
#include <iostream>
#include <map>
using namespace std;

#include "dynamicSystem.h"
#include "man.h"

Vec backNormal = Vec(0.0, -1.0, 0.0);
Vec backPosition = Vec(0.0, -0.5, 1.0);
GLfloat backTop = 2.5;
GLfloat backBottom = 2;
GLint chainNumber = 15;



DynamicSystem::DynamicSystem()
   : 
      defaultGravity(0.0, 0.0, -0.5),
      defaultMediumViscosity(1.0),
      dt(0.1),
      groundPosition(0.0, 0.0, -1.35),
      groundNormal(0.0, 0.0, 1.0),
      rebound(0.5)
{
   // default values reset in init()
}

DynamicSystem::~DynamicSystem()
{
   clear();
}


void DynamicSystem::clear()
{
   vector<Particle *>::iterator itP;
   for (itP = particles.begin(); itP != particles.end(); ++itP) {
      delete(*itP);
   }
   particles.clear();

   vector<Spring *>::iterator itS;
   for (itS = springs.begin(); itS != springs.end(); ++itS) {
      delete(*itS);
   }
   springs.clear();
}

const Vec &DynamicSystem::getFixedParticlePosition() const
{
   return particles[0]->getPosition();	// no check on 0!
}

void DynamicSystem::setFixedParticlePosition(const Vec &pos)
{
   if (particles.size() > 0)
      particles[0]->setPosition(pos);
}

void DynamicSystem::setGravity(bool onOff)
{
   gravity = (onOff ? defaultGravity : Vec());
}

void DynamicSystem::setViscosity(bool onOff)
{
   mediumViscosity = (onOff ? defaultMediumViscosity : 0.0);
}

void DynamicSystem::setCollisionsDetection(bool onOff)
{
   handleCollisions = onOff;
}


///////////////////////////////////////////////////////////////////////////////
void DynamicSystem::init()
{
   clear();

   // global scene parameters 
   defaultGravity = Vec(0.0, 0.0, -1.0);
   gravity = defaultGravity;
   defaultMediumViscosity = 1.0;
   mediumViscosity = defaultMediumViscosity;
   handleCollisions = true;
   dt = 0.1;
   groundPosition = Vec(0.0, 0.0, -1.35);
   groundNormal = Vec(0.0, 0.0, 1.0);
   rebound = 0.1;	
   partNumber = 6;
   // parameters shared by all particles
   particleMass = 1;
   particleRadius = 0.1;
   distanceBetweenParticles = 0.01 ;
   // parameters shared by all springs
   springStiffness = 2;
   springInitLength = 0;
   springDamping = 1;

   createSystemScene();
}


///////////////////////////////////////////////////////////////////////////////
void DynamicSystem::createSystemScene()
{ 
   // on crée les particules ligne par ligne
   Vec vel1 = Vec(0.0, -0.1, 0.0);	// non null initial velocity
   const float DEG2RAD = 3.14159/180;
   const float radius = 0.6;

   for (int i =0; i < chainNumber; i++) {
      // la particule fixe
      float degInRad = (i*10-160)*DEG2RAD;
      
      Vec initPos = Vec(cos(degInRad)*radius , sin(degInRad)*radius, 0.9);
      Vec pos = initPos;
      particles.push_back(new Particle(pos, Vec(), 0.0, particleRadius, true));
      
      // le reste de la chaîne
      for (int j = 1; j < partNumber; j++) {
         pos += Vec(0.0, distanceBetweenParticles, 0.0);
         particles.push_back(new Particle(pos, vel1, particleMass, 0, false));
      }
   }

   // maintenant on crée les springs
   for (int i =0; i < chainNumber-1; i++) {
      for (int j = i*partNumber; j < partNumber-1 + i*partNumber; j++) {
         int x = j;
         int y = j + 1;
         int z = j + partNumber;
         int t = j + partNumber + 1;
         Spring *s = new Spring(particles[x], particles[y], particles[z], particles[t],
               springStiffness, springInitLength, springDamping);
         springs.push_back(s);
      }
   }

}


///////////////////////////////////////////////////////////////////////////////
void DynamicSystem::draw()
{
   // Particles
   glPushMatrix();
   glColor3f(1,1,1);
   vector<Particle *>::iterator itP;
   for (itP = particles.begin(); itP != particles.end(); ++itP) {
      (*itP)->draw();
   }

   // Springs
   glLineWidth(500);
   vector<Spring *>::iterator itS;
   for (itS = springs.begin(); itS != springs.end(); ++itS) {
      (*itS)->draw();
   }
}

Vec updatePos(int i) 
{
   float belly = Man::getBelly();
   const float DEG2RAD = 3.14159/180;
   const float bodyRadius = 0.6;
   float degInRad = (i*10- 160)*DEG2RAD;
   float Z ;

   //cout<<" i2 "<<i<<"  deg "<<degInRad<<"\n";

   float pi = 3.141592;
   float bellyRad = pi * Man::getBelly() / 180;
   float R = 0.9;
   float beta = (180 - belly) /2;

   //float Y = cos(bellyRad+pi/2) * R ;//+ sin(degInRad)*bodyRadius;
   float X = cos(degInRad)*bodyRadius;
   float Y = sin(degInRad)*bodyRadius + cos(bellyRad+pi/2) * R;
   Z = sin(bellyRad+pi/2) * R + belly*abs(7-i)/1000 - 0.01*belly;

   return Vec(X, Y, Z);
}


///////////////////////////////////////////////////////////////////////////////
void DynamicSystem::animate()
{
   //======== 0. Update top particles position

   vector<Particle *>::iterator itPa;
   int i =0;
   for (itPa = particles.begin(); itPa != particles.end(); ++itPa) {
      Particle *p = *itPa;
      if (p->getTop()) {
         p->setPosition(updatePos(i));
         i++;
      }
   }


   //======== 1. Compute all forces
   // map to accumulate the forces to apply on each particle
   map<const Particle *, Vec> forces;

   // weights
   vector<Particle *>::iterator itP;
   for (itP = particles.begin(); itP != particles.end(); ++itP) {
      Particle *p = *itP;
      forces[p] = gravity * p->getMass();
   }

   // damped springs
   GLfloat lastRowPos = springs.size() - partNumber + 1;
   vector<Spring *>::iterator itS;
   for (itS = springs.begin(); itS != springs.end(); ++itS) {
      Spring *s = *itS;
      if (s == springs[lastRowPos]) {
         // on sort de la boucle
         break;
      }
      Vec f12 = s->getCurrentForce12();
      forces[s->getParticle1()] += f12;
      forces[s->getParticle2()] -= f12; // opposite force
   }
   

  for (; itS != springs.end(); ++itS) {
      // les springs de la dernière ligne
      Spring *s = *itS;
      Vec f12 = s->getCurrentForce12();

      forces[s->getParticle3()] += f12;
      forces[s->getParticle4()] -= f12; // opposite force
      forces[s->getParticle1()] += f12;
      forces[s->getParticle2()] -= f12; // opposite force
   }




   //======== 2. Integration scheme
   // update particles velocity (qu. 1)
   for (itP = particles.begin(); itP != particles.end(); ++itP) {
      Particle *p = *itP;
      const Vec SumForces = forces[p];
      // a = 1/m * SumForces
      const Vec a = p->getInvMass() * SumForces;
      // v = v + dt * a
      p->incrVelocity(dt * a);
   }


   // update particles positions
   for (itP = particles.begin(); itP != particles.end(); ++itP) {
      Particle *p = *itP;
      // q = q + dt * v
      p->incrPosition(dt * p->getVelocity());
   }


   //======== 3. Collisions
   if (handleCollisions) {
      for (itP = particles.begin(); itP != particles.end(); ++itP) {
         collisionParticleGround(*itP);
         //collisionParticleBack(*itP);
      }	
   }
}



void DynamicSystem::collisionParticleGround(Particle *p)
{
   // don't process fixed particles (ground plane is fixed)
   if (p->getInvMass() == 0)
      return;

   // particle-plane distance
   double penetration = (p->getPosition() - groundPosition) * groundNormal;
   penetration -= p->getRadius();
   if (penetration >= 0)
      return;

   // penetration velocity
   double vPen = p->getVelocity() * groundNormal;

   // updates position and velocity of the particle
   p->incrPosition(-(1 + rebound) * penetration * groundNormal);
   p->incrVelocity(-(1 + rebound) * vPen * groundNormal);
}


void DynamicSystem::collisionParticleBack(Particle *p)
{
     // don't process fixed particles (ground plane is fixed)
   if (p->getInvMass() == 0)
      return;

   // particle-plane distance
   double penetration = (p->getPosition() - backPosition) * backNormal;
   penetration -= p->getRadius();
   if (penetration >= 0)
      return;

   if (p->getPosition()[2] > backTop+1 || p->getPosition()[2] < backBottom-1) 
      return;


   // penetration velocity
   double vPen = p->getVelocity() * backNormal;

   // updates position and velocity of the particle
   p->incrPosition(-(1 + rebound) * penetration * backNormal);
   p->incrVelocity(-(1 + rebound) * vPen * backNormal);
}

