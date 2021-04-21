//
// Created by siddharth on 09/04/2021.
//

#include "Systeme.h"
#include "TextViewer.h"

using namespace std;


int main()
{
    /* Nous voulons un support à dessin :                          *
     * ici un TextViewer qui écrit sur cout                        */
    TextViewer ecran(cout);

    MontGaussienne everest(&ecran,{15,15,15},5,5, 20./29);

    // Nous voulons un contenu à dessiner
    Systeme c(&ecran, 20,284.5,101325, 30,30,30,20.0/29.0);
    c.ajoute_montagne(everest);
    // cout<<c; surcharge de << de Systeme permet cela
    c.demarre();

    // Nous dessinons notre contenu  sur notre support à dessin précédent
    

    return 0;
}