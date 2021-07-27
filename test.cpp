#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

template <typename... T>
using Void_T = void;


template <size_t... indices>
struct index_sequence {};

template <size_t N, size_t... Others>
struct make_idx_seq : public make_idx_seq<N-1, N-1, Others...> {};

template <size_t... Others>
struct make_idx_seq<0, Others...> : public index_sequence<Others...> {};


int main(){
    make_idx_seq<4>a;
    cout<<typeid(a).name()<<endl;
    return 0;
}