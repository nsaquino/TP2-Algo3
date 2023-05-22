#include <iostream>
#include <vector>
#include <list>
#include <stack>

using namespace std;

int n, m;               //n = cant. piezas
vector<list<int>> D;    //Lista de adyacencias
vector<list<int>> D_T;  //Grafo D con aristas invertidas
vector<int> cfc;        //Representantes de los cfc
vector<int> cfc_D;      //Grafo de cfc
int tam_cfc;

enum {BLANCO, GRIS, NEGRO};
vector<bool> visitado;
stack<int> S;

void dfs1(int u){
    visitado[u] = true;
    for (list<int>::iterator it = D[u].begin(); it != D[u].end(); it++)
    {
        int v = *it;
        if (!visitado[v])
            dfs1(v);
    }
    S.push(u);
}

void dfs2(int u, int representante){
    visitado[u] = true;
    for (list<int>::iterator it = D_T[u].begin(); it != D_T[u].end(); it++)
    {
        int v = *it;
        if (!visitado[v])
            dfs2(v, representante);
    }
    cfc[u] = representante;
}

void kosaraju(){
    //Paso 1
    visitado = vector<bool>(n, false);
    for (int i = 0; i < n; i++) {
        if (!visitado[i]) {
            dfs1(i);
        }
    }
    //Paso 2
    int cc = 0;
    cfc = vector<int>(n); //Vamos a decir a que cfc pertenece cada nodo
    visitado = vector<bool>(n, false);
    while (!S.empty())
    {
        int u = S.top(); S.pop();
        if (!visitado[u]) {
            cfc_D.push_back(u); //Para armar el digrafo nuevo
            dfs2(u, u); //El nodo popeado (Que aun no se visito) es el representante
            cc++;
        }
    }
    tam_cfc = cc;
}

void dfs_topo(int u, vector<int> &top_sorted, int &orden){
    visitado[u] = true;
    S.push(u);
    for (list<int>::iterator it = D[u].begin(); it != D[u].end(); it++)
    {
        int v = *it;        
        if (!visitado[v] && cfc[v] != v)    //si no fue visit, y no toque su cfc, le aplico dfs_topo
            dfs_topo(v, top_sorted, orden);
    }
    top_sorted[orden] = S.top();
    S.pop();
    orden--;
}

void topological_sort(){
    //Stack esta vacio al iniciar
    visitado = vector<bool>(n, false);
    vector<int> top_sorted(tam_cfc);
    int orden = tam_cfc - 1;
    for (int i = 0; i < tam_cfc; i++) {
        if (!visitado[cfc_D[i]]) {
            dfs_topo(cfc_D[i], top_sorted, orden);
        }
    }
    cfc_D = top_sorted; //cfc_D está ordenado topologicamente
}



vector<bool> visited;
vector<int> res_temp;

void dfs_sorted(int u){
    visited[u] = true;
    for (list<int>::iterator it = D[u].begin(); it != D[u].end(); it++)
    {
        int v = *it;        
        if (!visitado[v])
            dfs_sorted(v);
    }
}

void last_dfs(){
    visited = vector<bool>(n,false);
    for(int i = 0; i < cfc_D.size(); i++){
            if(visited[i]!=true){                
                dfs_sorted(i);
                res_temp.push_back(i);
        }
    }
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
    topological_sort();

    vector<int> res;
    last_dfs();

    //Imprimir tamaño de res_temp
    cout << res_temp.size() << endl;
    //Imprimir de a 1 los elementos de res_temp
    for (int i = 0; i < res_temp.size(); i++){
        cout << res_temp[i] + 1;
    }
    cout << endl;

    return 0;
}