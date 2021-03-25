#ifndef MONTAGNE_H
#define MONTAGNE_H

#include<array>

class Montagne 
{
private:

std::array<double,2> coordonnees;
double hauteur;
std::array<double,2> etalement_sigma;

public:
Montagne (double x=0, double y=0, double h=0,double es_x=1, double es_y=1);
Montagne (std::array<double,3> centre, double es_x, double es_y, double scale_factor =1);

double altitude(std::array<double,2> coord) const ;


};

#endif // MONTAGNE_H
