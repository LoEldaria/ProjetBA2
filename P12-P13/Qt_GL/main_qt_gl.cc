#include <QApplication>
#include "glwidget.h"
#include "ChaineDeMontagnes.h"
#include "MontGaussienne.h"

int main(int argc, char* argv[])
{
  QApplication a(argc, argv);
  GLWidget w(20,284.5,101325, 30,30,30,20.0/29.0);
  MontGaussienne mont({15,15,15},5,5);
  MontGaussienne mont2({22,22,20},3,3);
  ChaineDeMontagnes chaine;
  chaine.ajoute_montagne(mont);
  chaine.ajoute_montagne(mont2);
  MontGaussienne mont3({7,6,8},2,2);

  w.add(mont);
  //w.add(mont2);
  w.add(mont3);
  w.add(chaine);
  w.show();

  return a.exec();
}
