#include <cstdio>
#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include "generator.h"

#define MAXN 1500100

using namespace std;

double exec_times[MAXN];
int ladders[MAXN];

int main (){
    printf("=== Start Complexity Test for Solid Grid algorithm ===\n\n");
    printf("Maximum Vertex Size: ");

    int n;
    scanf("%d",&n);

    std::ofstream outFile;
    outFile.open("complexityExecTimes.txt");

    

    printf("Starting\n");

    for(int i=10;i<=n;i+=100){

        printf("\n ------------------------------------------------------ \n");

        printf("  Test for Vertex Set Size %d  ...\n",i);

        printf("  Generating Input Graph ... ");

        pair<Graph*,int> out = generate_random_solidGrid(i);

        Graph input = *out.first;
        ladders[i] = out.second;


        printf("    done!\n  Starting algorithm execution ....");


        auto start = std::chrono::high_resolution_clock::now();

        int k = input.MaximumTimeSolidGrid();

        auto end = std::chrono::high_resolution_clock::now();

        printf("  .... done!\n");

        std::chrono::duration<double> elapsed = end - start;
        
        printf("  Execution time: %lf s\n",elapsed.count());

        exec_times[i] = elapsed.count();

        outFile << i << " " << exec_times[i] << " " << ladders[i] << std::endl;

        printf("\n ------------------------------------------------------ \n");
    }

    outFile.close();

    printf("======== END OF EXECUTION ========= \n");
}