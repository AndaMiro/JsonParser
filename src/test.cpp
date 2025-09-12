#include <Array.hpp>
#include <iostream>

int main(void){
    using namespace andamiro;
    using namespace std;

    int a = 3;
    int &b = a;
    b = 5;
    cout << a << endl;

    a = 7; 
    cout << b << endl;


    return 0;
}