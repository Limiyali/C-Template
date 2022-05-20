#include "utils/type.h"
#include "utils/utils.h"
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

extern const char s03[] = "hi"; // external linkage
const char s11[] = "hi";        // internal linkage

template <int N, typename T> T addVal(T rhs) { return rhs + N; }

template <char const *T> struct P {
  P() { cout << T << endl; }
};

template <int I, bool B> void pt() { cout << I << " " << B << endl; }

template <auto N> class C {
public:
  void change() { cout << N << endl; }
};

char const s[] = "123";
int main() {
  int i = 5;
  cout << addVal<5>(i) << endl;
  vector<int> v{0, 1, 2};
  std::transform(v.begin(), v.end(), v.begin(), addVal<1, int>);
  shuxin::pt(v);
  cout << endl;
  P<s03> m03;                     // OK (all versions)
  P<s11> m11;                     // OK since C++11
  static const char s17[] = "hi"; // no linkage
  P<s17> m17;                     // OK since C++17  P<s03> m03;
  pt<sizeof(int) + 4, sizeof(int) == 4>();
  pt<1, (sizeof(int) > 4)>();
  static const char s[] = "hi";
  C<(s)> a;
  a.change();
}