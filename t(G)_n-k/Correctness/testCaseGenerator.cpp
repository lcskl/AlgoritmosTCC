#include <cmath>
#include <stack>
#include "testCaseGenerator.hpp"

Graph* generate_caterpillar(int v){
    
    Graph* inputGraph = new Graph(v);

    for(int i=0;i<v;i++){
        if( i < floor(v/2) ){
            if(i==0)
                inputGraph->degree[i] = 2;
            else 
                inputGraph->degree[i] = 3;
        }else{
            inputGraph->degree[i] = 1;
        }
    }

    for(int i=0;i<floor(v/2);i++){
        inputGraph->adjList[i].push_back(i + floor(v/2));
        inputGraph->adjList[i + floor(v/2)].push_back(i);
        if(i != floor(v/2) - 1){
            inputGraph->adjList[i].push_back(i+1);
            inputGraph->adjList[i+1].push_back(i);
        }else{
            inputGraph->adjList[i].push_back(v-1);
            inputGraph->adjList[v-1].push_back(i);
        }
    }

    return inputGraph;
}

Graph* generate_path(int v){
    Graph* inputGraph = new Graph(v);

    for(int i=0;i<v;i++){
        if(i == 0 || i == v-1)
            inputGraph->degree[i] = 1;
        else
        {
            inputGraph->degree[i] = 2;
        }
    }

    for(int i=0;i<v-1;i++){
        inputGraph->adjList[i].push_back(i+1);
        inputGraph->adjList[i+1].push_back(i);
    }

    return inputGraph;
}

Graph* generate_binary_tree(int n){
    Graph* input = new Graph(n);

    std::stack<int> next;
    next.push(0);

    for(int i=0;i<n;i++)
        input->degree[i] = 0;

    int pai,esq,dir;
    while(!next.empty()){
        pai = next.top(); next.pop();

        esq = 2*pai + 1;
        dir = 2*pai + 2;

        if(esq < n){
            input->degree[esq]++;
            input->degree[pai]++;

            input->adjList[pai].push_back(esq);
            input->adjList[esq].push_back(pai);

            next.push(esq);
        }

        if(dir < n){
            input->degree[dir]++;
            input->degree[pai]++;

            input->adjList[pai].push_back(dir);
            input->adjList[dir].push_back(pai);

            next.push(dir);
        }
    }

    return input;
}