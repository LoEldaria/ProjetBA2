#include<iostream>
#include "Montagne.h"

using namespace std;

int main (){
	Montagne everest(15,15,18,5,10);
	array<double ,2> coord({0,0});
	for(unsigned int i(0) ; i<30 ;++i){
		for(unsigned int j(0) ; j<30 ; ++j){
			coord[0]=i;
			coord[1]=j;
			cout<<i<<" "<<j<<" "<<everest.altitude(coord)<<endl;
		}
		cout<<endl;
	}
	
    return 0;
}
