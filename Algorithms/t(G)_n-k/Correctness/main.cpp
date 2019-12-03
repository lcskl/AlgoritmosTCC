#include <iostream>
#include <cmath>
#include <fstream>

#include "timeNK.hpp"
#include "testCaseGenerator.hpp"

#define MAX_GRAPH_TYPES 10

void printGraph(Graph *g){
    for(int i=0;i<g->n;i++){
        printf("%d: ",i);
        for(auto neigh : g->adjList[i])
            printf(" %d",neigh);
        printf("\n");
    }
}

int main (){
    int n_types = 3;
    std::string graph_names[MAX_GRAPH_TYPES];
    graph_names[0] = "Path";
    graph_names[1] = "Caterpillar";
    graph_names[2] = "Binary Tree";
    std::cout << "Graph Classes:\n";

    for(int i=0;i<n_types;i++)
        std::cout << i+1 << " -> " << graph_names[i] << std::endl;

    int correctness_results[10][2];


    int n_min,n_max;
    std::cout << "\n(Min-Max) Vertex Set Size: ";
    std::cin >> n_min >> n_max;

    Graph* testGraph;

    std::cout << "====== Path Graph =====\n";
    correctness_results[0][0] = correctness_results[0][1] = 0;
    for(int i=n_min;i<=n_max;i++){

        testGraph = generate_path(i);

        std::cout << "N = " << i << ": "; 

        for(int k=2;k<i;k++){

            correctness_results[0][0]++;

            testGraph->k = k;
            bool resp = testGraph->CheckInfectionTime();

            if((resp && (i-k)<=1) || (!resp && (i-k)>1)){
                std::cout << "+";
                correctness_results[0][1]++;
            }else{
                std::cout << "-";
            }

            std::cout << std::flush;
        }

        std::cout << std::endl;
        delete testGraph;
    }

    std::cout << "====== Caterpillar Graph =====\n";
    correctness_results[1][0] = correctness_results[1][1] = 0;
    for(int i=n_min + (n_min%2==0);i<=n_max;i+=2){

        testGraph = generate_caterpillar(i);

        std::cout << "N = " << i << ": "; 

        for(int k=2;k<i;k++){
            correctness_results[1][0]++;

            testGraph->k = k;
            bool resp = testGraph->CheckInfectionTime();

            if((resp && (i-k) <= floor(i/2)) || (!resp && (i-k) > floor(i/2))){
                printf("+");
                correctness_results[1][1]++;
            }else 
                printf("*");

            std::cout << std::flush;
        }

        std::cout << std::endl;
        delete testGraph;
    }

    // std::cout << "====== Double Cycle Graph =====\n";
    // correctness_results[2][0] = correctness_results[2][1] = 0;
    // for(int i=n_min + (n_min%2);i<=n_max;i+=2){

    //     testGraph = generate_double_cycle(i);

    //     std::cout << "N = " << i << ": "; 

    //     for(int k=2;k<i;k++){
    //         correctness_results[2][0]++;

    //         testGraph->k = k;
    //         bool resp = testGraph->CheckInfectionTime();

    //         int expected_time = ((i/2)+ 2)/2;

    //         if(  (resp && (i-k) <=  expected_time) || (!resp && (i-k) > expected_time )  ){
    //             printf("+");
    //             correctness_results[2][1]++;
    //         }else{ 
    //             printf("* (Time = %d) (resp = %d)\n",i-k,resp);
    //             if(resp){
    //                 std::cout << testGraph->iniInfected << std::endl;
    //             }
    //             printGraph(testGraph);
    //             getchar();getchar();
    //         }

    //         std::cout << std::flush;
    //     }

    //     std::cout << std::endl;
    //     delete testGraph;
    // }

    std::cout << "====== Second Cycle Graph =====\n";
    correctness_results[3][0] = correctness_results[3][1] = 0;
    for(int i=n_min + (n_min%2);i<=n_max;i+=2){

        testGraph = generate_cycle_2(i);

        std::cout << "N = " << i << ": "; 

        for(int k=2;k<i;k++){
            correctness_results[3][0]++;

            testGraph->k = k;
            bool resp = testGraph->CheckInfectionTime();

            if((resp && (i-k) <= i/2) || (!resp && (i-k) > i/2 )){
                printf("+");
                correctness_results[3][1]++;
            }else{ 
                printf("* (Time = %d) (resp = %d)\n",i-k,resp);
                if(resp){
                    std::cout << testGraph->iniInfected << std::endl;
                }
                printGraph(testGraph);
                getchar();getchar();
            }

            std::cout << std::flush;
        }

        std::cout << std::endl;
        delete testGraph;
    }

    int h_min,h_max;
    std::cout << "\n(Min-Max) Binary Tree Height: ";
    std::cin >> h_min >> h_max;

    std::cout << "====== Binary Tree =====\n";
    correctness_results[4][0] = correctness_results[4][1] = 0;
    for(int i=h_min;i<=h_max;i++){
        
        int n = pow(2,i+1)-1;

        testGraph = generate_binary_tree(n);

        std::cout << "N = " << n << ": "; 

        for(int k=2;k<n;k++){
            correctness_results[4][0]++;

            testGraph->k = k;
            bool resp = testGraph->CheckInfectionTime();

            if((resp && (n-k) <= i) || (!resp && (n-k) > i)){
                printf("+");
                correctness_results[4][1]++;
            }else 
                printf("*");

            std::cout << std::flush;
        }

        std::cout << std::endl;
        delete testGraph;
    }

    std::ofstream outFile;
    outFile.open("CorrectnessReport.txt");

    for(int i=0;i<=4;i++)
        outFile << correctness_results[i][0] << " " << correctness_results[i][1] << std :: endl;

    outFile.close();

    return 0;
}