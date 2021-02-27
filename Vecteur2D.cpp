#include "Vecteur2D.h"
#include <iostream>
#include <cmath>
using namespace std;

std::array<double,2> Vecteur2D :: get_vecteur()const{return vecteur;}

void Vecteur2D :: set_coord(bool position, double new_coord){
    vecteur[position]=new_coord;
}

void Vecteur2D :: affiche()const{
    cout<<vecteur[0]<<" "<<vecteur[1];
}

bool Vecteur2D :: compare (Vecteur2D const& vec2)const{
    return (vecteur[0]==vec2.get_vecteur()[0] and vecteur[1]==vec2.get_vecteur()[1]);
}

const Vecteur2D Vecteur2D :: addition( Vecteur2D const& autre) const {
    Vecteur2D A;
    A.set_coord(0,autre.get_vecteur()[0]+vecteur[0]);
    A.set_coord(1,autre.get_vecteur()[1]+vecteur[1]);
    return A;
}

const Vecteur2D Vecteur2D :: soustraction ( Vecteur2D const& autre) const {
    Vecteur2D A;
    A.set_coord(0,vecteur[0]-autre.get_vecteur()[0]);
    A.set_coord(1,vecteur[1]-autre.get_vecteur()[1]);
    return A;
}

const Vecteur2D Vecteur2D :: oppose() const{
    Vecteur2D A;
    A.set_coord(0,-vecteur[0]);
    A.set_coord(1,-vecteur[1]);
    return A;
}


const Vecteur2D Vecteur2D :: mult(double x) const{
    Vecteur2D A;
    A.set_coord(0,x*vecteur[0]);
    A.set_coord(1,x*vecteur[1]);
    return A;
}

double Vecteur2D :: prod_scal(Vecteur2D const& autre) const{
    double scalaire_result;
    scalaire_result=autre.get_vecteur()[0]*vecteur[0]+autre.get_vecteur()[1]*vecteur[1];
    return scalaire_result;
}
double Vecteur2D :: norme2() const {
    double norme;
    norme=vecteur[0]*vecteur[0]+vecteur[1]*vecteur[1];
    return norme;
}
double Vecteur2D :: norme () const{
    double norme;
    norme=sqrt(norme2());
    return norme;
}

const Vecteur2D Vecteur2D :: unitaire () const {
    Vecteur2D A;
    A.set_coord(0,vecteur[0]/norme());
    A.set_coord(1,vecteur[1]/norme());
    return A;
}
