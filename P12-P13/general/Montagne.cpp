#include "Montagne.h"
#include <cmath>
// using namespace std;

Montagne::Montagne(double lambda):lambda(lambda){}

double Montagne::altitude(Vecteur2D const& coord) const{
    return lambda*altitude(std::round(coord[0]/lambda), std::round(coord[1]/lambda));
}


void Montagne ::dessine_sur(SupportADessin &support){
    support.dessine(*this);
}


void Montagne::affiche_altitude(std::ostream &flot, std::size_t base_i, std::size_t base_j) const {
    for (unsigned int i(0) ; i<base_i ; ++i) {
        for (unsigned int j(0); j < base_j ; ++j) {
           flot<<i<<" "<<j<<" "<<altitude(i,j)<<std::endl;
        }
        flot<<std::endl;
    }
}
