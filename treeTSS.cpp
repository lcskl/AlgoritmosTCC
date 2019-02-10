#include <iostream>
#include <vector>
#include <queue>

using namespace std;

bool filhos_definidos(vector< vector<int> > arvore,int vertice,int tss [],int nivel []){
  for(auto viz : arvore[vertice])
    if(nivel[viz] < nivel[vertice] && tss[viz] < 0){
      cout << "Quebra " << viz;
      return false;
    }
  return true;
}

int main (){
  int n;
  cout << "Quantos vértices? ";
  cin >> n;

  vector < vector<int> > arvore(n, vector<int>());
  vector <int> grau(n,0);
  vector <int> pai(n,-1);

  cout << "Os vértices serão numerados de 0 a " << n << endl;
  cout << "Digite as " << n-1 << " arestas:\n";

  int a,b;
  for(int i=0;i<n-1;i++){
    cin >> a >> b;
    arvore[a].push_back(b);
    arvore[b].push_back(a);
    grau[a]++;
    grau[b]++;
  }

  int threshold[n+1];
  cout << "Digite o Threshold para cada vértice:\n";
  for(int i=0;i<n;i++){
    cout << i << ": ";
    cin >> threshold[i];
  }

  //Iterativamente retirando folhas, monta-se a estrutura hierarquica
  //da arvore, ou seja, populando o vetor pai
  vector<int> grau_aux = grau;
  int mapeados = 0;
  queue<int> fila;


  int nivel[n];

  for(int i=0;i<n;i++){
    if(grau_aux[i] == 1){
      fila.push(i);
      grau_aux[i] = -1;
      nivel[i] = 0;
    }
  }

  int davez;

  while(!fila.empty()){
    davez = fila.front();
    fila.pop();

    for(auto viz : arvore[davez]){
      if(grau_aux[viz] >= 0){
        fila.push(viz);
        nivel[viz] = nivel[davez] + 1;
        grau_aux[viz] = -1;
      }
    }
  }

  for(int i=0;i<n;i++){
    for(auto viz : arvore[i]){
      if(nivel[viz] == nivel[i]+1)
        pai[i] = viz;
    }
  }

  cout << "Árvore Mapeada\n";

  //O Target Set Selection (TSS) será denotado por vértices
  //com entradas positivas no vetor abaixo
  int tss[n+1];
  for(int i=0;i<=n;i++)
    tss[i] = -1;

  int definidos_TSS = 0;

  //Folhas não participam do TSS
  for(int i=0;i<n;i++){
    if(grau[i] == 1){
      tss[i] = 0;
      definidos_TSS++;
    }
  }

  //Algoritmo TSS para Árvores
  while(definidos_TSS < n){

    for(int i=0;i<n;i++){

      cout << ">" << i << endl;

      if(tss[i] == -1 && filhos_definidos(arvore,i,tss,nivel)){

        cout << "Analisando " << i << "..." <<  endl;

        definidos_TSS++;

        if(threshold[i] >= 2){

          cout << "threshold > 2\n";

          tss[i] = 1;
          if(pai[i] != -1){
            threshold[pai[i]]--;
            cout << "Decrescendo pai: " << pai[i] << endl;
          }
        }else{
          tss[i] = 0;
          if(pai[i] != -1 && threshold[pai[i]] <= 0)
            threshold[pai[i]]--;
        }

      }
    }
  }

  cout << "Target Set Selection:\n";

  for(int i=0;i<n;i++){
    if(tss[i]>0)cout << i << " ";
  }
  cout << endl;

  return 0;
}
