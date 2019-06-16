#include <cstdio>
#include <ctime>
using namespace std;

void quadratic(int k){
    long int a = 0;
    for(int i=0;i<k;i++){
        for(int j=0;j<k;j++){
            (a++)%10000;
        }
    }
}

void cubic(int n){
    long int a = 0;
    for(int i=0;i<n*n*n;i++){
        (a++)%10000;
        a*a;
        a/=100;
    }
}

void n5(int n){
    long int a = 0;
    for(int i=0;i<n*n*n*n*n;i++)
        (a++)%10000;
}


int main (){
    printf("[");
    for(int i=20;i<=1000;i+=10){
        clock_t begin = clock();

        cubic(i);

        clock_t end = clock();

        printf("[%d, %f], ",i,(double)(end - begin)/CLOCKS_PER_SEC);
        getchar();
    }
    printf("]");

    return 0;
}