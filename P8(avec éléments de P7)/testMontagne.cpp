#include<iostream>
#include "Montagne.h"

using namespace std;

int main (){
	Montagne everest({15,15,18},5,10);
	for(unsigned int i(0) ; i<30 ;++i){
		for(unsigned int j(0) ; j<30 ; ++j){
			cout<<i<<" "<<j<<" "<<everest.altitude({i,j})<<endl;
		}
		cout<<endl;
	}
	
    return 0;
}
