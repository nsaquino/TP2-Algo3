#include <iostream>
#include <vector>
#include <algorithm>
#include <bits/stdc++.h>    //sqrt(), pow()

using ll = long long;
using namespace std;

enum state {NO_LO_VI, EMPECE_A_VER, TERMINE_DE_VER};

int N, M;       //n = cant. vertices, m = cant. aristas
vector<vector<int>> adj; //Lista de adyacencias
vector<int> estado;

//*************Encontrar puentes*************
vector<vector<int>> treeEdges;
vector<vector<int>> grafo_sin_puentes;
//vector<vector<int>> bridges;
vector<int> padreEnTree;
vector<int> cant_vertices_en_cc;
vector<ll> backConExtremoInferiorEn;
vector<ll> backConExtremoSuperiorEn;
vector<ll> memo_cubren; //init en -1, para la funcion 'cubren'

void dfs_bridges(int v, int p) {
    estado[v] = EMPECE_A_VER;
    for (int u : adj[v]) {
        if (estado[u] == NO_LO_VI) {
            treeEdges[v].push_back(u);
            padreEnTree[u] = v;
            dfs_bridges(u, v);
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
    res += backConExtremoInferiorEn[v]; //backedge que cubren la arista p-v (con p = padre de v)
    res -= backConExtremoSuperiorEn[v]; //Restamos los backedges de los decendientes de v que "terminan" en v
    for (int hijo : treeEdges[v])       //Backedges de los descendientes de v 
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

    grafo_sin_puentes = vector<vector<int>>(N, vector<int>());
    
    dfs_bridges(r, -1);
    ll cant_puentes = 0;
    for (int v = 0; v < N; v++){
        if (cubren(v) == 0 && v != r){
            cant_puentes++;
        } else if (v != r) {
            int p = padreEnTree[v];
            grafo_sin_puentes[p].push_back(v);
            grafo_sin_puentes[v].push_back(p);
        }
    }
    return cant_puentes;
}
//*************Fin encontrar puentes*************
//*************Contar vertices en cc*************
void dfs_count(int v, int cc) {
    estado[v] = EMPECE_A_VER;
    cant_vertices_en_cc[cc]++;
    for (int u : grafo_sin_puentes[v]) {
        if (estado[u] == NO_LO_VI) {
            dfs_count(u, cc);
        }
    }
    estado[v] = TERMINE_DE_VER;
}

void contar_vertices_en_cc(){
    int cc = 0;
    estado = vector<int>(N, NO_LO_VI);
    
    for (int i = 0; i < N; i++) {
        if (estado[i] == NO_LO_VI) {
            dfs_count(i, cc);
            cc++;
        }
    }
}
//*************Fin contar vertices en cc*************

ll combinatoria_aux(vector<vector<ll>> &dp, ll n, ll k){
    if (n < 0 || k < 0 || k > n) return 0;
    if (k == 0 || k == n) return 1;

    if(dp[n][k] != -1) return dp[n][k];
    dp[n][k] = combinatoria_aux(dp, n-1, k-1) + combinatoria_aux(dp, n-1, k);
    return dp[n][k];
}

ll combinatoria(ll n, ll k) {
    if (n < 0 || k < 0 || k > n) return 0;
    if (k == 0 || k == n) return 1;

    vector<vector<ll>> dp(n+1 ,vector<ll>(k+1, -1));
    return combinatoria_aux(dp, n, k);
}

int main(int argc, char *argv[]){
    cin >> N >> M;  

    //Init adjacency list
    adj = vector<vector<int>>(N, vector<int>());
    while (M--) {
        int u, v;
        cin >> u >> v; // (u,v) = arista
        adj[u-1].push_back(v-1);
        adj[v-1].push_back(u-1);
    }

    int cant_puentes = find_bridges(0);
    cant_vertices_en_cc = vector<int>(cant_puentes + 1, 0);
    contar_vertices_en_cc();
    ll cant_formas_de_jugar = combinatoria(N, 2);

    ll cant_formas_de_ganar = 0;
    ll ver_cc;
    for(int i = 0; i < cant_vertices_en_cc.size(); i++){
        ver_cc = cant_vertices_en_cc[i];
        cant_formas_de_ganar += combinatoria(ver_cc, 2);
    }

    float res = 1.0 - ((1.0*cant_formas_de_ganar)/(1.0*cant_formas_de_jugar));
    
    cout << fixed << setprecision(5); //fixed hace que aparezcan los .00000
    cout << res << endl;    

    return 0;
}