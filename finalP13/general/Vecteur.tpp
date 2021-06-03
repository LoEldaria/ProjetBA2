#pragma once

#include <cmath>
//#include "Vecteur.h" // pas nécessaire , fonctionne très bien sans (pourquoi?)

template<typename T, std::size_t N>
const ArrayDbl<N> toDouble(const std::array<T,N> vect){
    ArrayDbl<N> v;
    for(std::size_t i(0); i<vect.size(); ++i){
        // convertit un potentiel type "integer" (p.ex. std::size_t) en
        // un type "floating-point", convertissable ensuite en double :
        v[i] = 1.0 * vect[i];
    }
    return v;
}

//====================== Constructeurs Vecteur =====================

template<std::size_t N>
Vecteur<N>::Vecteur(ArrayDbl<N> const& vect): vecteur(vect){}

//	Constructeur nécessaire pour les types qui ne peuvent être convertis
//	implicitement en double, tels que les "unsigned" (p.ex: std::size_t)
template<std::size_t N>
template<typename T, enable_if_t<std::is_integral<T>::value, int>>
Vecteur<N>::Vecteur(const std::array<T,N>& vect): vecteur(toDouble(vect)){}

//	Constructeur spécifique pour le cas à 2 dimensions N=2:
template<std::size_t N>
template<std::size_t M, enable_if_t<M == 2, int>>
Vecteur<N>::Vecteur(double x, double y) : vecteur({x,y}) {}

//	Constructeur spécifique pour le cas à 3 dimensions N=3:
template<std::size_t N>
template<std::size_t M, enable_if_t<M == 3, int>>
Vecteur<N>::Vecteur(double x, double y, double z) : vecteur({x,y,z}) {}

//======================= Méthodes Vecteur =========================

template<std::size_t N>
void Vecteur<N>::set_coord(std::size_t position, double new_coord){
    vecteur[position]=new_coord;
}

template<std::size_t N>
double Vecteur<N>::get_coord(std::size_t position)const{
    return vecteur[position];
}

template<std::size_t N>
ArrayDbl<N> Vecteur<N>::get_array()const{
    return vecteur;
}

template<std::size_t N>
double Vecteur<N>::norme2() const{
     return (*this)*(*this);
}

template<std::size_t N>
double Vecteur<N>::norme() const{
    return std::sqrt(norme2());
}

template<std::size_t N>
std::ostream& Vecteur<N>::affiche(std::ostream& sortie)const{
    for(auto a:vecteur)
        sortie<<a<<' ';
    return sortie;
}


//=================== Opérateurs internes Vecteur ==================

template<std::size_t N>
bool Vecteur<N>::operator==(const Vecteur<N>& autre)const{
    if(vecteur.empty() or autre.vecteur.empty()) return false;
    else{
        for(std::size_t i(0); i<N; ++i) if(std::abs(vecteur[i] - autre.vecteur[i])> 1e-20) return false;
        return true;
    }
}

template<std::size_t N>
bool Vecteur<N>::operator!=(const Vecteur<N>& autre)const{
    return not (Vecteur<N>(*this)==autre);
}

template<std::size_t N>
Vecteur<N>& Vecteur<N>::operator+=(const Vecteur<N>& autre){
    for(std::size_t i(0); i<N; ++i)
        vecteur[i] += autre.vecteur[i];
    return *this;
}

template<std::size_t N>
Vecteur<N>& Vecteur<N>::operator-=(const Vecteur<N>& autre){
    return *this += (-autre);
}

template<std::size_t N>
Vecteur<N>& Vecteur<N>::operator*=(const double valeur){
    for(auto& c : vecteur)
        c *= valeur;
    return *this;
}

template<std::size_t N>
Vecteur<N>& Vecteur<N>::operator/=(const double valeur){
    if(std::abs(valeur) > 1e-10)
        for(auto& c : vecteur)
            c /= valeur;
    return *this;
}

template<std::size_t N>
double Vecteur<N>::operator*(const Vecteur<N>& autre) const{
    double retour(0.0);
    for(std::size_t i(0); i<N; ++i)
        retour += vecteur[i]*autre.vecteur[i];
    return retour;
}

//	On implémente l'opérateur d'accès [] pour les rvalue, c'est-à-dire on autorise
//	l'accès x = vect[i]; (rvalue) mais pas la modification vect[i] = x; (lvalue) :
template<std::size_t N>
double Vecteur<N>::operator[](std::size_t position) const{
    return vecteur[position];
}

//	Opérateur "produit vectoriel" spécifique pour le cas à 3 dim. N=3:
template<std::size_t N>
template<std::size_t M, enable_if_t<(M == 3), int>>
const Vecteur<N> Vecteur<N>::operator^(const Vecteur<N>& autre)const{
    Vecteur<N> retour;
    for(std::size_t i(0); i<3; ++i)
        retour.vecteur[i]=(vecteur[(i+1)%3]*autre.vecteur[(i+2)%3]-vecteur[(i+2)%3]*autre.vecteur[(i+1)%3]);
    return retour;
}

//===================== Opérateurs externes Vecteur ====================

template<std::size_t N>
std::ostream& operator<<(std::ostream& sortie, Vecteur<N> const& vect){
    return vect.affiche(sortie);
}

template<std::size_t N>
const Vecteur<N> operator+(const Vecteur<N>& vect, const Vecteur<N>& autre){
    return Vecteur<N>(vect)+=autre;
}

template<std::size_t N>
const Vecteur<N> operator-(const Vecteur<N>& vect){
    return Vecteur<N>((-1)*vect);
}

template<std::size_t N>
const Vecteur<N> operator-(const Vecteur<N>& vect, const Vecteur<N>& autre){
    return Vecteur<N>(vect)-=autre;
}

template<std::size_t N>
const Vecteur<N> operator*(const double valeur,const Vecteur<N>& vect){
    return Vecteur<N>(vect)*=valeur;
}

template<std::size_t N>
const Vecteur<N> operator*(const Vecteur<N>& vect, const double valeur){
    return Vecteur<N>(vect)*=valeur;
}

template<std::size_t N>
const Vecteur<N> operator/(const Vecteur<N>& vect, const double valeur){
    return Vecteur<N>(vect)/=valeur;
}

template<std::size_t N>
const Vecteur<N> operator~(const Vecteur<N>& vect){
    return Vecteur<N>(vect)*=(1/vect.norme());
}
