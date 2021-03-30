#include "Potentiel.h"
#include "Vecteur2D.h"
#include "Montagne.h"
#include "ChampPotentiels.h"
#include <cmath>
#include <array>
#include <iomanip> //pour la précision des résultats

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
	if(i>=nombre_de_cubes[0] or j>=nombre_de_cubes[1] or k>=nombre_de_cubes[2]){
		cout<<"Votre bloc est hors du monde la valeur va être mise à zero"<<endl;
		return coord;
	}
	coord[0]=i*lambda;
	coord[1]=j*lambda-(Longueur()[1]/2);
	coord[2]=k*lambda;
	return coord;
}



void ChampPotentiels ::  initialise (double vit_vent_limite, Montagne const& Everest) {
	for (unsigned int i(0) ; i<nombre_de_cubes[0] ; ++i){
		for (unsigned int j(0) ; j<nombre_de_cubes[1] ; ++j){			
			for (unsigned int k(0) ; k<nombre_de_cubes[2] ; ++k){
				if( i==0 or i==nombre_de_cubes[0]-1
					or j==0 or j==nombre_de_cubes[1]-1
					or k==0 or k==nombre_de_cubes[2]-1
					or k > Everest.altitude({i,j}))
				{
					boite[i][j][k].access_potentiel(Vecteur2D(-(vit_vent_limite/2)*coordonnees(i,j,k)[2],(vit_vent_limite/2)*coordonnees(i,j,k)[1]));
				}
			}
		}
	}
}
// void ChampPotentiels ::  initialise (double vit_vent_limite, Montagne const& Everest) {
// 	boite.clear(); // pour garantir qu'un tableau non vide ne soit pas implémenté avec de nouvelles valeurs et que l'on ne puisse plus contrôler la taille de la boite
	
// 	for (unsigned int i(0) ; i<nombre_de_cubes[0] ; ++i){
// 	vector<vector<Potentiel>> P1;
// 		for (unsigned int j(0) ; j<nombre_de_cubes[1] ; ++j){
// 			vector<Potentiel> P2;
			
// 			for (unsigned int k(0) ; k<nombre_de_cubes[2] ; ++k){
			
// 				// array<double,2> coord({coordonnees(i,j,k)[0], coordonnees(i,j,k)[1]});
// 				// if(coordonnees(i,j,k)[2] > Everest.altitude({i,j})){ 
// 				if( i==0 or i==nombre_de_cubes[0]-1
// 					or j==0 or j==nombre_de_cubes[1]-1
// 					or k==0 or k==nombre_de_cubes[2]-1
// 					or k > Everest.altitude({i,j})) //si c'est au dessus de la montagne  ou sur les bords de la boite
// 				{ 
// 					P2.push_back(Potentiel (-(vit_vent_limite/2)*coordonnees(i,j,k)[2],(vit_vent_limite/2)*coordonnees(i,j,k)[1]));	
// 				}
// 				else{
// 					P2.push_back(Potentiel());
// 				}
// 			}
// 			P1.push_back(P2);
// 		}
// 		boite.push_back(P1);
// 	}
// }

double ChampPotentiels :: erreur () const {
	double e(0);
	for (unsigned int i(0) ; i<nombre_de_cubes[0]-1 ; ++i){
		for (unsigned int j(0) ; j<nombre_de_cubes[1]-1 ; ++j){
			for (unsigned int k(0) ; k<nombre_de_cubes[2]-1 ; ++k){
				e+= boite[i][j][k].get_Laplacien().norme2();
			}
		}
	}
	return e;
}

Vecteur2D ChampPotentiels :: calcule_laplacien (unsigned int i, unsigned int j, unsigned int k) const {
	return boite[i-1][j][k].get_potentiel()+boite[i][j-1][k].get_potentiel()+boite[i][j][k-1].get_potentiel()-6*boite[i][j][k].get_potentiel()+boite[i+1][j][k].get_potentiel()+boite[i][j+1][k].get_potentiel()+boite[i][j][k+1].get_potentiel();
}

void ChampPotentiels :: iteration(double epsilon){
	
	//on itere sur l'INTERIEUR de la boite -> on commence à 1(2eme cube)

	for (unsigned int i(1) ; i<nombre_de_cubes[0]-1 ; ++i){
		for (unsigned int j(1) ; j<nombre_de_cubes[1]-1 ; ++j){
			for (unsigned int k(1) ; k<nombre_de_cubes[2]-1 ; ++k){
				boite[i][j][k].access_Laplacien(calcule_laplacien(i,j,k));
			}
		}
	}

	for (unsigned int i(1) ; i<nombre_de_cubes[0]-1 ; ++i){
		for (unsigned int j(1) ; j<nombre_de_cubes[1]-1 ; ++j){
			for (unsigned int k(1) ; k<nombre_de_cubes[2]-1 ; ++k){
				boite[i][j][k].access_potentiel(boite[i][j][k].get_potentiel()+epsilon*boite[i][j][k].get_Laplacien());
			}
		}
	}

}

void ChampPotentiels :: resolution (double seuil, unsigned int nb_iterations_max, bool affichage){
	unsigned int n(0);
	double s(0);
	do {
		this->iteration();
		if(affichage){
			this->affiche( potentiel, laplacien);
		}
		s=this->erreur();
		++n;
		cout<< n <<' '<< s <<endl;
	}while(n<nb_iterations_max and s>seuil);
}



array<double,3> ChampPotentiels::vitesse(unsigned int i,unsigned int j, unsigned int k)const{
	array<double,3> vit_vent;

	//forcer la vitesse du vent aux bords à v(infini)


	double c(1.0/(2*lambda));

	vit_vent[0] = c*( (boite[i][j+1][k].get_potentiel())[1] - (boite[i][j-1][k].get_potentiel())[1] - (boite[i][j][k+1].get_potentiel())[0] + (boite[i][j][k-1].get_potentiel())[0] );

	vit_vent[1] = c*( -(boite[i+1][j][k].get_potentiel())[1] + (boite[i-1][j][k].get_potentiel())[1] );

	vit_vent[2] = c*( boite[i+1][j][k].get_potentiel()[0] - boite[i-1][j][k].get_potentiel()[0] ) ;

	return vit_vent;
}

void ChampPotentiels::display(unsigned int i,unsigned int j, unsigned int k ,a_afficher val)const{
	switch(val){
		case(potentiel): cout<<setprecision(12)<<boite[i][j][k].get_potentiel();break;
		case(laplacien): cout<<setprecision(12)<<boite[i][j][k].get_Laplacien();break;
		case(speed): {array<double,3> speed = vitesse(i,j,k);
					cout<<speed[0]<<' '<<speed[1]<<' '<<speed[2];
					cout<< speed[0]*speed[0]+speed[1]*speed[1]+speed[2]*speed[2]; break;
					}
		case(null): default: break;
	}
}

/*on a un pb d'affichage: le potentiel en z (2eme composante) est le même pour toute la surface de niveau z=c
OR , pour la cellule disons 12 0 0, pot en z =0; et pour 12 1 0, on a pot z !=0 
*/
void ChampPotentiels :: affiche( a_afficher val, a_afficher val2) const {
	
	for (unsigned int i(0) ; i<nombre_de_cubes[0] ; ++i){
		for (unsigned int j(0) ; j<nombre_de_cubes[1] ; ++j){
			for (unsigned int k(0) ; k<nombre_de_cubes[2] ; ++k){
				cout<<i<<" "<<j<<" "<<k<<" ";
				
				display(i,j,k,val);
				display( i,j,k,val2);
				cout<<endl;
			}
		}
	}
}


