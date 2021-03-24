#include <iostream>
#include "ChampPotentiels.h"
#include "Potentiel.h"
#include "Montagne.h"
#include "Vecteur2D.h"

using namespace std;

int main() {


ChampPotentiels cp (30,30,30,20.0/29.0);
Montagne K2 (cp.coordonnees(15,15,15)[0],cp.coordonnees(15,15,15)[1],cp.coordonnees(15,15,15)[2],5,5); /* Pour l'instant la méthode coordonnees appartient à Champ Potentiel qui est notre seule classe avec une boîte, il est donc logique qu'elle soit rattachée à cette classe.
Cependant, par la suite cette méthode pourra être utilisé par d'autre classe avec des boites, elle sera donc déplacée.*/

cp.initialise(20,K2);

cp.affiche();

return 0;
}
