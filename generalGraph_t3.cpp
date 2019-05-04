#include <iostream>
#include <vector>
#include <set>
using namespace std;

class Graph{

public:

    int n;
    vector< vector<int> > adjList;
    vector< pair<int,vector< set<int> > > > connectedComponents; //Each entry contains (for a cut vertex v) a vector of set of vertices (each set is a connected component of G-v)
    bool* isCutVertex;
    int* visitedTime;
    int* parent;
    int* lowest;
    int * degree;
    int currentTime;

    bool decide;
    int maxDepth;

    Graph(int const& n_vertex){
        n = n_vertex;
        adjList.resize(n);

        visitedTime = new int[n+1];
        degree  = new int[n+1];
        lowest = new int[n+1];
        parent = new int[n+1];
        currentTime = 0;
        isCutVertex = new bool[n+1];
    }

    void findArticulationPoints(int vertex){
        visitedTime[vertex] = ++currentTime;
        lowest[vertex] = visitedTime[vertex];
        for(auto neighbor : adjList[vertex]){
            if(!visitedTime[neighbor]){
                parent[neighbor] = vertex;
                findArticulationPoints(neighbor);
                if(lowest[neighbor] >= visitedTime[vertex] && !isCutVertex[vertex]){
                    isCutVertex[vertex] = true;
                    connectedComponents.push_back(make_pair(vertex, vector< set<int> >(0)));
                }
                lowest[vertex] = min(lowest[vertex],lowest[neighbor]);
            }else if(parent[vertex] != neighbor){
                lowest[vertex] = min (lowest[vertex], visitedTime[neighbor]);
            }
        }
    }
};

int main (){
    int n,m = 0;
    cout << "Number of vertices: ";
    cin >> n;

    Graph graph(n);

    cout << "Degree of vertices (d(v) <= 3): ";
    for(int i=0;i<n;i++){
        cin >> graph.degree[i];
        m += graph.degree[i];
    }
    m /=2;
    cout << "Describe the " << m << " edges:\n";

    int a,b;
    for(int i=0;i<m;i++){
        cin >> a >> b;
        graph.adjList[a].push_back(b);
        graph.adjList[b].push_back(a);
    }

    graph.findArticulationPoints(0);

    for(auto p : graph.connectedComponents){
        cout << p.first << endl;
    }

    return 0;
}