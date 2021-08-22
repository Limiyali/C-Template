#include <iostream>
#include <set>
#include <cassert>
#include <tuple>
#include "utils/type.h"
#include "utils/utils.h"
using namespace std;
#define link(x,y) x##y
#define toString(x) #x

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

template <bool> struct CompileTimeChecker
{
CompileTimeChecker(...);
};

template<> struct CompileTimeChecker<false> { };

#define STATIC_CHECK(expr, msg)                                                \
  {                                                                            \
    class ERROR_##msg {};                                                      \
    (void)sizeof(CompileTimeChecker<(expr) != 0>((ERROR_##msg())));            \
  }

  // https://segmentfault.com/a/1190000023442174

template <class To, class From>
To safe_cast(From from)
{
  STATIC_CHECK(sizeof(From) <= sizeof(To),
  Destination_Type_Too_Narrow);
  return static_cast<To>(from);
}

int main(int argc, char** argv) {
    // class ERROR_12 {};
    // ERROR_12 f;
    // CompileTimeChecker<true>aa(f);
    // CompileTimeChecker<false>bb(f);
    // int64_t a;
    // int32_t b = safe_cast<int32_t>(a);
    std::tuple<int,char,double>a(1,'a',2.3);
    shuxin::printTuple(a);
    shuxin::printTuple(std::make_tuple(1,"adsf",3,3.3));
    auto &b =a;
    const int * c;
    shuxin::print_type(c);
    shuxin::print_full_type<const int * &&>();
}