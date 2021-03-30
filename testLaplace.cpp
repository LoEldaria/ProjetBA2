
#include "ChampPotentiels.h"
#include "Montagne.h"
#include <cmath>

using namespace std;

int main() {

    ChampPotentiels cp (30,30,30,20.0/29.0);

    array<unsigned int,3>centre={15,15,15};
    Montagne K2 (centre, 5, 5); 
    //cout<<K2.altitude({22,17})<<endl;
    //Montagne K2 (cp.coordonnees(15,15,15)[0],cp.coordonnees(15,15,15)[1],cp.coordonnees(15,15,15)[2],5,5); 
    /* Pour l'instant la méthode coordonnees() appartient à Champ Potentiel qui est notre seule classe avec une boîte, il est donc logique qu'elle soit rattachée à cette classe.
    Cependant, par la suite cette méthode pourra être utilisée par d'autres classee avec des boites, elle sera donc déplacée.*/

    cp.initialise(20,K2);
    // cout << cp.temporaire(22,17,3) << endl;
    // cout << cp.temporaire(22,17,4) << endl;
    // cout << cp.temporaire(22,17,5) << endl;
    // cout << cp.temporaire(22,16,4) << endl;
    // cout << cp.temporaire(22,18,4) << endl;
    // cout << cp.temporaire(21,17,4) << endl;
    // cout << cp.temporaire(23,17,4) << endl<<endl;
    // cout << cp.temporaire(22,17,5) << endl;
    // cout << cp.temporaire(22,17,6) << endl;
    // cout << cp.temporaire(22,17,7) << endl;

    //cp.iteration();
    cp.resolution(pow(20.0/29.0, 4)*1e-4);
    cp.affiche(laplacien);
    //pour stocker les valeurs sur un fichier texte; il suffit d'enlever les ostream& flot dans les méthodes

    // array<unsigned int, 2> t({12,19});
    // cout << "altitude en 11 14 : "<< K2.altitude(t) << endl;
    // cout<<setprecision(13)<<cp.calcule_laplacien(22,17,4)<<endl;
    // cout<<setprecision(13)<<cp.calcule_laplacien(22,17,5)<<endl;
    // cout<<setprecision(13)<<cp.calcule_laplacien(22,17,6)<<endl;
    // cout<<setprecision(13)<<cp.calcule_laplacien(22,17,7)<<endl;
    // cout<<setprecision(13)<<cp.calcule_laplacien(22,17,8)<<endl;
    // cout<<setprecision(13)<<cp.calcule_laplacien(22,17,9)<<endl;
    return 0;
}