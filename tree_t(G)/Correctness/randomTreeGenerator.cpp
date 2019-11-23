#include "randomTreeGenerator.hpp"
#include "tree.hpp"
#include <random>
#include <set>
#include <algorithm>
#include <vector>

#define TO_BE_VISITED -1
#define PROCESSING 0
#define ENDED 1


bool dfs_cycle(Graph* g, int vertex_id, int* vertex_color, int parent){
    vertex_color[vertex_id] = PROCESSING;

    for(auto neighbor : g->adjList[vertex_id]){
        if(vertex_color[neighbor] == TO_BE_VISITED){
            if(dfs_cycle(g,neighbor,vertex_color,vertex_id))
                return true;
        }else if(neighbor != parent){
            return true;
        }
    }
    vertex_color[vertex_id] = ENDED;

    return false;
}

bool has_cycle(Graph* g){

    int* vertex_color = new int[g->n + 1];

    for(int i=0;i<g->n;i++)
        vertex_color[i] = TO_BE_VISITED;
    
    for(int i=0;i<g->n; i++){
        if(vertex_color[i] == TO_BE_VISITED){
            if(dfs_cycle(g,i,vertex_color,-1)){
                delete vertex_color;
                return true;
            }
        }
    }
    delete vertex_color;
    return false;
}


Graph* generate_random_tree(int n){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0,n-1);

    Graph* g = new Graph(n); 

    std::set< std::pair<int,int> > inserted_edges;

    int vert_A, vert_B;

    int e = 0;
    while(e < n-1){
            
        do{
            vert_A = dist(gen);
            vert_B = dist(gen);

            if(vert_A != vert_B){
                g->add_edge(vert_A,vert_B);

                if(!has_cycle(g)){
                    inserted_edges.insert(std::make_pair(vert_A,vert_B));
                    e++;
                }else{ 
                    g->remove_edge(vert_A,vert_B);
                }
            }
        }while(inserted_edges.find(std::make_pair(vert_A,vert_B)) == inserted_edges.end());
    }


    return g;
}

void randomizePercolationLimit(Graph* g){
    std::random_device rd;
    std::mt19937 gen(rd());

    for(int i=0;i<g->n;i++){
        g->maxS[i] = -1;
        g->inf_time[i] = -1;
        g->max_neighbor_time[i] = -1;
        for(int j=0;j<g->n;j++)
            g->s[i][j] = -1;
    }


    for(int v = 0; v < g->n ; v++){
        std::uniform_int_distribution<int> dist(1,g->adjList[v].size()+2);
        g->perc_limit[v] = dist(gen);
        g->neighbors_remaining[v] = g->perc_limit[v];
    }
}