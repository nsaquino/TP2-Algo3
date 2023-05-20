#include <iostream>
#include <vector>
#include <list>

using namespace std;

using ll = long long;
const ll inf = 1e18;

/*
    N = cantidad de oficinas
        1 ≤ N ≤ 1000
    R = distancia a partir de la cual no se pueden usar cables UTP
        1 ≤ R ≤ 10000  
    W = cantidad de modems adquiridos
        W < N
    U, V = precio por centímetro de los cables UTP y de fibra óptica, respectivamente.               
        1 ≤ U ≤ V ≤ 10 
*/
int N, R, W, U, V;

vector<vector<ll>> G_dist;
vector<pair<ll,ll>> coord_oficina;

int distancia(pair<ll, ll> a, pair<ll, ll> b) { //Distancia Manhattan
    return abs(a.first - b.first) + abs(a.second - b.second);
}

int main(int argc, char *argv[]) {
    int c; cin >> c; //c = casos de tests
    for (int i = 1; i <= c; i++) {
        cin >> N >> R >> W >> U >> V;

        G_dist.assign(N, vector<ll>(N,0)); //Matriz de adyacencia
        coord_oficina = vector<pair<ll, ll>>(N);
        for (int i = 0; i < N; i++) {
            ll x, y; cin >> x >> y;
            coord_oficina[i] = make_pair(x,y);
        }

        for (int i = 0; i < N; i++) {
            for (int j = i+1; j < N; j++) {
                ll dist = distancia(coord_oficina[i], coord_oficina[j]);
                G_dist[i][j] = G_dist[j][i] = dist;
            }
        }

        /*Debug
        cout << "Caso #" << i << ":" << endl;
        cout << "\tOficinas:" << endl;
        for (int i = 0; i < N; i++) {
            cout << "\t\t" << i << ": (";
            cout << coord_oficina[i].first << ", " << coord_oficina[i].second;
            cout << ")" << endl;
        }
        
        cout << "\tDistancias:" << endl;
        for (int i = 0; i < N; i++) {
            cout << "\t\t";
            for (int j = 0; j < N; j++) {
                cout << G_dist[i][j] << " ";
            }
            cout << endl;
        }*/
    }
    
    return 0;
}