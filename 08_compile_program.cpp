#include <array>
#include <iostream>
using std::cout;
using std::endl;

template <unsigned p, unsigned d> struct DoIsPrime {
  static constexpr bool value = (p % d != 0) && DoIsPrime<p, d - 1>::value;
};

template <unsigned p> struct DoIsPrime<p, 2> {
  static constexpr bool value = (p % 2 != 0);
};

template <unsigned p> struct IsPrime {
  static constexpr bool value = DoIsPrime<p, p / 2>::value;
};

template <> struct IsPrime<0> { static constexpr bool value = false; };
template <> struct IsPrime<1> { static constexpr bool value = false; };
template <> struct IsPrime<2> { static constexpr bool value = true; };
template <> struct IsPrime<3> { static constexpr bool value = true; };

constexpr bool doIsPrime(unsigned p, unsigned d) {
  return d != 2 ? (p % d != 0) && doIsPrime(p, d - 1) : (p % 2 != 0);
}

constexpr bool isPrime(unsigned p) {
  return (p < 4) ? !(p < 2) : doIsPrime(p, p / 2);
}

constexpr bool isPrime_17(unsigned p) {
  for (unsigned d = 2; d <= p / 2; d++) {
    if (p % d == 0)
      return false;
  }
  return p > 1;
}

template <int SZ, bool = isPrime(SZ)> struct Helper;

template <int SZ> struct Helper<SZ, false> {
  Helper() { cout << "false\n"; }
};

template <int SZ> struct Helper<SZ, true> {
  Helper() { cout << "true\n"; }
};

template <typename T, size_t SZ> void f(const std::array<T, SZ> &&coll) {
  Helper<SZ> h;
}

template <typename T, unsigned N> std::size_t len(T (&)[N]) { return N; }

template <typename T>
auto len(const T &t) -> decltype((void)(t.size()), T::size_type) {
  return t.size();
}

std::size_t len(...) { return 0; }

template <typename T, typename... Types>
void print(const T &t, const Types &... args) {
  cout << t << endl;
  if constexpr (sizeof...(args) > 0) {
    print(args...);
  }
}

void undeclared(){};

template <typename T> void f(T t) {
  if constexpr (std::is_integral_v<T>) {
    if (t > 0)
      f(t - 1);
  } else {
    undeclared(t);
    undeclared();
  }
}

int main() {
  std::cout << IsPrime<7>::value << std::endl;
  std::cout << IsPrime<8>::value << std::endl;
  cout << isPrime(5) << endl;
  cout << isPrime_17(9) << endl;
  int x = 5;
  cout << isPrime_17(9) << endl;
  f(std::array<int, 5>());
  int a[3];
  cout << len(a) << endl;
  std::string ss = "123456";
  std::allocator<int> s;
  cout << len(s) << endl;
  // f(std::array<int, 6>());
  print(1, 2, 4);
  print(1, 3.0, ss);
  f(3);
}