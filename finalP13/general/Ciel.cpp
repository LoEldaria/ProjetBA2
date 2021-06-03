#include "Ciel.h"

using namespace std;

Ciel::Ciel (const ChampPotentiels& cp, Physique::Parametres* param, bool init_vit): Collection3D<CubedAir>(cp)
 {
    applique_fonction([&](CubedAir& cba, std::size_t i, std::size_t j, std::size_t k){
        cba = CubedAir(param, init_vit?cp.vitesse(i,j,k):Vecteur3D(), k*lambda);
    });
 }

Ciel::Ciel (std::size_t i, std::size_t j, std::size_t k, double l, double vit,Physique::Parametres* param):
Collection3D<CubedAir>(i,j,k,l)
{   
    applique_fonction([&](CubedAir& cba){
        cba = CubedAir(param, Vecteur3D(vit), k*lambda);
    });
}

void Ciel::affiche_val(ostream& flot)const{
    //i j k V2 h T P Peau Prosee nuage
    applique_fonction([&flot](const CubedAir& cba, std::size_t i, std::size_t j, std::size_t k){
        flot<<i<<' '<<j<<' '<<k<<' '<< cba << endl;
    }, true, true);
}

void Ciel::update(const ChampPotentiels& cp){
    applique_fonction([&cp](CubedAir& cba, std::size_t i, std::size_t j, std::size_t k){
        cba.actualise_valeurs(cp.vitesse(i,j,k));
    });
}

void Ciel ::dessine_sur(SupportADessin &support)  {
    support.dessine(*this);
}



double Ciel::pluie_accumulee(size_t i, size_t j) const{
    double qtt_pluie;
    for(std::size_t k(0);k<nombre_de_cubes[2];++k)
        qtt_pluie += boite[i][j][k].pluie();
    return qtt_pluie;
}

void Ciel::affiche_pluie(ostream& flot)const{
    flot<<"Pluie accumulée: case au sol(i,j) - quantité"<<std::endl;
    double pluie_sol;
    for(std::size_t i(0); i<nombre_de_cubes[0];++i){
        for(std::size_t j(0);j<nombre_de_cubes[1];++j){
            if((pluie_sol=pluie_accumulee(i,j)))
            flot<< i<<' '<<j<<' '<<pluie_sol<<std::endl;
        }
    }
}

bool Ciel::etat_precedent(std::size_t i, std::size_t j, std::size_t k, double delta_t)const{
    Vecteur3D d(delta_t/lambda*boite[i][j][k].get_vit());   //division par lambda pour avoir une dimension d'indices
    if(d[0]>=i or d[1]>=j or d[2]>=k) return false;         //on sortirait de la boîte-> état forcément non nuageux

    //on fait le choix de tronquer les composantes du déplacement pour avoir un déplacment "entier"
    std::size_t ip(i-std::trunc(d[0])), jp(j-std::trunc(d[1])), kp(k-std::trunc(d[2]));
    if(ip>=nombre_de_cubes[0] or jp>=nombre_de_cubes[1] or kp>=nombre_de_cubes[2]) return false;
    return boite[ip][jp][kp].nuage();
}


