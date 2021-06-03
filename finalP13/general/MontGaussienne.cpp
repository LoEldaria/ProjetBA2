#include "MontGaussienne.h"
#include <cmath>

MontGaussienne::MontGaussienne (double x, double y, double H,double es_x, double es_y,double lambda):
Montagne(lambda), centre({((std::size_t)(x/lambda)),((std::size_t)(y/lambda))}), hauteur((std::size_t)(H/lambda)), etalement_sigma({((std::size_t)(es_x/lambda)),((std::size_t)(es_y/lambda))}) {}
// nous donne i, j, h, es_i,  es_y à partir des données en m (car H(en m)=h(en cubes)*lambda)

MontGaussienne::MontGaussienne (std::array<std::size_t,3> sommet, std::size_t es_i, std::size_t es_j, double lambda):
Montagne(lambda), centre({sommet[0],sommet[1]}), hauteur(sommet[2]), etalement_sigma({es_i,es_j}) {}


std::unique_ptr<MontGaussienne> MontGaussienne::clone() const{
    return std::unique_ptr<MontGaussienne>(new MontGaussienne(*this));
}

std::unique_ptr<Montagne> MontGaussienne::copie() const{
    return clone();
}


double MontGaussienne ::altitude(std::size_t i, std::size_t j) const {
    double  x1 = std::max(i,centre[0]) - std::min(i,centre[0]),
            x2 = std::max(j,centre[1]) - std::min(j,centre[1]),
            s1 = etalement_sigma[0],
            s2 = etalement_sigma[1],
            po = - x1*x1/(2*s1*s1) - x2*x2/(2*s2*s2),
            al = hauteur*std::exp(po);
    return al<0.5 ? 0 : al;
}


void MontGaussienne::affiche(std::ostream& flot) const {
    flot<<"une montagne : "<<std::endl<<"gaussienne de paramètres "<<std::endl;
    flot<<"i0 = "<<centre[0]<<"(x0 = "<< lambda*centre[0]<<")"<<std::endl;
    flot<<"j0= "<<centre[1]<<"(y0 = "<< lambda*centre[1]<<")"<<std::endl;
    flot<<"h= "<<hauteur<<"(H= "<< lambda*hauteur<<")"<<std::endl;
    flot<<"Si0= "<<etalement_sigma[0]<<"(Sx0= "<< lambda*etalement_sigma[0]<<")"<<std::endl;
    flot<<"Sj0= "<<etalement_sigma[1]<<"(Sy0= "<< lambda*etalement_sigma[1]<<")"<<std::endl;
}

