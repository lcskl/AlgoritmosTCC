#ifndef INFECTION3DEG_H
#define INFECTION3DEG_H

#include <vector>

class Graph{

public:
    int n;
    std::vector< std::vector<int> > adjList;
    bool* visited;
    int * degree;
    bool decide;
    int maxDepth;

    Graph(int const& n_vertex);

    void dfsInduced(int vertex, int depth);

    bool induced(int vertex, int last);
};

int decide(Graph graph,int k);

Graph generate_3deg_graph(int round);

#endif