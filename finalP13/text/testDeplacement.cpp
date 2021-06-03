//
// Created by siddharth on 09/04/2021.
//
#include <fstream>
#include "Systeme.h"
#include "TextViewer.h"
#include "MontGaussienne.h"
using namespace std;


int main()
{
    ofstream fichier("re_5.txt");
    /* Nous voulons un support à dessin :                          *
     * ici un TextViewer qui écrit sur cout                        */
    TextViewer ecran(fichier);

    MontGaussienne everest({15,15,15},5,5);

    // Nous voulons un contenu à dessiner
    Systeme c(20,284.5,101325, 30,30,30,20.0/29.0);
    c.ajoute_montagne(everest);

    c.demarre();
    c.evolue(0.031);
    c.evolue(.031);
    c.evolue(.031);
    c.dessine_sur(ecran);

    // autre syntaxe possible
//    double dt(0.05);
//    for(int i(0);i<5;++i){
//        c.evolue(dt);
//        c.dessine_sur(ecran);
//    }


    
    fichier.close();
    return 0;
}
