#ifndef SOLIDGRID_HPP
#define SOLIDGRID_HPP

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

    int d_func(int b, int k);

    int calculateDistance(int other1,int other2,int b,int k);

    int dfsCicle(int vertex, int income_vertex);

    void detectLadders();

    void Transform();

	int MaxWeightIndPath(int vertex,int vertexBeginning, int current_weight);

	bool induced(int vertex, int last);
	
	int MaximumTimeSolidGrid();
};

#endif