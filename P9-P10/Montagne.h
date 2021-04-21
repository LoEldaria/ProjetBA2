#ifndef MONTAGNE_H
#define MONTAGNE_H

#include<array>
#include "Dessinable.h"
#include "Vecteur.h"
#include <memory>

class Montagne : public Dessinable
{
protected:
    double lambda;
    Montagne(SupportADessin*, double=1);

public:
    virtual double altitude(std::array<unsigned int,2> coord, bool cartesien=false) const =0;
    virtual void affiche(std::ostream& flot) const =0;
    virtual std::unique_ptr<Montagne> copie() const =0;
    virtual ~Montagne(){}

};

class MontGaussienne: public Montagne{
private:
    std::array<unsigned int,2> centre;
    unsigned int hauteur;
    std::array<unsigned int,2> etalement_sigma;
    std::unique_ptr<MontGaussienne> clone() const;

public:
    MontGaussienne (SupportADessin* paper, double x=0, double y=0, double H=0,double es_x=1, double es_y=1, double scale_factor=1);
    MontGaussienne (SupportADessin* paper, std::array<unsigned int,3> sommet, unsigned int es_i, unsigned int es_j,double scale_factor=1);

    virtual std::unique_ptr<Montagne> copie() const override;
    virtual void dessine_sur(SupportADessin& support) override ;
    virtual double altitude(std::array<unsigned int,2> coord, bool cartesien=false) const override;
    virtual void affiche(std::ostream& flot) const override;

};

#endif // MONTAGNE_H
