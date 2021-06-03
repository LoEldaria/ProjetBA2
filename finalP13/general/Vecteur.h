#pragma once

#include <array>
#include <iostream>
#include <type_traits>

//  On crée un typedef pour éviter à avoir à écrire std::array<double,N> partout
template<std::size_t N>
using ArrayDbl = std::array<double,N>;

//  Permet d'«activer» ou non des méthodes template en fonction d'une condition choisie,
//  par exemple pour spécialiser des constructeurs, des opérateurs,etc. Cette définition
//  ici est nécessaire si on compile en C++11, mais pas utile après car définie en C++14
template <bool B, typename T=void>
using enable_if_t = typename std::enable_if<B, T>::type;

template<std::size_t N>
class Vecteur{
private:
   ArrayDbl<N> vecteur;

public:
    //====================== Constructeurs Vecteur =====================
    Vecteur(ArrayDbl<N> const& vect = {});

    //  Constructeur nécessaire pour les types qui ne peuvent être convertis
    //  implicitement en double, tels que les "unsigned" (p.ex: std::size_t)
    template<typename T, enable_if_t<std::is_integral<T>::value, int> = 0>
    Vecteur(const std::array<T,N>& vect);

    //  Constructeur spécifique pour le cas à 2 dimensions N=2:
    template <std::size_t M = N, enable_if_t<M == 2, int> = 0>
    Vecteur(double x, double y=0);

    //  Constructeur spécifique pour le cas à 3 dimensions N=3:
    template <std::size_t M = N, enable_if_t<M == 3, int> = 0>
    Vecteur(double x, double y=0, double z=0);

    //======================= Méthodes Vecteur =========================
    void			set_coord(std::size_t position, double new_coord);
    double			get_coord(std::size_t)const;
    ArrayDbl<N> 	get_array()const;
    double 			norme() const;
    double 			norme2() const;
    std::ostream& 	affiche(std::ostream&)const;

    //=================== Opérateurs internes Vecteur ==================
    bool 			operator==(const Vecteur&)const;
    bool 			operator!=(const Vecteur&)const;
    Vecteur& 		operator+=(const Vecteur&);
    Vecteur& 		operator-=(const Vecteur&);
    Vecteur& 		operator*=(const double);
    Vecteur& 		operator/=(const double);
    double 			operator*(const Vecteur&)const;
    double			operator[](std::size_t)const;

    //  opérateur "produit vectoriel" spécifique pour le cas à 3 dim. N=3:
    template<std::size_t M = N, enable_if_t<M == 3, int> = 0>
    const Vecteur   operator^(const Vecteur& autre)const;
};

//=================== Opérateurs externes Vecteur ======================
template<std::size_t N>
const Vecteur<N> 	operator+(const Vecteur<N>&, const Vecteur<N>&);
template<std::size_t N>
const Vecteur<N> 	operator-(const Vecteur<N>&);
template<std::size_t N>
const Vecteur<N> 	operator-(const Vecteur<N>&, const Vecteur<N>&);
template<std::size_t N>
const Vecteur<N> 	operator*(const double, const Vecteur<N>&);
template<std::size_t N>
const Vecteur<N> 	operator*(const Vecteur<N>&, const double);
template<std::size_t N>
const Vecteur<N> 	operator/(const Vecteur<N>&, const double);
template<std::size_t N>
const Vecteur<N> 	operator~(const Vecteur<N>&);
template<std::size_t N>
std::ostream& 		operator<<(std::ostream&, Vecteur<N> const&);


//  Définition des alias Vecteur2D et Vecteur3D
using Vecteur2D =  Vecteur<2>;
using Vecteur3D =  Vecteur<3>;


//	======================== Limites d'un template & explications ========================
//	L'utlisation d'une templated class "force" à écrire tout le code correspondant dans le
//	header, et donc ne permet pas de séparer proprement l'interface de la classe (dans un
//	header .h) de son implémentation (dans une source .cpp). Une manière est la suivante:
//		#include "Vecteur.tpp"
//	dans le .h après la définition de l'interface et des fonctions/opérateurs externes.
//	Ainsi, c'est "comme si" tout le code d'implémentation de l'interface et des fonctions/
//	opérateurs externes était effectivement écrit dans le header. On veillera cependant à
//	ne pas tenter de créer un Vecteur.o dans le Makefile, mais seulement ajouter Vecteur.h
//	là où c'est nécessaire, par ex. pour la ligne suivante dans le Makefile de testVecteur
//		testVecteur.o: testVecteur.cpp Vecteur.h
//	Plus d'info: https://stackoverflow.com/a/495056 & https://stackoverflow.com/a/44774074
#include "Vecteur.tpp"
