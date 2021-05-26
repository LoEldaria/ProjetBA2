
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

//    Massif.affiche(sortie);

//    CP.affiche_info(sortie);
//    sortie<<"valeurs: "<<endl;
////    CP.affiche(sortie, val1, val2, val3);
//    CP.affiche(sortie, vitesse_vent);
//    sortie<<endl<<endl;
//    sortie<<"Un ciel : "<<endl;
     sky.affiche_val(sortie);

    return sortie;
}

void Systeme ::dessine_sur(SupportADessin &support) {
    support.dessine(*this);// dans P10 SupportADessin est forcément un TextViewer
}

void Systeme::evolue(double dt) {
    deplacer_nuages(dt);
    sky.update(CP);
}

void Systeme::demarre() {
    CP.initialise(Massif);
    CP.resolution();
    sky.update(CP);
}

void Systeme::deplacer_nuages(double delta_t) {
    sky.deplacer_nuages(delta_t);
}


ostream& operator<< (ostream& sortie, Systeme const& D) {
   return D.affiche(sortie, potentiel, laplacien, vitesse_vent);
}
