#include "infection3deg_lib.hpp"
#include <cmath>
#include <queue>
#include <iostream>

Graph::Graph(int const& n_vertex){
    n = n_vertex;
    adjList.resize(n);

    visited = new bool[n+1];
    degree  = new int[n+1];
}

void Graph::dfsInduced(int vertex, int depth){
    if(decide)return;

    visited[vertex] = true;

    // for(int i=0;i<depth;i++)std::cout << " ";
    // std::cout << vertex << std::endl;

    if(depth == maxDepth){
        decide = true;
        return;
    }

    for(auto neighbor : adjList[vertex]){
        if(!visited[neighbor] && degree[neighbor] == 3 && induced(neighbor,vertex)){
            dfsInduced(neighbor,depth+1);
        }
    }

    visited[vertex] = false;

    return;
}

bool Graph::induced(int vertex, int last){

    for(auto neighbor : adjList[vertex])
        if(neighbor != last && visited[neighbor])
            return false;

    return true;
}

int decide(Graph graph,int k){
    graph.decide = false;

    for(int i=0;i<graph.n;i++)
        graph.visited[i] = false;

    for(int i=0;i<graph.n && !graph.decide;i++){
        if(graph.degree[i] == 2){
            graph.maxDepth = k-1;
            graph.dfsInduced(i,0);
        }else if(graph.degree[i] == 3){
            graph.maxDepth = 2*k - 2;
            graph.dfsInduced(i,0);
        }
    }
    return graph.decide;
}

Graph generate_3deg_graph(int round){
    int n = round;

    int n_vertices = 1 + 3*(((int)pow(2,n-1)) - 1);

    int degree[n_vertices+1];
    int terminalThreshold = n_vertices - 3*((int)pow(2,n-2));

    for(int i=0;i<n_vertices;i++){
        if(i < terminalThreshold)
            degree[i] = 3;
        else 
            degree[i] = 1;
    }

    std::vector< std::pair<int,int> > edges;
    std::queue<int> current_vertex;

    int neighbor = 1,next = 0;

    while(next < terminalThreshold){
        int k = (next==0) ? 3 : 2;

        while(k--){
            current_vertex.push(neighbor);
            edges.push_back( std::make_pair(next,neighbor++) );
        }
        next = current_vertex.front(); current_vertex.pop();
    }

    //Output

    Graph inputGraph(n_vertices);

    inputGraph.degree = degree;

    for(auto edge : edges){
        int v1,v2;
        v1 = edge.first;
        v2 = edge.second;

        inputGraph.adjList[v1].push_back(v2);
        inputGraph.adjList[v2].push_back(v1);
    }
    return inputGraph;
}

Graph generate_caterpillar(int v){
    
    Graph inputGraph(v);

    for(int i=0;i<v;i++){
        if( i < floor(v/2) ){
            if(i==0)
                inputGraph.degree[i] = 2;
            else 
                inputGraph.degree[i] = 3;
        }else{
            inputGraph.degree[i] = 1;
        }
    }

    for(int i=0;i<floor(v/2);i++){
        inputGraph.adjList[i].push_back(i + floor(v/2));
        inputGraph.adjList[i + floor(v/2)].push_back(i);
        if(i != floor(v/2) - 1){
            inputGraph.adjList[i].push_back(i+1);
            inputGraph.adjList[i+1].push_back(i);
        }else{
            inputGraph.adjList[i].push_back(v-1);
            inputGraph.adjList[v-1].push_back(i);
        }
    }

    return inputGraph;
}

Graph generate_path(int v){
    Graph inputGraph(v);

    for(int i=0;i<v;i++){
        if(i == 0 || i == v-1)
            inputGraph.degree[i] = 1;
        else
        {
            inputGraph.degree[i] = 2;
        }
    }

    for(int i=0;i<v-1;i++){
        inputGraph.adjList[i].push_back(i+1);
        inputGraph.adjList[i+1].push_back(i);
    }

    return inputGraph;
}

Graph generate_complete_caterpillar(int v){
    Graph inputGraph(v);

    for(int i=0;i<v;i++){
        if( i < floor((v-1)/2) ){
            if(i==0)
                inputGraph.degree[i] = 2;
            else 
                inputGraph.degree[i] = 3;
        }else{
            inputGraph.degree[i] = 1;
        }
    }

    for(int i=0;i<floor((v-1)/2);i++){
        inputGraph.adjList[i].push_back(i + floor(v/2));
        inputGraph.adjList[i + floor(v/2)].push_back(i);
        if(i != floor(v/2) - 1){
            inputGraph.adjList[i].push_back(i+1);
            inputGraph.adjList[i+1].push_back(i);
        }else{
            inputGraph.adjList[i].push_back(v-1);
            inputGraph.adjList[v-1].push_back(i);
        }
    }

    inputGraph.adjList[0].push_back(v-1);
    inputGraph.adjList[v-1].push_back(0);

    return inputGraph;
}

Graph generate_inf_cycle(int v){

    Graph input(v);

    for(int i=0;i<v;i++){
        if(i == v/2 || i==(v/2 -1))
            input.degree[i] = 2;
        else
        {
            if(i%2)
                input.degree[i] = 1;
            else
            {
                input.degree[i] = 3;
            }
        }
    }

    for(int i=0;i<v;i++){
        if(i%2==0){
            if(i!=(v-2)){
                input.adjList[i].push_back(i+2);
                input.adjList[i+2].push_back(i);
            }

            if(i!=(v/2-1)){
                input.adjList[i].push_back(i+1);
                input.adjList[i+1].push_back(i);
            }
        }else if(i == v/2){
            input.adjList[i].push_back(0);
            input.adjList[0].push_back(i);

            input.adjList[i].push_back((v-2));
            input.adjList[v-2].push_back(i);
        }
    }

    return input;
}

