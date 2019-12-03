#include "bipartiteK3.hpp"
#include <iostream>
#include <random>
#include <algorithm>
using namespace std;

Graph* generate_random_bipartite_N(int n){
    Graph *input = new Graph(n);

    std::random_device dev;
    std::mt19937 rng(dev());

    int n1 = 4;
    std::uniform_int_distribution<std::mt19937::result_type> dist2(n1,n-1);
    std::uniform_int_distribution<std::mt19937::result_type> dist3(0,n1-1);

    int created = 0;

        
    for(int i=0;i<n1/2;i++){
        for(int j=n1;j<n;j++){
            if(j%2)continue;
            int v = j;
            input->adjList[i].push_back(v);
            input->adjList[v].push_back(i);
            created++;
        }
        
    }
    
    for(int i=n1/2;i<n1;i++){
        for(int j=n1;j<n;j++){
            if(j%2==0)continue;
            int v = j;
            input->adjList[i].push_back(v);
            input->adjList[v].push_back(i);
            created++;
        }
    }

    for(int i=0;i<n;i++)
        input->degree[i] = input->adjList[i].size();

    return input;
}



int main (){
    int n,m;
    cin >> n >> m;

    Graph* x = generate_random_bipartite_N(n);

    for(int i=0;i<n;i++){
        cout << i << " d(i) = " << x->degree[i] << ": ";
        for(auto neighbor : x->adjList[i])
            cout << neighbor << " ";
        cout << endl;
    }

    cout << x->is_t_greater_3() << endl;

    return 0;
}