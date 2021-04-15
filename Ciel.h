#ifndef CIEL_H
#define CIEL_H

#include "CubedAir.h"
#include "ChampPotentiels.h"
#include "Dessinable.h"

class Ciel: public Collection3D<CubedAir>, public Dessinable{
public:
    Ciel(const ChampPotentiels&, Physique::Parametres* param);
    Ciel(unsigned int,unsigned int, unsigned int, double, double,Physique::Parametres*);
    void affiche_val(std::ostream&)const;
    void update(const ChampPotentiels&);
    void dessine_sur(SupportADessin& support) override ;

};

#endif // CIEL