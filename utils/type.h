#include <cxxabi.h>
#include <iostream>
#include <type_traits>

using std::cout;
using std::endl;

namespace shuxin {
template <typename T> void print_type(T obj) {
  cout << abi::__cxa_demangle(typeid(obj).name(), nullptr, nullptr, nullptr)
       << endl;
}

template <typename T> struct print_full_type {
  print_full_type(void) {
    std::cout << abi::__cxa_demangle(typeid(T).name(), nullptr, nullptr,
                                     nullptr);
  }
  ~print_full_type(void) { std::cout << std::endl; }
};

#define CHECK_TYPE__(OPT)                                                      \
  template <typename T> struct print_full_type<T OPT> : print_full_type<T> {   \
    print_full_type(void) { std::cout << " " #OPT; }                           \
  };

CHECK_TYPE__(const)
CHECK_TYPE__(volatile)
CHECK_TYPE__(const volatile)
CHECK_TYPE__(&)
CHECK_TYPE__(&&)
CHECK_TYPE__(*)

template <typename T> void pt(T objs) {
  for (auto it : objs)
    cout << it << " ";
  cout << endl;
}
} // namespace shuxin