#ifndef MONTAGNE_H
#define MONTAGNE_H

#include "Dessinable.h"
#include "Vecteur.h"
#include <memory>


class Montagne : public Dessinable
{
protected:
    double lambda;
    Montagne(double=1);

public:
    virtual double altitude(std::size_t i, std::size_t j) const =0;
    double altitude(Vecteur2D const& coord) const;
    virtual void affiche(std::ostream& flot) const =0;

    virtual std::unique_ptr<Montagne> copie() const =0;
    virtual void dessine_sur(SupportADessin& support) override;
    virtual ~Montagne(){}
    void affiche_altitude(std::ostream &flot, std::size_t base_i, std::size_t base_j) const;
};


#endif // MONTAGNE_H
