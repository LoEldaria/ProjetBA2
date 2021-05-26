#ifndef CHAMPPOTENTIELS_H
#define CHAMPPOTENTIELS_H

#include <iostream>
#include <vector>
#include "Collection3D.h"
#include "Constantes.h"
#include "Potentiel.h"
#include "Montagne.h"

enum a_afficher {null=0, potentiel, laplacien, vitesse_vent};

class ChampPotentiels: public Collection3D<Potentiel>{
private :
	Physique::Parametres* param;
	void display(std::ostream&, unsigned int i,unsigned int j, unsigned int k ,a_afficher val)const;
    void iteration(double epsilon =0.1);

public : 
	ChampPotentiels (Physique::Parametres* param, unsigned int i=0, unsigned int j=0, unsigned int k=0, double l=1) : Collection3D<Potentiel>(i,j,k,l), param(param){}

	void initialise (Montagne const& Everest) ;

	double erreur() const;
	Vecteur2D calcule_laplacien (unsigned int i, unsigned int j, unsigned int k) const ;
    void resolution (double seuil =0, unsigned int nb_iterations_max=5000, bool affichage=false);
	const Vecteur3D vitesse(unsigned int i,unsigned int j, unsigned int k)const;

	void affiche(std::ostream&, a_afficher val1, a_afficher val2 = null,a_afficher val3=null) const;
	void affiche_info(std::ostream&)const;

	Vecteur2D get_potentiel(unsigned int i,unsigned int j, unsigned int k)const{
		return boite[i][j][k].get_potentiel();
	}
	Physique::Parametres* get_param () const ;
};



#endif // CHAMPPOTENTIELS
