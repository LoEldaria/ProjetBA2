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
    bool etat_precedent(std::size_t i, std::size_t j, std::size_t k, double delta_t) const;


    double pluie_accumulee(std::size_t i, std::size_t j)const;

    void affiche_pluie(std::ostream &flot) const;

};

#endif // CIEL
