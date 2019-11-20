#include <vector>
#include "bruteForceValidator.hpp"
#include <string>
#include <algorithm>

void cleanInfectedArray(int *infected,int n,std::vector<int> infected_at_0){
    for(int i=0;i<=n;i++)
        infected[i] = -1;
    for(auto vertex : infected_at_0)
        infected[vertex] = 0;
}

int simulate(Graph *g, int* infected,int k){

    bool veredict = false;

    int total_infected, current_time, infected_neighbors;

    bool infection_occured;

    total_infected = k;
    current_time = 0;

    do{
        infection_occured = false;

        for(int i=0;i<g->n;i++){
            if(infected[i] != -1)continue;

            infected_neighbors = 0;

            for(auto x : g->adjList[i]){
                if(infected[x] != -1 && infected[x] <= current_time){
                    infected_neighbors++;
                }
            }


            if(infected_neighbors >= g->perc_limit[i]){
                infection_occured = true;
                total_infected++;
                infected[i] = current_time + 1; 
            }
        }

        current_time++;

    }while(infection_occured);

    if(total_infected == g->n)
        return current_time - 1;

    return -1;
}

int testIfSetSizeKPercolates(Graph *g,int k){
    int n = g->n;
    std::vector<int> infected_at_0;
    std::vector<int> remainingVertices;

    //Detect degree 1 vertices
    for(int i=0;i<g->n;i++){
        if(g->adjList[i].size() == 1){
            infected_at_0.push_back(i);
        }else
        {
            remainingVertices.push_back(i);
        }
    }

    int permutationVertices = remainingVertices.size();
    std::string infectedSet = "";

    for(int i=0;i<permutationVertices;i++){
        if(i>=(permutationVertices - (k - infected_at_0.size())))
            infectedSet.push_back('1');
        else 
            infectedSet.push_back('0');
    }

    int infected[n+1];
    int infectionTimeK = -1;
    int maxTime = -1;

    do{
        cleanInfectedArray(infected,n,infected_at_0);

        for(int i=0;i<permutationVertices;i++){
            if(infectedSet[i] == '1')
                infected[ remainingVertices[i] ] = 0;
        }

        infectionTimeK = simulate(g,infected,k);

        if(infectionTimeK != -1)
            maxTime = std::max(maxTime,infectionTimeK);

    }while( std::next_permutation(infectedSet.begin(),infectedSet.end()));

    return maxTime;
}