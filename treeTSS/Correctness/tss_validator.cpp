#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "tss_validator.hpp"

bool simulate(int *infected, Tree* t){

    //std::cout << ".\n";

    bool infection_occured;
    int time = 1;
    int total_infected = 0;

    bool debug = (infected[1] == 0 && infected[4] == 0);

    for(int i=0;i<t->n;i++)
        if(infected[i] != -1)
            total_infected++;

    //std::cout << "*\n";

    do{
        infection_occured = false;
        int n_inf;
        for(auto vertex : t->tree){

            

            if(infected[vertex->id] != -1)
                continue;

            //if(debug)std::cout << vertex->id << std::endl;

            n_inf = 0;
            for(auto child : vertex->children)
                if( infected[child->id] != -1 && infected[child->id] < time)
                    n_inf++;


            if(vertex->parent != NULL){
                int pai = vertex->parent->id;

                if( infected[pai] != -1 && infected[pai] < time )
                    n_inf++;
            }
            
            
            if(n_inf >= vertex->tss_threshold){
                //if(debug) std::cout << "Infected\n";
                infected[vertex->id] = time;
                infection_occured = true;
                total_infected++;
            }
        }

        time++;

        //std::cout << "+\n";

    }while(infection_occured);

    if(total_infected == t->n)
        return true;
    else 
        return false;
}



int smallestTSS(Tree* t){
    int smallest_tss = -1;
    for(int tssSize=1;tssSize<=t->n && smallest_tss == -1;tssSize++){

        //std::cout << "Test size " << tssSize << std::endl;

        std::string tss = "";

        for(int i=0;i<t->n;i++){
            if(i < t->n - tssSize)
                tss.push_back('0');
            else 
                tss.push_back('1');
        }

        int* infected = new int[t->n + 1]();

        do{
            for(int i=0;i<t->n;i++){
                if(tss[i] == '1')
                    infected[i] = 0;
                else 
                    infected[i] = -1;
            }

            if ( simulate(infected,t) ){
                smallest_tss = tssSize;
                return smallest_tss;
            }    

        }while(std::next_permutation(tss.begin(),tss.end()));


    }
    return smallest_tss;
}
