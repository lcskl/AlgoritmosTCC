#include "tree.hpp"
#include "randomTreeGenerator.hpp"
#include <cstdio>
#include <algorithm>
#include <chrono>
#include <fstream>

int main(){
    int n_vertex,maxN,rep,stepSize;
    
    printf("Max Tree size: ");
    scanf("%d",&maxN);

    printf("Repetitions per Vertex Size: ");
    scanf("%d",&rep);

    printf("Step Size: ");
    scanf("%d",&stepSize);

    std::ofstream file;
    file.open("timeReport.txt");

    for(int i=5;i<=maxN;i+=stepSize){
        printf("%d: ",i);

        n_vertex = i;

        double maxTime = -1;

        for(int k=0;k<rep;k++){
            Graph* g = generate_random_tree(n_vertex);
            randomizePercolationLimit(g);

            auto start = std::chrono::high_resolution_clock::now();

            int respAlg = g->max_time_arbitrary();

            auto end = std::chrono::high_resolution_clock::now();

            printf(".");

            std::chrono::duration<double> elapsed = end - start;

            maxTime = std::max(maxTime,elapsed.count());

            delete g;
        }
        printf("\n---------------------------------------- \n For N = %d, MaxTime = %lf \n-----------------------------------------------\n",i,maxTime);
        file << i << " " << maxTime << std::endl;
    }

    file.close();

    return 0;
}