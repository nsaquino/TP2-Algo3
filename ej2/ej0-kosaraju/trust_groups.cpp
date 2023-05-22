#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <stack>

using namespace std;

int n, m;
vector<vector<int>> D;
vector<vector<int>> D_T;

enum {BLANCO, GRIS, NEGRO};
vector<int> color;
stack<int> S;

void dfs1(int u){
    color[u] = GRIS;
    for (int i = 0; i < D[u].size(); i++)
    {
        int v = D[u][i];
        if (color[v] == BLANCO)
            dfs1(v);
    }
    color[u] = NEGRO;
    S.push(u);
}

void dfs2(int u){
    color[u] = GRIS;
    for (int i = 0; i < D_T[u].size(); i++)
    {
        int v = D_T[u][i];
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

int main() {
    while (true) {
        cin >> n >> m;
        if (n+m==0) break;

        map<string,int> name_to_index;
        
        string line; getline(cin, line);
        for (int i=0; i<n; i++) {getline(cin, line); name_to_index[line] = i;}
        
        D.assign(n, vector<int>(0)); D_T.assign(n, vector<int>(0));

        for (int j=0; j<m; j++) {
            string from, to;
            getline(cin, from); getline(cin, to);
            D[name_to_index[from]].push_back(name_to_index[to]);
            D_T[name_to_index[to]].push_back(name_to_index[from]);
        }

        // Completar
        int res = kosaraju();
        cout << res << endl;
    }

    return 0;
}
