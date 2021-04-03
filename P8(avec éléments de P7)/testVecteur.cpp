#include "Vecteur.h"
using namespace std;

int main(){
	// test Vecteur2D
	Vecteur2D vect1(1.0, 2.0);
	Vecteur2D vect2(2.6, 3.5);
	Vecteur2D vect3(vect1);
	Vecteur2D vect4;
	Vecteur2D vect5({3.14,2.72});

	cout << "Vecteur 1 : " << vect1 << endl;
	cout << "Vecteur 2 : " << vect2 << endl;
	cout << "Vecteur 3 : " << vect3 << endl;
	cout << "Vecteur 4 : " << vect4 << endl;
	cout << "Vecteur 4 : " << vect5 << endl;

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


	//test Vecteur<N>
	Vecteur<5> v1;
	cout << v1 << endl;
    Vecteur<5> v2({1,2,3,4,5});
    Vecteur<5> v3({3,6,9,12,15});
	cout << "v2 = " << v2 << endl;
	cout << "v3 = " << v3 << endl;
    cout << "-v3 = " << -v3 << endl;
    cout << "v2 + v3 = " << v2 + v3 << endl;
    cout << "v2 * v3 = " << v2 * v3 << endl;
    cout << "v2 - v3 = " << v2 - v3 << endl;
	cout << "||v2 - v3|| = " << (v2 - v3).norme() << endl;
	cout << "0.8*v2 = " << 0.8*v2 << endl;
	cout << "v2[3] = " << v2.get_array()[3] << endl;
	cout << "v2[3] = " << v2[3] << endl;
	cout << "v2[3] = " << v2.get_coord(3) << endl;
	cout << "||v2|| = " << v2.norme2() << endl;
	cout << "||v2|| = " << v2.norme() << endl;

	// test Vecteur3D
	// Vecteur3D v4(3,-4,5), v5(-2,3,3.8);
	// cout << "v4 = " << v4 << endl;
	// cout << "v5 = " << v5 << endl;
	// cout << "v4^v5 = " << (v4^v5) << endl;
	// cout << (v4==v4) << endl;
	// cout << "4*Vecteur3D(1,2,3) = " << 4*Vecteur3D(1,2,3) << endl;
	// cout << "Vecteur3D(4,2,8)/2 = " << Vecteur3D(4,2,8)/2 << endl;
	// cout << "Vecteur3D(4,2,8)/2 = " << test(2) << endl;
    return 0;
}
