#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Graph{
public: 

	int n;
    vector< vector<int> > adjList;
    int* visited;
    int * degree;

    Graph(int const& n_vertex){
        n = n_vertex;
        adjList.resize(n);

        visited = new int[n+1];
        degree  = new int[n+1];
    }


    int dfsCicle(int vertex, int income_vertex){
    	visited[vertex] = vertex;

    	//cout << "Vertex: " << vertex << endl;

    	int min_id = vertex;
    	for(auto neighbor : adjList[vertex]){
    		if(visited[neighbor] == -1){
    			min_id = min(min_id,dfsCicle(neighbor,vertex));
    			//cout << "min_id = " << min_id << " Neighbor: " << neighbor << endl;
    		}else if(neighbor != income_vertex && visited[neighbor] < min_id){
    			min_id = visited[neighbor];
    			//cout << "Vertex: " << vertex << " Neighbor: " << neighbor << " v[n] = " << visited[neighbor] << endl;
    		}
    	}
    	visited[vertex] = min_id;

    	return min_id;
    }
};

int main(int argc, char const *argv[])
{
	int n_vertex,m = 0,k;

    cout << "Number of vertices: ";
    cin >> n_vertex;

    Graph graph(n_vertex);

    cout << "Degree of vertices (d(v) <= 3): ";
    for(int i=0;i<n_vertex;i++){
        cin >> graph.degree[i];
        m += graph.degree[i];
        graph.visited[i] = -1;
    }
    m /=2;
    cout << "Describe the " << m << " edges:\n";

    int a,b;
    for(int i=0;i<m;i++){
        cin >> a >> b;
        graph.adjList[a].push_back(b);
        graph.adjList[b].push_back(a);
    }

    graph.dfsCicle(0,-1);

    for(int i=1;i<=n_vertex;i++){
    	cout << i << ": ";
    	for(int j=0;j<n_vertex;j++){
    		if(graph.visited[j] == i)
    			cout << j << " ";
    	}
    	cout << endl;
    }


	return 0;
}