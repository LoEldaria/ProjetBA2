#ifndef CHAMPPOTENTIELS_H
#define CHAMPPOTENTIELS_H

#include <iostream>
#include <array>
#include <vector>
#include "Vecteur2D.h"
#include "Potentiel.h"
#include "Montagne.h"

class ChampPotentiels {
private :

	std::array<unsigned int,3>  nombre_de_cubes;
	double lambda;
	std::vector<std::vector<std::vector<Potentiel>>> boite;
	
public : 
ChampPotentiels (unsigned int x=0, unsigned int y=0, unsigned int z=0, double l=0) : 
nombre_de_cubes({x,y,z}),lambda(l){}

std::array<double,3> Longueur  () const;


std::array<double,3> coordonnees(unsigned int i, unsigned int j, unsigned int k) const;
	
void initialise (double vent, Montagne const& Everest) ;

bool convergence( double erreur ) const;
Vecteur2D calcule_laplacien (unsigned int i, unsigned int j, unsigned int k) const ;
void Iteration(double epsilon, double erreur);

/*void resolution (double seuil =1e-4, unsigned int nb_iterations_max=5000, bool affichage=false);
array<double,3> vitesse(unsigned int i,unsigned int j, unsigned int k);*/

void affiche() const ;
};



#endif // CHAMPPOTENTIELS
