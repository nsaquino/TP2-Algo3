#ifndef DSU_HPP
#define DSU_HPP

#include <vector>
#include <algorithm> // max(), swap()

using namespace std;

struct DSU_noOptimization{

    DSU_noOptimization(int n){
        padre = vector<int>(n);
        for(int v = 0; v < n; v++) padre[v] = v;
    }

    int find(int v){
        if(v == padre[v]) return v;
        return find(padre[v]);
    }

    void unite(int u, int v){
        u = find(u), v = find(v);
        if(u == v) return;
        padre[v] = u;
    }

    vector<int> padre;
};

struct DSU_onlyPathCompression{

    DSU_onlyPathCompression(int n){
        padre = vector<int>(n);
        for(int v = 0; v < n; v++) padre[v] = v;
    }

    int find(int v){
        if(v == padre[v]) return v;
        return padre[v] = find(padre[v]);
    }

    void unite(int u, int v){
        u = find(u), v = find(v);
        if(u == v) return;
        padre[u] = v;//padre[v];
    }

    vector<int> padre;
};

struct DSU_size_noPath{

    DSU_size_noPath(int n){
        padre = size = vector<int>(n);
        for(int v = 0; v < n; v++) {
            padre[v] = v;
            size[v] = 1;
        }
    }

    int find(int v){
        if(v == padre[v]) return v;
        return find(padre[v]);
    }

    void unite(int u, int v){
        u = find(u), v = find(v);
        if(u == v) return;
        if(size[u] < size[v]) swap(u,v);
        padre[v] = padre[u];
        size[u] += size[v];
    }

    vector<int> padre;
    vector<int> size;
};

struct DSU_rank_noPath{

    DSU_rank_noPath(int n){
        padre = rank = vector<int>(n);
        for(int v = 0; v < n; v++) padre[v] = v;
    }

    int find(int v){
        if(v == padre[v]) return v;
        return find(padre[v]);
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

struct DSU_size_path{

    DSU_size_path(int n){
        padre = size = vector<int>(n);
        for(int v = 0; v < n; v++) {
            padre[v] = v;
            size[v] = 1;
        }
    }

    int find(int v){
        if(v == padre[v]) return v;
        return padre[v] = find(padre[v]);
    }

    void unite(int u, int v){
        u = find(u), v = find(v);
        if(u == v) return;
        if(size[u] < size[v]) swap(u,v);
        padre[v] = padre[u];
        size[u] += size[v];
    }

    vector<int> padre;
    vector<int> size;
};

struct DSU_rank_path{

    DSU_rank_path(int n){
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

#endif