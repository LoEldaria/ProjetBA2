//
// Created by siddharth on 07/05/2021.
//
#include "Chaînes_de_Montagnes.h"
#include<iostream>
#include "TextViewer.h"
#include <array>
#include <vector>
using namespace std;

int main(){
    TextViewer ecran (cout);
    MontGaussienne K2 (&ecran,15.0,18.0,15.0,5.0,10.0,1.0);
    MontGaussienne Everest (&ecran, 2.0,22.0,12.0,12.0,3.0,1);
    MontGaussienne Makalu (&ecran, 20.0,2.0,15.0,8.0,4.0,1.0);
    vector<Montagne*> petite_chaine;
    petite_chaine.push_back(&Everest);
    petite_chaine.push_back(&Makalu);
    Chaines_de_Montagnes Kamet (petite_chaine);
    vector<Montagne*> grande_chaine;
    grande_chaine.push_back(&K2);
    grande_chaine.push_back(&Kamet);
    Chaines_de_Montagnes Himalaya (grande_chaine);
    Himalaya.affiche(cout);
}
