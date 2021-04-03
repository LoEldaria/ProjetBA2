#ifndef VECTEUR2D_H
#define VECTEUR2D_H

#include <iostream>
#include <array>


class Vecteur2D
{
private:
    std::array<double,2> vecteur;

public:
    //====================== Constructeurs Vecteur2D =====================
    Vecteur2D(std::array<double,2> const& vecteur={0, 0}):vecteur(vecteur){} //constructeur par défaut
    Vecteur2D(double x, double y):vecteur({x, y}) {}
    /* Vecteur2D(Vecteur2D const& vect):vecteur(vect.get_vecteur()){}   // constructeur de copie */

    //======================= Méthodes Vecteur2D =========================
    std::array<double,2> get_vecteur()const;
    void set_coord (bool position, double new_coord);
    double norme() const ;
    double norme2() const ;
    std::ostream& affiche(std::ostream&)const; //affiche

    //=================== Opérateurs internes Vecteur2D ==================
    bool operator==(const Vecteur2D&)const; //comparaison
    bool operator!=(const Vecteur2D)const;
    Vecteur2D& operator+=(const Vecteur2D&);
    Vecteur2D& operator-=(const Vecteur2D&);
    Vecteur2D& operator*=(const double);
    double operator*(Vecteur2D const&) const; //produit scalaire
    double operator[](unsigned int)const;

};

//=================== Opérateurs externes Vecteur2D ======================
std::ostream& operator<<(std::ostream&, Vecteur2D const&);

const Vecteur2D operator+(const Vecteur2D&, const Vecteur2D&);
const Vecteur2D operator-(const Vecteur2D&); //anciennement méthode oppose()
const Vecteur2D operator-(const Vecteur2D&, const Vecteur2D&);
const Vecteur2D operator*(const double, const Vecteur2D&);
const Vecteur2D operator*(const Vecteur2D&, const double);
const Vecteur2D operator~(Vecteur2D const&); //renvoi du vecteur unitaire


#endif // VECTEUR2D_H