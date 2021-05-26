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
    //i j k V2 h T P Peau Prosee nuage
    applique_fonction([&cp](CubedAir& cba, std::size_t i, std::size_t j, std::size_t k){
        cba.actualise_valeurs(cp.vitesse(i,j,k));
    });
}

void Ciel ::dessine_sur(SupportADessin &support)  {
    support.dessine(*this);
}

void Ciel::deplacer_nuages(double delta_t){
//    for(unsigned int i(0) ; i<nombre_de_cubes[0]-1 ; ++i) {
//        for(unsigned int j(0) ; j<nombre_de_cubes[1]-1 ; ++j) {
//            for(unsigned int k(0) ; k<nombre_de_cubes[2]-1; ++k) {
//                bool etat_courant(boite[i][j][k].nuage());
//                Vecteur3D p(precedente(delta_t,i,j,k));
//                if(p[0]>=0 and p[1]>=0 and p[2]>=0 and p[0]<nombre_de_cubes[0] and p[1]<nombre_de_cubes[1] and p[2]<nombre_de_cubes[2]){
//                    std::size_t ip(std::trunc(p[0])), jp(std::trunc(p[1])), kp(std::trunc(p[2]));
//                    if(i!=ip or j!=jp or k!=kp){
//                        bool etat_precedent(boite[ip][jp][kp].nuage());
//                        if(etat_courant and !etat_precedent)
//                            boite[i][j][k].actualise_humidite(-0.017);
//                        else if(!etat_courant and etat_precedent)
//                            boite[i][j][k].actualise_humidite(0.05);
//                    }
//                }
//                else{
//                    if(etat_courant) boite[i][j][k].actualise_humidite(-0.017);
//                }

//              // if(boite[i][j][k].pluie()!=0) boite[i][j][k].actualise_humidite(-5);

//            }
//        }
//    }
    applique_fonction([this, delta_t](CubedAir& cba, std::size_t i, std::size_t j, std::size_t k){
        bool nuage_courant(cba.nuage()), nuage_precedent(etat_precedent(i,j,k,delta_t));
        if(nuage_courant and !nuage_precedent) cba.actualise_humidite(-0.017);
        if(!nuage_courant and nuage_precedent) cba.actualise_humidite(0.05);
        if(cba.pluie()) cba.actualise_humidite(-0.03);
    },true);
}

double Ciel::pluie_accumulee(size_t i, size_t j) const{
    double qtt_pluie;
    for(std::size_t k(0);k<nombre_de_cubes[2];++k)
        qtt_pluie += boite[i][j][k].pluie();
    return qtt_pluie;
}

bool Ciel::etat_precedent(std::size_t i, std::size_t j, std::size_t k, double delta_t)const{
    Vecteur3D d(delta_t/lambda*boite[i][j][k].get_vit());
    if(d[0]>=i or d[1]>=j or d[2]>=k) return false;
    std::size_t ip(i-std::trunc(d[0])), jp(j-std::trunc(d[1])), kp(k-std::trunc(d[2]));
    if(ip>=nombre_de_cubes[0] or jp>=nombre_de_cubes[1] or kp>=nombre_de_cubes[2]) return false;
    return boite[ip][jp][kp].nuage();
}

//Vecteur3D Ciel::precedente(double delta_t, std::size_t i, std::size_t j, std::size_t k) {
//    return Vecteur3D(i,j,k)-delta_t/lambda*boite[i][j][k].get_vit();
//    //return Vecteur3D(i,j,k)-delta_t*boite[i][j][k].get_vit();
//}
