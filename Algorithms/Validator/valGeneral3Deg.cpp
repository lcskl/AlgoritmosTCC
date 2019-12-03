#include <iostream>
#include <cstdio>
#include <cmath>
#include "infection3deg.h"
#include <ctime>
using namespace std;

int main (){
    printf("[");
    for(int t = 20;t <= 10000;t+=20){
        int n = t;

        Graph graph(n);


        graph.degree[0] = 1;
        graph.degree[n-1] = 1;

        //int y = 1,m = 1;

        int k = int(n/4 + 1);

        // while(y < n){
        //     for(int i=0;i<k-2 && y<n;i++){
                

        //         if(y == n-1){
        //             graph.degree[y++] = 3;
        //                 m+=3;
        //         }else{
        //             if(y == n-2){
        //                 graph.degree[y++] = 2;
        //                 m+=2; 
        //             }else{
        //                 graph.degree[y++] = 3;
        //                 m+=3;
        //             }
        //         } 
                
        //         if(y<n){
        //             graph.degree[y++] = 1;
        //             m++;
        //         }
        //     }
        //     if(y < n){

        //         if(y == n-1){
        //             graph.degree[y++] = 1;
        //             m+=1;
        //         }else{
        //             graph.degree[y++] = 2;
        //             m+=2;
        //         }
        //     }
        // }

        for(int i=1;i<n-1;i++){
            if(i%2)
                graph.degree[i] = 3;
            else 
                graph.degree[i] = 1;
        }


        //m/=2;

        graph.adjList[0].push_back(1);
        graph.adjList[1].push_back(0);

        for(int i=1;i<n-2;i+=2){
            graph.adjList[i].push_back(i+1);
            graph.adjList[i+1].push_back(i);

            graph.adjList[i].push_back(i+2);
            graph.adjList[i+2].push_back(i);
        }

        // y = 1;
        // while(y < n){

        //     if(graph.degree[y] == 3){
        //         if(y+1 < n){
        //             graph.adjList[y].push_back(y+1);
        //             graph.adjList[y+1].push_back(y);
        //         }

        //         if(y+2 < n){
        //             graph.adjList[y].push_back(y+2);
        //             graph.adjList[y+2].push_back(y);
        //         }

        //         y += 2;
        //     }else{
        //         if(y+1 < n){
        //             graph.adjList[y].push_back(y+1);
        //             graph.adjList[y+1].push_back(y);
        //         }
        //         y++;
        //     }           
        // }

        //DEBUG
        // for(int i=0;i<n;i++){
        //     printf("(%d) -> %d: ",i,graph.degree[i]);
        //     for(auto viz : graph.adjList[i])
        //         printf("%d, ",viz);
        //     printf("\n");
        // }
        
        

        clock_t begin = clock();

        decide(graph,k);

        //getchar();

        clock_t end = clock();

        //printf("%d\n",resp);

        printf("[%d, %f], ",n,(double)(end - begin)/CLOCKS_PER_SEC);
    }
    printf("]\n");

    return 0;
}