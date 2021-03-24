#ifndef POTENTIEL_H
#define POTENTIEL_H

#include <iostream>
#include <array>
#include "Vecteur2D.h"


class Potentiel {
	private :
	Vecteur2D potentiel;
	Vecteur2D Laplacien;
	public :
	Potentiel (double x=0, double y=0) : potentiel (x,y) , Laplacien(0,0) {}
	Vecteur2D get_Laplacien() const ;
	Vecteur2D get_potentiel() const ;
	void access_Laplacien (Vecteur2D u);
	void access_potentiel (Vecteur2D u);
};

#endif // POTENTIEL_H
