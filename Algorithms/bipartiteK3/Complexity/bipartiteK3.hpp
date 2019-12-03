#ifndef BIPARTITE_K3_HPP
#define BIPARTITE_K3_HPP

#include <vector>

class Graph{

public:
    int n;
    std::vector< std::vector<int> > adjList;
    int* infected;
    int * degree;
    bool *in_N_2;
    bool *in_N;

    Graph(int const& n_vertex);

    bool is_t_greater_3();

};

Graph* generate_random_bipartite(int n);

Graph* generate_random_bipartite_N_M(int n);

#endif