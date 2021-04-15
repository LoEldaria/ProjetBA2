//
// Created by siddharth on 04/04/2021.
//
#include <iostream>
#include "Systeme.h"
#include "Montagne.h"
#include "ChampPotentiels.h"

using namespace std;

Systeme :: Systeme (const ChampPotentiels c, Montagne M) : CP(c), Massif(M),  sky(CP,c.get_param()){}


void Systeme :: affiche (std::ostream& sortie, a_afficher val1, a_afficher val2, a_afficher val3) const {
    sortie<<"une montagne : "<<endl<<"gaussienne de paramètres "<<endl;

    sortie<<"i0 = "<<Massif.get_centre()[0]<<"(x0 = "<< CP.coordonnees(Massif.get_centre()[0],Massif.get_centre()[1],Massif.get_hauteur())[0]<<")"<<endl;
    sortie<<"j0= "<<Massif.get_centre()[1]<<"(y0 = "<< CP.coordonnees(Massif.get_centre()[0],Massif.get_centre()[1],Massif.get_hauteur())[1]<<")"<<endl;
    sortie<<"h= "<<Massif.get_hauteur()<<"(H= "<< CP.coordonnees(Massif.get_centre()[0],Massif.get_centre()[1],Massif.get_hauteur())[2]<<")"<<endl;
    sortie<<"Si0= "<<Massif.get_sigma()[0]<<"(Sx0= "<< CP.coordonnees(Massif.get_sigma()[0],Massif.get_sigma()[1],0)[0]<<")"<<endl;
    sortie<<"Sj0= "<<Massif.get_sigma()[1]<<"(Sy0= "<<CP.coordonnees(Massif.get_sigma()[0],Massif.get_sigma()[1],0)[1]<<")"<<endl;
    sortie<<endl<<endl;
    sortie<<"un champ de potentiels : "<<endl;
    sortie<<"Nx="<<CP.get_nbrcube()[0]<<" Ny="<<CP.get_nbrcube()[1]<<" Nz="<<CP.get_nbrcube()[2]<<endl;
    sortie<<"Lx="<<CP.Longueur()[0]<<" Ly="<<CP.Longueur()[1]<<" Lz="<<CP.Longueur()[2]<<endl;
    sortie<<"lambda= "<<CP.get_lambda()<<endl;

    if(val1!=null) {
        sortie<<"valeurs: "<<endl;
        cout << val1 << " : " << endl;
        sortie << endl;
        CP.affiche(sortie, val1, null);
    }
    sortie<<endl<<endl;
    if(val2!=null) {
        sortie<<"valeurs: "<<endl;
        cout << val2 << " : " << endl;
        sortie << endl;
        CP.affiche(sortie, null, val2);
    }
    cout<<endl<<endl;
    if(val3!=null) {
        sortie << "valeurs: " << endl;
        cout << val3 << " : " << endl;
        sortie << endl;
        CP.affiche(sortie, null, val3);
    }
    sortie<<endl<<endl;
    sortie<<"Un ciel : "<<endl;
    sky.affiche_val(sortie);

}
void Systeme ::dessine_sur(SupportADessin &support) {
    support.dessine(*this);
}

void Systeme::evolue(Vecteur3D& vitesse) {
dessine_sur(*blank_paper);
}

void Systeme::demarre(Vecteur3D& vitesse) {
    CP.initialise(Massif);
    CP.resolution();
    sky.update(CP);
dessine_sur(*blank_paper);
evolue(vitesse);

}

ostream& operator<< (ostream& sortie, Systeme const& D) {
   D.affiche(sortie, potentiel, laplacien, vitesse_vent);
   return sortie;
}
