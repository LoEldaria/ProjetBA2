

#include "TextViewer.h"
#include "Systeme.h"


void TextViewer::dessine(Ciel const& a_dessiner){
    a_dessiner.affiche_val(flot);
}
void TextViewer::dessine(Systeme const& a_dessiner){
    //si on veut afficher uniquement les infos (=ne pas avoir les valeurs de tous les potentiels par exemple)
    //il suffit de mettre a_dessiner.affiche(flot)
    a_dessiner.affiche(flot, potentiel, laplacien, vitesse_vent);
    a_dessiner.affiche_pluie(flot);
}

void TextViewer::dessine(Montagne const& a_dessiner){
    a_dessiner.affiche(flot);
}
