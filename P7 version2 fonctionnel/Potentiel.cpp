#include "Potentiel.h"
#include "Vecteur2D.h"
#include <cmath>

using namespace std;

Vecteur2D Potentiel:: get_Laplacien () const {return Laplacien;}
Vecteur2D Potentiel :: get_potentiel() const {return potentiel;}

void Potentiel :: access_potentiel (const Vecteur2D& u) {
	potentiel.set_coord(0, u.get_vecteur()[0]);
	potentiel.set_coord(1, u.get_vecteur()[1]);
}
void Potentiel :: access_Laplacien (const Vecteur2D& u) {
	Laplacien.set_coord(0, u.get_vecteur()[0]);
	Laplacien.set_coord(1, u.get_vecteur()[1]);
}