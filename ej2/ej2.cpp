#include <iostream>
#include <vector>
#include <list>

using namespace std;

vector<list<uint>> adj; //Lista de adyacencias

int main(int argc, char *argv[]){
    int n, m;       //n = cant. piezas
    cin >> n >> m;  //m = cant. pares de caída

    //Init adjacency list
    adj = vector<list<uint>>(n + 1); //Piezas de 1 a n
    for (uint i = 1; i <= n; i++)
        adj[i] = list<uint>(); //Inicializa lista vacía
    
    while (m--) { //Agregamos los pares de caída
        uint i, j;
        cin >> i >> j; // (i,j) = par de caída
        adj[i].push_back(j); //Digrafo?
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