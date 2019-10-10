/*
    Author: Lucas Rodrigues Keiler
    The maximum time of 2-neighbor bootstrap percolation: Complexity results
    Rudini Sampaio
    Theorem 5.1, pg 6

*/

#include <iostream>
#include <algorithm>
#include <string>
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

        visitedTime = new int[n+1]();
        degree  = new int[n+1]();
        lowest = new int[n+1]();
        parent = new int[n+1]();
        currentTime = 0;
        isCutVertex = new bool[n+1]();
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
                    connectedComponents.push_back(make_pair(vertex, vector< set<int> >()));
                }
                lowest[vertex] = min(lowest[vertex],lowest[neighbor]);
            }else if(parent[vertex] != neighbor){
                lowest[vertex] = min (lowest[vertex], visitedTime[neighbor]);
            }
        }
    }

    void dfs(int vertex,int timeStamp, int removed){
        visitedTime[vertex] = timeStamp;

        for(auto neighbor : adjList[vertex]){
            if(neighbor == removed) continue;

            if(!visitedTime[neighbor])
                dfs(neighbor,timeStamp,removed);
        }
    }

    void buildConnectedComponents(){
        for(auto& p : connectedComponents){
            
            for(int i=0;i<n;i++)
                visitedTime[i] = 0;

            int timeStamp = 1;
            for(int i=0;i<n;i++){
                if(i != p.first && !visitedTime[i]){
                    dfs(i,timeStamp,p.first);
                    timeStamp++;
                }
            }

            //Check which connected components H_{v,i} are subsets of N(v)
            for(int i=1;i<timeStamp;i++){
                bool subset = true;
                for(int j=0;j<n;j++)
                    if(visitedTime[j] == i && find(adjList[p.first].begin(),adjList[p.first].end(),j) == adjList[p.first].end()){
                       subset = false;
                       break; 
                    }

                if(subset){
                    set<int> H;
                    for(int j=0;j<n;j++){
                        if(visitedTime[j] == i){
                            H.insert(j);
                            
                        }
                    }
                    p.second.push_back(H);
                    
                }
            }
        }
    }

    //Max Percolation Problem for k = 3
    bool infectsAtTime3(){
        //For all u in V(G) do...
        for(int u=0;u<n;u++){
            cout << "# " <<  u << " #" <<  endl;
            //Building N_{>=3} (G)----------------------------------
            set<int> N_3;
            bool N_2[n+1] = {false};

            N_2[u] = true;
            for(auto neighbor : adjList[u]){
                N_2[neighbor] = true;
                for(auto second_neighbor : adjList[neighbor])
                    N_2[second_neighbor] = true;
            }
            cout << "N_3: ";
            for(int i=0;i<n;i++)
                if(!N_2[i]){
                    cout << i << " ";
                    N_3.insert(i);
                }
            cout << endl;
            //------------------------------------------------------

            cout << "T_0: ";
            set<int> T_0;
            //Find a set T_0 in T_0^u
            for(auto p : connectedComponents){
                for(auto H : p.second){
                    if(find(H.begin(),H.end(),u) == H.end()){
                        cout << *H.begin() << " ";
                        T_0.insert(*H.begin());
                    }
                }
            }
            cout << endl;

            

            for(int k=1;k<=4;k++){
                string F = "";

                for(int j=0;j<n;j++){
                    if(j < n-k)
                        F += '0';
                    else
                        F += '1';
                }

                

                do{
                    int infected_neighbors;
                    int infected[n+1];
                    for(int i=0;i<n;i++){
                        infected[i] = -1;
                        if(F[i] == '1')
                            infected[i] = 0;
                    }

                    for(auto v : T_0)
                        infected[v] = 0;

                    for(auto v : N_3)
                        infected[v] = 0;

                    // cout << F << " ----" << endl;
                    // for(int i=0;i<n;i++)
                    //     cout << infected[i] << " ";
                    // cout << endl;

                    for(int time = 1; time <= 3; time++){

                        for(int i=0;i<n;i++){
                            if(infected[i] != -1)continue;

                            infected_neighbors = 0;

                            for(auto neighbor : adjList[i]){
                                if(infected[neighbor] != -1 && infected[neighbor] < time)
                                    infected_neighbors++;
                            }

                            if(infected_neighbors >= 2){
                                infected[i] = time;
                            }

                        }

                    }
                    // cout << "After\n";
                    // for(int i=0;i<n;i++)
                    //     cout << infected[i] << " ";
                    // cout << endl;

                    if(infected[u] == 3){
                        cout << F << endl;
                        return true;
                    }
                }while(next_permutation(F.begin(),F.end()));
            }
            
        }
        return false;
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

    graph.buildConnectedComponents();

    for(auto p : graph.connectedComponents){
        cout << p.first << endl;
        for(auto x : p.second){
            cout << "(";
            for(auto y : x)
                cout << y << ",";
            cout << ")" << endl;
        }
    }

    cout << "Output\n: "  << graph.infectsAtTime3() << endl;

    return 0;
}