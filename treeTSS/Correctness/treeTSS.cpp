#include "treeTSS.hpp"
#include <iostream>
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
    for(auto vertex : tree){

        if(vertex->degree == 1){
            vertex->in_tss = 0;
            vertex->parent->in_tss = 1;
            defined_vertices+=2;
        }else
            vertex->in_tss = -1;
        
        //std::cout << vertex->in_tss << " ";
    }

    //getchar(); getchar();

    while(defined_vertices < n){

        int k = 0;
        for(auto vertex : tree){
            //std::cout << k++ << " " << vertex->in_tss << " " << children_defined(vertex) << std::endl; 
            if(vertex->in_tss == -1 && children_defined(vertex)){
                
                defined_vertices++;
                
                //std::cout << "Setting vertex\n";

                if(vertex->t_prime >= 2){
                    vertex->in_tss = 1;
                    if(vertex->parent != NULL)
                        vertex->parent->t_prime--;
                }else{
                    vertex->in_tss = 0;
                    if(vertex->t_prime < 0)
                        vertex->parent->t_prime--;
                }
            }
        }
    }

    return;
}

bool Tree::children_defined(Tree::Node* x){
    for(auto child : x->children){
        if(child->in_tss == -1)
            return false;
    }
    return true;
}
