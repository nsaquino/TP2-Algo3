#include <chrono>
#include <iostream>
#include <vector>
#include <list>
#include <tuple>
#include <algorithm>        //sort(), max()
#include <bits/stdc++.h>    //sqrt(), pow()
#include "dsu.hpp"
#include <sys/stat.h>
#include "kruskal_densos.hpp"

using namespace std;

using ll = long long;

string dir_path;

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
adjacency_matrix G; //Matriz de adj para kruskal para densos

double distancia(pair<ll, ll> a, pair<ll, ll> b) { //Distancia euclidiana
    return sqrt(double(pow(b.first - a.first, 2) + pow(b.second - a.second, 2)));
}

void read_input(int size, int k) {
    //Buscamos el input correspondiente
    string file_name = dir_path + "inputs/input_" + to_string(size);
    cout << "input_" << size << "\t" << k+1 << "/7" << endl;
    ifstream read_file(file_name); /*abre para leer*/
    
    read_file >> N >> R >> W >> U >> V;

    coord_oficina = vector<pair<ll, ll>>(N); //Asignamos un indice a las oficinas
    G_E.clear(); //Preparamos la lista de aristas
    //Kruskal_densos
    G = adjacency_matrix(N, vcost(N, INFINITY));
    
    for (int i = 0; i < N; i++){
        int x, y; read_file >> x >> y;
        coord_oficina[i] = make_pair(x,y);
    }
    
    read_file.close();
    
    for (int i = 0; i < N; i++) {
        for (int j = i+1; j < N; j++) {
            double dist = distancia(coord_oficina[i], coord_oficina[j]);
            G_E.push_back(make_tuple(dist, i, j));
            //Kruskal_densos
            G[i][j] = dist;
        }
    }
}

//default = DSU_rank_path
template <typename T = DSU_rank_path> double kruskal() {
    auto start = chrono::high_resolution_clock::now();

    sort(G_E.begin(),G_E.end());
    T dsu(N);
    double UTP, fibra = 0;
    int cc = N; //Componentes conexas (1 modem por cada cc)
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

    auto stop = chrono::high_resolution_clock::now();
    chrono::duration<double> diff = stop - start;
    return diff.count();
    //return std::chrono::duration_cast<std::chrono::milliseconds>(diff).count();
}


int main() {
    //Buscamos el directorio del codigo
    string code_path = __FILE__;
    dir_path = code_path.substr(0, code_path.rfind("/")) + "/";
    string out = dir_path + "output";
    if(mkdir(out.c_str(), 0777) == 0)
        cout << "Carpeta 'output/' creada" << endl;
    
    enum implementation { NOT_OPTIMIZED,
                PATH_COMPR_ONLY,
                BYSIZE_NO_PATH_COMPR,
                BYRANK_NO_PATH_COMPR,
                BYSIZE_WITH_PATH_COMPR,                
                BYRANK_WITH_PATH_COMPR,
                KRUSKAL_DENSOS};
    vector<string> output_name = {
        "output/runtime_tp_noOpt.csv",
        "output/runtime_tp_onlyPath.csv",
        "output/runtime_tp_size_noPath.csv",
        "output/runtime_tp_rank_noPath.csv",
        "output/runtime_tp_size_path.csv",
        "output/runtime_tp_rank_path.csv",
        "output/runtime_tp_densos.csv"  //Kruskal_densos
    };

    int repeat = 10;
    for (int k = 0; k <= 6; k++) {
    
        ofstream output_file;
        output_file.open(dir_path + output_name[k]);
        cout << output_name[k] << endl;
        output_file << "n,time\n";

        // for (int power = 1; power < 3; power++) {
        //     for (int i=2; i <= 10; i++) {
            for (int n=10; n <= 1000; n += 10) {
        //        int n = i * pow(10,power);
                read_input(n, k);

                double counter = 0;

                for (int ignore=0; ignore<repeat; ignore++) { 
                    switch (k) {
                    case NOT_OPTIMIZED:
                        counter += kruskal<DSU_noOptimization>();
                        break;
                    case PATH_COMPR_ONLY:
                        counter += kruskal<DSU_onlyPathCompression>();
                        break;
                    case BYSIZE_NO_PATH_COMPR:
                        counter += kruskal<DSU_size_noPath>();
                        break;
                    case BYRANK_NO_PATH_COMPR:
                        counter += kruskal<DSU_rank_noPath>();
                        break;
                    case BYSIZE_WITH_PATH_COMPR:
                        counter += kruskal<DSU_size_path>();
                        break;
                    case BYRANK_WITH_PATH_COMPR:
                        counter += kruskal<DSU_rank_path>();    
                        break;
                    case KRUSKAL_DENSOS:
                        counter += kruskal_warnes(G, R, W, U, V);
                        break;
                    }
                }

                output_file << n << "," << counter / repeat << endl;
            }
        //}

        output_file.close();
     }
    
    return 0;
}