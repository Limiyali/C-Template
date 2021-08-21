#include <iostream>
#include <set>
#include <cassert>
#include "utils/type.h"
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

struct AnyType {
  template <typename T> operator T();
};

// template <typename T> consteval size_t CountMember(auto &&...Args) {
//   if constexpr (!requires { T{Args...}; }) { // (1)
//     return sizeof...(Args) - 1;
//   } else {
//     return CountMember<T>(Args..., AnyType{}); // (2)
//   }
// }

template<typename T, typename = void, typename... Ts>
struct CountMember{
  const static size_t value = sizeof...(Ts) -1 ;
};

template<typename T, typename... Ts>
struct CountMember<T,std::void_t<decltype(T{Ts{} ...})>,Ts...>{
  const static size_t value = CountMember<T,void,Ts...,AnyType>::value;
};

template<typename T, typename = void, typename... Ts>
struct my_ptr{
  const static size_t value =0;
};

template<typename T, typename... Ts>
struct my_ptr<T,void,Ts...>{
  const static size_t value = 1;
};

#define GET_NTH_ARG(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13,    \
                    _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24,     \
                    _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35,     \
                    _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46,     \
                    _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57,     \
                    _58, _59, _60, _61, _62, _63, _64, n, ...)                 \
  n

#define GET_ARG_COUNT(...)                                                     \
  GET_NTH_ARG(__VA_ARGS__, 64, 63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, \
              51, 50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36,  \
              35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20,  \
              19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2,  \
              1)

template<bool> struct CompileTimeChecker
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
    struct Test { int a; int b; int c; int d; };
    printf("%zu\n", CountMember<Test>::value);
    AnyType ty;
    shuxin::print_type(ty);
    cout<<my_ptr<int,void,int>::value<<endl;
    cout<<GET_ARG_COUNT(a)<<endl;
}