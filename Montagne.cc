#include "Montagne.h"
#include <iostream>
#include <cmath>


using namespace std;


Montagne :: Montagne (double x, double y, double h,double es_x, double es_y) : coordonnees({x,y}), hauteur(h), etalement_sigma({es_x,es_y}) {}

double Montagne ::altitude(std::array<double,2> coord) const {
		double alt(hauteur*exp(-(pow((coord[0]-coordonnees[0]),2)/(2*pow(etalement_sigma[0],2)))-(pow((coord[1]-coordonnees[1]),2)/(2*pow(etalement_sigma[1],2)))));
		if(alt<0.5){
			return 0;
		}
		return alt;
	}



 
