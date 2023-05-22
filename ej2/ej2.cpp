#include <iostream>
#include <vector>
#include <list>
#include <stack>

using namespace std;

int n, m;       //n = cant. piezas
vector<list<int>> D; //Lista de adyacencias
vector<list<int>> D_T; //Grafo D con aristas invertidas

enum {BLANCO, GRIS, NEGRO};
vector<int> color;
stack<int> S;

void dfs1(int u){
    color[u] = GRIS;
    for (list<int>::iterator it = D[u].begin(); it != D[u].end(); it++)
    {
        int v = *it;
        if (color[v] == BLANCO)
            dfs1(v);
    }
    color[u] = NEGRO;
    S.push(u);
}

void dfs2(int u){
    color[u] = GRIS;
    for (list<int>::iterator it = D_T[u].begin(); it != D_T[u].end(); it++)
    {
        int v = *it;
        if (color[v] == BLANCO)
            dfs2(v);
    }
    color[u] = NEGRO;
}

int kosaraju(){
    //Paso 1
    color = vector<int>(n, BLANCO);
    for (int i = 0; i < n; i++) {
        if (color[i] == BLANCO) {
            dfs1(i);
        }
    }
    //Paso 2
    int cc = 0;
    color = vector<int>(n, BLANCO);
    while (!S.empty())
    {
        int u = S.top(); S.pop();
        if (color[u] == BLANCO) {
            dfs2(u);
            cc++;
        }
    }
    return cc;
}

int main(int argc, char *argv[]){
    cin >> n >> m;  //m = cant. pares de caída

    //Init adjacency list
    D = vector<list<int>>(n); //Piezas de 0 a n-1
    D_T = vector<list<int>>(n); 
    for (int i = 0; i < n; i++){
        D[i] = list<int>(); //Inicializa lista vacía
        D_T[i] = list<int>(); //Inicializa lista vacía
    }

    while (m--) { //Agregamos los pares de caída
        int i, j;
        cin >> i >> j; // (i,j) = par de caída
        D[i].push_back(j);  //Digrafo
        D_T[j].push_back(i);//Digrafo al revés
    }

    //Debug
    /*
    for (int i = 0; i < D.size(); i++){
        cout << i + 1 << ": { ";
        list<int>::iterator it;
        for(it = D[i].begin(); it != D[i].end(); it++){
            cout << (*it) + 1 << " ";
        }
        cout << "}" << endl;
    }*/

    kosaraju();

    return 0;
}