#include <iostream>
#include <vector>
#include <list>
#include <tuple>
#include <algorithm>        //sort()
#include <bits/stdc++.h>    //sqrt(), pow()

using namespace std;

using ll = long long;

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
vector<tuple<double,ll,ll>> G_E; //Vector de aristas: (d, i, j),donde la distancia
                                 //                   entre las oficinas i y j es d

/*******Debug********/
// void print_oficinas();
// void print_edge_list();
/*******Debug********/

struct DSU{

    DSU(int n){
        padre = rank = vector<int>(n);
        for(int v = 0; v < n; v++) padre[v] = v;
    }

    int find(int v){
        if(v == padre[v]) return v;
        return padre[v] = find(padre[v]);
    }

    void unite(int u, int v){
        u = find(u), v = find(v);
        if(u == v) return;
        if(rank[u] < rank[v]) swap(u,v);
        padre[v] = padre[u];
        rank[u] = max(rank[u],rank[v]+1);
    }

    vector<int> padre;
    vector<int> rank;
};

pair<double, double> kruskal() {
    sort(G_E.begin(),G_E.end());
    double UTP, fibra = 0;
    int cc = N; //Componentes conexas (1 modem por cada cc)
    DSU dsu(N);
    for(auto [d,u,v] : G_E){
        if(cc == W) break; //Tenemos las conexiones, agregamos un modem en cada cc y listo
        //si (u,v) es arista segura
        if(dsu.find(u) != dsu.find(v)){
            // unir oficinas con cable
            dsu.unite(u,v);
            cc--;
            if (d <= double(R)) //Si no se pasa de R cm, usar cable UTP
                UTP += (d * double(U));
            else //Si esta a distancia mayor a R, usar fibra optica
                fibra += (d * double(V));
        }
    }
    return make_pair(UTP, fibra);
}

double distancia(pair<ll, ll> a, pair<ll, ll> b) { //Distancia euclidiana
    return sqrt(double(pow(b.first - a.first, 2) + pow(b.second - a.second, 2)));
}

int main() {
    int C; cin >> C; //C = casos de tests
    for (int c = 1; c <= C; c++) {
        cin >> N >> R >> W >> U >> V;

        coord_oficina = vector<pair<ll, ll>>(N); //Asignamos un indice a las oficinas
        G_E.clear(); //Preparamos la lista de aristas

        for (int i = 0; i < N; i++) {
            ll x, y; cin >> x >> y;
            coord_oficina[i] = make_pair(x,y);
        }

        for (int i = 0; i < N; i++) {
            for (int j = i+1; j < N; j++) {
                double dist = distancia(coord_oficina[i], coord_oficina[j]);
                G_E.push_back(make_tuple(dist, i, j));
            }
        }

        auto [UTP, fibra] = kruskal();
        cout << "Caso #" << c << ": ";
        cout << fixed << setprecision(3); //fixed hace que aparezcan los .000
        cout << UTP << " " << fibra << endl;

        //Debug
        //cout << "Caso #" << c << ":" << endl;
        //print_oficinas();
        //print_edge_list();
    }
    
    return 0;
}

/*******Debug********/
// void print_oficinas(){
//     cout << "\tOficinas:" << endl;
//     for (int i = 0; i < N; i++) {
//         cout << "\t\t" << i << ": (";
//         cout << coord_oficina[i].first << ", " << coord_oficina[i].second;
//         cout << ")" << endl;
//     }
// }

// void print_edge_list(){
//     //Lista de aristas
//     cout << "\tDistancias:" << endl;
//     cout << "\t\tSin ordenar:" << endl;
//     cout << "\t\t{";
//     for (int i = 0; i < G_E.size(); i++) {
//         auto [d,u,v] = G_E[i];
//         cout << "(" << d << "," << u << "," << v << "), ";
//     }
//     cout << "}" << endl;

//     sort(G_E.begin(), G_E.end());
//     cout << "\t\tOrdenado:" << endl;
//     cout << "\t\t{";
//     for (int i = 0; i < G_E.size(); i++) {
//         auto [d,u,v] = G_E[i];
//         cout << "(" << d << "," << u << "," << v << "), ";
//     }
//     cout << "}" << endl;
// }