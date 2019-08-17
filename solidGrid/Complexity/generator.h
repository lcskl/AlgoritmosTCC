#include <vector>
#include <map>
using namespace std;

class Graph{
public: 

	int n;
    vector< vector< pair<int,int> > > adjList; //Pair -> Vertex and Edge weight
    map<int , vector<int> > Ladder; // "Color", "Vertices in Ladder with that color"
    int* visited;
    int * degree;
	bool* used;

    Graph(int const& n_vertex);
};


Graph generate_graph(int n);