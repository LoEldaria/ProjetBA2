#include "Potentiel.h"
#include <cmath>

using namespace std;

Vecteur2D Potentiel:: get_Laplacien () const {return Laplacien;}
Vecteur2D Potentiel :: get_potentiel() const {return potentiel;}

void Potentiel :: access_potentiel (const Vecteur2D& u) {
	potentiel = u;
}
void Potentiel :: access_Laplacien (const Vecteur2D& u) {
	Laplacien = u;
}
