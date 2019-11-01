#include "randomTreeGenerator.hpp"
#include <random>
#include <set>
#include <algorithm>
#include <iostream>
#include <vector>

#define TO_BE_VISITED -1
#define PROCESSING 0
#define ENDED 1

class SimpleGraph{
public:
    int n;
    std::vector< std::vector<int> > adjList;

    SimpleGraph(int const& n_vertex){
        this->n = n_vertex;
        this->adjList.resize(n);
    }

    void add_edge(int a,int b){
        this->adjList[a].push_back(b);
        this->adjList[b].push_back(a);
    }

    void remove_edge(int a,int b){
        this->adjList[a].pop_back();
        this->adjList[b].pop_back();
    }
};


bool dfs_cycle(SimpleGraph* g, int vertex_id, int* vertex_color){
    vertex_color[vertex_id] = PROCESSING;

    for(auto neighbor : g->adjList[vertex_id]){
        if(vertex_color[neighbor] == TO_BE_VISITED && dfs_cycle(g,neighbor,vertex_color) ){
            return true;
        }
    }

    vertex_color[vertex_id] = ENDED;

    return false;
}

bool has_cycle(SimpleGraph* g){

    int* vertex_color = new int[g->n + 1];

    for(int i=0;i<g->n;i++)
        vertex_color[i] = TO_BE_VISITED;
    
    for(int i=0;i<g->n; i++){
        if(vertex_color[i] == TO_BE_VISITED){
            if(dfs_cycle(g,i,vertex_color)){
                delete vertex_color;
                return true;
            }
        }
    }
    delete vertex_color;
    return false;
}

void dfsTree(int v,Tree* t,SimpleGraph *g){


}

Tree* convert_to_rooted_tree(SimpleGraph *g){
    Tree* new_tree = new Tree(g->n);

    int root = 0;
    for(int i = 0;i < g->n; i++)
        if(g->adjList[i].size() > g->adjList[root].size())
            root = i;
        
    dfsTree(root,);
}

Tree* generate_random_tree(int n){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0,n-1);

    SimpleGraph* g = new SimpleGraph(n); 

    std::cout << "Initial set up .... done!\n";

    std::set< std::pair<int,int> > inserted_edges;

    int vert_A, vert_B;

    std::cout << "Setting edges .... \n";

    for(int e = 0; e < n-1; e++){

        std::cout << e << ", \n";
            
        do{
            vert_A = dist(gen);
            vert_B = dist(gen);

            if(vert_A != vert_B){
                g->add_edge(vert_A,vert_B);

                std::cout << "  Test " << vert_A << ", " << vert_B << std::flush;

                if(!has_cycle(g)){
                    std::cout << "....ok!\n";
                    inserted_edges.insert(std::make_pair(vert_A,vert_B));
                }else{ 
                    std::cout << ".... cycle detected\n";
                    g->remove_edge(vert_A,vert_B);
                }
            }
        }while(inserted_edges.find(std::make_pair(vert_A,vert_B)) == inserted_edges.end());
    }

    std::cout << "done!\n";




    return new_tree;
}