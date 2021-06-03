
#include <iostream>
#include "Systeme.h"
#include "Montagne.h"
#include "ChampPotentiels.h"

using namespace std;

Systeme::Systeme(double v, double t, double p, unsigned int i, unsigned int j, unsigned int k, double l):
    param(v,t,p),  CP(&param,i,j,k,l) , sky(CP, &param, false), Massif(l){}

const Ciel& Systeme::get_ciel()const
{
    return sky;
}

const Montagne &Systeme::get_mont() const
{
    return Massif;
}



void Systeme::ajoute_montagne(Montagne& M){
    Massif.ajoute_montagne(M);
}

ostream& Systeme :: affiche (std::ostream& sortie, a_afficher val1, a_afficher val2, a_afficher val3) const {

    Massif.affiche(sortie);

    CP.affiche_info(sortie);
    sortie<<"valeurs: "<<endl;
    CP.affiche(sortie, val1, val2, val3);
    sortie<<endl<<endl;

    // à décommenter si on veut voir toutes les valeurs des grandeurs de Ciel
//    sortie<<"Un ciel : "<<endl;
//    sky.affiche_val(sortie);

    return sortie;
}

void Systeme::affiche_pluie(ostream& flot)const{
    sky.affiche_pluie(flot);
}

void Systeme ::dessine_sur(SupportADessin &support) {
    support.dessine(*this);
}

void Systeme::evolue(double dt) {
    deplacer_nuages(dt);
    sky.update(CP);         //on actualise les valeurs puisque deplacer_nuages() change les taux d'humidité
}

void Systeme::demarre() {
    CP.initialise(Massif);
    CP.resolution();
    sky.update(CP);
}

void Systeme::deplacer_nuages(double delta_t) {
    sky.applique_fonction([this,delta_t](CubedAir& cba, std::size_t i, std::size_t j, std::size_t k){
        bool nuage_courant(cba.nuage()), nuage_precedent(sky.etat_precedent(i,j,k,delta_t));
        if(nuage_courant and !nuage_precedent) cba.actualise_humidite(-0.017);
        if(!nuage_courant and nuage_precedent) cba.actualise_humidite(0.05);
        if(cba.pluie()) cba.actualise_humidite(-0.03);
    },true);
}


ostream& operator<< (ostream& sortie, Systeme const& D) {
   return D.affiche(sortie, potentiel, laplacien, vitesse_vent);
}
