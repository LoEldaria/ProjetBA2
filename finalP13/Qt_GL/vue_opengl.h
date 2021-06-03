#pragma once

#include <QOpenGLShaderProgram> // Classe qui regroupe les fonctions OpenGL liées aux shaders
#include <QMatrix4x4>
#include <random>   //nécessaire pour  std::uniform_real_distribution<> ainsi que std::mt19937
#include "SupportADessin.h"
#include "Vecteur.h"
#include "Systeme.h"
#include "glsphere.h"   //pour le dessin des nuages

class VueOpenGL : public SupportADessin {
 public:
  // méthode(s) de dessin (héritée(s) de SupportADessin)
    virtual void dessine(Systeme const& a_dessiner) override;
    virtual void dessine(Montagne const& a_dessiner) override;
    virtual void dessine(Ciel const& a_dessiner) override;

  // méthodes de (ré-)initialisation
  void init(Vecteur3D = {});
  void initializePosition(Vecteur3D ={});

  // méthode set
  void setProjection(QMatrix4x4 const& projection)
  { prog.setUniformValue("projection", projection); }

  // Méthodes set
  void translate(double x, double y, double z);
  void rotate(double angle, double dir_x, double dir_y, double dir_z);
  
  //si on veut utiliser un vecteur plutôt que des coordonnées
  void translate(QMatrix4x4&, const Vecteur3D&);



private:
  void dessineAxes(QMatrix4x4 const& point_de_vue, bool en_couleur = true);
  void dessineBoite(QMatrix4x4 const& point_de_vue, Systeme const& to_draw);
  void dessineSphere(Vecteur3D, double, bool , Vecteur3D ={0.6,0.6,0.6});
  void dessineSegment(const QMatrix4x4&, Vecteur3D, Vecteur3D, Vecteur3D = {0.8,0.8,0.8});
  void dessineFace(const Vecteur3D &s1, const Vecteur3D &s2, const Vecteur3D &s3, double seuil=4);
  void dessinePluie(const Vecteur3D&, double);

  // Un shader OpenGL encapsulé dans une classe Qt
  QOpenGLShaderProgram prog;
  GLSphere sphere;

  // Caméra: mémorise le point de vue courant
  QMatrix4x4 matrice_vue;

  // information sur la base de la boîte
  Vecteur2D xy;
  double lambda;

  //pour la représentation des ombres propres des montagnes à dessiner
  Vecteur3D soleil;

  //pour la représentation de la pluie et des nuages
  std::uniform_real_distribution<> distribution;
  std::mt19937 gen;
  double random();
};
