#include "Montagne.h"
#include <iostream>
#include <cmath>
// using namespace std;

Montagne::Montagne (double scale_factor, double x, double y, double H,double es_x, double es_y) : 
centre({((unsigned int)(x/scale_factor)),((unsigned int)(y/scale_factor))}), hauteur((unsigned int)(H/scale_factor)), etalement_sigma({((unsigned int)(es_x/scale_factor)),((unsigned int)(es_y/scale_factor))}) {}
// nous donne i, j, h, es_i,  es_y à partir des données en m (car H(en m)=h(en cubes)*scale_factor)

Montagne::Montagne (std::array<unsigned int,3> sommet, unsigned int es_i, unsigned int es_j):
centre({sommet[0],sommet[1]}), hauteur(sommet[2]), etalement_sigma({es_i,es_j}) {}

double Montagne ::altitude(std::array<unsigned int ,2> coord) const {
    double  x1 = std::max(coord[0],centre[0]) - std::min(coord[0],centre[0]),
            x2 = std::max(coord[1],centre[1]) - std::min(coord[1],centre[1]),
            s1 = etalement_sigma[0],
            s2 = etalement_sigma[1],
            po = - x1*x1/(2*s1*s1) - x2*x2/(2*s2*s2),
            al = hauteur*std::exp(po);
    return al<0.5 ? 0 : al;
}