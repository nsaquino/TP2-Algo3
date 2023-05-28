#include "kruskal_densos.hpp"

//Kruskal para densos - O(n²)
double kruskal_warnes(adjacency_matrix A, int r, int w, int u, int v) {
  auto start = chrono::high_resolution_clock::now();

  int n = A.size();
  cost UTP, fibra = 0;
  vcost dist(n, INFINITY);
  vbool representative(n);

  initialize(A, dist, representative);

  int cc = n - 1;
  while (cc-- > w) {
    weighted_edge e = lightest_edge(A, dist, representative);
    cost d = e.first;
    if (d <= double(r)) //Si no se pasa de R cm, usar cable UTP
        UTP += (d * double(u));
    else //Si esta a distancia mayor a R, usar fibra optica
        fibra += (d * double(v));
    
    contract(e, A, dist, representative);
  }

  auto stop = chrono::high_resolution_clock::now();
  chrono::duration<double> diff = stop - start;
  return diff.count();
}

void initialize(const adjacency_matrix& A,
                vcost& dist,
                vbool& representative) {
  int n = dist.size();
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      dist[i] = min(dist[i], A[i][j]);
    }
    representative[i] = true;
  }
}

weighted_edge lightest_edge(const adjacency_matrix& A,
                            const vcost& dist,
                            const vbool& representative) {
  int idx = 0, n = dist.size();
  while (!representative[idx]) ++idx;
  for (int i = idx + 1; i < n; ++i) {
    if (!representative[i]) continue;
    if (dist[i] < dist[idx]) idx = i;
  }
  cost weight = dist[idx];
  int target = 0;
  for (int i = 0; i < n; ++i) {
    if (!representative[i]) continue;
    if (A[idx][i] == weight) {
      target = i;
      break;
    }
  }

  return weighted_edge(weight, edge(idx, target));
}

void contract(const weighted_edge& e,
              adjacency_matrix& A,
              vcost& dist,
              vbool& representative) {
  int n = dist.size(),
      u = e.second.first,
      v = e.second.second;
  representative[v] = false;
  dist[u] = INFINITY;
  for (int i = 0; i < n; ++i) {
    if (!representative[i]) continue;
    if (i == u) continue;
    A[i][u] = A[u][i] = min(A[u][i], A[v][i]);
    dist[u] = min(dist[u], A[u][i]);
  }
}
