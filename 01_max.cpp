#include "utils/type.h"
#include <array>
#include <cstdlib>
#include <cstring>
#include <iostream>
using std::cout;
using std::endl;

template <typename T> T max(T const &a, T const &b) { return b < a ? a : b; }

char const *max(char const *a, char const *b) {
  cout << "char *\n";
  return strcmp(b, a) < 0 ? a : b;
}

template <typename T = int> T max(T a = -2, T b = -1) {
  cout << "T max(T a,T b)\n";
  return b < a ? a : b;
}

template <typename T> T max(T a, T b, T c) {
  cout << "T max(T a,T b,T c)\n";
  return max(max(a, b), c);
}

constexpr int max(int a, int b) { // to late
//   cout << "int max(int,int)\n";
  return b < a ? a : b;
}

template <typename T> T *max(T *a, T *b) {
  cout << "*\n";
  return *b < *a ? a : b;
}

// template <typename RT, typename T1, typename T2>
// RT max(T1 const &a, T2 const &b)
// {
//     cout << "RT" << endl;
//     return b < a ? a : b;
// }

// template <typename T1, typename T2>
// auto max(T1 a, T2 b) -> decltype(true ? a : b)
// {
//     cout << "decltype\n";
//     return b < a ? a : b;
// }

template <typename T1, typename T2> std::common_type_t<T1, T2> max(T1 a, T2 b) {
  cout << "common" << endl;
  return b < a ? a : b;
}

int main() {
  int a = 8, b = 9, c = 10;
  const char *aa = "a";
  const char *bb = "b";
  const char *cc = "c";
  cout << max(aa, bb, cc) << endl;
  auto rt = max(12, 3);
  shuxin::print_full_type<decltype(rt)>();
  std::array<int, max((int)sizeof(int), 10)> ar;
  shuxin::print_full_type<decltype(ar)>();
}