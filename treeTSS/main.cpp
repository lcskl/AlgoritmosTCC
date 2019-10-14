#include "treeTSS.hpp"
#include <iostream>
using namespace std;

int main(){
    int n;
    cin >> n;

    Tree* t = new Tree(n);


    int n_children,child;
    for(int i=0;i<n;i++){


        cout << i << ": ";
        cin >> n_children;

        t->tree[i].degree = n_children + 1;

        for(int j=0;j<n_children;j++){
            cin >> child;
            t->tree[i].children.push_back(&t->tree[child]);
            t->tree[child].parent = &t->tree[i];
        }
    }

    cout << "Executing\n";

    t->FindTSS();

    int k = 0;
    for(auto vertex : t->tree){
        if(vertex.in_tss > 0)
            cout << k << " ";
        k++;
    }



    return 0;
}