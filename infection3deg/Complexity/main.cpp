#include "infection3deg_lib.hpp"
#include <cstdio>
#include <cmath>
#include <chrono>
#include <fstream>

int main (){
    // int n;
    // scanf("%d",&n);

    // Graph x = generate_diamond_graph(n);

    // for(int i=0;i<x.n;i++)
    //     printf("%d ",x.degree[i]);
    
    // printf("\n");

    // for(int i=0;i<x.n;i++){
    //     printf("%d: ",i);
    //     for(auto viz : x.adjList[i]){
    //         printf("%d ",viz);
    //     }
    //     printf("\n");
    // }

    printf("=== Start Complexity Test for Max 3-deg algorithm ===\n\n");
    printf("Maximum Round Size: ");

    int m;
    scanf("%d",&m);

    double exec_times[m+1];

    std::ofstream outFile;
    outFile.open("complexityExecTimes.txt");

    for(int i=2;i<=m;i++){

        printf("\n ------------------------------------------------------ \n");

        

        printf("  Generating Input Graph ... ");

        Graph input = generate_diamond_graph(i);

        printf("  Test for round %d ( Vertex Set Size %d ) ...\n",i,input.n);

        printf("    done!\n  Starting algorithm execution ....");

        int k = log2(input.n); //Assuming constant c = 1

        printf(" (k = %d) ",k);

        auto start = std::chrono::high_resolution_clock::now();

        decide(input,k);

        auto end = std::chrono::high_resolution_clock::now();

        printf("  .... done!\n");

        std::chrono::duration<double> elapsed = end - start;
        
        printf("  Execution time: %lf s\n",elapsed.count());

        exec_times[i] = elapsed.count();

        outFile << i << " " << exec_times[i] << std::endl;

        printf("\n ------------------------------------------------------ \n");
    }

    int outChoice;
    printf("Tests Ended!\n 1-Write Results to a file \n 2-Print in Console \nYour choice: ");
    scanf("%d",&outChoice);

    switch(outChoice){
        case 1:
            outFile.open("complexityExecTimes.txt");
            for(int i=2;i<=m;i++){
                int n_vertices = 1 + 3*(((int)pow(2,i-1)) - 1);
                outFile << n_vertices << " " << exec_times[i] << std::endl;
            }
            outFile.close();
            break;
        case 2:
            printf("--//----//-----//--- Test Report ----//----//----//----\n");
            for(int i=2;i<=m;i++){
                int n_vertices = 1 + 3*(((int)pow(2,i-1)) - 1);
                printf("Round: %d ---- Number of vertices: %d ---- Execution Time: %lf\n",i,n_vertices,exec_times[i]);
            }
            break;
    }

     printf("======== END OF EXECUTION ========= \n");
}