#include <cstdio>
#include <chrono>
#include <cmath>
#include <vector>
#include <fstream>
using namespace std;

int main (){
    printf("==== Polynomial Time Execution Data Generator ====\n");

    int m;
    printf("Max Size: ");
    scanf("%d",&m);

    int jumpSize;
    printf("Step Size: ");
    scanf("%d",&jumpSize);

    vector< pair<int,long int> > exec_times;

    for(int i=1;i<=m;i+=jumpSize){
        printf("\n ------------------------------------------------------ \n");

        printf("  Test for %d ...\n",i);


        printf("\n  Starting algorithm execution ....");

        auto start = std::chrono::high_resolution_clock::now();

        for(int j=1;j<=i;j++){
            for(int k=1;k<=log2(i);k++){
            //     for(int l=1;l<=i;l++){
            //         for(int n=1;n<=i;n++){
                        double r = 273761253/1232;
                        r = 86418113515/56448;
                        r = 54723168516/215;
                        r = 245724858115/515;
                        r = 218564815188/475;
                        r = 784318435181/541;
            //         }
            //     }
            }
        }

        auto end = std::chrono::high_resolution_clock::now();

        printf("  .... done!\n");

        auto elapsed = std::chrono::duration_cast<std::chrono::microseconds> (end - start);
        
        printf("  Execution time: %ld s\n",elapsed.count());

        exec_times.push_back( make_pair(i,elapsed.count()) );

        printf("\n ------------------------------------------------------ \n");
    }


    ofstream outFile;
    outFile.open("complexityGuide.txt");
    for(auto p : exec_times){
        outFile << p.first << " " << p.second << std::endl;
    }
    outFile.close();


    printf("======== END OF EXECUTION ========= \n");

    return 0;
}