//
// Created by siddharth on 04/04/2021.
//
#include <iostream>
#include "Systeme.h"
#include "Montagne.h"
#include "ChampPotentiels.h"

using namespace std;

Systeme::Systeme(SupportADessin* support, double v, double t, double p, unsigned int i, unsigned int j, unsigned int k, double l):
Dessinable(support), param(v,t,p),  CP(&param,i,j,k,l) , sky(support, CP, &param, false) {}


void Systeme::ajoute_montagne(Montagne const& M){
    Massif.push_back(M.copie());
}

ostream& Systeme :: affiche (std::ostream& sortie, a_afficher val1, a_afficher val2, a_afficher val3) const {
    for(auto const& mont:Massif) mont->affiche(sortie);

    CP.affiche_info(sortie);
    sortie<<"valeurs: "<<endl;
    CP.affiche(sortie, val1, val2, val3);

    sortie<<endl<<endl;
    sortie<<"Un ciel : "<<endl;
    sky.affiche_val(sortie);

    return sortie;
}

void Systeme ::dessine_sur(SupportADessin &support) {
    support.dessine(*this);// dans P10 SupportADessin est forcément un TextViewer
}

void Systeme::evolue() {
    // sky.update(CP);
    // dessine_sur(*blank_paper);
}

void Systeme::demarre() {
    if(!Massif.empty()){
        CP.initialise(*Massif[0]); //provisoire, une seule montagne dans P10
    }
    CP.resolution();
    sky.update(CP);
    dessine_sur(*blank_paper); //dans P10 on a initialisé blank_paper à &ecran=pointeur statique sur ecran(qui est un TextViewer et donc un Support à dessin); ici on va chercher le contenu=l'adresse pointée (cout pour P10)
    evolue();
}

ostream& operator<< (ostream& sortie, Systeme const& D) {
   return D.affiche(sortie, potentiel, laplacien, vitesse_vent);
}
