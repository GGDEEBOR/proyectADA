#pragma once
#include <iostream>
#include "aeropuerto.h"
#include <stdio.h>
#include <vector>
#include <queue>
using namespace std;

class Vuelos{
	
	public:
		vector<Aeropuerto> ady[1000]; 
		int distancia[1000];     
		bool visitado[1000];     
		int previo[1000];         
		int V;
		priority_queue<Aeropuerto, vector<Aeropuerto>, cmp> Q; 
		
		Vuelos(int);
		void init(int, int, int);
		void relajacion(int, int, int);
		void print(int);
		void sistemaVuelo(int);
		
};

Vuelos::Vuelos(int V){
	
	for(int i = 0 ; i <= V ; ++i){
        distancia[i] = INT_MAX;  
        visitado[i] = false; 
        previo[i] = -1;    
    }
    
    this->V = V;
}

void Vuelos::init(int origen, int destino, int distancia){
	
    ady[origen].push_back(Aeropuerto(destino, distancia));
    
}

void Vuelos::relajacion(int actual, int adyacente, int peso){
    
    if(distancia[actual] + peso < distancia[adyacente]){
        distancia[adyacente] = distancia[actual] + peso; 
        previo[adyacente] = actual;                        
        Q.push(Aeropuerto(adyacente, distancia[adyacente]));
    }
    
}

void Vuelos::print(int destino){
    if(previo[destino] != -1) 
        print(previo[destino]);  
    cout<<destino<<" ";        
}

void Vuelos::sistemaVuelo(int inicial){
    
    Q.push(Aeropuerto(inicial, 0)); 
    distancia[inicial] = 0;  
    int actual, adyacente, peso;
    
    
    while(!Q.empty()){                   
        actual = Q.top().destino;           
        cout<<"top:"<<actual<<endl;
        
		Q.pop();                          
        if(visitado[actual]) continue;
        visitado[actual] = true;         

        for(int i = 0; i < ady[actual].size(); ++i){ 
            adyacente = ady[actual][i].destino;  
            peso = ady[actual][i].distancia;       
            if(!visitado[adyacente])    
                relajacion(actual, adyacente, peso); 
        }
    }

    
	int destino;
    cout<<"Punto de destino: ";
    
    cin>>destino;
    
    cout<<"Recorrido final\n";
    print(destino);
   
}

