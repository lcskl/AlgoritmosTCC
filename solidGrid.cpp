#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <queue>
using namespace std;

#define INF 999999999


class Graph{
public: 

	int n;
    vector< vector< pair<int,int> > > adjList; //Pair -> Vertex and Edge weight
    map<int , vector<int> > Ladder; // "Color", "Vertices in Ladder with that color"
    int* visited;
    int * degree;

    Graph(int const& n_vertex){
        n = n_vertex;
        adjList.resize(n);

        visited = new int[n+1];
        degree  = new int[n+1];
    }

    int d_func(int b, int k){
    	if(b == 0)
    		return ( (k-1) +  int((2*(k+1))/4) );
    	else
    		return (   k  +   int((2*(k-1))/4) );
    }

    int calculateDistance(int other1,int other2,int b,int k){
    	int deg_sum = degree[other1] + degree[other2];
    	int weight = INF;
    	switch(deg_sum){
    		case 6:
    			weight = d_func(b,k);
    			break;
    		case 5:
    			if(k > 1)
    				weight = d_func(b,k-1);
    			break;
    		case 4:
    			if(k > 2)
    				weight = d_func(b,k-2);
    			else
    				weight = -INF;
    			break; 
    	}
    	return weight;
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
    		k = (kv.second.size() / 2) - 1;

    		vector<int> corner_vertex; //It is necessary to know the corner vertices
    		for(auto vertex : kv.second){
    			for(auto vertex_edge : adjList[vertex]){
    				if(visited[vertex_edge.first] != visited[vertex] || degree[vertex] == 2){
    					corner_vertex.push_back(vertex);
    					cout << "Corner: " << vertex << endl;
    					break;
    				}
    			}
    		}

    		queue<int> BFSQueue;
    		BFSQueue.push(corner_vertex[0]);

    		int BFSvisited[n];
    		for(int i=0;i<n;i++)BFSvisited[i] = -1;
    		BFSvisited[corner_vertex[0]] = 0;

    		int current_vertex;
    		while(!BFSQueue.empty()){
    			current_vertex = BFSQueue.front();
    			BFSQueue.pop();

    			for(auto vertex_edge : adjList[current_vertex]){
    				if(visited[vertex_edge.first] == visited[current_vertex] && BFSvisited[vertex_edge.first] < 0){
    					BFSvisited[vertex_edge.first] = BFSvisited[current_vertex] + 1;
    					BFSQueue.push(vertex_edge.first);			
    				}
    			}
    		}

    		/*
				Now we can determine which vertices are adjacent, at a distance k apart, and at a distance k+1 apart.
				Below, the variables A,B,C,D will represent the topology:

					A ---- ... ---- C
					|               |
					|               |
					B ---- ... ---- D
    		*/

    		int A,B = -1,C,D;
    		A = corner_vertex[0];


    		for(auto corner : corner_vertex){
    			if(corner == A)continue;

    			if (B == -1 && find(adjList[A].begin(),adjList[A].end(),make_pair(corner,1)) != adjList[A].end()) //'corner' is adjacent -> That's B
    				B = corner;
    			else if(BFSvisited[corner] == k) // 'corner' is at distance k from A -> That's C
    				C = corner;
    			else if(BFSvisited[corner] == k+1) // 'corner' is at distance k+1 from A -> That's D
    				D = corner;
    			
    			cout << corner << " -> " << BFSvisited[corner] << endl;
    		}

    		cout << A << " " << B << " " << C << " " << D << "\n";

    		/* We need to define the following distances:
			   A to C
			   B to D
			   A to D
			   B to C 
			*/

			//First, distance K (A,C) & (B,D)
			int distance = calculateDistance(B,D,0,k);
			if(k > 1 && distance != INF){
				adjList[A].push_back(make_pair(C,distance));
				adjList[C].push_back(make_pair(A,distance));
			}
			

			distance = calculateDistance(A,C,0,k);
			if(k > 1 && distance != INF){
				adjList[B].push_back(make_pair(D,distance));
				adjList[D].push_back(make_pair(B,distance));
			}
			
			//Now, distance K+1 (A,D) & (B,C)
			distance = calculateDistance(B,C,1,k);
			if(distance != INF){
				adjList[A].push_back(make_pair(D,distance));
				adjList[D].push_back(make_pair(A,distance));
			}

			distance = calculateDistance(A,D,1,k);
			if(distance != INF){
				adjList[B].push_back(make_pair(C,distance));
				adjList[C].push_back(make_pair(B,distance));
			}

			//Now, delete remaining vertices of the ladder
			for(auto vertex : kv.second){
				if(find(corner_vertex.begin(),corner_vertex.end(),vertex) == corner_vertex.end() ){
					adjList[vertex].clear();
					continue;
				}

    			for(int i=0; i < adjList[vertex].size();i++){
    				if(find(corner_vertex.begin(),corner_vertex.end(),adjList[vertex][i].first) == corner_vertex.end()){
    					adjList[vertex].erase(adjList[vertex].begin()+i);
    					i--;
    				}
    			}
    		}
    		
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

    graph.Transform();

    for(int i=0;i<n_vertex;i++){
    	cout << i << " => ";
    	for(int j=0;j<graph.adjList[i].size();j++){
    		cout << "(" << graph.adjList[i][j].first << " ," << graph.adjList[i][j].second << ") ";
    	}
    	cout << endl;
    }


	return 0;
}