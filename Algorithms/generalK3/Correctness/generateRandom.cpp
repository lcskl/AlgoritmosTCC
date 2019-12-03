#include <iostream>
#include <random>
#include <algorithm>
#include "generalT3.hpp"
using namespace std; 

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


int main (){
    int n,m;
    cin >> n >> m;

    Graph *x = generate_random(n,m);

    for(int i=0;i<n;i++){
        cout << i << ": ";
        for(auto y : x->adjList[i])
            cout << y << " ";
        cout << endl;
    }
    
    return 0;
}