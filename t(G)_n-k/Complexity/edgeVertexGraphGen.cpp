#include <iostream>
#include "timeNK.hpp"
#include <algorithm>

#include <fstream>
#include <chrono>
#include <cstdio>

Graph* generate_graph_n_m(int n,int m){
    Graph* input = new Graph(n);

    for(int i=0;i<n;i++){
        input->adjList[i].push_back( (i>=n-1) ? 0 : (i+1) );
        input->adjList[(i>=n-1) ? 0 : (i+1)].push_back(i);
    }

    int remaining = m - n;
    int e = 0,v = 0;

    while(e < remaining){

        

        for(int i=0;i<n-1;i++){
            if(i == v || (std::find(input->adjList[v].begin(),input->adjList[v].end(),i) != input->adjList[v].end()))
                continue;

            input->adjList[v].push_back( i );
            input->adjList[i].push_back( v );
            e++;

            if(e >= remaining)
                break;

        }

        v++;
    }

    for(int i=0;i<n;i++)
        input->degree[i] = input->adjList[i].size();

    return input;
}

void test_n_m(int n_max){

    Graph* input;
    double timeExec;

    std::ofstream file;
    file.open("test.txt");

    for(int n=60;n<=n_max;n+=10){

        int limit = (n*(n-1))/2;

        printf("N = %d: ",n);
        fflush(stdin);

        for(int m=n;m<=limit;m+=200){
            printf(".");
            fflush(stdin);

            input = generate_graph_n_m(n,m);

            input->k = 1;

            auto start = std::chrono::high_resolution_clock::now();

            bool resp = input->CheckInfectionTime();

            auto end = std::chrono::high_resolution_clock::now();

            timeExec = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

            file << n << " " << m << " " << timeExec << std::endl;

        }

        std::cout << std::endl;

        delete input;
    }

    file.close();
}


int main (){
    int n;

    std::cin >> n;

    test_n_m(n);


    return 0;
}