#pragma once
#include <iostream>

class Aeropuerto{
	
	public:

		int destino;
		int distancia;
		
		Aeropuerto(){};
		Aeropuerto(int, int);
};

Aeropuerto::Aeropuerto(int destino, int distancia){
	
	this->destino = destino;
	this->distancia = distancia;

}

struct cmp {
    bool operator() ( const Aeropuerto &a , const Aeropuerto &b ) {
        return a.distancia > b.distancia;
    }
};
