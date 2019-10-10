#include <iostream>
#include <algorithm>
#include <string>
#include <random>
#include "generalT3.hpp"
using namespace std;



Graph::Graph(int const& n_vertex){
    n = n_vertex;
    adjList.resize(n);

    visitedTime = new int[n+1]();
    degree  = new int[n+1]();
    lowest = new int[n+1]();
    parent = new int[n+1]();
    currentTime = 0;
    isCutVertex = new bool[n+1]();

}

void Graph::findArticulationPoints(int vertex){
    visitedTime[vertex] = ++currentTime;
    lowest[vertex] = visitedTime[vertex];
    int children = 0;

    for(auto neighbor : adjList[vertex]){
        if(!visitedTime[neighbor]){
            children++;
            parent[neighbor] = vertex;
            findArticulationPoints(neighbor);

            lowest[vertex] = min(lowest[vertex],lowest[neighbor]);

            if(parent[vertex] == -1 && children > 1){
                isCutVertex[vertex] = true;
                connectedComponents.push_back(make_pair(vertex, vector< set<int> >()));
            }

            if(parent[vertex] != -1 && lowest[neighbor] >= visitedTime[vertex]){
                isCutVertex[vertex] = true;
                connectedComponents.push_back(make_pair(vertex, vector< set<int> >()));
            }
            
        }else if(parent[vertex] != neighbor){
            lowest[vertex] = min (lowest[vertex], visitedTime[neighbor]);
        }
    }
}

void Graph::dfs(int vertex,int timeStamp, int removed){
    visitedTime[vertex] = timeStamp;

    for(auto neighbor : adjList[vertex]){
        if(neighbor == removed) continue;

        if(!visitedTime[neighbor])
            dfs(neighbor,timeStamp,removed);
    }
}

void Graph::buildConnectedComponents(){
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

        // for(int i=0;i<n;i++)
        //     printf("%d ",visitedTime[i]);
        // printf("\n");

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
bool Graph::infectsAtTime3(){
    
    for(int i=0;i<this->n;i++)
        this->parent[i] = -1;

    for(int i=0;i<this->n;i++){
        if(!visitedTime[i])
            this->findArticulationPoints(i);
    }
    

    this->buildConnectedComponents();


    //For all u in V(G) do...

    // for(int i=0;i<this->n;i++)
    //     cout << i << "->" << this->isCutVertex[i] << " ";
    // cout << endl;

    for(int u=0;u<n;u++){
        if(this->debug)cout << "# " <<  u << " #" <<  endl;
        //Building N_{>=3} (G)----------------------------------
        set<int> N_3;
        bool N_2[n+1];
        for(int i=0;i<=n;i++)
            N_2[i] = false;


        N_2[u] = true;
        for(auto neighbor : adjList[u]){
            N_2[neighbor] = true;
            for(auto second_neighbor : adjList[neighbor])
                N_2[second_neighbor] = true;
        }
        if(this->debug)cout << "N_3: ";
        for(int i=0;i<n;i++)
            if(!N_2[i]){
                if(this->debug)cout << i << " ";
                N_3.insert(i);
            }
        if(this->debug)cout << endl;
        //------------------------------------------------------

        //cout << "T_0: ";
        set<int> T_0;
        //Find a set T_0 in T_0^u
        for(auto p : connectedComponents){
            for(auto H : p.second){
                if(find(H.begin(),H.end(),u) == H.end()){
                    if(this->debug)cout << *H.begin() << " ";
                    T_0.insert(*H.begin());
                }
            }
        }
        if(this->debug)cout << endl << endl;

        if(this->debug){
            for(auto p : connectedComponents){
                cout << p.first << ": ";
                for(auto H : p.second){
                    cout << "{";
                    for(auto z : H)
                        cout << z << ",";
                    cout << "}";
                }
                cout << endl;
            }
            cout << endl;
        }
        

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
                    if(this->debug)cout << F << endl;
                    return true;
                }
            }while(next_permutation(F.begin(),F.end()));
        }
        
    }
    return false;
}

Graph* generate_random(int n,int m){
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(1,100);

    Graph* input = new Graph(n);

    int edges = 0;

    while(edges < m){
        for(int i=0;i<n && edges < m;i++){
            for(int j=0;j<n && edges < m;j++){
                if(i!=j && find(input->adjList[i].begin(),input->adjList[i].end(),j) == input->adjList[i].end()){
                    if( dist(rng) <= 20 ){
                        input->adjList[i].push_back(j);
                        input->adjList[j].push_back(i);
                        edges++;
                    }
                }
            }

        }
    }

    for(int i=0;i<n;i++)
        input->degree[i] = input->adjList[i].size();

    return input;
}