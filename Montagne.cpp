#include "Montagne.h"
#include <cmath>
// using namespace std;

Montagne::Montagne(SupportADessin* support, double scale_factor): Dessinable(support), lambda(scale_factor){}

MontGaussienne::MontGaussienne (SupportADessin* support, double x, double y, double H,double es_x, double es_y,double scale_factor): 
Montagne(support, scale_factor), centre({((unsigned int)(x/lambda)),((unsigned int)(y/lambda))}), hauteur((unsigned int)(H/lambda)), etalement_sigma({((unsigned int)(es_x/lambda)),((unsigned int)(es_y/lambda))}) {}
// nous donne i, j, h, es_i,  es_y à partir des données en m (car H(en m)=h(en cubes)*scale_factor)

MontGaussienne::MontGaussienne (SupportADessin* support, std::array<unsigned int,3> sommet, unsigned int es_i, unsigned int es_j, double scale_factor):
Montagne(support, scale_factor), centre({sommet[0],sommet[1]}), hauteur(sommet[2]), etalement_sigma({es_i,es_j}) {}


std::unique_ptr<MontGaussienne> MontGaussienne::clone() const{
    return std::unique_ptr<MontGaussienne>(new MontGaussienne(*this));
}

std::unique_ptr<Montagne> MontGaussienne::copie() const{
    return clone();
}


double MontGaussienne ::altitude(std::array<unsigned int ,2> coord, bool cartesien) const {
    double  x1 = std::max(coord[0],centre[0]) - std::min(coord[0],centre[0]),
            x2 = std::max(coord[1],centre[1]) - std::min(coord[1],centre[1]),
            s1 = etalement_sigma[0],
            s2 = etalement_sigma[1],
            po = - x1*x1/(2*s1*s1) - x2*x2/(2*s2*s2),
            al = hauteur*std::exp(po);
    return al<0.5 ? 0 : (cartesien?lambda:1)*al; // si cartésien vrai, on mult par lambda
}

void MontGaussienne ::dessine_sur(SupportADessin &support){
    support.dessine(*this);
}


void MontGaussienne::affiche(std::ostream& flot) const {
        flot << "une montagne : " << std::endl << "gaussienne de paramètres " << std::endl;
        flot << "i0 = " << centre[0] << "(x0 = " << lambda * centre[0] << ")" << std::endl;
        flot << "j0= " << centre[1] << "(y0 = " << lambda * centre[1] << ")" << std::endl;
        flot << "h= " << hauteur << "(H= " << lambda * hauteur << ")" << std::endl;
        flot << "Si0= " << etalement_sigma[0] << "(Sx0= " << lambda * etalement_sigma[0] << ")" << std::endl;
        flot << "Sj0= " << etalement_sigma[1] << "(Sy0= " << lambda * etalement_sigma[1] << ")" << std::endl;
}

