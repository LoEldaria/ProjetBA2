#include "vue_opengl.h"
#include "vertex_shader.h" // Identifiants Qt de nos différents attributs
#include "Systeme.h"
#include <functional>
#include <iomanip>


void VueOpenGL::dessine(Systeme const& a_dessiner){

    glClearColor(0.83, 0.9, 1, 1); //fond bleu ciel
    QMatrix4x4 matrice; //matrice identité

    dessineAxes(matrice,true);// dessine le repère principal
    dessineBoite(matrice, a_dessiner);
    dessine(a_dessiner.get_ciel());
    dessine(a_dessiner.get_mont());
    a_dessiner.affiche_pluie(std::cout);
}

void VueOpenGL::dessine(const Montagne &a_dessiner){
    /*les montagnes sont dessinées ainsi: pour chaque cellule au sol, ses quatres sommets sur la
     * montagne sont à des altitudes potentiellement différentes; on les relie avec deux triangles,dont
     * l'hypothénuse est selon la diagonale de la face ayant la pente la moins prononcée*/

    Vecteur3D   base_diag1(lambda, lambda, 0),
                base_diag2(lambda, -lambda, 0);

    for(double x(0); x<=xy[0]; x+=lambda){
        for(double y(-xy[1]); y<=xy[1]; y+=lambda){
            Vecteur3D   p1(x,y,a_dessiner.altitude({x,y+xy[1]})),   //on utilise la méthode altitude() métrique de Montagne
                        p2(x+lambda,y,a_dessiner.altitude({x+lambda,y+xy[1]})),
                        p3(x,y+lambda,a_dessiner.altitude({x,y+lambda+xy[1]})),
                        p4(x+lambda,y+lambda,a_dessiner.altitude({x+lambda,y+lambda+xy[1]})),
                        diag1 = ~(p1 - p4),
                        diag2 = ~(p2 - p3);
            if(std::abs(base_diag1 * diag1) >= std::abs(base_diag2 * diag2)){
                dessineFace(p1,p2,p4);
                dessineFace(p1,p4,p3);
            }
            else{
                dessineFace(p1,p2,p3);
                dessineFace(p3,p2,p4);
            }
        }
    }
}

void VueOpenGL::dessine(Ciel const& a_dessiner){
    double qte;
    a_dessiner.applique_fonction([&](const CubedAir& cba, std::size_t i, std::size_t j, std::size_t k){
        if(cba.nuage()){
            double couleur = 0.6+random()/8+k/250.;     /*permet de varier aléatoirement la teinte grise des nuages
                                                        de plus, le nuage est plus foncé s'il est à haute altitude*/
            dessineSphere(a_dessiner.coordonnees(i,j,k)+0.5*lambda*Vecteur3D(1), 0.71*lambda, false, couleur*Vecteur3D(1,1,1)); // coordonnees() pour être directement en x,y,z
                           //grâce au contructeur de Vecteur3D, Vecteur3D(1)=(1,0,0)
        }
        if((qte=cba.pluie())){
             dessinePluie(a_dessiner.coordonnees(i,j,k), qte); // coordonnees() pour être directement en x,y,z
        }
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
  lambda = sommet_boite[2]; //1 cube de hauteur correspond à lambda
  soleil = ~Vecteur3D{-1,-1,-1};    //direction de la lumière

  std::random_device rd;            //on initialise notre générateur de nombres aléatoires
  gen = std::mt19937(rd());
  distribution = std::uniform_real_distribution<>(0.,1);
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

    /*on relie les sommets de la boîte en utilisant une astuce (détaillée dans la
     *méthode coordonnes() de Collection3D.h): mettre (-1,-1,-1) nous permet
     *d'atteindre le sommet en (n-1, n-1, n-1) si la boîte est de taille n x n x n
    */

    dessineSegment(point_de_vue, syst.get_coord(0,0,0), syst.get_coord(-1,0,0));
    dessineSegment(point_de_vue, syst.get_coord(0,0,0), syst.get_coord(0,-1,0));
    dessineSegment(point_de_vue, syst.get_coord(0,0,0), syst.get_coord(0,0,-1));
    dessineSegment(point_de_vue, syst.get_coord(0,-1,-1), syst.get_coord(-1,-1,-1));
    dessineSegment(point_de_vue, syst.get_coord(0,-1,-1), syst.get_coord(0,0,-1));
    dessineSegment(point_de_vue, syst.get_coord(0,-1,-1), syst.get_coord(0,-1,0));
    dessineSegment(point_de_vue, syst.get_coord(-1,0,-1), syst.get_coord(0,0,-1));
    dessineSegment(point_de_vue, syst.get_coord(-1,0,-1), syst.get_coord(-1,-1,-1));
    dessineSegment(point_de_vue, syst.get_coord(-1,0,-1), syst.get_coord(-1,0,0));
    dessineSegment(point_de_vue, syst.get_coord(-1,-1,0), syst.get_coord(0,-1,0));
    dessineSegment(point_de_vue, syst.get_coord(-1,-1,0), syst.get_coord(-1,0,0));
    dessineSegment(point_de_vue, syst.get_coord(-1,-1,0), syst.get_coord(-1,-1,-1));

}


void VueOpenGL::dessineSegment (QMatrix4x4 const& point_de_vue, Vecteur3D v1,Vecteur3D v2, Vecteur3D color)
{
  prog.setUniformValue("vue_modele", matrice_vue * point_de_vue);
  glBegin(GL_LINES);
  prog.setAttributeValue(CouleurId, color[0],color[1],color[2]); // gris par défaut
  prog.setAttributeValue(SommetId,v1[0] ,v1[1] ,v1[2]);
  prog.setAttributeValue(SommetId,v2[0] ,v2[1] ,v2[2]);
  glEnd();

}

void VueOpenGL::dessineSphere(Vecteur3D centre, double rayon, bool pleine, Vecteur3D color){

  QMatrix4x4 matrice;
  translate(matrice, centre);       //positionne la sphère
  matrice.scale(rayon);             //pour que la sphère ait le bon rayon

  if(!pleine) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);            //effet fil de fer
  prog.setUniformValue("vue_modele", matrice_vue * matrice);
  prog.setAttributeValue(CouleurId, color[0], color[1], color[2]);  // met la couleur
  sphere.draw(prog, SommetId);                                      // dessine la sphère

  if(!pleine) glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);        //on repasse par défaut en fill
}

void VueOpenGL::dessineFace(Vecteur3D const& s1, Vecteur3D const& s2, Vecteur3D const& s3, double seuil){

    //pour les ombres propres
    Vecteur3D ortho((s2-s1)^(s3-s1));   //nous donne le vecteur orthogonal à la face triangulaire
    double lum(0.6-(~ortho)*soleil/2);  /*soleil agit comme un rayon de lumière; le produit scalaire
                                          avec le vecteur précédent donne une information sur l'éclairement
                                          de la face (négatif: face devant le soleil; positif: face opposée)*/

    Vecteur3D green{0.13, 0.54, 0.13}, brown{0.5, 0.3, 0.2};    //couleur des montagnes

    QMatrix4x4 point_de_vue;
    prog.setUniformValue("vue_modele", matrice_vue * point_de_vue);
    Vecteur3D c1 = lum*(s1[2]>seuil?brown:green),       //la couleur des faces à dessiner varie selon leur hauteur
              c2 = lum*(s2[2]>seuil?brown:green),       //lum ajuste la couleur selon l'ensoleillement
              c3 = lum*(s3[2]>seuil?brown:green);
    glBegin(GL_TRIANGLES);

    prog.setAttributeValue(CouleurId, c1[0], c1[1], c1[2]);
    prog.setAttributeValue(SommetId,  s1[0], s1[1], s1[2]);

    prog.setAttributeValue(CouleurId, c2[0], c2[1], c2[2]);
    prog.setAttributeValue(SommetId,  s2[0], s2[1], s2[2]);

    prog.setAttributeValue(CouleurId, c3[0], c3[1], c3[2]);
    prog.setAttributeValue(SommetId,  s3[0], s3[1], s3[2]);
    glEnd();
}
/*c1 = lum*(s1[2]>seuil?Vecteur3D{0.6, 0.3, 0.0}:Vecteur3D{0.13, 0.54, 0.13}),
  c2 = lum*(s2[2]>seuil?Vecteur3D{0.5, 0.4, 0.0}:Vecteur3D{0.137, 0.51, 0.13}),
  c3 = lum*(s3[2]>seuil?Vecteur3D{0.5, 0.3, 0.1}:Vecteur3D{0.17, 0.64, 0.16});
  pour avoir des variations de couleurs plus prononcées
*/

void VueOpenGL::dessinePluie(const Vecteur3D & c, double qte){
    QMatrix4x4 point_de_vue;
    int n(floor(sqrt(qte*0.5 -5)));     //renvoie un entier, proportionnel à la quantité de pluie qui tombe
    for(int i(0);i<n;++i){
        Vecteur3D r(random(),random());
        dessineSegment(point_de_vue, c + lambda*r, Vecteur3D(c[0], c[1])+lambda*r, {0.33, 0.69, 0.84});
    }
    //on dessine un trait (bleu), partant d'une position aléatoire dans la cellule où se trouve le nuage, jusqu'au sol
}

//renvoie un nombre aléatoire entre 0 et 1
double VueOpenGL::random(){
    return distribution(gen);
}
