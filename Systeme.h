//
// Created by siddharth on 04/04/2021.
//

#ifndef PROJET_SYSTEME_H
#define PROJET_SYSTEME_H

#include <iostream>
#include "Dessinable.h"
#include<memory>
#include "Ciel.h"

class Systeme : Dessinable {
private:
    ChampPotentiels CP;
    Ciel sky;
    Montagne Massif;


public:
Systeme (const ChampPotentiels c , Montagne M) ;

virtual  void dessine_sur(SupportADessin& support) override ;
void affiche (std :: ostream& sortie,a_afficher val1, a_afficher val2, a_afficher val3) const ;
void evolue (Vecteur3D& vitesse) ;
void demarre (Vecteur3D& vitesse);
};

std::ostream& operator<< (std::ostream& sortie, Systeme  const& D) ;


#endif //PROJET_SYSTEME_H
