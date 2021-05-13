//
// Created by siddharth on 08/04/2021.
//

#include "TextViewer.h"
#include "Systeme.h"


void TextViewer::dessine(Ciel const& a_dessiner){
    a_dessiner.affiche_val(flot);
}
void TextViewer::dessine(Systeme const& a_dessiner){
    a_dessiner.affiche(flot, potentiel, laplacien, vitesse_vent);
}
/*dans cette méthode  est ce qu'on veut afficher les valeurs de ChampPotentiels même
si Champ n'est pas un dessinable de Systeme?
On voudra utiliser affiche() en entier quand on aura cout<<systeme, comme dans P9 par ex*/

void TextViewer::dessine(Montagne const& a_dessiner){
    a_dessiner.affiche(flot);
}