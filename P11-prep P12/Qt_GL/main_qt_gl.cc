#include <QApplication>
#include "glwidget.h"

int main(int argc, char* argv[])
{
  QApplication a(argc, argv);
  GLWidget w(20,284.5,101325, 30,30,30,20.0/29.0);
  MontGaussienne mont({15,15,15},5,5, 20.0/29.0);

  w.add(mont);
  w.show();

  return a.exec();
}
