#include "tree.hpp"
#include "randomTreeGenerator.hpp"
#include "bruteForceValidator.hpp"
#include <cstdio>
#include <algorithm>

int main(){
    int n_vertex,maxN,rep;
    
    printf("Max Tree size: ");
    scanf("%d",&maxN);

    printf("Repetitions per Vertex Size: ");
    scanf("%d",&rep);

    for(int i=5;i<=maxN;i++){
        printf("%d: ",i);

        n_vertex = i;

        for(int k=0;k<rep;k++){
            Graph* g = generate_random_tree(n_vertex);

            for(int l=0;l<10;l++){
                randomizePercolationLimit(g);

                int respAlg = g->max_time_arbitrary();

                int respBF = -1;
                for(int j=1;j<=n_vertex;j++){
                    respBF = std::max(respBF,testIfSetSizeKPercolates(g,j));     
                }

                char op;

                if(respBF == respAlg)
                    printf(".");
                else{ 
                    printf("x");
                    scanf(" %c",&op);
                    if(op == 's'){
                        printf("Veredict -> Alg: %d BruteForce: %d\n",respAlg,respBF);

                        printf("Tree:\n");
                        for(int i=0;i<n_vertex;i++){
                            printf("%d (%d): ",i,g->perc_limit[i]);
                            for(auto v : g->adjList[i])
                                printf("%d ",v);
                            printf("\n");
                        }
                    }
                }
            }
            printf(" / \n");

            delete g;
        }
        printf("\n");
        
    }

    // scanf("%d",&n_vertex);

    // Graph* g = new Graph(n_vertex);

    // int n_child,viz;
    // for(int i=0;i<n_vertex;i++){
    //     scanf("%d",&n_child);
    //     for(int j=0;j<n_child;j++){
    //         scanf("%d",&viz);
    //         g->add_edge(i,viz);
    //     }
    //     int l;
    //     printf("Limite: ");
    //     scanf("%d",&l);
    //     g->perc_limit[i] = g->neighbors_remaining[i] = l;
    // }

    // int resp = g->max_time_arbitrary();

    // printf("Resposta: %d\n",resp);

    return 0;
}