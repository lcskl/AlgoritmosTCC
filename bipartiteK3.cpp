/*
    Author: Lucas Rodrigues Keiler
    The maximum time of 2-neighbor bootstrap percolation: Complexity results
    Rudini Sampaio
    Theorem 4.1, pg 5
*/

#include <iostream>
#include <vector>
using namespace std;

class Graph{

public:

    int n;
    vector< vector<int> > adjList;
    int* infected;
    int * degree;
    bool *in_N_2;
    bool *in_N;

    Graph(int const& n_vertex){
        n = n_vertex;
        adjList.resize(n);

        infected = new int[n+1];
        degree  = new int[n+1];
        in_N_2 = new bool[n+1];
        in_N = new bool[n+1];
    }

    bool is_t_greater_3(){
        vector<int> N;
        vector<int> N_2;

        for(int u=0;u<n;u++){
            N.clear();
            N_2.clear();
            
            for(int i=0;i<n;i++){
                in_N_2[i] = false;
                in_N[i] = false;
                if(degree[i] == 1) //T_0
                    infected[i] = 0;
                else
                    infected[i] = -1;
            }

            //Build Neighborhood and second Neighborhood
            for(auto neighbor : adjList[u]){
                N.push_back(neighbor);
                if(degree[neighbor] > 1)
                    infected[neighbor] = -1;

                for(auto second_neighbor : adjList[neighbor]){
                    if(second_neighbor != u && !in_N_2[second_neighbor]){
                        N_2.push_back(second_neighbor);
                        in_N_2[second_neighbor] = true;

                        if(degree[second_neighbor] > 1)
                            infected[second_neighbor] = -1;
                    }
                }
            }

            //Infect N_3
            for(int i=0;i<n;i++){
                if(!in_N_2[i] && !in_N[i] && i != u){
                    infected[i] = 0;
                }
            }

            vector<int> infected_in_simulation;
 
            //Iterate over all Neighborhood
            for(auto v : N){
                infected[v] = 0;
                //Iterate over all Second Neighborhood
                for(auto s : N_2){
                    infected[s] = 0;

                    //Simulation Process
                    for(int t = 1;t <= 3 && infected[u] == -1;t++){
                        
                        int neigh_infected;
                        for(int i=0;i<n;i++){
                            if(infected[i] >= 0)continue;
                            neigh_infected = 0;
                            for(auto neighbor : adjList[i]){
                                if(infected [neighbor] != -1 && infected[neighbor] < t)
                                    neigh_infected++;
                            }

                            //If 2 or more neighbors are infected...
                            if(neigh_infected >= 2){
                                infected[i] = t;
                                infected_in_simulation.push_back(i);

                                if(i == u && t==3){
                                    cout << "u: " << u << endl;
                                    cout << "v: " << v << endl;
                                    cout << "s: " << s << endl;
                                    return true;
                                }
                                    
                            }

                        }
                    }
                    
                    for(auto inf : infected_in_simulation)
                        infected[inf] = -1;

                    if(degree[s] > 1)
                        infected[s] = -1;
                } 
                if(degree[v] > 1)
                    infected[v] = -1;
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

    cout << graph.is_t_greater_3() << endl;

    return 0;
}