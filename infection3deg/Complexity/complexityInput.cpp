#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cmath>
using namespace std;

int main (){
    int n; //round
    cin >> n;

    int n_vertices = 1 + 3*(((int)pow(2,n-1)) - 1);

    int degree[n_vertices+1];
    int terminalThreshold = n_vertices - 3*((int)pow(2,n-2));

    for(int i=0;i<n_vertices;i++){
        if(i < terminalThreshold)
            degree[i] = 3;
        else 
            degree[i] = 1;
    }

    vector< pair<int,int> > edges;
    queue<int> current_vertex;

    int neighbor = 1,next = 0;

    while(next < terminalThreshold){
        int k = (next==0) ? 3 : 2;

        while(k--){
            current_vertex.push(neighbor);
            edges.push_back( make_pair(next,neighbor++) );
        }
        next = current_vertex.front(); current_vertex.pop();
    }

    //Output
    cout << n_vertices << endl;
    for(int i=0;i<n_vertices;i++)
        cout << degree[i] << " ";
    cout << endl;

    for(auto edge : edges)
        cout << edge.first << " " << edge.second << endl;

    return 0;
}
