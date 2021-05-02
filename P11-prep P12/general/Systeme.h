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
//    std::vector<std::unique_ptr<Montagne>> Massif;
    Chaine Massif;

public:
    Systeme (double, double, double,unsigned int, unsigned int, unsigned int, double=1);

    Vecteur3D get_coord(unsigned int i, unsigned int j,unsigned int k)const{return CP.coordonnees(i,j,k);}
    const Ciel& get_ciel()const;
    const Montagne& get_mont() const;

    void ajoute_montagne(Montagne&);
    virtual  void dessine_sur(SupportADessin&) override ;
    std::ostream& affiche (std :: ostream&,a_afficher=null, a_afficher=null, a_afficher=null) const ;

    void evolue (double) ;
    void demarre ();
};

std::ostream& operator<< (std::ostream&, Systeme  const&) ;


#endif //PROJET_SYSTEME_H
