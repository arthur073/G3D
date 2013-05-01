//#include <cmath>
#include <GL/glut.h>
#include "spring.h"


Spring::Spring(Particle *p1, Particle *p2, Particle *p3, Particle *p4,
	       double s, double l0, double d)
	: p1(p1), 
	p2(p2),
   p3(p3),
   p4(p4),
	stiffness(s),
	equilibriumLength(l0),
	damping(d) 
{
}


Vec Spring::getCurrentForce12() const
{
	// we compute the force applied on particle 1 by particle 2
	
	Vec u = p1->getPosition() - p2->getPosition();
	
	double uNorm = u.normalize();	// u is thereafter normalized!
	if (uNorm < 1.0e-6) 
		return Vec();	// null force
	
	// force due to stiffness only
	Vec sF = -stiffness * (uNorm - equilibriumLength) * u;
	// damping force
	Vec dF = -damping * ((p1->getVelocity() - p2->getVelocity()) * u) * u;

	return sF + dF/2;
}


const Particle *Spring::getParticle1() const
{
	return p1;
}

const Particle *Spring::getParticle2() const
{
	return p2;
}

const Particle *Spring::getParticle3() const
{
	return p3;
}

const Particle *Spring::getParticle4() const
{
	return p4;
}


void Spring::draw() const
{
	Vec pos1 = p1->getPosition();
	Vec pos2 = p2->getPosition();
	Vec pos3 = p3->getPosition();
	Vec pos4 = p4->getPosition();

   // calcul du normal
   Vec U = p2->getPosition() - p1->getPosition();
   Vec V = p4->getPosition() - p1->getPosition();

   GLfloat Nx = U[1]*V[2] - U[2]*V[1];
   GLfloat Ny = U[2]*V[0] - U[0]*V[2];
   GLfloat Nz = U[0]*V[1] - U[1]*V[0];

   Nx = Nx * 10 / (U.normalize() + V.normalize());
   Ny = Ny * 10 / (U.normalize() + V.normalize());
   Nz = Nz * 10 / (U.normalize() + V.normalize());
   
   glPushMatrix();
   glBegin(GL_POLYGON);
   glColor3ub(255,0,0);

   glNormal3f(Nx,Ny,Nz);
   glVertex3f(pos1.x, pos1.y, pos1.z);
   glVertex3f(pos2.x, pos2.y, pos2.z);
   glVertex3f(pos4.x, pos4.y, pos4.z);
   glVertex3f(pos3.x, pos3.y, pos3.z);
   glEnd();
  

   glPopMatrix();
}
