#include "Potentiel.h"
#include "Vecteur2D.h"
#include "Montagne.h"
#include "ChampPotentiels.h"
#include <cmath>
#include <array>
#include <iomanip> //pour la précision

using namespace std;

array<double,3> ChampPotentiels :: Longueur ()const {
	
array<double, 3> L;

L[0]=lambda*(nombre_de_cubes[0]-1);
L[1]=lambda*(nombre_de_cubes[1]-1);
L[2]=lambda*(nombre_de_cubes[2]-1);

return L;
}

array<double,3> ChampPotentiels :: coordonnees(unsigned int i, unsigned int j, unsigned int k)const{
	array<double,3> coord;
	if(i>nombre_de_cubes[0] or j>nombre_de_cubes[1] or k>nombre_de_cubes[2]){
		cout<<"Votre bloc est hors du monde la valeur va être mise à zero"<<endl;
		return coord;
	}
	coord[0]=i*lambda;
	coord[1]=j*lambda-(Longueur()[1]/2);
	coord[2]=k*lambda;
	return coord;
}

void ChampPotentiels ::  initialise (double vent, Montagne const& Everest) {
	boite.clear(); // pour garantir qu'un tableau non vide ne soit pas implémenté avec de nouvelles valeurs et que l'on ne puisse plus contrôler la taille de la boite
	
	for (unsigned int i(0) ; i<nombre_de_cubes[0] ; ++i){
	vector<vector<Potentiel>> P1;
		for (unsigned int j(0) ; j<nombre_de_cubes[1] ; ++j){
			vector<Potentiel> P2;
			
			for (unsigned int k(0) ; k<nombre_de_cubes[2] ; ++k){
			
				array<double,2> coord({coordonnees(i,j,k)[0], coordonnees(i,j,k)[1]});
				if(coordonnees(i,j,k)[2] > Everest.altitude(coord)){ //si c'est sous/sur la montagne 
					P2.push_back(Potentiel (-(vent/2)*coordonnees(i,j,k)[2],(vent/2)*coordonnees(i,j,k)[1]));	
				}
				else{
					P2.push_back(Potentiel());
				}
			}
			P1.push_back(P2);
		}
		boite.push_back(P1);
	}
}

bool ChampPotentiels :: convergence (double erreur) const {
	double e(0);
	for (unsigned int i(0) ; i<nombre_de_cubes[0]-1 ; ++i){
		for (unsigned int j(0) ; j<nombre_de_cubes[1]-1 ; ++j){
			for (unsigned int k(0) ; k<nombre_de_cubes[2]-1 ; ++k){
				e+= boite[i][j][k].get_Laplacien().norme2();
			}
		}
	}
	if(e>erreur){		
		return false;
	}
	return true;
}

Vecteur2D ChampPotentiels :: calcule_laplacien (unsigned int i, unsigned int j, unsigned int k) const {
	return boite[i-1][j][k].get_potentiel()+boite[i][j-1][k].get_potentiel()+boite[i][j][k-1].get_potentiel()-6*boite[i][j][k].get_potentiel()+boite[i+1][j][k].get_potentiel()+boite[i][j+1][k].get_potentiel()+boite[i][j][k+1].get_potentiel();
}

void ChampPotentiels :: Iteration (double epsilon, double erreur){
	unsigned int n(0);
do {
	for (unsigned int i(0) ; i<nombre_de_cubes[0]-1 ; ++i){
		for (unsigned int j(0) ; j<nombre_de_cubes[1]-1 ; ++j){
			for (unsigned int k(0) ; k<nombre_de_cubes[2]-1 ; ++k){
				boite[i][j][k].access_Laplacien(calcule_laplacien(i,j,k));
			}
		}
	}
	for (unsigned int i(0) ; i<nombre_de_cubes[0]-1 ; ++i){
		for (unsigned int j(0) ; j<nombre_de_cubes[1]-1 ; ++j){
			for (unsigned int k(0) ; k<nombre_de_cubes[2]-1 ; ++k){
				boite[i][j][k].access_potentiel(boite[i][j][k].get_potentiel()+epsilon*boite[i][j][k].get_Laplacien());
			}
		}
	}
	++n;
}while(convergence(erreur)==false or n<1000);

}

void ChampPotentiels :: affiche() const {
	for (unsigned int i(0) ; i<nombre_de_cubes[0] ; ++i){
		for (unsigned int j(0) ; j<nombre_de_cubes[1] ; ++j){
			for (unsigned int k(0) ; k<nombre_de_cubes[2] ; ++k){
				cout<<i<<" "<<j<<" "<<k<<" "<<setprecision(12)<<boite[i][j][k].get_potentiel()<<endl;
			}
		}
	}
}
