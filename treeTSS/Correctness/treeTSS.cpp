#include "treeTSS.hpp"
#include <iostream>
#include <queue>
#include <cstdio>
#include <chrono>

Tree::Tree(int const& n_vertex){
    this->n = n_vertex;
    this->tree.resize(n_vertex);

    //this->defined_vertices = 0;
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
    for(auto vertex : this->tree)
        if(vertex->in_tss == -1 && vertex->children_in_tss == (vertex->degree - (vertex->parent != nullptr)))
            vertex_ready.push(vertex);

    while(!vertex_ready.empty()){

        //printf("Operation count: %d\n",++op);

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
            if(vertex->parent->in_tss == -1 && vertex->parent->children_in_tss == (vertex->parent->degree - (vertex->parent->parent != nullptr)))
                this->vertex_ready.push(vertex->parent);
        }
    }
    return;
}

