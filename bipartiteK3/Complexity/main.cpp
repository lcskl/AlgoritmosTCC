#include <cstdio>
#include <chrono>
#include <fstream>
#include "bipartiteK3.hpp"

int main (){
    int n_min,n_max,m_max;
    printf("N_MIN N_MAX M_MAX: ");
    scanf("%d %d",&n_min,&n_max);

    std::ofstream file;
    file.open("ComplexityResults.txt");


    for(int n=n_min;n<=n_max;n+=50){
        printf("N = %d -> ",n);

        Graph* input = generate_random_bipartite_N_M(n); 

        auto start = std::chrono::high_resolution_clock::now();

        bool resp = input->is_t_greater_3();


        auto end = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> elapsed = end - start;

        file << n << " " << elapsed.count() << std::endl;

        printf(".(%d)",resp); fflush(stdout);

        delete input;

        printf("\n");
    }

    file.close();

    return 0;
}