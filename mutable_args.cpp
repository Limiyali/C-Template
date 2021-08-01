#include <iostream>
#include <tuple>
using namespace std;

// void print(){

// }

template <typename T>
void print(T first)
{
    cout << first << " " << endl;
}

template <typename T, typename... Types>
void print(T first, Types... args)
{
    cout << first << " " << sizeof...(Types) << " " << sizeof...(args) << endl;
    // print(first);
    print(args...);
}

template <typename... Types>
auto foldSum(Types... args)
{
    return (1 + ... + args);
}

struct node
{
    node(int d) : data(d)
    {
        left = right = nullptr;
    }
    int data;
    node *left;
    node *right;
    /* data */
};

template <typename T>
class AddSpace
{
private:
    T const &ref; // refer to argument passed in constructor
public:
    AddSpace(T const &r) : ref(r){
    }
    friend std::ostream &operator<<(std::ostream &os, AddSpace<T>s)
    {
        return os << s.ref << " "; // output passed argument and a space
    }
};

template <typename T, typename... Types>
T traverse(T root, Types... paths)
{
    return (root->*...->*paths);
}

template <typename... Types>
void pt(Types... args)
{
    (cout << ... << AddSpace(args)) << endl;
}

template<typename T,typename...Types>
bool is_Same(T first, Types... args){
    return (is_same_v<T,Types> && ...);
}

template<typename T,typename... Args>
void ptIdx(T t,Args... idx){
    (cout<< ... << AddSpace(t[idx])) <<endl;
}

template<size_t... Args, typename T>
void ptIndex(T const& t){
    (cout<< ... << AddSpace(t[Args])) <<endl;
}

template<size_t... >
struct Indices{
};

template<typename T,size_t... idx>
void printByIdx(T t,Indices<idx...>){
    print(get<idx>(t)...);
}



int main()
{
    auto t = make_tuple(12, "monkeys", 2.0);
    printByIdx(t,Indices<0,1,2>());
    tuple<int,string,float>a={1,"a",0.5};
    cout<<get<2>(a);
}