#include <vector>
using namespace std;

class Graph{

public:

    int n;
    vector< vector<int> > adjList;
    bool* visited;
    int * degree;

    bool decide;
    int maxDepth;

    Graph(int const& n_vertex);

    void dfsInduced(int vertex, int depth);

    bool induced(int vertex, int last);

};

bool decide(Graph graph,int k);