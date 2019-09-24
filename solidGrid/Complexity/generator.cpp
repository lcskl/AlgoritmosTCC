#include <fstream>
#include <random>
#include <vector>
#include <iostream>
#include "generator.h"
using namespace std;

int generate_graph_segment(int lenght, Graph *g, int v_created){

    int number_ladders = 0;

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(1,50);

    int n = lenght + v_created;
    bool *in_ladder = new bool[n+1]();

    int last = 0;

    while(v_created < n){

        if( dist(rng) % 2 && v_created <= n-4){ //Ladder
            //cout << v_created << " LADDER\n";

            if(in_ladder[last] == false){
                number_ladders++;

                g->adjList[v_created].push_back ( make_pair(v_created+1,1) ); g->adjList[v_created].push_back ( make_pair(v_created+2,1) );
                g->adjList[v_created+1].push_back ( make_pair(v_created+3,1) ); g->adjList[v_created+1].push_back ( make_pair(v_created,1) );
                g->adjList[v_created+2].push_back ( make_pair(v_created+3,1) ); g->adjList[v_created+2].push_back ( make_pair(v_created,1) );
                g->adjList[v_created+3].push_back ( make_pair(v_created+1,1) ); g->adjList[v_created+3].push_back ( make_pair(v_created+2,1) );

                g->degree[v_created] = g->degree[v_created+1] = g->degree[v_created+2] = g->degree[v_created+3] = 2;
                in_ladder[v_created] = in_ladder[v_created+1] = in_ladder[v_created+2] = in_ladder[v_created+3] = true;

                if(v_created){
                    g->degree[last]++;    g->degree[v_created]++;
                    g->adjList[v_created].push_back ( make_pair(last,1) ); g->adjList[last].push_back ( make_pair(v_created,1) );
                }

                v_created += 4;

            }else{
                    g->adjList[v_created].push_back ( make_pair(v_created+1,1) ); g->adjList[v_created].push_back ( make_pair(v_created-2,1) );
                    g->adjList[v_created+1].push_back ( make_pair(last,1) ); g->adjList[v_created+1].push_back ( make_pair(v_created,1) );
                    g->degree[v_created] = g->degree[v_created+1] = 2;

                    g->adjList[v_created-2].push_back ( make_pair(v_created,1) ); g->adjList[last].push_back ( make_pair(v_created+1,1) );
                    g->degree[last]++;
                    g->degree[v_created-2]++;

                    in_ladder[v_created] = in_ladder[v_created+1] = true;
                    v_created += 2;
            }

        }else{
            if(v_created){
                //cout << v_created << " NOT LADDER\n";

                g->degree[v_created] = 1;
                if(in_ladder[last] == false){
                    g->adjList[v_created].push_back ( make_pair(last,1) ); g->adjList[last].push_back ( make_pair(v_created,1) );
                    g->degree[last]++;
                }else{
                    g->adjList[v_created].push_back ( make_pair(v_created-2,1) ); g->adjList[v_created-2].push_back ( make_pair(v_created,1) );
                    g->degree[v_created-2]++;
                }
            }

            v_created++;
        }
        last = v_created - 1;
    }
    //cout << "------ END SEGMENT ------\n";
    return number_ladders;
}

pair<Graph,int> generate_random_solidGrid(int n){
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist1(1,n-4);

    int lenght1 = dist1(rng);

    std::uniform_int_distribution<std::mt19937::result_type> dist2(1,n-lenght1-2);

    int lenght2 = dist2(rng);

    int lenght3 = n - lenght1 - lenght2 - 1;

    //std:: cout << lenght1 << " | " << lenght2 << " | " << lenght3 << std::endl;

    Graph input_graph(n);

    int total_ladders = 0;

    total_ladders += generate_graph_segment(lenght1,&input_graph,1);
    total_ladders += generate_graph_segment(lenght2,&input_graph,lenght1+1);
    total_ladders += generate_graph_segment(lenght3,&input_graph,lenght1+lenght2+1);

    //cout << "\nTotal Ladders: " << total_ladders << endl;

    return make_pair(input_graph,total_ladders);
}
