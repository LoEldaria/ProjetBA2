#pragma once

#include <array>
#include <iostream>

//	On crée un typedef pour éviter à avoir à écrire std::array<double,N> partout
template<std::size_t N>
using ArrayDbl = std::array<double,N>;

template<typename T, std::size_t N>
const ArrayDbl<N> toDouble(const std::array<T,N> vect){
    ArrayDbl<N> v;
    for(std::size_t i(0); i<vect.size(); ++i)
        v[i] = 1.0 * vect[i]; // convert potential int to double
    return v;
}

template<std::size_t N>
class Vecteur{
protected:
   ArrayDbl<N> vecteur;

public:
	//====================== Constructeurs Vecteur =====================
    Vecteur(ArrayDbl<N> const& vect = ArrayDbl<N>{}): vecteur(vect){}
    template<typename T> Vecteur(const std::array<T,N> vect): vecteur(toDouble(vect)){}

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
	double			operator[](std::size_t)const; // à garder ?
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


//	Création du type Vecteur2D qui est un vecteur à 2 coords. On crée pour ça une sous-
//	classe de Vecteur<2> (au lieu d'utiliser un simple 'using Vecteur2D = Vecteur<2>;')
//	afin de pouvoir spécifier le constructeur, pour autoriser une initialisation du type
//		Vecteur2D myvect(3.14, 2.72);
class Vecteur2D : public Vecteur<2>{
public:
	Vecteur2D(double x = 0, double y = 0): Vecteur({x,y}) {}
    Vecteur2D(const Vecteur<2>& autre): Vecteur(autre){}
};

//	On pourrait également imaginer une spécification pour le vecteur à 3 dimensions en
//	cas de besoin d'une implémentation du produit vectoriel. Par ex. on pourrait avoir

class Vecteur3D : public Vecteur<3>{
public:
	Vecteur3D(double x = 0, double y = 0, double z = 0): Vecteur({x,y,z}) {}
    Vecteur3D(const Vecteur<3>& autre): Vecteur(autre){}
    const Vecteur3D operator^(const Vecteur3D&) const; // produit vectoriel
};


//	======================== Limites d'un template & explications ========================
//	L'utlisation d'une templated class "force" à écrire tout le code correspondant dans le
//	header, et donc ne permet pas de séparer proprement l'interface de la classe (dans un 
//	header .h) de son implémentation (dans une source .cpp) . Une manière est la suivante: 
//		#include "Vecteur.tpp"
//	dans le .h après la définition de l'interface et des fonctions/opérateurs externes.
//	Ainsi, c'est "comme si" tout le code d'implémentation de l'interface et des fonctions/
//	opérateurs externes était effectivement écrit dans le header. On veillera cependant à 
//	ne pas tenter de créer un Vecteur.o dans le Makefile, mais seulement ajouter Vecteur.h
//	là où c'est nécessaire, par ex. pour la ligne suivante dans le Makefile de testVecteur
//		testVecteur.o: testVecteur.cpp Vecteur.h
//	Plus d'info: https://stackoverflow.com/a/495056 & https://stackoverflow.com/a/44774074
#include "Vecteur.tpp"