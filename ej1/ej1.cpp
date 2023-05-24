#include <iostream>
#include <vector>
#include <list>

using ll = long long;
using namespace std;

vector<list<uint>> adj; //Lista de adyacencias

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

    // //Debug combinatoria
    // int N, K; cin >> N >> K;
    // cout << combinatoria(N,K) << endl;
    // return 0;

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