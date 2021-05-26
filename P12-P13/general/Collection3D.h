#pragma once

#include <vector>
#include "Vecteur.h"
#include <functional>

template<class T>
class Collection3D{
protected:
	std::array<unsigned int,3> nombre_de_cubes;
    double lambda;
    std::vector<std::vector<std::vector<T>>> boite;

public:
    Collection3D(unsigned int i=0, unsigned int j=0, unsigned int k=0, double l=1): nombre_de_cubes({i,j,k}),
    lambda(l), boite(i,std::vector<std::vector<T>>(j, std::vector<T>(k, T())))
    {}

    template<class T2>
    Collection3D(const Collection3D<T2>& autre): nombre_de_cubes(autre.get_nbrcube()), lambda(autre.get_lambda()), 
    boite(nombre_de_cubes[0],std::vector<std::vector<T>>(nombre_de_cubes[1], std::vector<T>(nombre_de_cubes[2], T())))
    {}

    Vecteur3D Longueur() const{
        return lambda*(Vecteur3D(nombre_de_cubes)-Vecteur3D(1,1,1));
    }

    Vecteur3D coordonnees(unsigned int i, unsigned int j, unsigned int k) const{

        if (i>=nombre_de_cubes[0]) i=nombre_de_cubes[0]-1;
        if (j>=nombre_de_cubes[1]) j=nombre_de_cubes[1]-1;
        if (k>=nombre_de_cubes[2]) k=nombre_de_cubes[2]-1;
            //std::cout<<"Votre bloc est hors du monde la valeur va être mise à zero"<<std::endl;
            //return Vecteur3D();

    	return lambda*Vecteur3D(i,j,k)-Vecteur3D(0,Longueur()[1]/2,0);
    }
    
    std::array<unsigned int,3> get_nbrcube()const{return nombre_de_cubes;}
    double get_lambda()const{return lambda;}


    // pour appliquer une fonction à tous les éléments de la boîte (et qui les modifie) qui dépend de leur position i,j,k
    void applique_fonction(std::function<void(T&, std::size_t,std::size_t,std::size_t)> funct, bool int_fin = false, bool int_deb = false){
        for(std::size_t i(int_deb); i<nombre_de_cubes[0]-int_fin; ++i)
            for(std::size_t j(int_deb); j<nombre_de_cubes[1]-int_fin; ++j)
                for(std::size_t k(int_deb); k<nombre_de_cubes[2]-int_fin; ++k)
                    funct(boite[i][j][k],i,j,k);
    }
    // pareil mais version const, on ne modifie pas les éléments de la boîte
    void applique_fonction(std::function<void(const T&, std::size_t,std::size_t,std::size_t)> funct, bool int_fin = false, bool int_deb = false)const{
        for(std::size_t i(int_deb); i<nombre_de_cubes[0]-int_fin; ++i)
            for(std::size_t j(int_deb); j<nombre_de_cubes[1]-int_fin; ++j)
                for(std::size_t k(int_deb); k<nombre_de_cubes[2]-int_fin; ++k)
                    funct(boite[i][j][k],i,j,k);
    }
    // pour appliquer une fonction à tous les éléments de la boîte (et qui les modifie) qui ne dépend pas de leur position i,j,k
    void applique_fonction(std::function<void(T&)> funct, bool int_fin = false, bool int_deb = false){
        applique_fonction([funct](T& t,std::size_t, std::size_t, std::size_t){funct(t);}, int_fin, int_deb);
    }
    // pareil mais version const, on ne modifie pas les éléments de la boîte
    void applique_fonction(std::function<void(const T&)> funct, bool int_fin = false, bool int_deb = false)const{
        applique_fonction([funct](const T& t,std::size_t, std::size_t, std::size_t){funct(t);}, int_fin, int_deb);
    }

//    bool dans_la_boite (const Vecteur3D& coord) const{
//        return (coord[0]<nombre_de_cubes[0] and coord[1]<nombre_de_cubes[1] and coord[2]<nombre_de_cubes[2]);
//    }
};

