#include <iostream>
#include <vector>
#include <assert.h>
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
    void pt(std::ostream&) const;
    bool empty() const{
        return elems.empty();
    }
    template<typename U>
    friend std::ostream& operator<<(std::ostream& strm,Stack<U> const&);
private:
    std::vector<T>elems;
};

template<typename T>
std::ostream& operator<<(std::ostream& strm, Stack<T> const&s){
    s.pt(strm);
    return strm;
}

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
void Stack<T>::pt(std::ostream& out) const {
    for(T const& it:elems)
        out<<it<<" ";
    out<<endl;
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
    a.push(3);
    a.push(4);
    cout<<a<<endl;

}