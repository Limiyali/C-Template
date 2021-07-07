#include <iostream>
using namespace std;

template<typename T>
T check(T a){
    static_assert(sizeof(T)>=4,"T too small");
    return a;
}

int main(){
    check(5);
    cout<<"yes\n";
    char a;
    check(a);
    cout<<"yes\n";
}