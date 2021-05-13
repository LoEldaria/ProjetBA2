//
// Created by siddharth on 23/04/2021.
//

#include "Chaînes_de_Montagnes.h"
#include <array>
#include <iostream>

double Chaines_de_Montagnes::altitude(std::array<unsigned int,2> coord, bool cartesien) const {
    double max (0);
for (unsigned int i(0) ; i<chaine.size() ; ++i) {
 if(chaine[i]->altitude(coord,cartesien)>=max){
     max=chaine[i]->altitude(coord,cartesien);
 }
}
    return max;
}

void Chaines_de_Montagnes::affiche(std::ostream &flot) const {
    std::array<unsigned int, 2> coord;
    for (unsigned int i(0) ; i<30 ; ++i) {
        for (unsigned int j(0); j < 30 ; ++j) {
            coord[0]=i;
            coord[1]=j;
           flot<<i<<" "<<j<<" "<<altitude(coord)<<std::endl;
        }
        flot<<std::endl;
    }
}

std::unique_ptr<Montagne> Chaines_de_Montagnes::copie() const {
    return std::unique_ptr<Montagne>();
}

void Chaines_de_Montagnes::dessine_sur(SupportADessin &support) {

}


