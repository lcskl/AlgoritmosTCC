/*
    Author: Lucas Rodrigues Keiler
    _The maximum infection time of the P 3 convexity in graphs with bounded maximum degree_
    Rudini
    Teorema 2.3, pg 3
*/

#include <iostream>
#include <vector>
#include "infection3deg.h"

using namespace std;


Graph :: Graph(int const& n_vertex){
    n = n_vertex;
    adjList.resize(n);

    visited = new bool[n+1];
    degree  = new int[n+1];
}

void Graph :: dfsInduced(int vertex, int depth){
    if(decide)return;

    visited[vertex] = true;

    if(depth == maxDepth){
        decide = true;
        return;
    }

    // for(int i=0;i<depth;i++)cout << " ";
    //     cout << vertex << endl;

    for(auto neighbor : adjList[vertex]){
        if(!visited[neighbor] && degree[neighbor] == 3 && induced(neighbor,vertex)){
            dfsInduced(neighbor,depth+1);
        }
    }

    visited[vertex] = false;

    return;
}

bool Graph :: induced(int vertex, int last){

    for(auto neighbor : adjList[vertex])
        if(neighbor != last && visited[neighbor])
            return false;

    return true;
}


bool decide(Graph graph,int k){
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

