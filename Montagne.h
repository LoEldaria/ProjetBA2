#ifndef MONTAGNE_H
#define MONTAGNE_H

#include<array>
#include "Dessinable.h"
#include "Vecteur.h"

class Montagne : public Dessinable
{
private:

std::array<unsigned int,2> centre;
unsigned int hauteur;
std::array<unsigned int,2> etalement_sigma;
public:
Montagne (double scale_factor, double x=0, double y=0, double H=0,double es_x=1, double es_y=1);
Montagne (std::array<unsigned int,3> sommet, unsigned int es_i, unsigned int es_j);

double altitude(std::array<unsigned int,2> coord) const ;
std :: array<unsigned  int , 2 > get_centre () const ;
unsigned int get_hauteur () const;
std :: array <unsigned int , 2> get_sigma() const ;
virtual void dessine_sur(SupportADessin& support) override ;

};

#endif // MONTAGNE_H
