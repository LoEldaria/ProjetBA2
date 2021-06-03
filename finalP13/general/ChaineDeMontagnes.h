#ifndef CHAINEDEMONTAGNES_H
#define CHAINEDEMONTAGNES_H

#include "Montagne.h"
#include <vector>

class ChaineDeMontagnes : public Montagne{
private:
    std::vector<std::unique_ptr<Montagne>> chaine;
    std::unique_ptr<ChaineDeMontagnes> clone() const;
public:

    ChaineDeMontagnes(double lambda=1);
    ChaineDeMontagnes(ChaineDeMontagnes const& autre);
    virtual std::unique_ptr<Montagne> copie() const override;
//    virtual void dessine_sur(SupportADessin& support) override;
    virtual double altitude(std::size_t i, std::size_t j) const override;
    virtual void affiche(std::ostream& flot) const override;
    void ajoute_montagne(Montagne& mont){
        chaine.push_back(mont.copie());
    }

    /*chaine( du systeme, ou à l'intérieur de chaine systeme) a son propre lambda par construction; inside classe chaine,
    les montagnes sous jacentes n'ont pas besoin d'avoir un lambda qui leur est propre:
    altitude() de chaine va demander les altitudes en (i, j, k ), qui n'a pas besoin de lambda;
    c'est l'autre altitude(), celle d'un élément de la base, qui en a besoin (par ex dans dessine())*/
};

#endif // CHAINEDEMONTAGNES_H
