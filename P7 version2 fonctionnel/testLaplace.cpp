#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include "ChampPotentiels.h"

using namespace std;

int main() {
    //initialisation des valeurs au loin dans la plaine
    Physique::Parametres simulation (20,284.5,101325);

    ChampPotentiels cp (&simulation, 30,30,30,20.0/29.0);

    array<unsigned int,3>centre={15,15,15};
    Montagne K2 (centre, 5, 5); 
    
    cp.initialise(K2);
    
    // cp.iteration();
    cp.resolution(pow(20.0/29.0, 4)*1e-4);
    // cout<<K2.altitude({14,10});
    ofstream fichier("re.txt");
    cp.affiche(fichier, potentiel, speed);

    fichier.close();
    return 0;
}