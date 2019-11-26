#include <cstdio>
#include "infection3deg_lib.hpp"
#include <cmath>
#include <algorithm>
#include <fstream>

int main (){
    
    std::ofstream outFile;
    outFile.open("correctnessReport.txt");



    int total, correct;
    printf("============== Correctness Tests ===================\n");

    printf(" Caterpillar Graph \n");

    //Caterplillar Graphs
    total = correct = 0;
    for(int i=3;i<=41;i+=2){
        Graph x = generate_caterpillar(i);

        

        printf("N = %d : [",i);

        for(int j=1;j<=i;j++){
            bool resp = decide(x,j);
            total++;
            if((resp && j <= floor(i/2)) || (!resp && j > floor(i/2))){
                printf("+");
                correct++;
            }else 
                printf("*");
        }

        printf("]\n\n");
    }

    outFile << total << " " << correct << std::endl;

    printf(" Path Graph \n");

    //Path Graphs
    total = correct = 0;
    for(int i=3;i<=41;i+=2){
        Graph x = generate_path(i);

        

        printf("N = %d : [",i);

        for(int j=1;j<=i;j++){
            bool resp = decide(x,j);
            total++;
            if((resp && j == 1) || (!resp && j>1)){
                printf("+");
                correct++;
            }else 
                printf("*");
        }

        printf("]\n\n");
    }
    outFile << total << " " << correct << std::endl;

    printf(" 'Complete' Caterpillar Graph \n");

    //Complete Caterplillar Graphs
    total = correct = 0;
    for(int i=6;i<=30;i+=2){
        Graph x = generate_complete_caterpillar(i);

        printf("N = %d : [",i);

        for(int j=1;j<=i;j++){
            bool resp = decide(x,j);
            total++;
            if(  (resp && j <= floor(i/4) ) || ( !resp && j > floor(i/4) )){
                correct++;
                printf("+");
            }else 
                printf("*");
        }

        printf("]\n\n");
    }
    outFile << total << " " << correct << std::endl;
    printf(" Infection Cycle Graph \n");

    //Infection Cycle
    total = correct = 0;
    for(int i=6;i<=52;i+=4){
        Graph x = generate_inf_cycle(i);
        
        printf("N = %d : [",i);

        for(int j=1;j<=i;j++){
            bool resp = decide(x,j);
            total++;
            if((resp && j <= ((i/2 - 1)/2 + 1)) || (!resp && j > ((i/2 - 1)/2 + 1))){
                correct++;
                printf("+");
            }else 
                printf("*");
        }

        printf("]\n\n");
    }
    outFile << total << " " << correct << std::endl;
    printf(" Random Caterpillar Graph \n");

    //Random Caterpillar
    total = correct = 0;
    for(int i=6;i<=52;i+=4){
        int a = 0;
        Graph x = generate_rand_caterpillar_center2d(i,&a);
        
        printf("N = %d : [",i);

        for(int j=1;j<=x.n;j++){
            bool resp = decide(x,j);
            total++;
            if((resp && j <= (std::max(a,i-a-1)+1)) || (!resp && j > (std::max(a,i-a-1)+1))){
                printf("+");
                correct++;
            }else 
                printf("*");
        }

        printf("]\n\n");
    }
    outFile << total << " " << correct << std::endl;
    printf(" Worst 3deg Graph \n");
    total = correct = 0;
    for(int i=2;i<=9;i++){
        Graph x = generate_3deg_graph(i);

        printf("N = %d : [",i);
        
        for(int j=1;j<=x.n;j++){
            bool resp = decide(x,j);
            total++;
            if((resp && j <= (i-1)) || (!resp && j > (i-1))){
                printf("+");
                correct++;
            }else{ 
                printf("*");
            }
        }


        printf("]\n\n");
    }
    outFile << total << " " << correct << std::endl;

    printf(" Binary Tree \n");
    total = correct = 0;
    for(int i=2;i<=10;i++){
        int n = pow(2,i+1)-1;
        Graph *x = generate_binary_tree(n);

        printf("N = %d : [",n);
        
        for(int j=1;j<=x->n;j++){
            bool resp = decide(*x,j);
            total++;
            if((resp && j <= (i)) || (!resp && j > (i))){
                printf("+");
                correct++;
            }else{ 
                printf("* - (%d %d %d %d)",n,i,j,resp);
            }
        }


        printf("]\n\n");
    }
    outFile << total << " " << correct << std::endl;
    outFile.close();

    return 0;
}