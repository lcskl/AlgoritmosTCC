#ifndef TREE_HPP
#define TREE_HPP

#include <vector>

class Graph{
public:
    int n;
    int** s;
    std::vector< std::vector<int> > adjList;

    Graph(int const& n_vertex);

    int max_time();

    void add_edge(int a,int b);

    void remove_edge(int a,int b);

private:
    int calculate(int u,int v);
};


#endif