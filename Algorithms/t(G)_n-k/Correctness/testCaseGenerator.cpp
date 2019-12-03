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

Graph* generate_double_cycle(int v){
    Graph *input = new Graph(v);

    for(int i=0;i<v/2;i++){
        input->adjList[i].push_back( ((i+1)>=(v/2)) ? 0 : (i+1) );
        input->adjList[((i+1)>=(v/2)) ? 0 : (i+1)].push_back( i );
    }

    for(int i=v/2;i<v;i++){
        input->adjList[i].push_back( ((i+1)>=(v)) ? (v/2) : (i+1) );
        input->adjList[((i+1)>=(v)) ? (v/2) : (i+1)].push_back( i );

        input->adjList[i].push_back(i-(v/2));
        input->adjList[i-(v/2)].push_back(i);
    }

    for(int i=0;i<v;i++)
        input->degree[i] = input->adjList[i].size();
    
    return input;
}

Graph* generate_cycle_2(int v){
    Graph* input = new Graph(v);

    for(int i=0;i<v/2;i++){
        input->adjList[i].push_back( ((i+1)>=(v/2)) ? 0 : (i+1) );
        input->adjList[((i+1)>=(v/2)) ? 0 : (i+1)].push_back( i );
    }

    for(int i=0;i<v/2;i++){
        if(i==0){
            input->adjList[i].push_back(v/2);
            input->adjList[(v/2)].push_back( i );

            input->adjList[i].push_back( (v/2+1) );
            input->adjList[(v/2+1)].push_back( i );
        }else if (i > 1){
            input->adjList[i].push_back(i+v/2);
            input->adjList[i+(v/2)].push_back( i );
        }
    }

    for(int i=0;i<v;i++)
        input->degree[i] = input->adjList[i].size();
    
    return input;
}