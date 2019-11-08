#ifndef TREE_TSS_HPP
#define TREE_TSS_HPP

#include <vector>

class Tree{
public:
    struct Node{
        std::vector< Node* > children;
        Node* parent;
        int degree;

        int t_prime; 
        int in_tss;
        int tss_threshold; 

        int children_in_tss;

        int id;

        Node(){};          
    };

    int n;
    int defined_vertices;
    std::vector< Node* > tree;

    Tree(int const& n_vertex);

    void insert_edge(int a, int b);

    void delete_edge(int a,int b);

    void FindTSS();
};

#endif