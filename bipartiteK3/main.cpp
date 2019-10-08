#include <iostream>
#include "bipartiteK3.hpp"

using namespace std;

int main (){
    int n,m;
    cin >> n >> m;

    Graph x(n);

    int a,b;

    for(int i=0;i<m;i++){
        cin >> a >> b;
        x.adjList[a].push_back(b);
        x.adjList[b].push_back(a);
    }

    for(int i=0;i<n;i++)
        x.degree[i] = x.adjList[i].size();
    
    cout << x.is_t_greater_3();

    return 0;
}