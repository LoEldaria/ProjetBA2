#pragma once

#include <QOpenGLShaderProgram> // Classe qui regroupe les fonctions OpenGL liées aux shaders
#include <QMatrix4x4>
#include "SupportADessin.h"
#include "Vecteur.h"
#include "Systeme.h"
#include "glsphere.h"

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
  
  void translate(QMatrix4x4&, const Vecteur3D&);

  // méthode utilitaire offerte pour simplifier
  //void dessineCube(QMatrix4x4 const& point_de_vue = QMatrix4x4() );


private:
  void dessineAxes(QMatrix4x4 const& point_de_vue, bool en_couleur = true);
  void dessineBoite(QMatrix4x4 const& point_de_vue, Systeme const& to_draw);
  void dessineSphere(Vecteur3D, double, bool , Vecteur3D ={0.6,0.6,0.6});
  void dessineSegment(const QMatrix4x4&, Vecteur3D, Vecteur3D, Vecteur3D = {0.8,0.8,0.8});
  void dessineTriangle(const Vecteur3D &s1, const Vecteur3D &s2, const Vecteur3D &s3);

  // Un shader OpenGL encapsulé dans une classe Qt
  QOpenGLShaderProgram prog;
  GLSphere sphere;

  // Caméra: mémorise le point de vue courant
  QMatrix4x4 matrice_vue;

  // information sur la base de la boîte
  Vecteur2D xy;
  double lambda;

};
