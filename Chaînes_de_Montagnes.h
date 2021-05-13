//
// Created by siddharth on 23/04/2021.
//

#ifndef PROJET_CHAINES_DE_MONTAGNES_H
#define PROJET_CHAINES_DE_MONTAGNES_H
#include "Montagne.h"
#include "Dessinable.h"
#include <vector>

class Chaines_de_Montagnes : public Montagne, public Dessinable {
private :
    std::vector<Montagne*> chaine ;

public:
    Chaines_de_Montagnes(std::vector<Montagne*> A) : chaine(A) {}
    virtual double altitude (std::array<unsigned int,2> coord, bool cartesien=false) const override ;
    virtual void affiche (std::ostream& flot) const override ;
    virtual std::unique_ptr<Montagne> copie() const override;
    virtual void dessine_sur(SupportADessin& support) override ;
};


#endif //PROJET_CHAINES_DE_MONTAGNES_H
