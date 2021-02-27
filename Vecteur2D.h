#ifndef VECTEUR2D_H
#define VECTEUR2D_H

#include<array>


class Vecteur2D
{
private:

    std::array<double,2> vecteur;

public:

    Vecteur2D();

    std::array<double,2> get_vecteur();

    void set_coord (bool position, double new_coord);

    void affiche();

    bool compare (Vecteur2D vec2);


    Vecteur2D addition(Vecteur2D autre) const;
    Vecteur2D soustraction (Vecteur2D autre) const;
    Vecteur2D oppose() const;
    Vecteur2D mult(double x) const;
    double prod_scal(Vecteur2D autre) const;
    double norme() const ;
    double norme2() const ;
    Vecteur2D unitaire () const;
};

#endif // VECTEUR2D_H
