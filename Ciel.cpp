#include "Ciel.h"

using namespace std;

Ciel::Ciel (SupportADessin* support, const ChampPotentiels& cp, Physique::Parametres* param, bool init_vit): Collection3D<CubedAir>(cp), Dessinable(support)
 {
     for(unsigned int i(0); i<nombre_de_cubes[0];++i){
         for(unsigned int j(0); j<nombre_de_cubes[1];++j){
             for(unsigned int k(0); k<nombre_de_cubes[2];++k){
                 boite[i][j][k] = CubedAir(param, init_vit?cp.vitesse(i,j,k):Vecteur3D(), k*lambda);
             }
         }
     }
 }

Ciel::Ciel (SupportADessin* support, unsigned int i,unsigned int j, unsigned int k, double l, double vit,Physique::Parametres* param):
Collection3D<CubedAir>(i,j,k,l), Dessinable(support)
{   
    for (auto& plan : boite){
        for(auto& vect: plan){
            for(unsigned int k(0); k<nombre_de_cubes[2];++k){
                vect[k]= CubedAir(param, Vecteur3D(vit), k*lambda);
            }
        }
    }
}

void Ciel::affiche_val(ostream& flot)const{
    //i j k V2 h T P Peau Prosee nuage
    for(unsigned int i(0); i<nombre_de_cubes[0];++i){
         for(unsigned int j(0); j<nombre_de_cubes[1];++j){
             for(unsigned int k(0); k<nombre_de_cubes[2];++k){
                 flot<<i<<' '<<j<<' '<<k<<' '<< boite[i][j][k] << endl;
             }
         }
     }
}

void Ciel::update(const ChampPotentiels& cp){
    //i j k V2 h T P Peau Prosee nuage
    for(unsigned int i(0); i<nombre_de_cubes[0];++i){
         for(unsigned int j(0); j<nombre_de_cubes[1];++j){
             for(unsigned int k(0); k<nombre_de_cubes[2];++k){
                 boite[i][j][k].actualise_valeurs(cp.vitesse(i,j,k));
             }
         }
     }
}
void Ciel ::dessine_sur(SupportADessin &support)  {
    support.dessine(*this);
}

Vecteur3D Ciel::precedente(double delta_t, Vecteur3D coord) {
    Vecteur3D deplacement (-delta_t*boite[coord.get_coord(0)][coord.get_coord(1)][coord.get_coord(2)].get_vit()[0],-delta_t*boite[coord.get_coord(0)][coord.get_coord(1)][coord.get_coord(2)].get_vit()[1],-delta_t*boite[coord.get_coord(0)][coord.get_coord(1)][coord.get_coord(2)].get_vit()[2]) ;
    coord+=deplacement;
    return coord;
}

CubedAir Ciel::get_cube(Vecteur3D coord) const {
    return boite[coord.get_coord(0)][coord.get_coord(1)][coord.get_coord(2)];
}
