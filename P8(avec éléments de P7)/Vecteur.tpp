#pragma once

#include "Vecteur.h" // pas nécessaire, fonctionne très bien sans (pourquoi?)
#include <cmath>

//======================== Méthodes Vecteur ============================
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
    if(vecteur.empty() or autre.vecteur.empty()){
        return false;
    }else{
        for(std::size_t i(0); i<N; ++i){
            if(std::abs(vecteur[i] - autre.vecteur[i])> 1e-20){
                return false;
            }
        }
        return true;
    }
}

template<std::size_t N>
bool Vecteur<N>::operator!=(const Vecteur<N>& autre)const{
    return not (Vecteur<N>(*this)==autre);
}

template<std::size_t N> 
Vecteur<N>& Vecteur<N>::operator+=(const Vecteur<N>& autre){
    for(std::size_t i(0); i<N; ++i){
        vecteur[i] += autre.vecteur[i];
    }
    return *this;
}

template<std::size_t N> 
Vecteur<N>& Vecteur<N>::operator-=(const Vecteur<N>& autre){
    return *this += (-autre);
}

template<std::size_t N> 
Vecteur<N>& Vecteur<N>::operator*=(const double valeur){
    for(auto& c : vecteur){
        c *= valeur;
    }
    return *this;
}

template<std::size_t N> 
Vecteur<N>& Vecteur<N>::operator/=(const double valeur){
    if(std::abs(valeur) > 1e-10){
        for(auto& c : vecteur){
            c /= valeur;
        }
    }
    return *this;
}

template<std::size_t N> 
double Vecteur<N>::operator*(const Vecteur<N>& autre) const{
    double retour(0.0);
    for(std::size_t i(0); i<N; ++i){
        retour += vecteur[i]*autre.vecteur[i];
    }
    return retour;
}

//	On implémente l'opérateur d'accès [] pour les rvalue, c'est-à-dire on autorise 
//	l'accès x = vect[i]; (rvalue) mais pas la modification vect[i] = x; (lvalue)
template<std::size_t N> 
double Vecteur<N>::operator[](std::size_t position) const{
	return vecteur[position];
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

//implémentation du produit vectoriel pour la spécialisation
/*
const Vecteur3D Vecteur3D::operator^(const Vecteur3D& autre) const{
	Vecteur3D retour;
    for(std::size_t i(0); i<3; ++i)
        retour.vecteur[i]=(vecteur[(i+1)%3]*autre.vecteur[(i+2)%3]-vecteur[(i+2)%3]*autre.vecteur[(i+1)%3]);
    return retour;
}
*/