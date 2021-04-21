//
// Created by siddharth on 04/04/2021.
//

#ifndef PROJET_SYSTEME_H
#define PROJET_SYSTEME_H

#include "Dessinable.h"
#include "Ciel.h"
#include <iostream>
#include <memory>


class Systeme : public Dessinable {
private:
    Physique::Parametres param; 
    ChampPotentiels CP;
    Ciel sky;
    std::vector<std::unique_ptr<Montagne>> Massif;

public:
    Systeme (SupportADessin*, double, double, double,unsigned int, unsigned int, unsigned int, double=1);

    void ajoute_montagne(Montagne const&);
    virtual  void dessine_sur(SupportADessin&) override ;
    std::ostream& affiche (std :: ostream&,a_afficher=null, a_afficher=null, a_afficher=null) const ;

    void evolue () ;
    void demarre ();
};

std::ostream& operator<< (std::ostream&, Systeme  const&) ;


#endif //PROJET_SYSTEME_H
