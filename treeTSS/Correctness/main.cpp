#include "treeTSS.hpp"
#include "tss_validator.hpp"
#include "randomTreeGenerator.hpp"
#include <iostream>
using namespace std;

int main(){
    int n;
    cin >> n;

    cout << "Generating new tree...\n";

    Tree* t = generate_random_tree(n);

    cout << "done! \n";

    for(int i=0;i<n;i++){
        
        cout << "Vertex: " << i << std::endl;
        cout << "   Parent: ";

        if(t->tree[i]->parent != nullptr)
            cout << t->tree[i]->parent->id << std::endl;
        else 
            cout << "NULL" << std::endl;
        
        cout << "   Children: ";

        for(auto child : t->tree[i]->children){
            cout << child->id << " ";
        }

        cout << endl;
    }

    return 0;
}