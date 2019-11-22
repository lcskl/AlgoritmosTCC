#ifndef TREE_HPP
#define TREE_HPP

#include <vector>

class Graph{
public:
    int n;
    int** s;
    std::vector< std::vector<int> > adjList;
    std::vector< int > inf_time;
    std::vector< int > neighbors_remaining;
    std::vector< int > max_neighbor_time;
    std::vector< int > perc_limit;
    std::vector< int > maxS; 

    Graph(int const& n_vertex);

    int max_time();

    int max_time_arbitrary();

    void add_edge(int a,int b);

    void remove_edge(int a,int b);

private:
    int calculate(int u,int v);
};


#endif