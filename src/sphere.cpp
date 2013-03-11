#include <iostream>
#include <math.h>
using namespace std;
#include "sphere.h"

/*
   sphere's drawing
   */

// constructeur
Sphere::Sphere(float taille, int nb_morceaux) {
   drawImmediate(taille, nb_morceaux);
}

//destructor
Sphere::~Sphere() {
}

void Sphere::draw() {
}
void Sphere::drawImmediate(float taille, int nb_morceaux)
{
   glutSolidSphere(taille,nb_morceaux,nb_morceaux);
}
