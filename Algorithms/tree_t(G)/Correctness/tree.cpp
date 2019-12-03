#include "tree.hpp"
#include <algorithm>
#include <queue>
#include <iostream>
#include <chrono>
#define INF 999999999

Graph::Graph(int const& n_vertex){
    this->n = n_vertex;
    this->adjList.resize(n);
    this->inf_time.resize(n_vertex,-1);
    this->neighbors_remaining.resize(n_vertex,2);
    this->max_neighbor_time.resize(n_vertex,-1);
    this->perc_limit.resize(n_vertex,-1);
    this->maxS.resize(n_vertex,-1);

    this->s.resize(n_vertex);
    for(int i=0;i<n_vertex;i++){
        this->s[i].resize(n_vertex);
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
    //printf("    %d  %d\n",u,v);
    if(this->s[u][v] != -1)
        return this->s[u][v];

    if(this->inf_time[u] != -1){
        this->maxS[v] = std::max(this->maxS[v],this->inf_time[u]);
        return this->s[u][v] = this->inf_time[u];
    }

    int maxS = -1,tmp;
    for(auto x : this->adjList[u]){
        if(x != v){
            tmp = calculate(x,u);
            maxS = std::max(maxS,tmp);
        }
    }

    this->s[u][v] = 1 + maxS;
    this->maxS[v] = std::max(this->maxS[v],this->s[u][v]);

    return (this->s[u][v]);
}

int Graph::max_time(){
    std::vector< std::pair<int,int> > remaining;
    std::queue< int > ready;


    for(int x = 0;x < n; x++){
        if(this->adjList[x].size() == 1){ //Leaves always will be infected at time 0
            this->inf_time[x] = 0;
            int neighbor = this->adjList[x][0];
            this->neighbors_remaining[neighbor]--;
            this->max_neighbor_time[neighbor] = std::max(this->max_neighbor_time[neighbor],this->inf_time[x]);
            if(!this->neighbors_remaining[neighbor]){
                this->inf_time[neighbor] = 1 + this->max_neighbor_time[neighbor];
                ready.push(neighbor);
            }
        }
    }

    while(!ready.empty()){
        int v_now = ready.front(); ready.pop();

        for(auto neighbor : this->adjList[v_now]){
            if(this->inf_time[neighbor] == -1){
                this->neighbors_remaining[neighbor]--;
                this->max_neighbor_time[neighbor] = std::max(this->max_neighbor_time[neighbor],this->inf_time[v_now]);
                if(!this->neighbors_remaining[neighbor]){
                    this->inf_time[neighbor] = 1 + this->max_neighbor_time[neighbor];
                    ready.push(neighbor);
                }
            }
        }
    }

    // for(int u=0;u<n;u++)
    //     std::cout << u << " -> " << this->inf_time[u] << std::endl;
    // std::cout << std::endl;



    for(int u=0;u<n;u++){
        if(this->inf_time[u] != -1){
            for(auto v : this->adjList[u])
                this->s[u][v] = this->inf_time[u];
        }else{
            if(this->adjList[u].size() <= 2){
                for(auto v : this->adjList[u])
                    this->s[u][v] = 0;
            }else{
                for(auto v : this->adjList[u])
                    remaining.push_back( std::make_pair(u,v) );
            }
        }
    }

    for(auto edge : remaining)
        this->s[edge.first][edge.second] = calculate(edge.first,edge.second);
    
    int t_G = -1;
    for(int u=0;u<n;u++){
        if(this->inf_time[u] == -1){
            int maxU = -1;
            for(auto x : this->adjList[u])
                maxU = std::max(maxU,this->s[x][u]);
            this->inf_time[u] = 1 + maxU;
        }
        t_G = std::max(t_G, this->inf_time[u]);
    }
    return t_G;
}

int Graph::max_time_arbitrary(){
    std::vector< std::pair<int,int> > remaining;
    std::queue< int > ready;

    for(int x = 0;x < n; x++){
        if(this->adjList[x].size() < this->perc_limit[x]){ //Leaves always will be infected at time 0 in P3 Bootstrap Percolation
            this->inf_time[x] = 0;
            for(auto neighbor : this->adjList[x]){
                this->neighbors_remaining[neighbor]--;
                this->max_neighbor_time[neighbor] = std::max(this->max_neighbor_time[neighbor],this->inf_time[x]);
                if(!this->neighbors_remaining[neighbor]){
                    this->inf_time[neighbor] = 1 + this->max_neighbor_time[neighbor];
                    ready.push(neighbor);
                }
            }
            
        }
    }

    while(!ready.empty()){
        int v_now = ready.front(); ready.pop();

        for(auto neighbor : this->adjList[v_now]){
            if(this->inf_time[neighbor] == -1){
                this->neighbors_remaining[neighbor]--;
                this->max_neighbor_time[neighbor] = std::max(this->max_neighbor_time[neighbor],this->inf_time[v_now]);
                if(!this->neighbors_remaining[neighbor]){
                    this->inf_time[neighbor] = 1 + this->max_neighbor_time[neighbor];
                    ready.push(neighbor);
                }
            }
        }
    }


    for(int u=0;u<n;u++){
        if(this->inf_time[u] != -1){
            for(auto v : this->adjList[u]){
                this->s[u][v] = this->inf_time[u];
                this->maxS[v] = std::max(this->maxS[v],this->s[u][v]);
            }
        }else{
            if(this->adjList[u].size() <= this->perc_limit[u]){
                for(auto v : this->adjList[u]){
                    this->s[u][v] = 0;
                    this->maxS[v] = std::max(this->maxS[v],this->s[u][v]);
                }
            }else{
                for(auto v : this->adjList[u])
                    remaining.push_back( std::make_pair(u,v) );
            }
        }
    }

    for(auto edge : remaining){
        // printf("Calculating edge %d--%d\n",edge.first,edge.second);
        // getchar();
        this->s[edge.first][edge.second] = calculate(edge.first,edge.second);
    }
    
    // for(int i=0;i<n;i++){
    //     for(int j=0;j<n;j++){
    //         printf("%d ",this->s[i][j]);
    //     }
    //     printf("\n");
    // }


    int t_G = -1;
    for(int u=0;u<n;u++){
        //printf("u: %d ",u);
        if(this->inf_time[u] == -1)            
            this->inf_time[u] = 1 + this->maxS[u];
        //printf("inf: %d\n",this->inf_time[u]);
        t_G = std::max(t_G, this->inf_time[u]);
    }


    return t_G;
}

