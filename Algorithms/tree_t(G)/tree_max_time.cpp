#include <cstdio>
#include <vector>
#define INF 999999999
using namespace std;

class Graph{
public:
    int n;
    int** s;
    vector< vector<int> > adjList;

    Graph(int const& n_vertex){
        n = n_vertex;
        adjList.resize(n);
        s = new int*[n_vertex];
        for(int i=0;i<n_vertex;i++){
            s[i] = new int[n_vertex]();
            for(int j=0;j<n_vertex;j++)
                s[i][j] = -1;
        }
    }
};

int calculate(Graph *t,int u,int v){

    if(t->s[u][v] != -1)
        return t->s[u][v];

    int min1 = INF,min2 = INF,tmp;
    for(auto x : t->adjList[u]){
        if(x != v){

            tmp = calculate(t,x,u);
            if(tmp < min1){
                min2 = min1;
                min1 = tmp;
            }else if(tmp < min2){
                min2 = tmp;
            }
        }
    }

    t->s[u][v] = 1 + min2;

    return (t->s[u][v]);
}

int main (){
    int n,m;
    printf("Number of vertices: ");
    scanf("%d",&n);

    m = n-1;

    Graph *tree = new Graph(n);

    int a,b;
    for(int i=0;i<m;i++){
        scanf("%d %d",&a,&b);
        tree->adjList[a].push_back(b);
        tree->adjList[b].push_back(a);
    }

    vector< pair<int,int> > remaining;

    for(int u=0;u<n;u++){
        if(tree->adjList[u].size() <= 2){
            for(auto v : tree->adjList[u])
                tree->s[u][v] = 0;
        }else{
            for(auto v : tree->adjList[u])
                remaining.push_back( make_pair(u,v) );
        }
    }

    for(auto edge : remaining)
        tree->s[edge.first][edge.second] = calculate(tree,edge.first,edge.second);

    int t_G = -1,t_u;

    for(int u=0;u<n;u++){
        if(tree->adjList[u].size() <= 1)
            t_u = 0;
        else{
            int min1 = INF,min2 = INF;
            for(auto x : tree->adjList[u])
                if(tree->s[x][u] < min1){
                    min2 = min1;
                    min1 = tree->s[x][u];
                }else if(tree->s[x][u] < min2)
                    min2 = tree->s[x][u];
            t_u = 1 + min2;
        }

        t_G = max(t_G,t_u);
    }

    printf("Maximum Infection Time -> t(G) = %d\n",t_G);


    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++)
            printf("%d ",tree->s[i][j]);
        printf("\n");
    }

    return 0;
}