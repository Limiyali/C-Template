#include <iostream>
#include <string>
using std::cout;
using std::endl;

class Data{
public:
#if 1
    Data(){
        cout<<"Data()\n";
    }
    Data(Data const&){
        cout<<"Data(const &)\n";
    }
    Data(Data const&&){
        cout<<"Data(const &)\n";
    }
    ~Data(){
        cout<<"~Data()\n";
    }
    Data& operator=(Data const&){
        cout<<"Data=\n";
        return *this;
    }
#endif
};

class A{
public:
#if 1
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
    A& operator=(A const&){
        cout<<"A=\n";
        return *this;
    }
    operator Data(){
        cout<<"A to Data\n";
        Data tmp;
        cout<<&tmp<<endl;
        return tmp;
    }
private:
    Data d1;
    Data d2;
};

class B:public A{
public:
    virtual void pt(){
        cout <<"is b\n";
    }
};

void f(A a){
    cout <<"f(A )\n";
}

void f2(A a){
    a.pt();
}

int main(){
    // A a;
    // cout<<"----\n";
    // f(a);
    // cout<<"----\n";
    // B b;
    // cout<<"----\n";
    // f2(b);
    // A a;
    // A b = a;
    // b =a;
    A a;
    cout <<"----\n";
    Data d = a;
    cout<<&d<<endl;
    cout <<"----\n";
    return 0;
}