#include <QKeyEvent>
#include <QTimerEvent>
#include <QMatrix4x4>
#include "glwidget.h"

//fenêtre sur laquelle on voit scène est un GLWidget
GLWidget::GLWidget(double v, double t, double p,
                   unsigned int i, unsigned int j, unsigned int k, double l, QWidget* parent):
    QOpenGLWidget(parent), syst(v, t, p, i, j ,k, l){}

void GLWidget::add(Montagne& mont){
    syst.ajoute_montagne(mont);
}



// ======================================================================
void GLWidget::initializeGL()
{
  vue.init(syst.get_coord(-1,-1,1));                //initialiser le SupportADessin: shaders et autres
  vue.initializePosition(syst.get_coord(-1,0,-1));  //initialisation du point de vue(position caméra) initial
  timerId = startTimer(20);
  syst.demarre();
}

// ======================================================================
void GLWidget::resizeGL(int width, int height)
{
  /* On commance par dire sur quelle partie de la 
   * fenêtre OpenGL doit dessiner.
   * Ici on lui demande de dessiner sur toute la fenêtre.
   */
  glViewport(0, 0, width, height);

  /* Puis on modifie la matrice de projection du shader.
   * Pour ce faire on crée une matrice identité (constructeur 
   * par défaut), on la multiplie par la droite par une matrice
   * de perspective.
   * Plus de détail sur cette matrice
   *     http://www.songho.ca/opengl/gl_projectionmatrix.html
   * Puis on upload la matrice sur le shader à l'aide de la
   * méthode de la classe VueOpenGL
   */
  QMatrix4x4 matrice;
  matrice.perspective(70.0, qreal(width) / qreal(height ? height : 1.0), 1e-3, 1e5);
  vue.setProjection(matrice);
}

// ======================================================================
void GLWidget::paintGL()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  syst.dessine_sur(vue);
}


// ======================================================================
void GLWidget::keyPressEvent(QKeyEvent* event)
{
  constexpr double petit_angle(5.0); // en degrés
  constexpr double petit_pas(1.0);

  switch (event->key()) {

  case Qt::Key_Left:
    vue.rotate(petit_angle, 0.0, -1.0, 0.0);
    break;

  case Qt::Key_Right:
    vue.rotate(petit_angle, 0.0, +1.0, 0.0);
    break;

  case Qt::Key_Up:
    vue.rotate(petit_angle, -1.0, 0.0, 0.0);
    break;

  case Qt::Key_Down:
    vue.rotate(petit_angle, +1.0, 0.0, 0.0);
    break;

  case Qt::Key_PageUp:
  case Qt::Key_W:
    vue.translate(0.0, 0.0,  petit_pas);
    break;

  case Qt::Key_PageDown:
  case Qt::Key_S:
    vue.translate(0.0, 0.0, -petit_pas);
    break;

  case Qt::Key_A:
    vue.translate( petit_pas, 0.0, 0.0);
    break;

  case Qt::Key_D:
    vue.translate(-petit_pas, 0.0, 0.0);
    break;

  case Qt::Key_R:
    vue.translate(0.0, -petit_pas, 0.0);
    break;

  case Qt::Key_F:
    vue.translate(0.0,  petit_pas, 0.0);
    break;

  case Qt::Key_Q:
    vue.rotate(petit_angle, 0.0, 0.0, -1.0);
    break;

  case Qt::Key_E:
    vue.rotate(petit_angle, 0.0, 0.0, +1.0);
    break;

  case Qt::Key_Home:
    vue.initializePosition(syst.get_coord(-1,0,-1));    //pour se retrouver au point de vue initial
    break;

  case Qt::Key_Space:
	pause();
	break;
  };

  update(); // redessine
}

// ======================================================================
void GLWidget::timerEvent(QTimerEvent* event)
{
  Q_UNUSED(event);

  double dt = chronometre.restart() / 1000.0;
  syst.evolue(dt);
  update();

  //pour voir les différentes étapes du déplacement:
//  pause();
}

// ======================================================================
void GLWidget::pause()
{
  if (timerId == 0) {
	// dans ce cas le timer ne tourne pas alors on le lance
	timerId = startTimer(20);
	chronometre.restart();
  } else {
	// le timer tourne alors on l'arrête
	killTimer(timerId);
	timerId = 0;
  }
}


//========================================================================
void GLWidget::mousePressEvent(QMouseEvent* event)
{
  lastMousePosition = event->pos();

}

void GLWidget::mouseMoveEvent(QMouseEvent* event){

    constexpr double petit_angle(.4); // en degrés


    QPointF d = event->pos() - lastMousePosition;
    lastMousePosition = event->pos();

    switch (event->buttons()) {

      case Qt::MidButton:
        vue.rotate(petit_angle * d.manhattanLength(), d.y(), d.x(), 0); //si clic-molette, modifie l'angle de vue dans la direction du mouvement
        break;

      case Qt::LeftButton:
        if(event->modifiers().testFlag(Qt::ControlModifier)) //si CTRL + clic gauche, modifie l'angle de vue dans la direction du mouvement
            vue.rotate(petit_angle * d.manhattanLength(), d.y(), d.x(), 0);
        else
            vue.translate(d.x()/25, -d.y()/25, 0); //si juste clic gauche, bouge le point de vue dans le plan orthogonal à la direction de la vue
        break;
      };

    update();
}

void GLWidget::wheelEvent(QWheelEvent* event){//la molette permet d'avancer/reculer dans la direction de la vue
    double petit_pas(0.2);
    QOpenGLWidget::wheelEvent(event);
    double numStep(event->angleDelta().y()/120);
    if(event->modifiers().testFlag(Qt::ControlModifier)){petit_pas*=20;}//si CTRL + molette, avance/recule plus vite
    vue.translate(0.0, 0.0, numStep * petit_pas);
    update();
}
