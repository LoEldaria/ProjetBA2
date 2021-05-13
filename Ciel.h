#ifndef CIEL_H
#define CIEL_H

#include "CubedAir.h"
#include "ChampPotentiels.h"
#include "Dessinable.h"

class Ciel: public Collection3D<CubedAir>, public Dessinable{
public:
    Ciel(SupportADessin*, const ChampPotentiels&, Physique::Parametres*, bool=true);
    Ciel(SupportADessin*, unsigned int,unsigned int, unsigned int, double, double,Physique::Parametres*);
    void affiche_val(std::ostream&)const;
    void update(const ChampPotentiels&);
    CubedAir get_cube (Vecteur3D coord) const;
    void dessine_sur(SupportADessin& support) override ;
    Vecteur3D precedente (double pas, Vecteur3D coord) ;

};

#endif // CIEL