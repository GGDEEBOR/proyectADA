#pragma once
#include <iostream>
#include "vuelos.h"
#include <map>
#include <vector>
#include <string.h>
#include <fstream>
using namespace std;
typedef map<int, vector<int>> MAPA;
MAPA mapa;

void print_graph(ostream& output) {
    output << "digraph {" << endl;
    output << "rankdir = LR" << endl;
    for (auto & vertice: mapa) {
        for (size_t i = 0; i < vertice.second.size(); i++)
        {
            if (vertice.second[i+1] == vertice.second.size())
            {
                output << "[label = " << vertice.second[i+1] << ", weight = " << vertice.second[i+1] << "];" << endl;
                break;
            }
            output << vertice.first << " -> ";
            output << vertice.second[i]; 
            output << "[label = " << vertice.second[i+1] << ", weight = " << vertice.second[i+1] << "];";
            output << endl;
            i++;
        }
        output << endl;
    }
    output << "}";
    // 
}
int main(){
	
    int V, E , origen, destino, distancia, inicio;
    
    cin>>V>>E; // n de vertices y aristas
    
    Vuelos obj(V);	
    
    while(E--){
    	
    	cin>>origen>>destino>>distancia;
        
    	mapa[origen].push_back(destino);
        //string num_str1(to_string(distancia));
        mapa[origen].push_back(distancia);
    	obj.init(origen, destino, distancia);
    	
	}


	cout<<"Punto de inicio: ";
    cin>>inicio;
    
    obj.sistemaVuelo(inicio);
    
    ofstream file("graph.dot");
    print_graph(file);
    return 0;
}
/*
input 
50 56
1 2 113
1 4 258
2 3 102
2 4 94
2 5 102
3 5 212
4 2 102
4 3 214
4 5 30
5 3 212

5 10
1 2 113
1 4 258
2 3 102
2 4 102
2 5 102
3 5 212
4 2 102
4 3 214
4 5 30
5 3 212





Lima-Arequipa=1h55m
Lima-La libertad=1h42m
Lima-Piura=1h49m
Lima-Tacna=2h10m
Lima-Cajamarca=1h24m
Lima-Loreto=1h49m
Lima-San Martin=1h30m
Lima-Madre de Dios=2h2m
Lima-Cuzco=2h16m
Lima-Ayacucho=1h19m

Arequipa-Lima=1h30m
Arequipa-Cuzco=1h5m

Piura-Lima=1h28m

La libertad-Lima=1h31m

Tacna-Lima=2h8m

Cajamarca-Lima=1h24m

Loreto-Lima=1h56m

San Martin-Lima=1h29m

Madre de Dios-Lima=1h54m

Cuzco-Lima=2h45m

dot -Tpdf graph.dot -o graph.pdf
*/


/*
input 2
21 34
1 2 100
1 4 315
2 16 124
3 5 312
3 10 234
4 3 102
4 9 140
5 6 240
5 7 101
6 7 412
7 18 103
7 21 50
8 12 135
8 16 123
8 13 413
9 10 314
9 7 135
10 15 132
11 14 741
11 15 255
12 3 264
12 11 374
13 20 235
15 21 126
15 19 174
16 19 123
16 14 531
16 17 136
16 18 461
19 14 136
21 20 563
17 7 136
18 19 731
20 14 135
*/