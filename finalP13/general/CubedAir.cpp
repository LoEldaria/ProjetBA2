#include "CubedAir.h"
#include <cmath>

using namespace std;

ostream& CubedAir::affiche(std::ostream& flot)const{
    flot  << ' ' << vit.norme2() << ' ' << h << ' ' << temperature  << ' ' << pression << ' ' << p_eau << ' ' << p_rosee  << ' ' << nuage();
    return flot;
}

void CubedAir::actualise_valeurs(const Vecteur3D& vitesse){
    vit         = vitesse;
    h           = param->cte_Bernoulli -  Physique::g*z - 0.5*vitesse.norme2();
    temperature = (2.0/7.0)*(Physique::mmolaire_airsec/Physique::R)*h;
    pression    = param->p_inf*pow((temperature/(param->temp_inf)), 3.5);
    p_eau       = taux_humidite*pression/(taux_humidite + (Physique::mmolaire_eau/Physique::mmolaire_airsec));
    p_rosee     = Physique::Pref*exp(13.96-5208/temperature);
}

std::ostream& operator<<(std::ostream& flot, const CubedAir& cube){
    return cube.affiche(flot);
}


Vecteur3D CubedAir::get_vit() const {
    return vit;
}


void CubedAir::actualise_humidite(double delta_h) {
    taux_humidite*=1+delta_h;
}



double CubedAir::pluie()const{
    if (p_eau<=1.04*p_rosee) return 0.0;
    return abs(p_eau-p_rosee);  //croissance linéaire de la quantité de pluie selon cet écart
}




