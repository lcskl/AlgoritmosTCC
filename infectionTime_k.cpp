#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

class Graph{

public:

    int n,k;
    vector< vector<int> > adjList;
    int* infected;
    int * degree;
    string iniInfected;

    bool decide;
    int maxDepth;

    Graph(int const& n_vertex){
        n = n_vertex;
        adjList.resize(n);

        infected = new int[n+1];
        degree  = new int[n+1];
    }

    bool CheckInfectionTime(){
        string infectedTimeZero;

        for(int i=1;i<=k;i++){

            for(int j=0;j<n;j++){
                if(j < n-i){
                    infectedTimeZero += '0';
                }else{ 
                    infectedTimeZero += '1';
                }
            }

            do{
                //cout << "Try: " << infectedTimeZero << endl;

                for(int j=0;j<n;j++){
                    if(infectedTimeZero[j] == '1')
                        infected[j] = 0;
                    else
                    {
                        infected[j] = -1;
                    }          
                }

                bool infection_occured;
                int total_infected = i,current_time = 0,infected_neighbors;
                do{
                    //cout << "Time: " << current_time + 1 << endl;
                    infection_occured = false;

                    for(int j=0;j<n;j++){
                        if(infected[j] != -1)continue;

                        infected_neighbors = 0;

                        for(auto neighbor : adjList[j]){
                            if(infected[neighbor] <= current_time)
                                infected_neighbors++;
                        }

                        if(infected_neighbors >= 2){
                            //cout << "Infecting... " << j << endl;
                            total_infected++;
                            infected[j] = current_time + 1;
                            infection_occured = true;
                        }
                    }
                    current_time++;
                }while(infection_occured);

                if(total_infected == n){
                    iniInfected = infectedTimeZero;
                    return true;
                }
                    

            }while(next_permutation(infectedTimeZero.begin(),infectedTimeZero.end()));

            infectedTimeZero.clear();
        }
        return false;
    }
};

int main (){
    int n_vertex,m = 0;

    cout << "Number of vertices: ";
    cin >> n_vertex;

    Graph graph(n_vertex);

    cout << "Degree of vertices (d(v) <= 3): ";
    for(int i=0;i<n_vertex;i++){
        cin >> graph.degree[i];
        m += graph.degree[i];
    }
    m /=2;
    cout << "Describe the " << m << " edges:\n";

    int a,b;
    for(int i=0;i<m;i++){
        cin >> a >> b;
        graph.adjList[a].push_back(b);
        graph.adjList[b].push_back(a);
    }

    int k = 1;
    while(k > 0){
        cout << "Decision problem: Is t(G) >= n-k?\nValue of constant k: ";
        cin >> k;
        graph.k = k;

        bool decision = graph.CheckInfectionTime();

        cout << (decision ? "Yes" : "No") << endl;
        if(decision){
            cout << "Infected Subset at time 0: ";
            for(int i=0;i<n_vertex;i++)
                if(graph.iniInfected[i] == '1')
                    cout << i << " ";
            cout << endl;
        }
    }

    return 0;
}