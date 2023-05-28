// https://fedelebron.com/a-dense-version-of-kruskals-algorithm

#ifndef KRUSKAL_DENSOS_HPP
#define KRUSKAL_DENSOS_HPP

#include <vector>
#include <chrono>
#include <math.h>

using namespace std;

typedef double cost;
typedef vector<cost> vcost;
typedef vector<vcost> vvcost;
typedef vvcost adjacency_matrix;
typedef vector<bool> vbool;
typedef pair<int, int> edge;
typedef pair<cost, edge> weighted_edge;

double kruskal_warnes(adjacency_matrix A, int r, int w, int u, int v);

void initialize(const adjacency_matrix& A,
                vcost& dist,
                vbool& representative);

weighted_edge lightest_edge(const adjacency_matrix& A,
                            const vcost& dist,
                            const vbool& representative);


void contract(const weighted_edge& e,
              adjacency_matrix& A,
              vcost& dist,
              vbool& representative);

#endif