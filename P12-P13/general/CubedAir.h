#ifndef CUBEDAIR_H
#define CUBEDAIR_H

#include <array>
#include "Vecteur.h"
#include "Constantes.h"


class CubedAir{
public:
    CubedAir(Physique::Parametres* param=nullptr, Vecteur3D vit={}, double z=0, double taux=8e-3):
    param(param), vit(vit), taux_humidite(taux), z(z) {}

    bool nuage() const{return p_eau > p_rosee;}
    void actualise_valeurs(const Vecteur3D& vitesse);
    std::ostream& affiche(std::ostream& flot)const;

   //bool nuage(bool en_dehors_de_la_boite=false) const ;
   //bool pluie (bool en_dehors_de_la_boite=false) const;
    double pluie() const;
    void actualise_humidite (double delta_h) ;
    Vecteur3D get_vit () const ;

private:
    Physique::Parametres* param;

    Vecteur3D vit;
    double taux_humidite;
    double z;
    double temperature;
    double pression;
    double p_eau;
    double p_rosee;
    double h;

};

std::ostream& operator<<(std::ostream& flot, const CubedAir& cube);

#endif // CUBEDAIR
