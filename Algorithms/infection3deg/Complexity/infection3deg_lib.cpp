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

    // for(int i=0;i<depth;i++)cout << " ";
    // cout << vertex << endl;

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

    for(auto edge : edges){
        int v1,v2;
        v1 = edge.first;
        v2 = edge.second;

        inputGraph.adjList[v1].push_back(v2);
        inputGraph.adjList[v2].push_back(v1);
    }

    for(int i=0;i<n_vertices;i++)
        inputGraph.degree[i] = inputGraph.adjList[i].size();

    return inputGraph;
}

Graph generate_brick_wall(int n){
    int n_vertices = n*n;
    Graph out(n_vertices);

    //Horizontal edges
    for(int i=0;i<n_vertices;i++){
        if((i+1)%n!=0){
            out.adjList[i].push_back(i+1);
            out.adjList[i+1].push_back(i);
        }
    }

    //Vertical Edges
    bool even = true;
    for(int i=0;i<(n_vertices-n);i++){
        if(i && i%n==0)
            even = !even;
        
        if((even && ((i%n)%2)==0) || (!even &&  (i%n)%2)){
            out.adjList[i].push_back(i+n);
            out.adjList[i+n].push_back(i);
        }
    }

    for(int i=0;i<n_vertices;i++){
        out.degree[i] = out.adjList[i].size();
    }

    return out;
}

Graph generate_double_cycle(int n){

    Graph input(n);

    for(int i=0;i<n/2;i++){
        input.adjList[i].push_back(  ((i+1)>=(n/2)) ? 0 : (i+1) );

        input.adjList[i].push_back( ((i-1)<0) ? (n/2 -1) : (i-1) );

        input.adjList[i].push_back( i + n/2 );
        input.adjList[i + n/2].push_back(i);
    }

    for(int i=n/2;i<n;i++){
        input.adjList[i].push_back(  ((i+1)>=(n)) ? n/2 : (i+1) );

        input.adjList[i].push_back( ((i-1)<(n/2)) ? (n-1) : (i-1) );
    }

    for(int i=0;i<n;i++)
        input.degree[i] = input.adjList[i].size();

    return input;
}

Graph generate_diamond_graph(int round){
    Graph input = generate_3deg_graph(round);
    int terminalThreshold = input.n - 3*((int)pow(2,round-2));

    for(int i=terminalThreshold;i<input.n;i+=2){
        input.adjList[i].push_back( ((i+1)>=input.n) ? terminalThreshold : (i+1) );
        input.adjList[((i+1)>=input.n) ? terminalThreshold : (i+1)].push_back(i);

        input.degree[i] = 3;
        input.degree[((i+1)>=input.n) ? terminalThreshold : (i+1)] = 3;
    }

    // for(int i=0;i<input.n;i++)
    //     printf("%d ",input.degree[i]);
    // printf("\n");

    return input;
}