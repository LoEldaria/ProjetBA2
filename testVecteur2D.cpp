#include "Vecteur2D.h"
#include <iostream>
using namespace std;

int main(){
Vecteur2D vect1;
Vecteur2D vect2;
Vecteur2D vect3;

vect1.set_coord(0, 1.0);
vect1.set_coord(1, 2.0);
vect2.set_coord(0, 2.6);
vect2.set_coord(1, 3.5);
vect3 = vect1;

cout << "Vecteur 1 : ";
vect1.affiche();
cout << endl;

cout << "Vecteur 2 : ";
vect2.affiche();
cout << endl;

cout << "Le vecteur 1 est ";
if (vect1.compare(vect2)) {
    cout << "égal au";
} else {
    cout << "différent du";
}
cout << " vecteur 2," << endl << "et est ";
if (not vect1.compare(vect3)) {
    cout << "différent du";
} else {
    cout << "égal au";
}
cout << " vecteur 3." << endl;


Vecteur2D vect4;
cout<<'(';
vect1.affiche();
cout<<") + (";
vect2.affiche();
cout<<") = (";
vect4=vect1.addition(vect2);
vect4.affiche(); cout<<')'<<endl;

cout<<'(';
vect2.affiche();
cout<<") + (";
vect1.affiche();
cout<<") = (";
vect4=vect2.addition(vect1);
vect4.affiche(); cout<<')'<<endl;

vect3.set_coord(0,0);
vect3.set_coord(1,0);
cout<<'(';
vect1.affiche();
cout<<") + (";
vect3.affiche();
cout<<") = (";
vect4=vect1.addition(vect3);
vect4.affiche(); cout<<')'<<endl;

cout<<'(';
vect1.affiche();
cout<<") - (";
vect2.affiche();
cout<<") = (";
vect4=vect1.soustraction(vect2);
vect4.affiche(); cout<<')'<<endl;

cout<<'(';
vect2.affiche();
cout<<") - (";
vect2.affiche();
cout<<") = (";
vect4=vect2.addition(vect2.oppose());
vect4.affiche(); cout<<')'<<endl;

cout<<"-(";
vect1.affiche();
cout<<") = (";
vect4=vect1.oppose();
vect4.affiche();cout<<')'<<endl;

cout<<"3*(";
vect1.affiche();
cout<<") = (";
vect4=vect1.mult(3);
vect4.affiche(); cout<<')'<<endl;

cout<<'(';
vect1.affiche();
cout<<") * (";
vect2.affiche();
cout<<") = ("<<vect1.prod_scal(vect2)<<')'<<endl;

cout<<'(';
vect2.affiche();
cout<<") * (";
vect1.affiche();
cout<<") = ("<< vect2.prod_scal(vect1)<<')'<<endl;

cout<<"||";
vect1.affiche();
cout<< "||^2 ="<<vect1.norme2()<<endl;

cout<<"||";
vect2.affiche();
cout<<"|| = "<< vect2.norme()<<endl;



return 0;

}
