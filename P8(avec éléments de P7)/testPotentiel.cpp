#include <iostream>
#include "ChampPotentiels.h"

using namespace std;

int main() {

ChampPotentiels cp (30,30,30,20.0/29.0);
array<double,3>centre={15,15,15};
Montagne K2 (centre, 5, 5, 20.0/29.0); 

//Montagne K2 (cp.coordonnees(15,15,15)[0],cp.coordonnees(15,15,15)[1],cp.coordonnees(15,15,15)[2],5,5); 
/* Pour l'instant la méthode coordonnees() appartient à Champ Potentiel qui est notre seule classe avec une boîte, il est donc logique qu'elle soit rattachée à cette classe.
Cependant, par la suite cette méthode pourra être utilisée par d'autres classee avec des boites, elle sera donc déplacée.*/

cp.initialise(20,K2); // le premier argument est la vitesse du vent aux limites de la boite

cp.affiche(true, false, false);

return 0;
}