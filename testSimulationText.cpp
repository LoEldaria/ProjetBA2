//
// Created by siddharth on 09/04/2021.
//

#include "Systeme.h"
#include "text_viewer.h"

using namespace std;


int main()
{
    /* Nous voulons un support à dessin :                          *
     * ici un TextViewer qui écrit sur cout                        */

    Physique::Parametres param (20,284.5,101325);
    Montagne everest({15,15,18},5,10);
    ChampPotentiels CP(&param,30,30,30,1.2);
    // Nous voulons un contenu à dessiner
    Systeme c(CP,everest);
    cout<<c;
    // Nous dessinons notre contenu  sur notre support à dessin précédent


    return 0;
}