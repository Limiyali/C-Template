#include <iostream>
#include <string>
using std::cout;
using std::endl;

class Data{
public:
    Data(){
        cout<<"Data()\n";
    }
    ~Data(){
        cout<<"~Data()\n";
    }
};

class A{
public:
    A(){
        cout<<"A()\n";
    }
    A(A const&){
        cout<<"A(const &)\n";
    }
    ~A(){
        cout<<"~A()\n";
    }
private:
    Data d1;
    Data d2;
};

void f(A a){
    cout <<"f(A )\n";
}

int main(){
    A a;
    cout<<"----\n";
    f(a);
    cout<<"----\n";
    return 0;
}