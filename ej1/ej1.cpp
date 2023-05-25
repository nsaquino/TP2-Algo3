#include <iostream>
#include <vector>

using ll = long long;
using namespace std;

int N, M;       //n = cant. vertices, m = cant. aristas
vector<vector<int>> adj; //Lista de adyacencias

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

    cin >> N >> M;  

    //Init adjacency list
    adj = vector<vector<int>>(N, vector<int>());
    while (M--) {
        int u, v;
        cin >> u >> v; // (u,v) = arista
        adj[u-1].push_back(v-1);
        adj[v-1].push_back(u-1);
    }

    //TODO: Resolver el ejercicio T_T

    // //Debug
    // for (int i = 0; i < adj.size(); i++) {
    //     cout << i + 1 << ": { ";
    //     for(int j = 0; j < adj[i].size(); j++)
    //         cout << adj[i][j] + 1 << " ";
    //     cout << "}" << endl;
    // }

    return 0;
}