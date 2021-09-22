#include "utils/type.h"
#include <iostream>

using std::cout;
using std::endl;

template <typename T> void f(const T &x) {
  shuxin::print_full_type<T>();
  shuxin::print_full_type<decltype(x)>();
}

template <typename T> void f2(T &x) {
  shuxin::print_full_type<T>();
  shuxin::print_full_type<decltype(x)>();
}

template <typename T> void f3(T *x) {
  shuxin::print_full_type<T>();
  shuxin::print_full_type<decltype(x)>();
}

template <typename T> void f4(T &&x) {
  shuxin::print_full_type<T>();
  shuxin::print_full_type<decltype(x)>();
}

template <typename T> void f5(T x) {
  shuxin::print_full_type<T>();
  shuxin::print_full_type<decltype(x)>();
}

template <typename T, std::size_t N> constexpr std::size_t arraySize(T (&)[N]) {
  return N;
}

void someFunc(int, double) {}

int main() {
  cout << "\n\n\nfirst---------------\n";
  const int a = 0;
  f(a);
  cout << "\n\n\n引用---------------\n";
  int x = 27;
  int &rx = x;
  f2(x);
  f2(rx);

  cout << "\n\n\n指针---------------\n";
  int *px = &x;
  f3(&x);
  f3(px);

  cout << "\n\n\n右值引用---------------\n";
  const int cx = x;
  f4(x);
  f4(cx);
  f4(rx);
  f4(27);

  cout << "\n\n\n值传递---------------\n";
  x = 27;
  volatile const &cvx = x;
  f5(x);
  f5(cx);
  f5(rx);
  f5(cvx);

  cout << "\n\n\n退化---------------\n";
  const char name[] = "shuxin.wang";
  const char *ptrToName = name;
  cout << abi::__cxa_demangle(typeid(name).name(), nullptr, nullptr, nullptr)
       << endl;
  cout << abi::__cxa_demangle(typeid(ptrToName).name(), nullptr, nullptr,
                              nullptr)
       << endl;
  cout << arraySize(name) << endl;

  cout << "\n\n\n函数指针---------------\n";
  f2(someFunc);
  f5(someFunc);
}