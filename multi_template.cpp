#include <iostream>
#include <vector>
#include <deque>
using std::cout;
using std::endl;

//函数不能偏特化

template <typename T1, typename T2>
class A
{
public:
    void f(T1 a, T2 b)
    {
        cout << "T1 T2\n";
    }
};

template <typename T>
class A<T,T>
{
public:
    void f(T a, T b)
    {
        cout << "T\n";
    }
};

template <typename T>
class A<T, double>
{
public:
    void f(T a, double b)
    {
        cout << "T int\n";
    }
};

template <typename T>
class A<T *, T *>
{
public:
    void f(T *a, T *b)
    {
        cout << "T* T*\n";
    }
};

template<typename T,typename Cont = std::vector<T>>
class Stack{
public:
    void push(T const&);
    Stack():elems(){};
    Stack (Stack const&);
    bool operator== (Stack const&);
    void pop();
    T const & top();
    void pt(std::ostream&) const;
    bool empty() const{
        return elems.empty();
    }
    template<typename U,typename Cont2>
    friend std::ostream& operator<<(std::ostream& strm,Stack<U,Cont2> const&);
    Cont elems;
};

template<typename T,typename Cont>
std::ostream& operator<<(std::ostream& strm, Stack<T, Cont> const&s){
    s.pt(strm);
    return strm;
}

template<typename T,typename Cont>
void Stack<T,Cont>::push(T const &elem){
    elems.push_back(elem);
}

template<typename T,typename Cont>
void Stack<T,Cont>::pop(){
    assert(!elems.empty());
    elems.pop_back();
}

template<typename T,typename Cont>
T const & Stack<T,Cont>::top(){
    assert(!elems.empty());
    return elems.back();
}

template<typename T,typename Cont>
void Stack<T, Cont>::pt(std::ostream& out) const {
    for(T const& it:elems)
        out<<it<<" ";
    out<<endl;
}

template<typename T,typename Cont>
Stack<T,Cont>::Stack(Stack<T,Cont> const& stack){
    elems = stack.elems;
}

template<typename T,typename Cont>
bool Stack<T,Cont>::operator==(Stack<T,Cont> const& rhs){
    return this->elems==rhs.elems;
}

int main()
{
    Stack<int, std::deque<int>>a;
    a.push(1);
    a.push(2);
    cout<<a<<endl;
    cout<<typeid(a.elems).name()<<endl;
    // int a = 3;
    // float b = 4;
    // A<int,int> test;
    // test.f(a,a);
    // A<int,double> testd;
    // testd.f(a,b);
    // A<int,float> testf;
    // testf.f(a,3.14);
    // A<int*,int*>testp;
    // testp.f(&a,&a);
    return 0;
}