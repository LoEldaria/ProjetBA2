#pragma once

#include <vector>
#include "Vecteur.h"
#include <iostream>

template<class T>
class Collection3D{
protected:
	std::array<unsigned int,3> nombre_de_cubes;
    double lambda;
    std::vector<std::vector<std::vector<T>>> boite;

public:
    Collection3D(unsigned int i=0, unsigned int j=0, unsigned int k=0, double l=1): nombre_de_cubes({i,j,k}),
    lambda(l), boite(std::vector<std::vector<std::vector<T>>>(i,std::vector<std::vector<T>>(j, std::vector<T>(k, T()))))
    {}

    template<class T2>
    Collection3D(const Collection3D<T2>& autre): nombre_de_cubes(autre.get_nbrcube()), lambda(autre.get_lambda()), 
    boite(std::vector<std::vector<std::vector<T>>>(nombre_de_cubes[0],std::vector<std::vector<T>>(nombre_de_cubes[1], std::vector<T>(nombre_de_cubes[2], T()))))
    {}

    Vecteur3D Longueur() const{
        return lambda*(Vecteur3D(nombre_de_cubes)-Vecteur3D(1,1,1));
    }

    Vecteur3D coordonnees(unsigned int i, unsigned int j, unsigned int k) const{
    	if(i>=nombre_de_cubes[0] or j>=nombre_de_cubes[1] or k>=nombre_de_cubes[2]){
    		std::cout<<"Votre bloc est hors du monde la valeur va être mise à zero"<<std::endl;
    		return Vecteur3D();
    	}
    	return lambda*Vecteur3D(i,j,k)-Vecteur3D(0,Longueur()[1]/2,0);
    }
    
    std::array<unsigned int,3> get_nbrcube()const{return nombre_de_cubes;}
    double get_lambda()const{return lambda;}
    std::vector<std::vector<std::vector<T>>> get_boite() const {
        return boite;
    }

    bool dans_la_boite (Vecteur3D coord) const;
};

template<class T>
bool Collection3D<T>::dans_la_boite(Vecteur3D coord) const {
    return (coord.get_coord(0)<nombre_de_cubes[0] and coord.get_coord(1)<nombre_de_cubes[1] and coord.get_coord(2)<nombre_de_cubes[2]);
}


