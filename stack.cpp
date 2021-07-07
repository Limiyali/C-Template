#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::begin;
using std::end;

template<typename T>
class Stack{
public:
    void push(T const&);
    Stack():elems(){};
    Stack (Stack const&);
    bool operator== (Stack const&);
    void pop();
    T const & top();
    void pt();
    bool empty() const{
        return elems.empty();
    }
private:
    std::vector<T>elems;
};

template<typename T>
void Stack<T>::push(T const &elem){
    elems.push_back(elem);
}

template<typename T>
void Stack<T>::pop(){
    assert(!elems.empty());
    elems.pop_back();
}

template<typename T>
T const & Stack<T>::top(){
    assert(!elems.empty());
    return elems.back();
}

template<typename T>
void Stack<T>::pt(){
    for(auto it:elems)
        cout<<it<<" ";
    cout<<endl;
}

template<typename T>
Stack<T>::Stack(Stack<T> const& stack){
    elems = stack.elems;
}

template<typename T>
bool Stack<T>::operator==(Stack<T> const& rhs){
    return this->elems==rhs.elems;
}


int main(){
    Stack<int>a;
    a.push(1);
    a.push(2);
    a.pt();
    Stack<int>b(a);
    b.pt();
    cout<<(a==b)<<endl;
}