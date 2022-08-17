#include <iostream>
#include <list>
#include <vector>
#include <fstream>
#include <map>
#include <string>
#include <math.h>
#include <queue>
#include <charconv>
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
class Vertex {
    public:
	      V m_Dato;
	      list<Edge<V, E>> member_list_edges;
	      list<Vertex<V, E>> member_list_Vertex_ady;
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
	          m_Dato 			                  = dato;
	          member_pointer_to_next_Vertex = pointer;
	  }
};

template <typename V, typename E>
class Graph{
    private:
	      list<Vertex<V, E>> member_list_of_Vertex;
	      //V origen_ = "A"; // element of type Vertex
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
		        V1.member_list_Vertex_ady.push_back(Vertex<V, E> (V2));
		        mapa[data_vertex1].push_back(data_vertex2);
		        string num_str1(to_string(data_edge));
		        mapa[data_vertex1].push_back(num_str1);
	      }
	  }

	  bool isNumber(const string& str) {
	    for (char const &c : str) 
		    if (std::isdigit(c) == 0) return false;
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
	
    template<typename T>
	  int computeIndexValue(vector<T> vecaux) {
	      int menor = vecaux[0];
        int pos = 0;
        size_t i = 0;
	      for (; i < vecaux.size(); i++) {
		        if (vecaux[i] < menor) {
		            menor = vecaux[i];
                pos = i;

		        }
	      }
	      return pos;
	  }

	  int computeMinValue(vector<int> vecaux) {
	      int menor = vecaux[0];
	      for (size_t i = 0; i < vecaux.size(); i++) {
		        if (menor > vecaux[i]) {
		            menor = vecaux[i];
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

	  bool visitados(vector<string> vect, string element) {
	      for (size_t i = 0; i < vect.size(); i++) {
		        if (vect[i] == element) {
                return true;
            }
	      }
	      return false;
	  }
    
    string peso_entre_vertices(string data_vertex1, string data_vertex2) {
        auto iter = mapa.begin();
        string aux;
        while (iter != mapa.end()) {
            if (mapa.find(data_vertex1) != mapa.end()) {
                if (iter -> first == data_vertex1){
                    for (size_t i = 0; i < iter -> second.size(); i++) {
                        if (iter -> second[i] == data_vertex2){
                            string aux = iter -> second[i + 1];
                            return aux;
                        }
                    }
                    break;
                } else {
                    iter++;
                }
            }
        }
        return aux;
    }

    int pesoENTREvertices(string data_vertex1, string data_vertex2) {
        string result = peso_entre_vertices(data_vertex1, data_vertex2);
        int result_int;
        from_chars(result.c_str(), result.c_str() + result.length(), result_int);
        return result_int;
        

    }

    void print_vector(vector<string> v) {
        for (size_t i = 0; i < v.size(); i++) {
            cout << v[i] << " ";
        }
    }


    vector<string> returned_ady_key(string data_vertex) {
        auto iter = mapa.begin();
        vector<string> vect;
        while (iter != mapa.end()) {
            if (mapa.find(data_vertex) != mapa.end()) {
                if (iter -> first == data_vertex) {
                    for (size_t i = 0; i < iter -> second.size(); i += 2) {
                        vect.push_back(iter -> second[i]);
                    }
                    break;
                } else {
                    iter++;
                }
            } 
        }
        //print_vector(vect);
        return vect;
    }
    
    string Vertice_adyacente_mas_corto(string origen) {
        vector<string> adyacentes_a;
        vector<int> pesos;
        queue<string> u;
        adyacentes_a = returned_ady_key(origen);
        for(size_t i = 0; i < adyacentes_a.size(); i++) {
            int w = pesoENTREvertices(origen, adyacentes_a[i]);
            pesos.push_back(w);
        }
        int indexvalue = computeIndexValue(pesos);
        u.push(adyacentes_a[indexvalue]);
        string aux = u.front();
        /*if (visitados(aux) == true) {
            u.pop(); 
            Vertice_adyacente_mas_corto(origen);
        }*/
        return aux;
    }
    void ruta_mas_corta(string origen, string final) {
        queue<string> Q;
        //Q.push(origen);
        int peso = 0;
        vector<string> visit_vect;
        string u_aux;
        while (origen != final) {
            visit_vect.push_back(origen);
            u_aux = Vertice_adyacente_mas_corto(origen);
            if (visitados(visit_vect, u_aux) == true) {
                visit_vect.push_back(u_aux);
            }
            //cout << "u_aux: "<<u_aux << endl;
            peso = peso + pesoENTREvertices(origen, u_aux);
            //cout << "peso: " << peso;
            origen = u_aux;
            //cout << endl;
            //cout << "nuevo origen: " << origen;
            

        }
        cout << endl;
        cout << "La ruta mas corta es: " << peso << endl;
    }


};


int main() {
    Graph<string, int> graph;
    graph.insertVertex("A");
    graph.insertVertex("B");
    graph.insertVertex("C");
    graph.insertVertex("D");
    graph.insertVertex("E");
    graph.InsertEdge("A", 7, "B");
    graph.InsertEdge("B", 7, "A");
    graph.InsertEdge("B", 5, "C");
    graph.InsertEdge("C", 5, "B");
    graph.InsertEdge("D", 1, "C");
    graph.InsertEdge("C", 1, "D");
    graph.InsertEdge("A", 15, "C");
    graph.InsertEdge("C", 15, "A");
    graph.InsertEdge("D", 3, "E");
    graph.InsertEdge("E", 3, "D");
    graph.InsertEdge("E", 6, "C");
    graph.InsertEdge("C", 6, "E");
    ofstream file("graph.dot");
    graph.print_graph(file);
    cout << endl; 
    cout << "Call to function ruta mas corta entre A y D: " << endl;
    graph.ruta_mas_corta("A", "D");
    cout << "Call to function ruta mas corta entre A y C: " << endl;
    graph.ruta_mas_corta("A", "C");
    return 0;
}
