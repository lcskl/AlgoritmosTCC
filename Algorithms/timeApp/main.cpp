#include <iostream>

int main (){
    int n;
    std::cin >> n;

    double r = 12983.123;
    for(int i=0;i<n;i++){
        r /=123;
        r *= 123.1234;
        r *= -124.48764;
    }

    return 0;
}