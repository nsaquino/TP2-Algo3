/*  EC_P - Critical Edges
    https://www.spoj.com/problems/EC_P/

    Pasa el juez de encontrar puentes.
    TODO: Adaptar el algoritmo para el ejercicio 1
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using ll = long long;

enum state {NO_LO_VI, EMPECE_A_VER, TERMINE_DE_VER};
int N, M;       //N = cant. vertices, M = cant. aristas
vector<vector<int>> adj; //Lista de adyacencias
vector<int> estado;

vector<vector<int>> treeEdges;
vector<vector<int>> bridges;
vector<int> padreEnTree;
vector<ll> backConExtremoInferiorEn;
vector<ll> backConExtremoSuperiorEn;
vector<ll> memo_cubren; //init en -1

void dfs(int v, int p) {
    estado[v] = EMPECE_A_VER;
    for (int u : adj[v]) {
        if (estado[u] == NO_LO_VI) {
            treeEdges[v].push_back(u);
            padreEnTree[u] = v;
            dfs(u, v);
        } else if (u != p && estado[u] == EMPECE_A_VER) {
            backConExtremoInferiorEn[v]++;
            backConExtremoSuperiorEn[u]++;
        }
    }
    estado[v] = TERMINE_DE_VER;
}

int cubren(int v) {
    if (memo_cubren[v] != -1) return memo_cubren[v];

    ll res = 0;
    res += backConExtremoInferiorEn[v];
    res -= backConExtremoSuperiorEn[v];
    for (int hijo : treeEdges[v]) 
        res += cubren(hijo);

    memo_cubren[v] = res;
    return res;
}

int find_bridges(int r) { //r = root
    estado = vector<int>(N, NO_LO_VI);
    treeEdges = vector<vector<int>>(N, vector<int>());
    backConExtremoInferiorEn = vector<ll>(N, 0);
    backConExtremoSuperiorEn = vector<ll>(N, 0);
    memo_cubren = vector<ll>(N, -1);
    padreEnTree = vector<int>(N, -1);
    
    dfs(r, -1);
    ll cant_puentes = 0;
    for (int v = 0; v < N; v++){
        if (cubren(v) == 0 && v != r){
            cant_puentes++;
            int p = padreEnTree[v];
            bridges[min(p, v)].push_back(max(p, v));
        }
    }
    return cant_puentes;
}

int main(){
    int NC;
    cin >> NC;
    for (int c = 1; c <= NC; c++) {
        cin >> N >> M;

        //Añadir vertices (Init adjacency list)
        adj = vector<vector<int>>(N, vector<int>()); //Indexado en 0

        while (M--) { //Agregamos las aristas
            int u, v;
            cin >> u >> v; // (u,v) = arista
            adj[u-1].push_back(v-1);
            adj[v-1].push_back(u-1);
        }

        bridges = vector<vector<int>>(N, vector<int>());
        ll cant_puentes = find_bridges(0);
        for (int i = 0; i < N; i++) sort(bridges[i].begin(), bridges[i].end());
        
        cout << "Caso #" << c << endl;
        if (cant_puentes == 0)
            cout << "Sin bloqueos" << endl;
        else {
            cout << cant_puentes << endl;
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < bridges[i].size(); j++) {
                    cout << i+1 << " " << bridges[i][j]+1 << endl;
                }
            }
        }
    }

    return 0;
}