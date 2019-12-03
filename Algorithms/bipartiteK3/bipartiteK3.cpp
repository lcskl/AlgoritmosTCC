/*
    Author: Lucas Rodrigues Keiler
    The maximum time of 2-neighbor bootstrap percolation: Complexity results
    Rudini Sampaio
    Theorem 4.1, pg 5
*/

#include <iostream>
#include "bipartiteK3.hpp"
#include <random>

Graph::Graph(int const& n_vertex){
    n = n_vertex;
    adjList.resize(n);

    infected = new int[n+1];
    degree  = new int[n+1];
    in_N_2 = new bool[n+1];
    in_N = new bool[n+1];
}

bool Graph::is_t_greater_3(){
    std::vector<int> N;
    std::vector<int> N_2;

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
            in_N[neighbor] = true;
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

        std::vector<int> infected_in_simulation;

        //Iterate over all Neighborhood
        for(auto v : N){
            infected[v] = 0;
            //Iterate over all Second Neighborhood
            for(auto s : N_2){
                infected[s] = 0;

                infected_in_simulation.clear();

                if(u == 5 && v == 9 && s == 6)
                    std::cout << "Agora: ";

                //Simulation Process
                for(int t = 1;t <= 3 && infected[u] == -1;t++){
                    
                    int neigh_infected;
                    for(int i=0;i<n;i++){
                        if(infected[i] >= 0)continue;
                        neigh_infected = 0;
                        for(auto neighbor : adjList[i]){
                            if(infected [neighbor] != -1 && infected[neighbor] < t){
                                neigh_infected++;
                                if(u == 5 && v == 9 && s == 6)
                                    std::cout << neighbor << " - Infected. Neighbor from " << i << std::endl;
                            }
                        }

                        //If 2 or more neighbors are infected...
                        if(neigh_infected >= 2){
                            infected[i] = t;
                            infected_in_simulation.push_back(i);

                            if(u == 5 && v == 9 && s == 6)
                                std::cout << t << " - Infect: " << i << std::endl;

                            if(i == u && t==3){
                                std::cout << "u: " << u << std::endl;
                                std::cout << "v: " << v << std::endl;
                                std::cout << "s: " << s << std::endl;
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

Graph* generate_random_bipartite(int n){
    Graph* input = new  Graph(n);

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(2,n-2);

    int n1 = dist(rng);

    std::uniform_int_distribution<std::mt19937::result_type> dist2(n1,n-1);
    std::uniform_int_distribution<std::mt19937::result_type> dist3(0,n1-1);

    for(int i=0;i<n1;i++){
        for(int j=n1;j<n;j++){

            if(dist(rng) % 2 ){
                input->adjList[i].push_back(j);
                input->adjList[j].push_back(i);
            }
        }
    }

    for(int i=0;i<n1;i++){
        if(input->adjList[i].size())
            continue;
        
        
        int j = dist2(rng);    

        input->adjList[i].push_back(j);
        input->adjList[j].push_back(i);
    }

    for(int i=n1;i<n;i++){
        if(input->adjList[i].size())
            continue;
        
        int j = dist3(rng);    

        input->adjList[i].push_back(j);
        input->adjList[j].push_back(i);
    }

    for(int i=0;i<n;i++)
        input->degree[i] = input->adjList[i].size();

    return input;
}



