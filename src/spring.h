#ifndef _SPRING_H_
#define _SPRING_H_

#include <vector>
using namespace std;
#include <QGLViewer/vec.h>
using namespace qglviewer;  

#include "particle.h"


class Spring 
{
private:
	Particle *p1, *p2, *p3, *p4;

	double stiffness;
	double equilibriumLength;
	double damping;
	
public:
	/**
	 *  Build a new Spring.
	 *  @param[in] p1 the first particle of this spring
	 *  @param[in] p2 the second particle of this spring
	 *  @param[in] s spring stiffness
	 *  @param[in] l equilibrium length
	 *  @param[in] d damping factor 
	 */
	Spring(Particle *p1, Particle *p2, Particle *p3, Particle *p4,
	       double s, double l0, double d);
	
        /**
	 * Returns the force applied by this spring on particle 1 by
	 * particle 2, out of their current positions and velocities.
	 * The force applied on particle 2 is the opposite one.
	 */
	Vec getCurrentForce12() const;
	
	const Particle *getParticle1() const;
	const Particle *getParticle2() const;
	const Particle *getParticle3() const;
	const Particle *getParticle4() const;
	
	void draw() const;
};

#endif // _SPRING_H_

