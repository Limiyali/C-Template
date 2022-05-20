#include <cstdarg>
#include <iostream>
#include <tuple>
using namespace std;

using std::cout;
using std::endl;
void va_print(int n, ...) {
  std::va_list args;
  cout << "begin" << endl;
  va_start(args, n);
  std::cout << "1: " << va_arg(args, double) << std::endl;
  std::cout << "2: " << va_arg(args, int) << std::endl;
  std::cout << "3: " << va_arg(args, const char *) << std::endl;
  std::cout << "4: " << va_arg(args, const char *) << std::endl;
  va_end(args);
  cout << "end" << endl;
}

void va_print(const char *fmt, ...) {
  char buf[256];
  std::va_list args;
  va_start(args, fmt);
  vsnprintf(buf, 256, fmt, args);
  va_end(args);
  cout << buf << endl;
}

template <typename T> void print(T first) { cout << first << " "; }

template <typename T, typename... Ts> void print(const T &t, Ts &&... ts) {
  print(t);
  print(std::forward<Ts>(ts)...);
}

template <typename T, typename... Ts>
void s_print(const T &t, const Ts &&... ts) {
  cout << t << " ";
  if constexpr (sizeof...(ts) > 0) {
    s_print(forward<ts>(ts)...);
  }
}

template <bool b> struct A;
template <typename T, typename... Ts> void s11_print(const T &t, Ts &&... ts) {
  cout << t << " ";
  A<(sizeof...(ts) > 0)>::f(std::forward<Ts>(ts)...);
}

template <bool b> struct A {
  template <typename... Ts> static void f(Ts &&... ts) {
    s11_print(std::forward<Ts>(ts)...);
  }
};

void s11_2_print(){};

template <typename T, typename... Ts>
void s11_2_print(const T &t, Ts &&... ts) {
  cout << t << " ";
  s11_2_print(std::forward<Ts>(ts)...);
}

template <> struct A<false> {
  template <typename... Ts> static void f(Ts &&... ts) {}
};

template <typename... Ts> void dot_print(Ts &&... ts) {
  auto a = {(cout << ts << " ", 0)...};
}

template <typename... Ts> void fold_print(Ts &&... ts) {
  ((cout << ts << " "), ...);
}

template <typename F, typename T, typename... Ts>
void foldlList(F &&f, T &&first, Ts &&... x) {
  ((f(std::string(sizeof...(Ts), '(')), f(first)), ..., (f('+'), f(x), f(')')));
}

template <typename F, typename T, typename... Ts>
void foldrList(F &&f, T &&first, Ts &&... x) {
  ((f('('), f(x), f('+')), ..., (f(std::string(sizeof...(Ts), ')'))));
}
template <typename... Types> auto foldSum(Types... args) {
  return (... + args);
}

struct node {
  node(int d) : data(d) { left = right = nullptr; }
  int data;
  node *left;
  node *right;
  /* data */
};

template <typename T> class AddSpace {
private:
  T const &ref; // refer to argument passed in constructor
public:
  AddSpace(T const &r) : ref(r) {}
  friend std::ostream &operator<<(std::ostream &os, AddSpace<T> s) {
    return os << s.ref << " "; // output passed argument and a space
  }
};

template <typename T, typename... Types> T traverse(T root, Types... paths) {
  return (root->*...->*paths);
}

template <typename... Types> void pt(Types... args) {
  (cout << ... << AddSpace(args)) << endl;
}

template <typename T, typename... Types> bool is_Same(T first, Types... args) {
  return (is_same_v<T, Types> && ...);
}

template <typename T, typename... Args> void ptIdx(T t, Args... idx) {
  (cout << ... << AddSpace(t[idx])) << endl;
}

template <size_t... Args, typename T> void ptIndex(T const &t) {
  (cout << ... << AddSpace(t[Args])) << endl;
}

template <size_t...> struct Indices {};

template <typename T, size_t... idx> void printByIdx(T t, Indices<idx...>) {
  print(get<idx>(t)...);
}

template <typename... Ts, size_t... idx>
void dotAdd(const std::tuple<Ts...> &t, Indices<idx...>) {
  print((std::get<idx>(t) + std::get<idx>(t))...);
}

struct p_single {
  void operator()(int a) const { cout << a << endl; }
};

struct p_two {
  void operator()(int a, int b) const { cout << a << " " << b << endl; }
};

template <typename... Bases> struct Overloader : Bases... {
  using Bases::operator()...;
};

template <typename F, typename... Ts, size_t... idx>
void pt_tuple(F f, std::tuple<Ts...> &t, std::index_sequence<idx...>) {
  f(get<idx>(t)...);
}
template <typename F, typename... Ts> void pt_tuple(F f, std::tuple<Ts...> &t) {
  pt_tuple(f, t, std::make_index_sequence<sizeof...(Ts)>{});
}

int main() {
  va_print(4, 3.14, 42, std::string{"hello"}.c_str(), "world");
  va_print("%.2f %d %s %s", 3.14, 42, std::string{"hello"}.c_str(), "world");
  print(3.14, 42, std::string{"hello"}, "world");
  cout << endl;
  print(3.14, 42, std::string{"hello"}, "world");
  cout << endl;
  s11_print(3.14, 42, std::string{"hello"}, "world");
  cout << endl;
  s11_2_print(3.14, 42, std::string{"hello"}, "world");
  cout << endl;
  dot_print(3.14, 42, std::string{"hello"}, "world");
  cout << endl << foldSum(1, 2, 3) << endl;
  fold_print(3.14, 42, std::string{"hello"}, "world");
  cout << endl;
  foldlList([](auto &&x) { cout << x; }, 0, 1, 2, 3, 4); // ((((0+1)+2)+3)+4)
  cout << endl;
  foldrList([](auto &&x) { cout << x; }, 0, 1, 2, 3, 4); // (1+(2+(3+(4+0))))
  cout << endl;

  auto t = std::make_tuple(3.14, 42, std::string{"hello"}, "world");
  printByIdx(t, Indices<2, 3>{}); // hello world
  cout << endl;
  dotAdd(t, Indices<0, 1, 2>{});
  cout << endl;

  using op = Overloader<p_single, p_two>;
  op o;
  o(1);
  o(1, 2);
  auto pp = [](auto &&... ts) { ((std::cout << ts << " "), ...); };
  pt_tuple(pp, t);
}