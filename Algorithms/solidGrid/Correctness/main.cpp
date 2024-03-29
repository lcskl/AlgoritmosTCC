#include "bruteForceValidator.hpp"
#include "generator.hpp"

#include <fstream>
#include <chrono>

void printGraph(Graph *g){
    for(int i=0;i<g->n;i++){
        printf("%d: ",i);
        for(auto kv : g->adjList[i])
            printf(" %d",kv.first);
        printf("\n");
    }
}


int main (){
    int n_min,n_max,rep;
    printf("======== Execution Tests from Random Graphs - Solid Grid =========\n");
    printf("Vertex Set Size (min-max): ");
    scanf("%d %d",&n_min,&n_max);
    printf("Iterations for each size: ");
    scanf("%d",&rep);

    int correctnessResults[ 35 ][2];
    double time[35];
    

    for(int n_vertices = n_min; n_vertices <= n_max; n_vertices++){
        printf("\n n = %d ",n_vertices);
        correctnessResults[n_vertices][0] = correctnessResults[n_vertices][1] = 0;

        auto start = std::chrono::high_resolution_clock::now();

        for(int t=0;t<rep;t++){
            printf("."); fflush(stdout);
            correctnessResults[n_vertices][0]++;
            Graph *baseGraph = generate_random_solidGrid(n_vertices).first;
            Graph g(n_vertices);

            for(int i=0;i<baseGraph->n;i++){
                g.degree[i] = baseGraph->degree[i];
                //printf("%d (%d): ",i,g.degree[i]);
                g.adjList[i].clear();
                for(auto kv : baseGraph->adjList[i]){
                    g.adjList[i].push_back(kv);
                    //printf(" (%d,%d)",kv.first,kv.second);
                }
                //printf("\n");
            }



            int r = g.MaximumTimeSolidGrid();

            //printf("Time: %d\n",r);

            bool testResult = true;

            for(int k=1;k<=n_vertices;k++){
                int time = testIfSetSizeKPercolates(*baseGraph,k);
                if(time > r){
                    printf("Time Found: %d Time Calculated: %d\n",time,r);
                    printGraph(baseGraph);
                    getchar();
                    testResult = false;
                    break;
                }
            }

            if(testResult)
                correctnessResults[n_vertices][1]++;

            delete baseGraph;

            //printf("Result: %d\n",testResult);
        }

        auto end = std::chrono::high_resolution_clock::now();

        auto elapsed = end - start;

        printf("%d %d %lf\n",correctnessResults[n_vertices][0],correctnessResults[n_vertices][1],time[n_vertices]);

        time[n_vertices] = elapsed.count();
    }

    printf("\n Ended \n");

    std::ofstream outFile;
    outFile.open("CorrectnessReport.txt");

    for(int i=n_min;i<=n_max;i++)
        outFile << correctnessResults[i][0] << " " << correctnessResults[i][1] << " " << time[i] << std :: endl;

    outFile.close();

    return 0;
}