#include "randomTreeGenerator.hpp"
#include <random>
#include <set>
#include <algorithm>
#include <iostream>
#include <vector>
#include <cstdio>

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


bool dfs_cycle(SimpleGraph* g, int vertex_id, int* vertex_color, int parent){
    vertex_color[vertex_id] = PROCESSING;

    for(auto neighbor : g->adjList[vertex_id]){
        if(vertex_color[neighbor] == TO_BE_VISITED){
            if(dfs_cycle(g,neighbor,vertex_color,vertex_id))
                return true;
        }else if(neighbor != parent){
            //std::cout << "Cycle " << vertex_id << " " << neighbor << " " << vertex_color[neighbor] << " " <<  parent << std::endl;
            //getchar();
            //getchar();
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
            if(dfs_cycle(g,i,vertex_color,-1)){
                delete vertex_color;
                return true;
            }
        }
    }
    delete vertex_color;
    return false;
}

void dfsTree(int v,Tree* t,SimpleGraph *g,int parent_dfs_tree,bool* visited){
    visited[v] = true;

    if(parent_dfs_tree != -1)
        t->tree[v]->parent = t->tree[parent_dfs_tree];

    for(auto neigh : g->adjList[v]){
        if(visited[neigh] == false){
            t->tree[v]->children.push_back( t->tree[neigh] );
            dfsTree(neigh,t,g,v,visited);
        }
    }
}

Tree* convert_to_rooted_tree(SimpleGraph *g){
    Tree* new_tree = new Tree(g->n);

    for(int i=0;i<g->n;i++){
        new_tree->tree[i] = new Tree::Node();
        new_tree->tree[i]->id = i;
        new_tree->tree[i]->degree = g->adjList[i].size();
        new_tree->tree[i]->parent = nullptr;
    }

    bool* visited = new bool[g->n+1]();

    int root = 0;
    for(int i = 0;i < g->n; i++)
        if(g->adjList[i].size() > g->adjList[root].size())
            root = i;
        
    dfsTree(root,new_tree,g,-1,visited);

    std::random_device rd;
    std::mt19937 gen(rd());

    bool all_one = true;

    for(auto node : new_tree->tree){
        std::uniform_int_distribution<int> dist(1, node->degree );
        node->tss_threshold = dist(gen);

        if(node->tss_threshold != 1)
            all_one = false;
    }

    if(all_one)
        new_tree->tree[root]->tss_threshold++;

    return new_tree;
}

Tree* generate_random_tree(int n){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0,n-1);

    SimpleGraph* g = new SimpleGraph(n); 

    //std::cout << "Initial set up .... done!\n";

    std::set< std::pair<int,int> > inserted_edges;

    int vert_A, vert_B;

    //std::cout << "Setting edges .... \n";

    int e = 0;
    while(e < n-1){

        //std::cout << e << ", \n";
            
        do{
            vert_A = dist(gen);
            vert_B = dist(gen);

            if(vert_A != vert_B){
                g->add_edge(vert_A,vert_B);

                //std::cout << "  Test " << vert_A << ", " << vert_B << std::flush;

                if(!has_cycle(g)){
                    //std::cout << "....ok!\n";
                    inserted_edges.insert(std::make_pair(vert_A,vert_B));
                    e++;
                }else{ 
                    //std::cout << ".... cycle detected\n";
                    g->remove_edge(vert_A,vert_B);
                }
            }
        }while(inserted_edges.find(std::make_pair(vert_A,vert_B)) == inserted_edges.end());
    }

    //std::cout << "done!\n";

    Tree* new_tree = convert_to_rooted_tree(g);

    return new_tree;
}