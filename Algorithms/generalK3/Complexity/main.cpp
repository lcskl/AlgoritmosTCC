#include "generalT3.hpp"
#include <cstdio>
#include <chrono>
#include <fstream>
#include <algorithm>

int main (){
    int max_n;
    scanf("%d",&max_n);

    std::ofstream outFile;
    outFile.open("ComplexityReport.txt");

    for(int n=10;n<=max_n;n++){
        int max_m = n*(n-1)/2;
        printf("Executing n = %d: ",n);
        for(int m=n;m<max_m;m+=5){
            
            double maxTime = -1;

            for(int k=0;k<100;k++){
                Graph* input = generate_random(n,m);

                
                auto start = std::chrono::high_resolution_clock::now();

                bool resp = input->infectsAtTime3();

                auto end = std::chrono::high_resolution_clock::now();

                std::chrono::duration<double> elapsed = end - start;

                maxTime = std::max(maxTime,elapsed.count());

                delete input;
            }

            printf("."); fflush(stdout);
            outFile << n << " " << m << " " << maxTime << std::endl;
        }
        printf("\n");
    }

    outFile.close();

    return 0;
}