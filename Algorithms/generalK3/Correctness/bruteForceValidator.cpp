#include <vector>
#include "bruteForceValidator.hpp"
#include <string>
#include <algorithm>
#include <iostream>

bool debug;

void cleanInfectedArray(int *infected,int n){
    for(int i=0;i<=n;i++)
        infected[i] = -1;
}

int simulate(Graph g, int* infected,int k){

    bool veredict = false;

    int total_infected, current_time, infected_neighbors;

    bool infection_occured;

    total_infected = k;
    current_time = 0;

    do{
        infection_occured = false;

        for(int i=0;i<g.n;i++){
            if(infected[i] != -1)continue;

            infected_neighbors = 0;

            for(auto neighbor : g.adjList[i]){
                if(infected[neighbor] != -1 && infected[neighbor] <= current_time){
                    infected_neighbors++;
                }
            }


            if(infected_neighbors >= 2){
                if(debug){
                    printf("Vertex %d infected in time %d\n",i,current_time+1);
                }
                infection_occured = true;
                total_infected++;
                infected[i] = current_time + 1; 
            }
        }

        current_time++;

    }while(infection_occured);

    if(total_infected == g.n)
        return current_time - 1;

    return -1;
}

int testIfSetSizeKPercolates(Graph g,int k){
    int n = g.n;
    std::string infectedSet = "";

    for(int i=0;i<n;i++){
        if(i>=(n - k))
            infectedSet.push_back('1');
        else 
            infectedSet.push_back('0');
    }

    int infected[n+1];
    int infectionTimeK = -1;

    do{
        cleanInfectedArray(infected,n);

        for(int i=0;i<n;i++){
            if(infectedSet[i] == '1')
                infected[ i ] = 0;
        }

        debug = false;
        

        infectionTimeK = simulate(g,infected,k);

        if(infectionTimeK >= 3){
            //std:: cout << "INFECTED SET: " << infectedSet << std::endl;
            break;
        }
    }while( std::next_permutation(infectedSet.begin(),infectedSet.end()));

    return infectionTimeK;
}