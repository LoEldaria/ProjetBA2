#ifndef VECTEUR2D_H
#define VECTEUR2D_H

#include <array>


class Vecteur2D
{
private:

    std::array<double,2> vecteur;

public:

    //Vecteur2D();

    std::array<double,2> get_vecteur()const;

    void set_coord (bool position, double new_coord);

    void affiche()const;

    bool compare (Vecteur2D const& vec2)const;


    const Vecteur2D addition(Vecteur2D const& autre) const;
    const Vecteur2D soustraction (Vecteur2D const& autre) const;
    const Vecteur2D oppose() const;
    const Vecteur2D mult(double x) const;
    double prod_scal(Vecteur2D const& autre) const;
    double norme() const ;
    double norme2() const ;
    const Vecteur2D unitaire () const;
};

#endif // VECTEUR2D_H
