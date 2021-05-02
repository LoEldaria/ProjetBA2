#include "vue_opengl.h"
#include "vertex_shader.h" // Identifiants Qt de nos différents attributs
#include "Systeme.h"



void VueOpenGL::dessine(Systeme const& a_dessiner){

    glClearColor(1, 1, 1, 1); //fond blanc
    /*quand on appelle cette méthode avec dessine_sur() dans demarre() de systeme,
    on a normalement que la résolution de laplace et donc l'updste du ciel sont déjà fait */
    QMatrix4x4 matrice;

    dessineAxes(matrice,true);// dessine le repère principal
    dessineBoite(matrice, a_dessiner);
    dessine(a_dessiner.get_ciel());
    dessine(a_dessiner.get_mont());
    //a_dessiner.get_ciel().dessine_sur(*this);
}

void VueOpenGL::dessine(const Montagne &a_dessiner){
//    for(double x(0); x<=xy[0]; x+=lambda){
//        for(double y(-xy[1]); y<=xy[1]; y+=lambda){
//            dessineSphere({x,y,a_dessiner.altitude({x,y+xy[1]})}, 0.2, true, {0,0,0});
//        }
//    }
    Vecteur3D   base_diag1(lambda, lambda, 0),
                base_diag2(lambda, -lambda, 0);

    for(double x(0); x<=xy[0]; x+=lambda){
        for(double y(-xy[1]); y<=xy[1]; y+=lambda){
            Vecteur3D   p1(x,y,a_dessiner.altitude({x,y+xy[1]})),
                        p2(x+lambda,y,a_dessiner.altitude({x+lambda,y+xy[1]})),
                        p3(x,y+lambda,a_dessiner.altitude({x,y+lambda+xy[1]})),
                        p4(x+lambda,y+lambda,a_dessiner.altitude({x+lambda,y+lambda+xy[1]})),
                        diag1 = ~(p1 - p4),
                        diag2 = ~(p2 - p3);
            if(std::abs(base_diag1 * diag1) >= std::abs(base_diag2 * diag2)){
                dessineTriangle(p1,p2,p4);
                dessineTriangle(p1,p4,p3);
            }
            else{
                dessineTriangle(p1,p2,p3);
                dessineTriangle(p3,p2,p4);
            }
        }
    }
}

void VueOpenGL::dessine(Ciel const& a_dessiner){
    a_dessiner.applique_fonction([&](const CubedAir& cba, std::size_t i, std::size_t j, std::size_t k){
        if(cba.nuage()) dessineSphere(a_dessiner.coordonnees(i,j,k), (2./3)*(a_dessiner.get_lambda()),false);
    });
}


// ======================================================================
void VueOpenGL::init(Vecteur3D sommet_boite)
{
  /* Initialise notre vue OpenGL.
   * Dans cet exemple, nous créons et activons notre shader.
   *
   * En raison du contenu des fichiers *.glsl, le shader de cet exemple
   * NE permet QUE de dessiner des primitives colorées
   * (pas de textures, brouillard, reflets de la lumière ou autres).
   *
   * Il est séparé en deux parties VERTEX et FRAGMENT.
   * Le VERTEX :
   * - récupère pour chaque sommet des primitives de couleur (dans
   *     l'attribut couleur) et de position (dans l'attribut sommet)
   * - multiplie l'attribut sommet par les matrices 'vue_modele' et
   *     'projection' et donne le résultat à OpenGL
   *   - passe la couleur au shader FRAGMENT.
   *
   * Le FRAGMENT :
   *   - applique la couleur qu'on lui donne
   */

  prog.addShaderFromSourceFile(QOpenGLShader::Vertex,   ":/vertex_shader.glsl");
  prog.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fragment_shader.glsl");

  /* Identifie les deux attributs du shader de cet exemple
   * (voir vertex_shader.glsl).
   *
   * L'attribut identifié par 0 est particulier, il permet d'envoyer un
   * nouveau "point" à OpenGL
   *
   * C'est pourquoi il devra obligatoirement être spécifié et en dernier
   * (après la couleur dans cet exemple, voir plus bas).
   */

  prog.bindAttributeLocation("sommet",  SommetId);
  prog.bindAttributeLocation("couleur", CouleurId);

  // Activation du shader
  prog.bind();

  /* Activation du "Test de profondeur" et du "Back-face culling"
   * Le Test de profondeur permet de dessiner un objet à l'arrière-plan
   * partielement caché par d'autres objets.
   *
   * Le Back-face culling consiste à ne dessiner que les face avec ordre
   * de déclaration dans le sens trigonométrique.
   */
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);

  sphere.initialize();
  xy = {sommet_boite[0], sommet_boite[1]};
  lambda = sommet_boite[2];
  initializePosition({xy[0], 0, xy[0]});
}

// ======================================================================
void VueOpenGL::initializePosition(Vecteur3D sb)
{
  // position initiale
  matrice_vue.setToIdentity();
  translate(-sb[0],-sb[1],-sb[2]);
  rotate(-30.0, 0.0, 0.0, 1.0);
  rotate(-70.0, 1.0, 0.0, 0.0);
  translate(0,sb.norme()/4,-sb.norme()/3); //point de vue adapté à la taille de la boite
}

// ======================================================================
void VueOpenGL::translate(double x, double y, double z)
{
  /* Multiplie la matrice de vue par LA GAUCHE.
   * Cela fait en sorte que la dernière modification apportée
   * à la matrice soit appliquée en dernier (composition de fonctions).
   */
  QMatrix4x4 translation_supplementaire;
  translation_supplementaire.translate(x, y, z);
  matrice_vue = translation_supplementaire * matrice_vue;
}

// ======================================================================
void VueOpenGL::rotate(double angle, double dir_x, double dir_y, double dir_z)
{
  // Multiplie la matrice de vue par LA GAUCHE
  QMatrix4x4 rotation_supplementaire;
  rotation_supplementaire.rotate(angle, dir_x, dir_y, dir_z);
  matrice_vue = rotation_supplementaire * matrice_vue;
}

void VueOpenGL::translate(QMatrix4x4 & matrice, const Vecteur3D & v)
{
    matrice.translate(v[0],v[1],v[2]);
}




//=======================================================================

void VueOpenGL::dessineAxes (QMatrix4x4 const& point_de_vue, bool en_couleur)
{
  prog.setUniformValue("vue_modele", matrice_vue * point_de_vue);
  //matrice_vue=matrice de point de vue, qui a en mémoire le point de vue courant

  glBegin(GL_LINES);

  // axe X
  if (en_couleur) {
    prog.setAttributeValue(CouleurId, 1.0, 0.0, 0.0); // rouge
  } else {
    prog.setAttributeValue(CouleurId, 1.0, 1.0, 1.0); // blanc
  }
  prog.setAttributeValue(SommetId, 0.0, 0.0, 0.0);
  prog.setAttributeValue(SommetId, 10.0, 0.0, 0.0); //on veut des axes assez grands

  // axe Y
  if (en_couleur) prog.setAttributeValue(CouleurId, 0.0, 1.0, 0.0); // vert
  prog.setAttributeValue(SommetId, 0.0, 0.0, 0.0);
  prog.setAttributeValue(SommetId, 0.0, 10.0, 0.0);

  // axe Z
  if (en_couleur) prog.setAttributeValue(CouleurId, 0.0, 0.0, 1.0); // bleu
  prog.setAttributeValue(SommetId, 0.0, 0.0, 0.0);
  prog.setAttributeValue(SommetId, 0.0, 0.0, 10.0);

  glEnd();
}

void VueOpenGL::dessineBoite(QMatrix4x4 const& point_de_vue, Systeme const& syst){

    dessineSegment(point_de_vue, syst.get_coord(0,0,0), syst.get_coord(-1,0,0));
    dessineSegment(point_de_vue, syst.get_coord(0,0,0), syst.get_coord(0,-1,0));
    dessineSegment(point_de_vue, syst.get_coord(0,0,0), syst.get_coord(0,0,-1));
    dessineSegment(point_de_vue, syst.get_coord(0,-1,-1), syst.get_coord(-1,-1,-1));
    dessineSegment(point_de_vue, syst.get_coord(0,-1,-1), syst.get_coord(0,0,-1));
    dessineSegment(point_de_vue, syst.get_coord(0,-1,-1), syst.get_coord(0,-1,0));
    dessineSegment(point_de_vue, syst.get_coord(-1,-1,0), syst.get_coord(0,-1,0));
    dessineSegment(point_de_vue, syst.get_coord(-1,-1,0), syst.get_coord(-1,0,0));
    dessineSegment(point_de_vue, syst.get_coord(-1,-1,0), syst.get_coord(-1,-1,-1));
    dessineSegment(point_de_vue, syst.get_coord(-1,0,-1), syst.get_coord(0,0,-1));
    dessineSegment(point_de_vue, syst.get_coord(-1,0,-1), syst.get_coord(-1,-1,-1));
    dessineSegment(point_de_vue, syst.get_coord(-1,0,-1), syst.get_coord(-1,0,0));

}


void VueOpenGL::dessineSegment (QMatrix4x4 const& point_de_vue, Vecteur3D v1,Vecteur3D v2, Vecteur3D color)
{


  prog.setUniformValue("vue_modele", matrice_vue * point_de_vue);
  glBegin(GL_LINES);
  prog.setAttributeValue(CouleurId, color[0],color[1],color[2]); // gris
  prog.setAttributeValue(SommetId,v1[0] ,v1[1] ,v1[2]);
  prog.setAttributeValue(SommetId,v2[0] ,v2[1] ,v2[2]);
  glEnd();

}

void VueOpenGL::dessineSphere(Vecteur3D centre, double rayon, bool pleine, Vecteur3D color){

  QMatrix4x4 matrice;
  translate(matrice, centre);
  matrice.scale(rayon);

  if(!pleine) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  prog.setUniformValue("vue_modele", matrice_vue * matrice);
  prog.setAttributeValue(CouleurId, color[0], color[1], color[2]);  // met la couleur
  sphere.draw(prog, SommetId);                                      // dessine la sphère

  if(!pleine) glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //on repasse par défaut en fill
}

void VueOpenGL::dessineTriangle(Vecteur3D const& s1, Vecteur3D const& s2, Vecteur3D const& s3){
    QMatrix4x4 point_de_vue;
    prog.setUniformValue("vue_modele", matrice_vue * point_de_vue);

    glBegin(GL_TRIANGLES);

    prog.setAttributeValue(CouleurId, 0.6, 0.3, 0.0);
    prog.setAttributeValue(SommetId,  s1[0], s1[1], s1[2]);

    prog.setAttributeValue(CouleurId, 0.5, 0.4, 0.0);
    prog.setAttributeValue(SommetId,  s2[0], s2[1], s2[2]);

    prog.setAttributeValue(CouleurId, 0.5, 0.3, 0.1);
    prog.setAttributeValue(SommetId,  s3[0], s3[1], s3[2]);
    glEnd();
}



