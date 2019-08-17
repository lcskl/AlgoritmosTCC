#include <fstream>
#include <random>
#include <vector>
#include <iostream>
#include "generator.h"
using namespace std;

Graph::Graph(int const& n_vertex){
    n = n_vertex;
    adjList.resize(n);

    visited = new int[n+1];
    degree  = new int[n+1];
    used = new bool[n+1];
}

Graph generate_graph(int n){
    Graph g(n);

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(1,50);

    int v_created = 0;
    bool *in_ladder = new bool[n+1]();

    while(v_created < n){

        if( dist(rng) % 2 && v_created <= n-4){ //Ladder

            if(v_created == 0 || in_ladder[v_created-1] == false){
                g.adjList[v_created].push_back ( make_pair(v_created+1,1) ); g.adjList[v_created].push_back ( make_pair(v_created+2,1) );
                g.adjList[v_created+1].push_back ( make_pair(v_created+3,1) ); g.adjList[v_created+1].push_back ( make_pair(v_created,1) );
                g.adjList[v_created+2].push_back ( make_pair(v_created+3,1) ); g.adjList[v_created+2].push_back ( make_pair(v_created,1) );
                g.adjList[v_created+3].push_back ( make_pair(v_created+1,1) ); g.adjList[v_created+3].push_back ( make_pair(v_created+2,1) );

                g.degree[v_created] = g.degree[v_created+1] = g.degree[v_created+2] = g.degree[v_created+3] = 2;
                in_ladder[v_created] = in_ladder[v_created+1] = in_ladder[v_created+2] = in_ladder[v_created+3] = true;

                if(v_created){
                    g.degree[v_created-1]++;    g.degree[v_created]++;
                    g.adjList[v_created].push_back ( make_pair(v_created-1,1) ); g.adjList[v_created-1].push_back ( make_pair(v_created,1) );
                }

                v_created += 4;

            }else{
                    g.adjList[v_created].push_back ( make_pair(v_created+1,1) ); g.adjList[v_created].push_back ( make_pair(v_created-2,1) );
                    g.adjList[v_created+1].push_back ( make_pair(v_created-1,1) ); g.adjList[v_created+1].push_back ( make_pair(v_created,1) );
                    g.degree[v_created] = g.degree[v_created+1] = 2;

                    g.adjList[v_created-2].push_back ( make_pair(v_created,1) ); g.adjList[v_created-1].push_back ( make_pair(v_created+1,1) );
                    g.degree[v_created-1]++;
                    g.degree[v_created-2]++;

                    in_ladder[v_created] = in_ladder[v_created+1] = true;
                    v_created += 2;
            }

        }else{
            if(v_created){
                g.degree[v_created] = 1;
                if(in_ladder[v_created-1] == false){
                    g.adjList[v_created].push_back ( make_pair(v_created-1,1) ); g.adjList[v_created-1].push_back ( make_pair(v_created,1) );
                    g.degree[v_created-1]++;
                }else{
                    g.adjList[v_created].push_back ( make_pair(v_created-2,1) ); g.adjList[v_created-2].push_back ( make_pair(v_created,1) );
                    g.degree[v_created-2]++;
                }
            }

            v_created++;
        }
    }
    for(int i=0;i<n;i++)
        cout << in_ladder[i] << " ";
    cout << endl << endl;

    return g;
}

