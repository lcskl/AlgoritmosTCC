#include <cstdio>
#include <fstream>
#include <chrono>
#include <vector>
#include "generator.h"
using namespace std;

int main (){
    vector< pair<int,double> > times;
    for(int i=10;i<=145;i++){
        printf("Generating...");

        Graph g = generate_graph(i);

        printf("done\n");

	    auto start = chrono::steady_clock::now();

        int maxTime = g.MaximumTimeSolidGrid();

        auto end = chrono::steady_clock::now();

        auto p = make_pair(i,chrono::duration_cast<chrono::microseconds>(end - start).count()/1000.0);

        printf("%d %f\n",p.first,p.second);

        times.push_back( p );
    }

    ofstream file;
    file.open("time.txt");
    file << "X = [";
    for(auto x : times){
        file << x.first << ", ";
    }
    file << "]\nY = [";
    for(auto x : times){
        file << x.second << ", ";
    }
    file << "]\n";
    file.close();

    return 0;
}