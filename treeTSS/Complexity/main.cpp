#include "treeTSS.hpp"
#include "randomTreeGenerator.hpp"
#include <iostream>
#include <fstream>
#include <chrono>
#include <algorithm>
#include <cstdint>
using namespace std;


int main(){    
    int n_max;
    int n_rep;

    std::cout << "Maximum number of nodes: ";
    cin >> n_max;
    std::cout << "Number of repetitions per tree size: ";
    cin >> n_rep;

    ofstream file;
    file.open("timeReport.txt");

    int64_t maxTime;


    for(int n=5;n<=n_max;n+=5){
        std::cout << n << ": " << flush;
        file << n << " ";

        maxTime = -1;

        for(int j=0;j<n_rep;j++){
            Tree* t = generate_random_tree(n);

            auto start = std::chrono::high_resolution_clock::now();

            t->FindTSS();

            auto end = std::chrono::high_resolution_clock::now();

            maxTime = max(maxTime, std::chrono::duration_cast<std::chrono::milliseconds>( end - start ).count() );
            
            delete t;
        }
        cout << maxTime << " <- Max time in " << n_rep << " tries\n";
        file << maxTime << endl;
    }
    file.close();

    return 0;
}