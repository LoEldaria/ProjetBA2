#ifndef CIEL_H
#define CIEL_H

#include "CubedAir.h"
#include "ChampPotentiels.h"
#include "Dessinable.h"

class Ciel: public Collection3D<CubedAir>, public Dessinable{
public:
    Ciel(const ChampPotentiels&, Physique::Parametres*, bool=true);
    Ciel(std::size_t,std::size_t,std::size_t, double, double,Physique::Parametres*);

    void affiche_val(std::ostream&)const;
    void update(const ChampPotentiels&);
    void dessine_sur(SupportADessin& support) override ;

    void deplacer_nuages(double);
    double pluie_accumulee(std::size_t i, std::size_t j)const;
private:
//    Vecteur3D precedente(double delta_t, std::size_t i, std::size_t j, std::size_t k);
    bool etat_precedent(std::size_t i, std::size_t j, std::size_t k, double delta_t) const;
};

#endif // CIEL
