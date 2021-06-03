#ifndef MONTGAUSSIENNE_H
#define MONTGAUSSIENNE_H

#include "Montagne.h"

class MontGaussienne: public Montagne{
private:
    std::array<std::size_t,2> centre;
    std::size_t hauteur;
    std::array<std::size_t,2> etalement_sigma;

    std::unique_ptr<MontGaussienne> clone() const;

public:
    MontGaussienne (double x=0, double y=0, double H=0,double es_x=1, double es_y=1, double lambda=1);
    MontGaussienne (std::array<std::size_t,3> sommet, std::size_t es_i, std::size_t es_j,double lambda=1);

    virtual std::unique_ptr<Montagne> copie() const override;
    virtual double altitude(std::size_t i, std::size_t j) const override;
    virtual void affiche(std::ostream& flot) const override;

};

#endif // MONTGAUSSIENNE_H
