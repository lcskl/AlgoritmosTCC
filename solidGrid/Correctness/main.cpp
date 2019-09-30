#include "bruteForceValidator.hpp"
#include "generator.hpp"

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

    for(int n_vertices = n_min; n_vertices <= n_max; n_vertices++){

        for(int t=0;t<rep;t++){
            Graph *baseGraph = generate_random_solidGrid(n_vertices).first;
            Graph g(n_vertices);

            for(int i=0;i<baseGraph->n;i++){
                g.degree[i] = baseGraph->degree[i];
                for(auto kv : baseGraph->adjList[i]){
                    g.adjList[i].push_back(kv);
                }
            }



            int r = g.MaximumTimeSolidGrid();

            printf("Time: %d\n",r);

            bool testResult = true;

            for(int k=1;k<=n_vertices;k++){
                int time = testIfSetSizeKPercolates(*baseGraph,k);
                if(time > r){
                    printf("Time Found: %d\n",time);
                    printGraph(baseGraph);
                    getchar();
                    testResult = false;
                    break;
                }
            }

            printf("Result: %d\n",testResult);
        }

    }

    return 0;
}