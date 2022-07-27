#include <iostream>
#include <list>
#include <vector>
#include <fstream>
#include <map>
#include <string>
#include <math.h>
#include <queue>
using namespace std;

template <typename V, typename E>
class Vertex;

template <typename V, typename E>
class Edge;

template <typename V, typename E>
class Graph;

typedef map<string, vector<string>> MAPA;
MAPA mapa;

priority_queue<string> q;
template <typename V, typename E>
class Vertex{
    public:
	V m_Dato;
	list<Edge<V, E>> member_list_edges;
    public:
	// constructor
	Vertex(V dato) {
	    m_Dato = dato;
	}
};

template <typename V, typename E>
class Edge{
    public:
	E m_Dato;
	Vertex<V, E>* member_pointer_to_next_Vertex;
    public:
	// constructor
	Edge(E dato, Vertex<V, E>* pointer = nullptr) {
	    m_Dato 			  = dato;
	    member_pointer_to_next_Vertex = pointer;
	}
};

template <typename V, typename E>
class Graph{
    private:
	list<Vertex<V, E>> member_list_of_Vertex;
	V origen; // element of type Vertex
    public:
	// constructor
	Graph() {}
	
	// function Find Vertex
	bool find_Vertex(V data_vertex) {
	    list<Vertex<string, int>> :: iterator it = member_list_of_Vertex.begin();
	    for (; it != member_list_of_Vertex.end(); it++) 
		if (it -> m_Dato == data_vertex)  return true;
	    return false;

	}

	// function Insert Vertex
	void insertVertex(V data_vertex) {
	    member_list_of_Vertex.push_back(Vertex<V, E> (data_vertex));
	}

	// function Insert Edge
	void InsertEdge(string data_vertex1, int data_edge, string data_vertex2) {
	    Vertex<V, E> V1(data_vertex1);
	    Vertex<V, E> V2(data_vertex2); 

	    if (find_Vertex(data_vertex1) == true && find_Vertex(data_vertex2) == true) {
		V1.member_list_edges.push_back(Edge<V, E> (data_edge, &V2));
		mapa[data_vertex1].push_back(data_vertex2);
		string num_str1(to_string(data_edge));
		mapa[data_vertex1].push_back(num_str1);
	    }
	}
	bool isNumber(const string& str) {
	    for (char const &c : str) {
		if (std::isdigit(c) == 0) return false;
	    }
	    return true;
	}

	void print_graph(ostream& output){
	    output << "graph {" << endl;
	    output << "rankdir = LR" << endl;
	    for (auto &vertice: mapa) {
		for (size_t i = 0; i < vertice.second.size(); i++) {
		    if (isNumber(vertice.second[i]) == true) {
			output << "[label = " << vertice.second[i] <<", weight = " << vertice.second[i] <<"];" << endl;
			continue;
		    }
		    output << vertice.first << "--";
		    output << vertice.second[i];
		}	
		output << endl;
	    }
	    output << "}";
	}
	
	bool visitados(vector<string> vect, string element) {
	    for (size_t i = 0; i < vect.size(); i++) {
		if (vect[i] == element) return true;
	    }
	    return false;
	}
	size_t computeIndexValue(vector<int> vecuax) {
	    int menor = vecuax[0];
	    int pos = 0;
	    size_t i = 1;
	    for (; i < vecuax.size(); i++) {
		if (vecuax[i] < menor) {
		    menor = vecuax[i];
		    pos = i;
		}
	    }
	    return pos;
	}
	int computeMinValue(vector<int> vecuax) {
	    int menor = vecuax[0];
	    for (size_t i = 0; i < vecuax.size(); i++) {
		if (menor > vecuax[i]) {
		    menor = vecuax[i];
		}
	    }
	    return menor;
	}

	template<typename T>
	void print_vector(vector<T> vec) {
	    for (size_t i = 0; i < vec.size(); i++){
		cout << vec[i] << " ";
	    }
	    cout << endl;
	}

	void computeRouteMinimalist(string origen, string fin){
	    int cont = 0;
	    vector<int> vecpesos_aristas;
	    vector<string> vec_vertices;
	    for ( auto & vertice: mapa) {
		
		//while (vertice.first != fin) { 
		    /*for (size_t i = 0; i < vertice.second.size(); i+= 2) {
			if (isNumber(vertice.second[i]) == false) {
			    string valnum = vertice.second[i]; 
			    vec_vertices.push_back(valnum);
			    //continue;
			}*/
			
		    //}
		    //break;

		    for (size_t i = 1; i < vertice.second.size(); i+= 2) {
			if (isNumber(vertice.second[i]) == true) {
			    int valnum = stoi(vertice.second[i]); 
			    vecpesos_aristas.push_back(valnum);
			    //continue;
			}
			
		    }
		    cont += computeMinValue(vecpesos_aristas);
		    
		    int position = computeIndexValue(vecpesos_aristas);
		    cout << "position "<<position << endl;
		    string aux = vertice.second[position*2];
		    //vertice.first = aux;
		    cout << "aux: " << aux << endl;



		    break;
		//}
	    } 



	    print_vector(vecpesos_aristas);
	    print_vector(vec_vertices);
	    cout << endl;
	    cout << computeMinValue(vecpesos_aristas);
	    cout << "La ruta minima es: " << cont << endl;
	    
	}


};


int main() {
    Graph<string, int> graph;
    graph.insertVertex("A");
    graph.insertVertex("B");
    graph.insertVertex("C");
    graph.insertVertex("D");
    graph.insertVertex("E");
    graph.InsertEdge("A", 5, "B");
    graph.InsertEdge("B", 5, "A");
    //graph.InsertEdge("A", 7, "D");
    //graph.InsertEdge("D", 7, "A");
    graph.InsertEdge("B", 10, "C");
    graph.InsertEdge("C", 10, "B");
    graph.InsertEdge("D", 3, "C");
    graph.InsertEdge("C", 3, "D");
    graph.InsertEdge("A", 15, "C");
    graph.InsertEdge("C", 15, "A");
    graph.InsertEdge("B", 5, "D");
    graph.InsertEdge("D", 5, "B");
    graph.InsertEdge("D", 1, "E");
    graph.InsertEdge("E", 1, "D");
    graph.InsertEdge("E", 4, "A");
    graph.InsertEdge("A", 4, "E");
    graph.InsertEdge("E", 6, "C");
    graph.InsertEdge("C", 6, "E");
    ofstream file("graph.dot");
    graph.print_graph(file);
    cout << endl; 
    /*cout << "Call to function Dijkstra: " << endl;
    int result = graph.Dijkstra("C");
    cout << result << endl;
    */
    //graph.computeRouteMinimalist("A", "D");

    return 0;
}
