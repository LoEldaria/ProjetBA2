#include "ChaineDeMontagnes.h"


ChaineDeMontagnes::ChaineDeMontagnes(double lambda): Montagne(lambda) {}

ChaineDeMontagnes::ChaineDeMontagnes(const ChaineDeMontagnes &autre): Montagne(autre.lambda){
    for(auto const& mont:autre.chaine)
        chaine.push_back(mont->copie());
}

double ChaineDeMontagnes::altitude(std::size_t i, std::size_t j) const {
    double max (0), a;
    for (unsigned int k(0) ; k<chaine.size() ; ++k) {
        if((a=chaine[k]->altitude(i,j))>max){
         max=a;
        }
    }
    return max;
}

void ChaineDeMontagnes::affiche(std::ostream &flot) const
{
    flot<<"Chaine de Montagnes contenant:";
    for(auto const& mont:chaine){
        flot<<std::endl;
        mont->affiche(flot);
    }
}



std::unique_ptr<ChaineDeMontagnes> ChaineDeMontagnes::clone() const{
    return std::unique_ptr<ChaineDeMontagnes>(new ChaineDeMontagnes(*this));
}

std::unique_ptr<Montagne> ChaineDeMontagnes::copie() const {
    return clone();
}

