/*
    Author: Lucas Rodrigues Keiler
    _The maximum infection time of the P 3 convexity in graphs with bounded maximum degree_
    Rudini
    Teorema 2.3, pg 3
*/

#include <iostream>
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

    Graph(int const& n_vertex){
        n = n_vertex;
        adjList.resize(n);

        visited = new bool[n+1];
        degree  = new int[n+1];
    }

    void dfsInduced(int vertex, int depth){
        if(decide)return;

        visited[vertex] = true;

        // for(int i=0;i<depth;i++)cout << " ";
        // cout << vertex << endl;

        if(depth == maxDepth){
            decide = true;
            return;
        }

        for(auto neighbor : adjList[vertex]){
            if(!visited[neighbor] && degree[neighbor] == 3 && induced(neighbor,vertex)){
                dfsInduced(neighbor,depth+1);
            }
        }

        visited[vertex] = false;

        return;
    }

    bool induced(int vertex, int last){

        for(auto neighbor : adjList[vertex])
            if(neighbor != last && visited[neighbor])
                return false;

        return true;
    }

};

int decide(Graph graph,int k){
    graph.decide = false;

    for(int i=0;i<graph.n;i++)
        graph.visited[i] = false;

    for(int i=0;i<graph.n && !graph.decide;i++){
        if(graph.degree[i] == 2){
            graph.maxDepth = k-1;
            graph.dfsInduced(i,0);
        }else if(graph.degree[i] == 3){
            graph.maxDepth = 2*k - 2;
            graph.dfsInduced(i,0);
        }
    }
    return graph.decide;
}

int main() {
    int n_vertex,m = 0,k;

    cout << "Number of vertices: ";
    cin >> n_vertex;

    Graph graph(n_vertex);

    cout << "Degree of vertices (d(v) <= 3): ";
    for(int i=0;i<n_vertex;i++){
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

    while(true){
        cout << "Value of k: ";
        cin >> k;

        if(k < 0)break;

        graph.decide = false;

        for(int i=0;i<graph.n;i++)
            graph.visited[i] = false;

        for(int i=0;i<graph.n && !graph.decide;i++){
            if(graph.degree[i] == 2){
                cout << i << " -> Iniciando busca...\n";
                graph.maxDepth = k-1;
                graph.dfsInduced(i,0);
            }else if(graph.degree[i] == 3){
                cout << i << " -> Iniciando busca...\n";
                graph.maxDepth = 2*k - 2;
                graph.dfsInduced(i,0);
            }
        }
        cout << "Decision (t(G) >= k): ";
        cout << graph.decide << endl;
    }

    return 0;
}
