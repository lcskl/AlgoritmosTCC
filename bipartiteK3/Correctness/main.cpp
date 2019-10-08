#include <cstdio>
#include <fstream>
#include "bruteForceValidator.hpp"

int main (){
    int n_min,n_max,rep;
    printf("N_MIN: ");
    scanf("%d",&n_min);

    printf("N_MAX: ");
    scanf("%d",&n_max);

    printf("Repetitions per vertex size: ");
    scanf("%d",&rep);

    int correct, total;
    total = correct = 0;

    std::ofstream outFile;
    outFile.open("CorrectnessReport.txt");

    for(int i=n_min;i<=n_max;i++){
        total = correct = 0;
        for(int j=0;j<rep;j++){
            total++;
            Graph* input = generate_random_bipartite(i);

            bool algResp = input->is_t_greater_3();
            bool resp = false;
            int time = 0, aux = -1;

            for(int k=2;k<=i-3 && !resp;k++){
                time = testIfSetSizeKPercolates(*input,k);
                if(time >= 3)
                    resp = true;
                if(time > aux)
                    aux = time;
            }

            if(resp == algResp)
                correct++;
            else{
                printf("%d %d %d\n",algResp,resp,aux);
                printf("%d\n",i);
                for(int l=0;l<input->n;l++){
                    printf("\n%d: ",l);
                    for(auto neighbor: input->adjList[l])
                        printf("%d ",neighbor);
                }
                getchar(); getchar();
            }
            
            delete input;
        }
        printf("N = %d => Total: %d Correct %d\n",i,total,correct);
        outFile << i << " " << total << " " << correct << std::endl;
    }

    outFile.close();

    return 0;
}