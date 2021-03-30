#ifndef CHAMPPOTENTIELS_H
#define CHAMPPOTENTIELS_H

#include <iostream>
#include <array>
#include <vector>
#include "Vecteur2D.h"
#include "Potentiel.h"
#include "Montagne.h"

enum a_afficher {null=0, potentiel, laplacien, speed};

class ChampPotentiels {
private :

	std::array<unsigned int,3>  nombre_de_cubes;
	double lambda;
	std::vector<std::vector<std::vector<Potentiel>>> boite;

	void display(unsigned int i,unsigned int j, unsigned int k ,a_afficher val)const;

public : 
	ChampPotentiels (unsigned int i=0, unsigned int j=0, unsigned int k=0, double l=1) : 
	nombre_de_cubes({i,j,k}),lambda(l), boite(std::vector<std::vector<std::vector<Potentiel>>>(i, std::vector<std::vector<Potentiel>>(j, std::vector<Potentiel>(k, Potentiel())))){}

	std::array<double,3> Longueur  () const;
	std::array<double,3> coordonnees(unsigned int i, unsigned int j, unsigned int k) const;
		
	void initialise (double vit_vent_limite, Montagne const& Everest) ;

	double erreur() const;
	Vecteur2D calcule_laplacien (unsigned int i, unsigned int j, unsigned int k) const ;
	void iteration(double epsilon =0.1);
	void resolution (double seuil =1e-4, unsigned int nb_iterations_max=5000, bool affichage=false);

	std::array<double,3> vitesse(unsigned int i,unsigned int j, unsigned int k)const;


	void affiche( a_afficher val1, a_afficher val2 = null) const;

	// Vecteur2D temporaire(unsigned int i, unsigned int j, unsigned int k)const{
	// 	return boite[i][j][k].get_potentiel();
	// }
};



#endif // CHAMPPOTENTIELS
