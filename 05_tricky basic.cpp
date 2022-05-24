#include "utils/type.h"
#include <array>
#include <bitset>
#include <cassert>
#include <deque>
#include <iostream>
#include <vector>
using std::cout;
using std::endl;

template <typename T> void print(const T &c) {
  shuxin::print_full_type<T>();
  typename T::const_iterator pos;
  typename T::const_iterator end(c.end());
  for (pos = c.begin(); pos != end; ++pos)
    cout << *pos << " ";
  cout << endl;
}

template <typename T> void f(T p = T{}) {
  T x{};
  cout << x << endl;
}

template <typename T> class Aa {
public:
  T x{};
  // A():x(){}
};

template <typename T> class B {
public:
  virtual void f() { cout << 1 << endl; }
};

template <typename T> class D : public B<T> {
public:
  using B<T>::f;
  virtual void f() { cout << 2 << endl; }
  void f2() { f(); }
  //   void f2(){this->f();}
};

template <typename T, int N, int M> bool less(T (&a)[N], T (&b)[M]) {
  for (int i = 0; i < N && i < M; ++i) {
    if (a[i] < b[i])
      return true;
    if (b[i] < a[i])
      return false;
  }
  return N < M;
}

template <typename T> struct A; // primary template

template <typename T, std::size_t SZ>
struct A<T[SZ]> // 偏特化：用于已知边界的数组
{
  static void print() { std::cout << "print() for T[" << SZ << "]\n"; }
};

template <typename T, std::size_t SZ>
struct A<T (&)[SZ]> // 偏特化：用于已知边界的数组的引用
{
  static void print() { std::cout << "print() for T(&)[" << SZ << "]\n"; }
};

template <typename T>
struct A<T[]> // 偏特化：用于未知边界的数组
{
  static void print() { std::cout << "print() for T[]\n"; }
};

template <typename T>
struct A<T (&)[]> // 偏特化：用于未知边界的数组的引用
{
  static void print() { std::cout << "print() for T(&)[]\n"; }
};

template <typename T>
struct A<T *> // 偏特化：用于指针
{
  static void print() { std::cout << "print() for T*\n"; }
};

template <typename T1, typename T2, typename T3>
void fp(int a1[7], int a2[], int (&a3)[42], int (&x0)[], T1 x1, T2 &x2,
        T3 &&x3) {
  A<decltype(a1)>::print(); // A<T*>
  A<decltype(a2)>::print(); // A<T*>
  A<decltype(a3)>::print(); // A<T(&)[SZ]>
  A<decltype(x0)>::print(); // A<T(&)[]>
  A<decltype(x1)>::print(); // A<T*>
  A<decltype(x2)>::print(); // A<T(&)[]>
  A<decltype(x3)>::print(); // A<T(&)[]>
}

template <typename T, template<typename>class Conv = std::deque> class Stack {
public:
  void push(const T &rhs) { v_.emplace_back(rhs); }
  void pop() {
    assert(!v_.empty());
    v_.pop_back();
  }
  const T &top() const {
    assert(!v_.empty());
    return v_.back();
  }
  template <typename U, template<typename>class Conv2>
  Stack &operator=(const Stack<U, Conv2> &);
  template <typename, template<typename> class> friend class Stack;

private:
  Conv<T> v_;
};

template <typename T, template<typename>class Conv>
template <typename U, template<typename>class Conv2>
Stack<T, Conv> &Stack<T, Conv>::operator=(const Stack<U, Conv2> &rhs) {
  v_.clear();
  // v_.emplace(v_.begin(), rhs.v_.begin(), rhs.v_.end());
  Stack<U, Conv2> tmp(rhs);
  while (!tmp.v_.empty()) {
    v_.emplace_front(tmp.top());
    tmp.pop();
  }
  return *this;
}

class TBool {
public:
  TBool() = default;
  TBool(const std::string &x) : s(x) {}
  template <typename T = std::string> T get() const { return s; }

private:
  std::string s;
};

template <> inline bool TBool::get<bool>() const {
  return s == "true" || s == "1" || s == "on";
}

template <unsigned long N> void pt_bitset(const std::bitset<N> &b) {
  cout << b.template to_string<char, std::char_traits<char>,
                               std::allocator<char>>();
}

class X {
public:
  X() = default;
  template <typename T1, typename T2> auto operator()(T1 x, T2 y) {
    return x + y;
  }
};

template <typename T> constexpr T pi{3.1415926535897932385};
template <typename T = int> constexpr T xP{0x7fffffff};
template <int N> std::array<int, N> arr{};
template <auto N> decltype(N) xN = N;

template <typename T> class num_limit {
public:
  static const bool is_signed = false;
};

template <> class num_limit<char> {
public:
  static const bool is_signed = true;
};
template <> class num_limit<int> {
public:
  static const bool is_signed = true;
};
template <> class num_limit<short> {
public:
  static const bool is_signed = true;
};
template <> class num_limit<long> {
public:
  static const bool is_signed = true;
};
template <> class num_limit<long long> {
public:
  static const bool is_signed = true;
};

template <typename T> constexpr bool is_signed_v = num_limit<T>::is_signed;

int main() {
  std::vector<int> a{1, 2, 3, 4};
  print(a);
  f<int>();
  Aa<int> b;
  cout << b.x << endl;
  D<int> d;
  d.f2();
  cout << less("ab", "abc") << endl;
  int x[] = {1, 2, 3, 4};
  int y[] = {1, 2, 3};
  cout << less(x, y) << endl;

  int aa[42];
  A<decltype(aa)>::print(); // A<T[SZ]>
  extern int xx[]; // 前置声明数组，x传引用时将变为int(&)[]
  A<decltype(xx)>::print(); // A<T[]>
  cout << endl;
  fp(aa, aa, aa, xx, xx, xx, xx);

  Stack<int> sa;
  Stack<float, std::vector> sf;
  sa.push(1);
  sf.push(8);
  sa = sf;
  cout << sa.top() << endl;
  sa.pop();
  //   sa.pop();
  TBool tb("on");
  cout << tb.get() << endl;
  cout << tb.get<bool>() << endl;
  std::bitset<4> bset;
  bset.set(0);
  pt_bitset(bset);
  cout << endl;
  cout << X()(1, 2.1) << endl;
  cout << pi<double> << " " << pi<float> << endl;
  cout << xP<> << " " << xP<double> << endl;
  shuxin::print_full_type<decltype(arr<3>)>();
  shuxin::print_full_type<decltype(arr<32>)>();
  shuxin::print_full_type<decltype(xN<14>)>();
  shuxin::print_full_type<decltype(xN<'c'>)>();
  xN<14> --;
  cout << xN<14> << " " << xN<13> << endl;
  cout << num_limit<int>::is_signed << " " << num_limit<u_char>::is_signed
       << endl;
  cout << is_signed_v<int> << " " << is_signed_v<u_char> << endl;
}

int xx[] = {1, 2, 3};