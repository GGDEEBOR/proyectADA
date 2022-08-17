#pragma once
#include <iostream>
#include "vuelos.h"
using namespace std;

int main(){
	
    int V, E , origen, destino, distancia, inicio;
    
    cin>>V>>E; // n de vertices y aristas
    
    Vuelos obj(V);	
    
    while(E--){
    	
    	cin>>origen>>destino>>distancia;
    	
    	obj.init(origen, destino, distancia);
    	
	}

	cout<<"Punto de inicio: ";
    cin>>inicio;
    
    obj.sistemaVuelo(inicio);
    
    return 0;
}
