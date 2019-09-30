#include "solidGrid.hpp"
#include <vector>
#include <algorithm>
#include <map>
#include <queue>
#include <chrono>
using namespace std;

#define INF 999999999

Graph::Graph(int const& n_vertex){
    n = n_vertex;
    adjList.resize(n);

    visited = new int[n+1];
    degree  = new int[n+1];
    used = new bool[n+1];
}

int Graph::d_func(int b, int k){
    if(b == 0)
        return ( (k-1) +  2*int((k+1)/4) );
    else
        return (   k  +   2*int((k-1)/4) );
}

int Graph::calculateDistance(int other1,int other2,int b,int k){
    int deg_sum = degree[other1] + degree[other2];
    int weight = INF;
    switch(deg_sum){
        case 6:
            weight = d_func(b,k);
            break;
        case 5:
            weight = d_func(b,k-1) + 1;
            break;
        case 4:
            if(k > 2)
                weight = d_func(b,k-2) + 2;
            else
                weight = -INF;
            break; 
    }
    return weight;
}


int Graph::dfsCicle(int vertex, int income_vertex){
    visited[vertex] = vertex;

    //printf("[dfs - vertex] %d\n",vertex);

    int min_id = vertex;
    int neighbor;
    for(auto vertex_edge : adjList[vertex]){
        neighbor = vertex_edge.first;

        if(visited[neighbor] == -1){
            min_id = min(min_id,dfsCicle(neighbor,vertex));
        }else if(neighbor != income_vertex && visited[neighbor] < min_id){
            min_id = visited[neighbor];
        }
    }
    visited[vertex] = min_id;

    //printf("[dfs - min_id] %d = %d\n",vertex,min_id);

    return min_id;
}

void Graph::detectLadders(){
    for(int i = 0;i<n;i++){
        visited[i] = min(visited[i],visited[visited[i]]);
    }


    for(int i=0;i<n;i++){
        Ladder[ visited[i] ].push_back(i);
    }

    for(int i=0;i<n;i++)
        if(Ladder.find(i) != Ladder.end() &&  Ladder[i].size() == 1)
            Ladder.erase(i);
}

void Graph::Transform(){
    //Detect every cicle as every cicle in a Grid Graph is a Ladder
    //printf("[Transform] dfsCycle\n");
    //printf("1.");
    dfsCicle(0,-1);

    // for(int i=0;i<n;i++){
    //     printf("%d ",visited[i]);
    // }
    // printf("\n");

    //Arranging vertex in a Ladder set
    //printf("[Transform] detectLadders\n");
    //printf("2.");
    detectLadders();

    // for(int i=0;i<n;i++){
    //     printf("%d ",visited[i]);
    // }
    //printf("\n");

    int k; //Ladder L_k
    //printf("[Transform] iterating over ladders\n");
    //printf("3.");
    for(auto &kv : Ladder){
        k = (kv.second.size() / 2);


        vector<int> corner_vertex; //It is necessary to know the corner vertices
        for(auto vertex : kv.second){
            for(auto vertex_edge : adjList[vertex]){
                if(visited[vertex_edge.first] != visited[vertex] || degree[vertex] == 2){
                    //printf("Corner: %d\n",vertex);

                    corner_vertex.push_back(vertex);
                    break;
                }
            }
        }

        queue<int> BFSQueue;
        BFSQueue.push(corner_vertex[0]);

        int BFSvisited[n];
        for(int i=0;i<n;i++)BFSvisited[i] = -1;
        BFSvisited[corner_vertex[0]] = 0;

        int current_vertex;
        while(!BFSQueue.empty()){
            current_vertex = BFSQueue.front();
            BFSQueue.pop();

            for(auto vertex_edge : adjList[current_vertex]){
                if(visited[vertex_edge.first] == visited[current_vertex] && BFSvisited[vertex_edge.first] < 0){
                    BFSvisited[vertex_edge.first] = BFSvisited[current_vertex] + 1;
                    BFSQueue.push(vertex_edge.first);			
                }
            }
        }

        /*
            Now we can determine which vertices are adjacent, at a distance k apart, and at a distance k+1 apart.
            Below, the variables A,B,C,D will represent the topology:

                A ---- ... ---- C
                |               |
                |               |
                B ---- ... ---- D
        */

        int A,B = -1,C,D;
        A = corner_vertex[0];


        for(auto corner : corner_vertex){
            if(corner == A)continue;

            if (B == -1 && find(adjList[A].begin(),adjList[A].end(),make_pair(corner,1)) != adjList[A].end()) //'corner' is adjacent -> That's B
                B = corner;
            else if(BFSvisited[corner] == k-1) // 'corner' is at distance k from A -> That's C
                C = corner;
            else if(BFSvisited[corner] == k) // 'corner' is at distance k+1 from A -> That's D
                D = corner;
        }

        //printf("[Transform] calculating distances\n");

       
        /* We need to define the following distances:
            A to C
            B to D
            A to D
            B to C 
        */

        //First, distance K (A,C) & (B,D)
        int distance = calculateDistance(B,D,0,k);
        if(k > 2 && distance != INF){
            
            adjList[A].push_back(make_pair(C,distance));
            adjList[C].push_back(make_pair(A,distance));
        }
        

        distance = calculateDistance(A,C,0,k);
        if(k > 2 && distance != INF){
            adjList[B].push_back(make_pair(D,distance));
            adjList[D].push_back(make_pair(B,distance));
        }
        
        //Now, distance K+1 (A,D) & (B,C)
        distance = calculateDistance(B,C,1,k);
        if(distance != INF){
            adjList[A].push_back(make_pair(D,distance));
            adjList[D].push_back(make_pair(A,distance));
        }

        distance = calculateDistance(A,D,1,k);
        if(distance != INF){
            adjList[B].push_back(make_pair(C,distance));
            adjList[C].push_back(make_pair(B,distance));
        }

        //printf("[Transform] delete Vertices\n");
        //printf("4.");
        //Now, delete remaining vertices of the ladder
        for(auto vertex : kv.second){
            if(find(corner_vertex.begin(),corner_vertex.end(),vertex) == corner_vertex.end() ){
                adjList[vertex].clear();
                degree[vertex] = 0;
                continue;
            }

            for(int i=0; i < adjList[vertex].size();i++){
                if(visited[vertex] == visited[adjList[vertex][i].first] && find(corner_vertex.begin(),corner_vertex.end(),adjList[vertex][i].first) == corner_vertex.end()){
                    adjList[vertex].erase(adjList[vertex].begin()+i);
                    i--;
                }
            }
        }
        //printf("5..");
    }
}

int Graph::MaxWeightIndPath(int vertex,int vertexBeginning, int current_weight){
    used[vertex] = true;

    if(vertex != vertexBeginning && degree[vertex] == 2){
        if (degree[vertexBeginning] == 2){
        //used[vertex] = false;
            return (current_weight - 1);
        }else{
            return current_weight;
        }
    } 

    int max_weight = current_weight;
    for(auto vertex_edge : adjList[vertex]){
        int neighbor = vertex_edge.first;

        if(!used[neighbor] && degree[neighbor] >= 2 && induced(neighbor,vertex)){
            max_weight = max( max_weight, MaxWeightIndPath(neighbor,vertexBeginning,current_weight + vertex_edge.second) );
        }
    }

    //used[vertex] = false;

    return max_weight;
}

bool Graph::induced(int vertex, int last){

    for(auto vertex_edge : adjList[vertex]){
        int neighbor = vertex_edge.first;
        if(neighbor != last && used[neighbor] && vertex_edge.second == 1)
            return false;
    }

    return true;
}

int Graph::MaximumTimeSolidGrid(){

    // printf("[Start] MaximumTimeSolidGrid\n");
    // printf("[Start] Transform\n");

    for(int i=0;i<n;i++){
        visited[i] = -1;
    }

    auto start = std::chrono::high_resolution_clock::now();

    Transform();

    // auto end = std::chrono::high_resolution_clock::now();
    // //printf("T...");

    // std::chrono::duration<double> elapsed = end - start;
        
    // printf("\nTransform time: %lf s\n",elapsed.count());

    // printf("[End] Transform\n");

    //start = std::chrono::high_resolution_clock::now();

    int maxPercTime = -1;
    for(int i=0;i<n;i++){
        //Vertices need to have degree at least 2
        if(degree[i] < 2)
            continue;
        
        int percTimeI;

        for(int j=0;j<n;j++)
            used[j] = false;

        //Conditional of vertex degree
        if(degree[i] == 2)
            percTimeI = MaxWeightIndPath(i,i,0) + 1;
        else
            percTimeI = (MaxWeightIndPath(i,i,0)+2)/2;
        
        maxPercTime = max(maxPercTime,percTimeI);
    }

    // end = std::chrono::high_resolution_clock::now();
    // elapsed = end - start;
    // printf("  MaxWeight time: %lf s\n",elapsed.count());

    //printf("F...");

    return maxPercTime;
}