#include <iostream>
#include "generator.h"
using namespace std;

int main (){
    int n;
    
    while(cin >> n && n > 0){
        Graph g = generate_graph(n);

        cout << g.n << endl;
        for(int i=0;i<g.n;i++){
            cout << g.degree[i] << " ";
        }
        cout << endl;

        for(int i=0;i<n;i++){
            for(auto v : g.adjList[i]){
                cout << v.first << " ";
            }
            cout << endl;
        }

        cout << endl;
    }

    return 0;
}