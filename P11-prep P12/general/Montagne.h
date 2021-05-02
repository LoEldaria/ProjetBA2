#ifndef MONTAGNE_H
#define MONTAGNE_H

#include "Dessinable.h"
#include "Vecteur.h"
#include <memory>

// pour chaine
#include <vector>

class Montagne : public Dessinable
{
protected:
    double lambda;
    Montagne(double=1);

public:
    virtual double altitude(std::size_t i, std::size_t j) const =0;
    double altitude(Vecteur2D const& coord) const;
    virtual void affiche(std::ostream& flot) const =0;
    virtual std::unique_ptr<Montagne> copie() const =0;
    virtual void dessine_sur(SupportADessin& support) override;
    virtual ~Montagne(){}
};

class MontGaussienne: public Montagne{
private:
    std::array<std::size_t,2> centre;
    std::size_t hauteur;
    std::array<std::size_t,2> etalement_sigma;
    std::unique_ptr<MontGaussienne> clone() const;

public:
    MontGaussienne (double x=0, double y=0, double H=0,double es_x=1, double es_y=1, double lambda=1);
    MontGaussienne (std::array<std::size_t,3> sommet, std::size_t es_i, std::size_t es_j,double lambda=1);

    virtual std::unique_ptr<Montagne> copie() const override;
//    virtual void dessine_sur(SupportADessin& support) override;
    virtual double altitude(std::size_t i, std::size_t j) const override;
    virtual void affiche(std::ostream& flot) const override;

};

class Chaine : public Montagne{
private:
    std::vector<std::unique_ptr<Montagne>> Massif;
    std::unique_ptr<Chaine> clone() const;
public:

    Chaine(double lambda=1);
    virtual std::unique_ptr<Montagne> copie() const override;
//    virtual void dessine_sur(SupportADessin& support) override;
    virtual double altitude(std::size_t i, std::size_t j) const override;
    virtual void affiche(std::ostream& flot) const override;
    void ajoute_montagne(Montagne& mont){
        Massif.push_back(mont.copie());
    }

    /*chaine( du systeme, ou à l'intérieur de chaine systeme) a son propre lambda par construction; inside classe chaine,
    les montagnes sous jacentes n'ont pas besoin d'avoir un lambda qui leur est propre:
    altitude() de chaine va demander les altitudes en (i, j, k ), qui n'a pas besoin de lambda;
    c'est l'autre altitude(), celle d'un élément de la base, qui en a besoin (par ex dans dessine())*/
};

#endif // MONTAGNE_H
