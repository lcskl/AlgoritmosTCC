#include "bruteForceValidator.hpp"
#include "generalT3.hpp"
#include <cstdio>
#include <algorithm>
#include <fstream>


int main (){
    int n;
    scanf("%d",&n);

    int total, correct;
    total = correct = 0;

    std::ofstream outFile;
    outFile.open("corrGeneralT3.txt");

    for(int i=10;i<=n;i++){
        printf("N=%d: ",i);
        for(int j=i;j<2*i;j++){
            total = correct = 0;
            printf("."); fflush(stdout);
            for(int r=0;r<50;r++){
                total++;

                Graph* input = generate_random(i,j);

                bool respAlgori = input->infectsAtTime3();

                int time = -1;

                for(int k=2;k<=i-3 && time < 3;k++){
                    time = std::max(time,testIfSetSizeKPercolates(*input,k));
                }

                bool respTester = (time >= 3);


                if(respAlgori != respTester){
                    printf("\n%d =/= %d (%d)\n",respAlgori,respTester,time);

                    printf("%d %d\n",i,j);

                    for(int k=0;k<n;k++){
                        printf("\n%d: ",k);
                        for(auto y : input->adjList[k])
                            printf("%d ",y);
                    }

                    getchar(); getchar();
                }else 
                    correct++;

                delete input;
            }
            outFile << i << " " << j << " " << total << " " << correct << std::endl;
        }
        printf("\n\n");
    }
    //printf("Total: %d\nCorrect: %d\n",total,correct);
    outFile.close();
    return 0;
}