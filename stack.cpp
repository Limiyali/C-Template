#include <iostream>
#include <vector>
#include <string>
#include <assert.h>
#include <deque>
using std::cout;
using std::endl;
using std::begin;
using std::end;
using std::string;
using std::deque;

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

template<>
class Stack<string>{
public:
    void push(string const&);
    Stack():elems(){
        cout<<"string\n";
    };
    Stack (Stack const&);
    bool operator== (Stack const&);
    void pop();
    string const & top();
    void pt(std::ostream&) const;
    bool empty() const{
        return elems.empty();
    }
    friend std::ostream& operator<<(std::ostream& strm,Stack<string> const&);
private:
    std::deque<string> elems;
};

std::ostream& operator<<(std::ostream& strm, Stack<string> const&s){
    s.pt(strm);
    return strm;
}

void Stack<string>::push(string const &elem){
    elems.push_back(elem);
}

void Stack<string>::pop(){
    assert(!elems.empty());
    elems.pop_back();
}

string const & Stack<string>::top(){
    assert(!elems.empty());
    return elems.back();
}

void Stack<string>::pt(std::ostream& out) const {
    for(string const& it:elems)
        out<<it<<" ";
    out<<endl;
}

Stack<string>::Stack(Stack<string> const& stack){
    elems = stack.elems;
}

bool Stack<string>::operator==(Stack<string> const& rhs){
    return this->elems==rhs.elems;
}

template<typename T>
class Stack<T*>{
public:
    void push(T* const&);
    Stack():elems(){
        cout<<"T*\n";
    };
    Stack (Stack const&);
    bool operator== (Stack const&);
    void pop();
    T* top();
    void pt(std::ostream&) const;
    bool empty() const{
        return elems.empty();
    }
    template<typename U>
    friend std::ostream& operator<<(std::ostream& strm,Stack<U*> const&);
private:
    std::vector<T*>elems;
};

template<typename T>
std::ostream& operator<<(std::ostream& strm, Stack<T*> const&s){
    s.pt(strm);
    return strm;
}

template<typename T>
void Stack<T*>::push(T* const &elem){
    elems.push_back(elem);
}

template<typename T>
void Stack<T*>::pop(){
    assert(!elems.empty());
    elems.pop_back();
}

template<typename T>
T* Stack<T*>::top(){
    assert(!elems.empty());
    return elems.back();
}

template<typename T>
void Stack<T*>::pt(std::ostream& out) const {
    for(T* const& it:elems)
        out<<*it<<" ";
    out<<endl;
}

template<typename T>
Stack<T*>::Stack(Stack<T*> const& stack){
    elems = stack.elems;
}

template<typename T>
bool Stack<T*>::operator==(Stack<T*> const& rhs){
    return this->elems==rhs.elems;
}



int main(){
    Stack<int*>a;
    a.push(new int{1});
    a.push(new int{2});
    a.pt(cout);
    delete a.top();
    a.pop();
    cout<<a<<endl;
    return 0;
}