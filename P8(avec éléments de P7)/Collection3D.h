#pragma once

#include <vector>
#include <array>
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

    std::array<double,3> Longueur() const{
        return std::array<double, 3>({
            lambda*(nombre_de_cubes[0]-1),
            lambda*(nombre_de_cubes[1]-1),
            lambda*(nombre_de_cubes[2]-1)
        });
    }
    std::array<double,3> coordonnees(unsigned int i, unsigned int j, unsigned int k) const{
        std::array<double,3> coord;
    	if(i>=nombre_de_cubes[0] or j>=nombre_de_cubes[1] or k>=nombre_de_cubes[2]){
    		std::cout<<"Votre bloc est hors du monde la valeur va être mise à zero"<<std::endl;
    		return coord;
    	}
    	coord[0]=i*lambda;
    	coord[1]=j*lambda-(Longueur()[1]/2);
    	coord[2]=k*lambda;
    	return coord;
    }
    
    std::array<unsigned int,3> get_nbrcube()const{return nombre_de_cubes;}
    double get_lambda()const{return lambda;}
};