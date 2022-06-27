#include <iostream>
#include "09/my_first.hpp"
// template void printTypeof<double>(double&);
template <typename T> class A {
public:
  void f() { std::cout << "common\n"; }
};

template <> class A<int> {
public:
  void f() { std::cout << "int\n"; }
};
template class A<int>;
int main() {
  float pi = 3.14;
  printTypeof<float>(pi);
  A<int> a;
  a.f();
}