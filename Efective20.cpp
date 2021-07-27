#include <iostream>
#include <string>
using std::cout;
using std::endl;

class Data{
public:
#if 0
    Data(){
        cout<<"Data()\n";
    }
    Data(Data const&){
        cout<<"Data(const &)\n";
    }
    ~Data(){
        cout<<"~Data()\n";
    }
#endif
};

class A{
public:
#if 0
    A(){
        cout<<"A()\n";
    }
    A(A const&){
        cout<<"A(const &)\n";
    }
    ~A(){
        cout<<"~A()\n";
    }
#endif
    virtual void pt(){
        cout<<"is A\n";
    }
private:
    Data d1;
    Data d2;
};

void f(A& a){
    cout <<"f(A )\n";
}

class B:public A{
public:
    virtual void pt(){
        cout <<"is b\n";
    }
};

void f2(A& a){
    a.pt();
}

int main(){
    // A a;
    // cout<<"----\n";
    // f(a);
    // cout<<"----\n";
    B b;
    cout<<"----\n";
    f2(b);
    return 0;
}