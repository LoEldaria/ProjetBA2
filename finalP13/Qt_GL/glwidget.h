#pragma once

#include <QOpenGLWidget>        // Classe pour faire une fenêtre OpenGL
#include <QTime>            // Classe pour gérer le temps
#include "vue_opengl.h"
#include "Systeme.h"

class GLWidget : public QOpenGLWidget
/* La fenêtre hérite de QOpenGLWidget ;
 * les événements (clavier, souris, temps) sont des méthodes virtuelles à redéfinir.
 */
{
public:
  GLWidget(double, double, double,unsigned int, unsigned int, unsigned int, double=1, QWidget* = nullptr);
  virtual ~GLWidget() = default;
  void add(Montagne&);


private:
  // Les 3 méthodes clés de la classe QOpenGLWidget à réimplémenter
  virtual void initializeGL()                  override;
  virtual void resizeGL(int width, int height) override;
  virtual void paintGL()                       override;

  // Méthodes de gestion interne
  void pause();

  // Méthodes de gestion d'évènements
  virtual void keyPressEvent(QKeyEvent* event) override;
  virtual void timerEvent(QTimerEvent* event)  override;
  virtual void mousePressEvent(QMouseEvent* event) override;
  virtual void mouseMoveEvent(QMouseEvent* event)  override;
  virtual void wheelEvent(QWheelEvent* event) override;

  // position de la souris
  QPoint lastMousePosition;

  // Vue : ce qu'il faut donner au contenu pour qu'il puisse se dessiner sur la vue
  VueOpenGL vue;

  // Timer
  int timerId;

  // pour faire évoluer les objets avec le bon "dt"
  QTime chronometre;

  // objets à dessiner, faire évoluer
  Systeme syst;
};
