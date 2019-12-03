#include <cstdio>
#include "infection3deg_lib.hpp"

int main (){
    int n;
    scanf("%d",&n);

    Graph *x = generate_binary_tree(n);

    for(int i=0;i<n;i++)
        printf("%d ",x->degree[i]);
    
    printf("\n");
    for(int i=0;i<n;i++){
        printf("%d: ",i);
        for(auto viz : x->adjList[i]){
            printf("%d ",viz);
        }
        printf("\n");
    }   

    printf("%d\n",decide(*x,1));

    return 0;
}