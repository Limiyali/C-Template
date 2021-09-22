#include "utils/type.h"
#include <iostream>

using std::cout;
using std::endl;

void someFunc(int, double) {}

int main() {
  cout << "\n\n\nfirst---------------\n";
  int x = 27;
  const auto cx = x;
  const auto &rx = cx;
  shuxin::print_full_type<decltype(x)>();
  shuxin::print_full_type<decltype(cx)>();
  shuxin::print_full_type<decltype(rx)>();
  cout << "\n\n\nsecond---------------\n";
  auto &&uref1 = x;
  auto &&uref2 = cx;
  auto &&uref3 = 27;
  shuxin::print_full_type<decltype(uref1)>();
  shuxin::print_full_type<decltype(uref2)>();
  shuxin::print_full_type<decltype(uref3)>();
  cout << "\n\n\n3th---------------\n";
  const char name[] = "shuxin.wang";
  auto arr1 = name;
  auto &arr2 = name;
  shuxin::print_full_type<decltype(name)>();
  shuxin::print_full_type<decltype(arr1)>();
  shuxin::print_full_type<decltype(arr2)>();
  auto func1 = someFunc;
  auto &func2 = someFunc;
  shuxin::print_full_type<decltype(someFunc)>();
  shuxin::print_full_type<decltype(func1)>();
  shuxin::print_full_type<decltype(func2)>();
  cout << "\n\n\n4th---------------\n";
  auto x1 = 27;
  auto x2(27);
  auto x3 = {27};
  auto x4{27};
  shuxin::print_full_type<decltype(x1)>();
  shuxin::print_full_type<decltype(x2)>();
  shuxin::print_full_type<decltype(x3)>();
  shuxin::print_full_type<decltype(x4)>();
}