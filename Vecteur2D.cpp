#include "Vecteur2D.h"
#include <cmath>
using namespace std;


//======================= Méthodes Vecteur2D =========================
std::array<double,2> Vecteur2D::get_vecteur()const{return vecteur;}

void Vecteur2D::set_coord(bool position, double new_coord){
    vecteur[position]=new_coord;
}

double Vecteur2D::norme2() const {
     return vecteur*vecteur;
}
double Vecteur2D::norme () const{
    return (sqrt(norme2()));
}

ostream& Vecteur2D::affiche(ostream& sortie)const{
    sortie<<vecteur[0]<<' '<<vecteur[1]<<endl;
    return sortie;
}


//=================== Opérateurs internes Vecteur2D ==================

bool Vecteur2D::operator==(const Vecteur2D& autre)const{
    if(vecteur.empty() or autre.vecteur.empty()){
        return false;
    }else{
        for(size_t i(0); i<vecteur.size(); ++i){
            if(abs(vecteur[i] - autre.vecteur[i])> 0.0000000001){
                return false;
            }
        }
        return true;
    }
}

bool Vecteur2D::operator!=(const Vecteur2D autre)const{
    return not (Vecteur2D(*this)==autre);
}

Vecteur2D& Vecteur2D::operator+=(const Vecteur2D& autre){
    for(size_t i(0); i<autre.vecteur.size(); ++i){
        vecteur[i]+=autre.vecteur[i];
    }
    return *this;
}

Vecteur2D& Vecteur2D::operator-=(const Vecteur2D& autre){
    return *this+=(-autre);
}

Vecteur2D& Vecteur2D::operator*=(const double valeur){
    for(auto& c : vecteur){
        c*=valeur;
    }
    return *this;
}

double Vecteur2D::operator*(Vecteur2D const& autre) const{
    Vecteur2D v(*this);
    double retour(0.0);
    for(size_t i(0); i<v.vecteur.size(); ++i){
        retour+=v.vecteur[i]*autre.vecteur[i];
    }
    return retour;
}



//=================== Opérateurs externes Vecteur2D ======================
ostream& operator<<(std::ostream& sortie, Vecteur2D const& vecteur){
    return vecteur.affiche(sortie);
}

const Vecteur2D operator+(Vecteur2D const& vecteur, Vecteur2D const& autre){
    return Vecteur2D(vecteur)+=autre;
}
const Vecteur2D operator-(Vecteur2D const& vecteur){
    return Vecteur2D((-1)*vecteur);
}
const Vecteur2D operator-(Vecteur2D const& vecteur, Vecteur2D const& autre){
    return Vecteur(vecteur)-=autre;
}
const Vecteur2D operator*(const double valeur, Vecteur2D const& vecteur){
    return Vecteur(vecteur)*=valeur;
}
const Vecteur2D operator*(Vecteur2D const& vecteur, const double valeur){
    return Vecteur(vecteur)*=valeur;
}
const Vecteur2D operator~(Vecteur2D const& vecteur){
    return Vecteur(vecteur)*=(1/vecteur.norme());
}


