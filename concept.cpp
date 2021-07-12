#include <iostream>
#include <string>
using std::cout;
using std::endl;

class Data{
public:
#if 1
    Data()=delete;
    Data(Data const&){
        cout<<"Data(const &)\n";
    }    
    Data(int){
        cout<<"Data(int)\n";
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
    A():d1(2),d2(3){
        cout<<"A()\n";
    }
    A(A const&):d1(2),d2(3){
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
        Data tmp(3);
        cout<<&tmp<<endl;
        return tmp;
    }
private:
    Data d1;
    Data d2;
};

template<typename T>
int is_d_construct(T const&rhs){
    return std::is_default_constructible<T>::value;
}

int main(){
    std::string a = "123";
    Data t(3);
    A at;
    cout<<"------\n";
    cout<<std::is_error_code_enum<int>::value<<endl;
    cout<<std::is_error_code_enum<Data>::value<<endl;
    cout<<std::is_pointer<Data*>::value<<endl;
}