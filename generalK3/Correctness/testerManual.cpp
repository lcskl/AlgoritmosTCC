#include "bruteForceValidator.hpp"
#include "generalT3.hpp"
#include <iostream>
using namespace std;

int main (){
    int n,m;
    cin >> n >> m;

    Graph* x = new Graph(n);

    int a,b;
    for(int i=0;i<m;i++){
        cin >> a >> b;
        x->adjList[a].push_back(b);
        x->adjList[b].push_back(a);
    }

    for(int i=0;i<n;i++){
        x->degree[i] = x->adjList[i].size();
    }

    int time = -1;
    for(int k=2;k<=n-3;k++){
        time = max(time,testIfSetSizeKPercolates(*x,k));
    }

    cout << time << endl;

    x->debug = true;

    cout << x->infectsAtTime3() << endl;

    return 0;
}