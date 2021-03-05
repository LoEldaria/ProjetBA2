#include "Vecteur2D.h"
using namespace std;

int main(){
Vecteur2D vect1(1.0, 2.0);
Vecteur2D vect2(2.6, 3.5);
Vecteur2D vect3(vect1);
Vecteur2D vect4;

cout << "Vecteur 1 : " << vect1 << endl;
cout << "Vecteur 2 : " << vect2 << endl;
cout << "Vecteur 3 : " << vect3 << endl;
cout << "Vecteur 4 : " << vect4 << endl;

cout << "Le vecteur 1 est ";
if (vect1==vect2) {
    cout << "égal au";
} else {
    cout << "différent du";
}
cout << " vecteur 2," << endl << "et est ";
if (vect1!=vect3) {
    cout << "différent du";
} else {
    cout << "égal au";
}
cout << " vecteur 3." << endl<<endl;


/*Tests des différents opérateur(en commutant les termes)*/

cout<<"Vecteur1 + Vecteur2 = " << vect1+vect2 <<endl;
cout<<"Vecteur2 + Vecteur1 = " << vect2+vect1 <<endl;
cout<<"Vecteur1 + Vecteur4 = " << vect1+vect4 <<endl;
cout<<"Vecteur4 + Vecteur1 = " << vect4+vect1 <<endl;
cout<<"Vecteur1 - Vecteur2 = " << vect1-vect2 <<endl;
cout<<"Vecteur2 - Vecteur1 = " << vect2-vect1 <<endl;
cout<<"-Vecteur3 = " << -vect3 <<endl;
cout<<"Vecteur3 - Vecteur3 = " << vect3-vect3 <<endl;
cout<<"-Vecteur1 + Vecteur2 = " << (-vect1)+vect2 <<endl;
cout<<"Vecteur1 * Vecteur4 = "<< vect1*vect4 <<endl;
cout<<"3*Vecteur1 = " << 3*vect1 <<endl;
cout<<"Vecteur1 * Vecteur2 = " << vect1*vect2 <<endl;
cout<<"Vecteur2 * Vecteur1 = " << vect2*vect1 <<endl;
cout<<"Vecteur2 * (-Vecteur1) = " << vect2*(-vect1) <<endl;
cout<<"Vecteur unitaire associé au Vecteur2 = " << ~vect2 <<endl;
cout<<"||Vecteur3||^2 = " << vect3.norme2() <<endl;
cout<<"||Vecteur3|| = " << vect3.norme() <<endl;


return 0;

}