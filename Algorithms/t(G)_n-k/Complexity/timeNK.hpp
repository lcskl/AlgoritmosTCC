#ifndef TIMENK_HPP
#define TIMENK_HPP

#include <vector>
#include <string>

class Graph{

public:
    int n,k;
    std::vector< std::vector<int> > adjList;
    int* infected;
    int* degree;
    std::string iniInfected;

    bool decide;
    int maxDepth;

    Graph(int const& n_vertex);

    bool CheckInfectionTime();
};

#endif