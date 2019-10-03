/*
    Author: Lucas Rodrigues Keiler
    _The maximum infection time of the P 3 convexity in graphs with bounded maximum degree_
    Rudini Sampaio
    Lemma 4.1, pg 9
*/

#include "timeNK.hpp"
#include <algorithm>

Graph::Graph(int const& n_vertex){
    n = n_vertex;
    adjList.resize(n);

    infected = new int[n+1];
    degree  = new int[n+1];
}

bool Graph::CheckInfectionTime(){
    std::string infectedTimeZero = "";

    for(int i=1;i<=k;i++){

        for(int j=0;j<n;j++){
            if(j < n-i){
                infectedTimeZero += '0';
            }else{ 
                infectedTimeZero += '1';
            }
        }

        do{
            //cout << "Try: " << infectedTimeZero << endl;

            for(int j=0;j<n;j++){
                if(infectedTimeZero[j] == '1')
                    infected[j] = 0;
                else
                {
                    infected[j] = -1;
                }          
            }

            bool infection_occured;
            int total_infected = i,current_time = 0,infected_neighbors;
            do{
                //cout << "Time: " << current_time + 1 << endl;
                infection_occured = false;

                for(int j=0;j<n;j++){
                    if(infected[j] != -1)continue;

                    infected_neighbors = 0;

                    for(auto neighbor : adjList[j]){
                        if(infected[neighbor] != -1 && infected[neighbor] <= current_time)
                            infected_neighbors++;
                    }

                    if(infected_neighbors >= 2){
                        //cout << "Infecting... " << j << endl;
                        total_infected++;
                        infected[j] = current_time + 1;
                        infection_occured = true;
                    }
                }
                current_time++;
            }while(infection_occured);

            if(total_infected == n && (current_time-1) >= n-k){
                iniInfected = infectedTimeZero;
                return true;
            }
                

        }while(next_permutation(infectedTimeZero.begin(),infectedTimeZero.end()));

        infectedTimeZero.clear();
    }
    return false;
}
