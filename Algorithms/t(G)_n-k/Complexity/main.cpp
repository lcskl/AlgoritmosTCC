#include <cstdio>
#include "timeNK.hpp"
#include "testCaseGenerator.hpp"

#include <chrono>
#include <fstream>
#include <iostream>

#define MAXN 1010

double timeExec[MAXN][MAXN];

int main (){

    int maxN,maxK;

    printf("Limits for N and K: ");

    scanf("%d %d",&maxN,&maxK);

    std::ofstream outFile;
    outFile.open("complexityExecTimes.txt");

    for(int n=10;n<=maxN;n++){
        Graph *input = generate_binary_tree(n);

        printf("%d: ",n);

        for(int k=1;k<=maxK;k++){
            input->k = k;

            auto start = std::chrono::high_resolution_clock::now();

            bool resp = input->CheckInfectionTime();

            auto end = std::chrono::high_resolution_clock::now();

            timeExec[n][k] = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

            outFile << n << " " << k << " " << timeExec[n][k] << std::endl;

            printf(".");
            fflush(stdout);
        }

        printf("\n");

        delete input;
    }

    outFile.close();

    return 0;
}