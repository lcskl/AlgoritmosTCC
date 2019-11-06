#include "treeTSS.hpp"
#include "tss_validator.hpp"
#include "randomTreeGenerator.hpp"
#include <iostream>
#include <fstream>
using namespace std;

void printTree(Tree* t){
    
    int n = t->n;
    for(int i=0;i<n;i++){
        
        cout << "Vertex: " << i << std::endl;
        cout << "   TSS Treshold: " << t->tree[i]->tss_threshold << endl;
        cout << "   In TSS? " << t->tree[i]->in_tss << endl;
        cout << "   Parent: " << flush;

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
}

int main(){    
    int n_max;
    int n_rep;

    std::cout << "Maximum number of nodes: ";
    cin >> n_max;
    std::cout << "Number of repetitions per tree size: ";
    cin >> n_rep;

    ofstream file;
    file.open("testReport.txt");

    int correct,total;

    for(int n=5;n<=n_max;n+=5){
        std::cout << n << ": " << flush;
        file << n << " ";
        total = correct = 0;
        for(int j=0;j<n_rep;j++){
            total++;

            Tree* t = generate_random_tree(n);

            t->FindTSS();
            int tss_size = 0;

            //cout << "Algorithm Response\n";
            for(int i=0;i<n;i++)
                if(t->tree[i]->in_tss == 1){
                    //cout << i << ", ";
                    tss_size++;
                }
            //cout << endl << "Size: " << tss_size << endl;

            int bruteForceResp = smallestTSS(t);

            //cout << "Brute Force Response: " << bruteForceResp << endl;

            if(tss_size == bruteForceResp){
                std::cout << "." << flush;
                correct++;
            }else{ 
                std::cout << "x - " << tss_size << " =/= " << bruteForceResp << flush;
                printTree(t);
                getchar(); getchar();
            }
            delete t;
        }
        std::cout << endl;
        file << total << " " << correct << endl;
    }
    file.close();

    return 0;
}