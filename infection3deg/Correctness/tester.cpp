#include <cstdio>
#include "infection3deg_lib.hpp"
#include <cmath>

int main (){
    
    printf("============== Correctness Tests ===================\n");

    printf(" Caterpillar Graph \n");

    //Caterplillar Graphs
    for(int i=3;i<=21;i+=2){
        Graph x = generate_caterpillar(i);

        printf("N = %d : [",i);

        for(int j=1;j<=i;j++){
            bool resp = decide(x,j);

            if((resp && j <= floor(i/2)) || (!resp && j > floor(i/2)))
                printf("+");
            else 
                printf("*");
        }

        printf("]\n\n");
    }

    printf(" Path Graph \n");

    //Path Graphs
    for(int i=3;i<=21;i+=2){
        Graph x = generate_path(i);

        printf("N = %d : [",i);

        for(int j=1;j<=i;j++){
            bool resp = decide(x,j);

            if((resp && j == 1) || (!resp && j>1))
                printf("+");
            else 
                printf("*");
        }

        printf("]\n\n");
    }

    printf(" 'Complete' Caterpillar Graph \n");

    //Caterplillar Graphs
    for(int i=4;i<=22;i+=2){
        Graph x = generate_complete_caterpillar(i);

        printf("N = %d : [",i);

        for(int j=1;j<=i;j++){
            bool resp = decide(x,j);

            if((resp && j <= floor((i-1)/2)) || (!resp && j > floor((i-1)/2)))
                printf("+");
            else 
                printf("*");
        }

        printf("]\n\n");
    }

    printf(" Infection Cycle Graph \n");

    //Infection Cycle
    for(int i=6;i<=32;i+=4){
        Graph x = generate_inf_cycle(i);

        printf("N = %d : [",i);

        for(int j=1;j<=i;j++){
            bool resp = decide(x,j);

            if((resp && j <= ((i/2 - 1)/2 + 1)) || (!resp && j > ((i/2 - 1)/2 + 1)))
                printf("+");
            else 
                printf("*");
        }

        printf("]\n\n");
    }

    return 0;
}