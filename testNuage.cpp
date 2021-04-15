#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>

#include "Ciel.h"
// #include "ChampPotentiels.h"
// #include "Constantes.h"


using namespace std;

int main() {

    //initialisation des valeurs au loin dans la plaine
    Physique::Parametres simulation (20,284.5,101325);
    
    array<unsigned int,3>centre={15,15,15};
    Montagne K2 (centre, 5, 5); 

    ChampPotentiels cp (&simulation, 30,30,30,20.0/29.0);
    Ciel sky (cp, &simulation);
    // cout << K2.altitude({3,8}) << endl;
    // cout << K2.altitude({3,9}) << endl;
    // cout << K2.altitude({3,10}) << endl;
    
    cp.initialise(K2);
    // cout << cp.get_potentiel(3,11,1) << endl;
    // cout << cp.get_potentiel(3,10,1) << endl;
    // cout << cp.get_potentiel(3,12,1) << endl;
    // cout << cp.get_potentiel(3,11,0) << endl;
    // cout << cp.get_potentiel(3,11,2) << endl;
    // cout << cp.get_potentiel(2,11,1) << endl;
    // cout << cp.get_potentiel(4,11,1) << endl;

    // cout << cp.calcule_laplacien(3,11,1) << endl;
    cp.resolution(pow(20.0/29.0, 4)*1e-4);
    // cp.iteration();

    ofstream fichier("re2.txt");
    // cp.affiche(fichier, potentiel);

    //pour récupérer les valeurs de sorties; suffit d'enlever les ostream& flot
    
    sky.update(cp);
    sky.affiche_val(fichier);

    fichier.close();
    return 0;
}