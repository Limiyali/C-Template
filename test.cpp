#include <iostream>
#include <set>
using namespace std;

template<size_t... Types>
set<int> gen_set(){
    return set<int>({Types...});
}

template<typename T>
class my_alloc{

};

template<typename T,template <typename T2> class Container>
class ttp{
public:
    void pt(){
        cout << typeid(T).name()<<" "<< typeid(mcon).name()<<endl;
    }
    Container<T> mcon;
};


int main(){
    ttp<int,my_alloc> a;
    a.pt();
}