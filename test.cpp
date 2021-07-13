#include <iostream>
using namespace std;

class A{
public:
    A(){
        cout<<"A()\n";
    }
    ~A(){
        cout<<"~A()\n";
    }
};

int main(){
    A * p = new A[4];
    delete p;
    return 0;
}