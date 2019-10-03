#include <iostream>

#include "timeNK.hpp"
#include "testCaseGenerator.hpp"

#define MAX_GRAPH_TYPES 10

int main (){
    int n_types = 3;
    std::string graph_names[MAX_GRAPH_TYPES];
    graph_names[0] = "Path";
    graph_names[1] = "Caterpillar";
    graph_names[2] = "Binary Tree";
    std::cout << "Graph Classes:\n";

    for(int i=0;i<n_types;i++)
        std::cout << i+1 << " -> " << graph_names[i] << std::endl;

    int n_min,n_max;
    std::cout << "\n(Min-Max) Vertex Set Size: ";
    std::cin >> n_min >> n_max;

    Graph* testGraph;

    for(int i=n_min;i<=n_max;i++){

        testGraph = generate_path(i);

        std::cout << "N = " << i << ": "; 

        for(int k=2;k<i;k++){

            testGraph->k = k;
            bool resp = testGraph->decide;

            std::cout << resp << " ";

            if((resp && (i-k)<=1) || (!resp && (i-k)>1)){
                std::cout << "+";
            }else{
                std::cout << "-";
            }

            std::cout << std::flush;
        }

        std::cout << std::endl;
        delete testGraph;
    }





    return 0;
}