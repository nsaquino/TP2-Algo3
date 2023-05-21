#include <iostream>
#include <vector>
#include <list>
#include <tuple>
#include <algorithm>

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

vector<pair<ll,ll>> coord_oficina; //Indexamos las oficinas
vector<vector<ll>> G_dist; //Matriz de adyacencia
vector<tuple<ll,ll,ll>> G_E; //Vector de aristas: (d, i, j),donde la distancia
                                 //                   entre las oficinas i y j es d

/*******Debug********/
void print_oficinas();
void print_edge_list();
void print_matrix();
/*******Debug********/

int distancia(pair<ll, ll> a, pair<ll, ll> b) { //Distancia Manhattan
    return abs(a.first - b.first) + abs(a.second - b.second);
}

int main(int argc, char *argv[]) {
    int C; cin >> C; //C = casos de tests
    for (int c = 1; c <= C; c++) {
        cin >> N >> R >> W >> U >> V;

        //G_dist.assign(N, vector<ll>(N,0)); 
        coord_oficina = vector<pair<ll, ll>>(N); //Asignamos un indice a las oficinas
        G_E.clear(); //Preparamos la lista de aristas

        for (int i = 0; i < N; i++) {
            ll x, y; cin >> x >> y;
            coord_oficina[i] = make_pair(x,y);
        }

        for (int i = 0; i < N; i++) {
            for (int j = i+1; j < N; j++) {
                ll dist = distancia(coord_oficina[i], coord_oficina[j]);
                G_E.push_back(make_tuple(dist, i, j));
                //G_dist[i][j] = G_dist[j][i] = dist;
            }
        }

        //Debug
        // cout << "Caso #" << c << ":" << endl;
        // print_oficinas();
        // print_edge_list();
        // print_matrix();
        
    }
    
    return 0;
}

/*******Debug********/
void print_matrix(){
    cout << "\tDistancias:" << endl;
    for (int i = 0; i < N; i++) {
        cout << "\t\t";
        for (int j = 0; j < N; j++) {
            cout << G_dist[i][j] << " ";
        }
        cout << endl;
    }
}

void print_oficinas(){
    cout << "\tOficinas:" << endl;
    for (int i = 0; i < N; i++) {
        cout << "\t\t" << i << ": (";
        cout << coord_oficina[i].first << ", " << coord_oficina[i].second;
        cout << ")" << endl;
    }
}

void print_edge_list(){
    //Lista de aristas
    cout << "\tDistancias:" << endl;
    cout << "\t\tSin ordenar:" << endl;
    cout << "\t\t{";
    for (int i = 0; i < G_E.size(); i++) {
        tuple<ll,ll,ll> e = G_E[i];
        cout << "(" << get<0>(e) << "," << get<1>(e) << "," << get<2>(e) << "), ";
    }
    cout << "}" << endl;

    sort(G_E.begin(), G_E.end());
    cout << "\t\tOrdenado:" << endl;
    cout << "\t\t{";
    for (int i = 0; i < G_E.size(); i++) {
        tuple<ll,ll,ll> e = G_E[i];
        cout << "(" << get<0>(e) << "," << get<1>(e) << "," << get<2>(e) << "), ";
    }
    cout << "}" << endl;
}