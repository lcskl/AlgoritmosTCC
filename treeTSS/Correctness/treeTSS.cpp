#include "treeTSS.hpp"
#include <iostream>
#include <queue>
#include <cstdio>

Tree::Tree(int const& n_vertex){
    this->n = n_vertex;
    this->tree.resize(n_vertex);

    this->defined_vertices = 0;
}

void Tree::insert_edge(int a, int b){
    this->tree[a]->children.push_back( this->tree[b] );
    this->tree[a]->degree++;

    this->tree[b]->parent = this->tree[a];
    this->tree[b]->degree++;
}

//Use only if a--b edge was the last appended to vertex a!
void Tree::delete_edge(int a,int b){
    this->tree[a]->children.pop_back();
    this->tree[a]->degree--;

    this->tree[b]->degree--;
    this->tree[b]->parent = nullptr;

    std::cout << "Edge deleted\n";
}

void Tree::FindTSS(){
    for(auto vertex : tree)
        vertex->children_in_tss = 0;
    

    for(auto vertex : tree){
        vertex->t_prime = vertex->tss_threshold;

        if(vertex->degree == 1){
            vertex->in_tss = 0;
            defined_vertices+=1;

            if(vertex->parent != nullptr)
                vertex->parent->children_in_tss++;
        }else{
            vertex->in_tss = -1;
        }
    }

    std::queue<Tree::Node*> vertex_ready;
    for(auto vertex : tree)
        if(vertex->in_tss == -1 && children_defined(vertex))
            vertex_ready.push(vertex);
    
    while(!vertex_ready.empty()){

        Node* vertex = vertex_ready.front(); vertex_ready.pop();

        if(vertex->t_prime >= 2 || (vertex->t_prime == 1 && vertex->parent == nullptr)  ){
            vertex->in_tss = 1;
            if(vertex->parent != nullptr)
                vertex->parent->t_prime--;
        }else{
            vertex->in_tss = 0;
            if(vertex->t_prime <= 0 && vertex->parent != nullptr)
                vertex->parent->t_prime--;
        }

        if(vertex->parent != nullptr){
            vertex->parent->children_in_tss++;
            if(vertex->parent->children_in_tss = vertex->parent->children.size())
                vertex_ready.push(vertex->parent);
        }
    }

    // while(defined_vertices < n){
    //     int k = 0;
    //     for(auto vertex : tree){
    //         //std::cout << k++ << " " << vertex->in_tss << " " << children_defined(vertex) << std::endl; 
    //         if(vertex->in_tss == -1 && children_defined(vertex)){
                
    //             defined_vertices++;
                
    //             //std::cout << "Setting vertex: " << vertex->id << "\n";

    //             if(vertex->t_prime >= 2 || (vertex->t_prime == 1 && vertex->parent == nullptr)  ){
    //                 vertex->in_tss = 1;
    //                 if(vertex->parent != nullptr)
    //                     vertex->parent->t_prime--;
    //             }else{
    //                 vertex->in_tss = 0;
    //                 if(vertex->t_prime <= 0 && vertex->parent != nullptr)
    //                     vertex->parent->t_prime--;
    //             }
    //         }
    //     }
    // }

    return;
}

bool Tree::children_defined(Tree::Node* x){
    for(auto child : x->children){
        if(child->in_tss == -1)
            return false;
    }
    return true;
}
