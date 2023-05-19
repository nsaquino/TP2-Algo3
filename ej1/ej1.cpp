#include <iostream>
#include <vector>
#include <list>

using namespace std;

vector<list<uint>> adj; //Lista de adyacencias

int main(int argc, char *argv[]){
    int n, m;       //n = cant. vertices
    cin >> n >> m;  //m = cant. aristas

    //Añadir vertices (Init adjacency list)
    adj = vector<list<uint>>(n+1); //El vertice 0 no lo usamos
    for (uint i = 1; i <= n; i++)
        adj[i] = list<uint>(); //Inicializa lista vacía
    
    while (m--) { //Agregamos las aristas
        uint u, v;
        cin >> u >> v; // (u,v) = arista
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    //Debug
    /*
    cout << 0 << ": UNUSED" << endl;
    for (uint i = 1; i < adj.size(); i++){
        cout << i << ": { ";
        list<uint>::iterator it;
        for(it = adj[i].begin(); it != adj[i].end(); it++){
            cout << *it << " ";
        }
        cout << "}" << endl;
    }*/

    //TODO: Resolver el ejercicio T_T

    return 0;
}