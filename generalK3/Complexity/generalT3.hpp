#ifndef GENERAL_T3_HPP
#define GENERAL_T3_HPP

#include <vector>
#include <set>

class Graph{

public:

    int n;
    std::vector< std::vector<int> > adjList;
    std::vector< std::pair<int,std::vector< std::set<int> > > > connectedComponents; //Each entry contains (for a cut vertex v) a vector of set of vertices (each set is a connected component of G-v)
    bool* isCutVertex;
    int* visitedTime;
    int* parent;
    int* lowest;
    int* degree;
    int currentTime;

    bool decide;
    int maxDepth;

    bool debug;

    Graph(int const& n_vertex);

    //Max Percolation Problem for k = 3
    bool infectsAtTime3();

private:
    void findArticulationPoints(int vertex);
    void dfs(int vertex,int timeStamp, int removed);
    void buildConnectedComponents();
};

Graph* generate_random(int n,int m);

#endif