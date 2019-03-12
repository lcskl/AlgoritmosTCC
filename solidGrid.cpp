#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;



class Graph{
public: 

	int n;
    vector< vector< pair<int,int> > > adjList; //Pair -> Vertex and Edge weight
    map<int , vector<int> > Ladder;
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
    	int neighbor;
    	for(auto vertex_edge : adjList[vertex]){
    		neighbor = vertex_edge.first;

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

    void detectLadders(){
    	for(int i=0;i<n;i++){
    		cout << visited[i] << " ";
    		Ladder[ visited[i] ].push_back(i);
    	}
    	cout << endl;

    	for(int i=0;i<n;i++)
    		if(Ladder.find(i) != Ladder.end() &&  Ladder[i].size() == 1)
    			Ladder.erase(i);
    }

    void Transform(){
    	int k; //Ladder L_k
    	for(auto &kv : Ladder){
    		k = kv.second.size() / 2;

    		//To-do: BFS em Ladder
    	}
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
        graph.adjList[a].push_back( make_pair(b,1));
        graph.adjList[b].push_back( make_pair(a,1));
    }

    graph.dfsCicle(0,-1);

    graph.detectLadders();

    for(auto &kv : graph.Ladder){
    	cout << kv.first << " => ";
    	for(auto vertex : kv.second)
    		cout << vertex  << " ";
    	cout << endl;
    }


	return 0;
}