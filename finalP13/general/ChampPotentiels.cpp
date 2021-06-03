#include "Potentiel.h"
#include "Montagne.h"
#include "ChampPotentiels.h"
#include "Constantes.h"
#include <cmath>
#include <array>
#include <iomanip> //pour la précision des résultats

using namespace std;




void ChampPotentiels ::  initialise (Montagne const& Everest) {
    applique_fonction([&](Potentiel& pot, std::size_t i, std::size_t j, std::size_t k){
        if( i==0 or i==nombre_de_cubes[0]-1
            or j==0 or j==nombre_de_cubes[1]-1
            or k >= Everest.altitude(i,j)){
            pot.access_potentiel(Vecteur2D(-(param->v_inf/2)*coordonnees(i,j,k)[2],(param->v_inf/2)*coordonnees(i,j,k)[1]));
        }
    });
}


double ChampPotentiels :: erreur () const {
	double e(0);
    applique_fonction([&e](const Potentiel& pot){
        e+= pot.get_Laplacien().norme2();
    },true);
	return e;
}

Vecteur2D ChampPotentiels :: calcule_laplacien (std::size_t i, std::size_t j, std::size_t k) const {
	return boite[i-1][j][k].get_potentiel() + boite[i][j-1][k].get_potentiel() + boite[i][j][k-1].get_potentiel() - 6*boite[i][j][k].get_potentiel() + boite[i+1][j][k].get_potentiel() + boite[i][j+1][k].get_potentiel() + boite[i][j][k+1].get_potentiel();
}

void ChampPotentiels :: iteration(double epsilon){
	
	//on itere sur l'INTERIEUR de la boite -> on commence à 1(2eme cube)

    applique_fonction([&](Potentiel& pot, std::size_t i, std::size_t j, std::size_t k){
        if(pot.get_potentiel()!=Vecteur2D())
            pot.access_Laplacien(calcule_laplacien(i,j,k));
    },true, true);

    applique_fonction([&](Potentiel& pot){
       pot.access_potentiel(pot.get_potentiel()+epsilon*pot.get_Laplacien());
    },true, true);

}

void ChampPotentiels :: resolution (double seuil, unsigned int nb_iterations_max, bool affichage){
    if (seuil==0) seuil = std::pow(lambda,4)*1e-4;
    std::size_t n(0);
    unsigned int s(0);
	do {
		this->iteration();
		if(affichage){
			this->affiche(cout, potentiel, laplacien);
		}
		s=this->erreur();
		++n;
	}while(n<nb_iterations_max and s>seuil);
}



const Vecteur3D ChampPotentiels::vitesse(std::size_t i,std::size_t j, std::size_t k)const{
    //forcer la vitesse du vent aux bords à v_infini
	if(i==0 or i==nombre_de_cubes[0]-1
		or j==0 or j==nombre_de_cubes[1]-1
		or k==0 or k==nombre_de_cubes[2]-1)
	{return Vecteur3D(param->v_inf,0,0);}

    return Vecteur3D(
		(boite[i][j+1][k].get_potentiel())[1] - (boite[i][j-1][k].get_potentiel())[1] - (boite[i][j][k+1].get_potentiel())[0] + (boite[i][j][k-1].get_potentiel())[0],
		-(boite[i+1][j][k].get_potentiel())[1] + (boite[i-1][j][k].get_potentiel())[1],
		boite[i+1][j][k].get_potentiel()[0] - boite[i-1][j][k].get_potentiel()[0] 
    ) / (2*lambda);
}

void ChampPotentiels::display(ostream& flot, std::size_t i,std::size_t j, std::size_t k ,a_afficher val)const{
	switch(val){
		case(potentiel): flot<<setprecision(12)<<boite[i][j][k].get_potentiel()<<' ';break;
		case(laplacien): flot<<setprecision(12)<<boite[i][j][k].get_Laplacien()<<' ';break;
		case(vitesse_vent): {Vecteur3D vit(vitesse(i,j,k));
					flot << vit << vit.norme2() << ' '; break;
					}
		case(null): default: break;
	}
}


void ChampPotentiels :: affiche(ostream& flot, a_afficher val1, a_afficher val2, a_afficher val3) const {
	
    if(val1!=null){
        applique_fonction([&](const Potentiel&, std::size_t i, std::size_t j, std::size_t k){
            flot<<i<<" "<<j<<" "<<k<<" ";

            display(flot, i,j,k,val1);
            display(flot, i,j,k,val2);
            display(flot, i,j,k,val3);
            flot<<endl;
        });
    }

}

void ChampPotentiels::affiche_info(ostream& sortie)const{
	sortie<<"un champ de potentiels : "<<endl;
    sortie<<"Nx="<<get_nbrcube()[0]<<" Ny="<<get_nbrcube()[1]<<" Nz="<<get_nbrcube()[2]<<endl;
    sortie<<"Lx="<<Longueur()[0]<<" Ly="<<Longueur()[1]<<" Lz="<<Longueur()[2]<<endl;
    sortie<<"lambda= "<<get_lambda()<<endl;
}

Physique::Parametres* ChampPotentiels::get_param() const  {
    return param;
}


