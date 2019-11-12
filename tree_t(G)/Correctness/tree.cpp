#include "tree.hpp"
#include <algorithm>
#define INF 999999999

Graph::Graph(int const& n_vertex){
    this->n = n_vertex;
    this->adjList.resize(n);
    this->s = new int*[n_vertex];
    for(int i=0;i<n_vertex;i++){
        this->s[i] = new int[n_vertex]();
        for(int j=0;j<n_vertex;j++)
            this->s[i][j] = -1;
    }
}

void Graph::add_edge(int a,int b){
    this->adjList[a].push_back(b);
    this->adjList[b].push_back(a);
}

void Graph::remove_edge(int a,int b){
    this->adjList[a].pop_back();
    this->adjList[b].pop_back();
}

int Graph::calculate(int u,int v){
    if(this->s[u][v] != -1)
        return this->s[u][v];

    int min1 = INF,min2 = INF,tmp;
    for(auto x : this->adjList[u]){
        if(x != v){

            tmp = calculate(x,u);
            if(tmp < min1){
                min2 = min1;
                min1 = tmp;
            }else if(tmp < min2){
                min2 = tmp;
            }
        }
    }

    this->s[u][v] = 1 + min2;

    return (this->s[u][v]);
}

int Graph::max_time(){
    std::vector< std::pair<int,int> > remaining;

    for(int u=0;u<n;u++){
        if(this->adjList[u].size() <= 2){
            for(auto v : this->adjList[u])
                this->s[u][v] = 0;
        }else{
            for(auto v : this->adjList[u])
                remaining.push_back( std::make_pair(u,v) );
        }
    }

    for(auto edge : remaining)
        this->s[edge.first][edge.second] = calculate(edge.first,edge.second);

    int t_G = -1,t_u;

    for(int u=0;u<n;u++){
        if(this->adjList[u].size() <= 1)
            t_u = 0;
        else{
            int min1 = INF,min2 = INF;
            for(auto x : this->adjList[u])
                if(this->s[x][u] < min1){
                    min2 = min1;
                    min1 = this->s[x][u];
                }else if(this->s[x][u] < min2)
                    min2 = this->s[x][u];
            t_u = 1 + min2;
        }

        t_G = std::max(t_G,t_u);
    }
    return t_G;
}

