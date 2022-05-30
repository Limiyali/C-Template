#include <iostream>
#include <string>
#define pline cout << endl;
using std::cout;
using std::endl;
void f(int &) { std::cout << 1; }
void f(const int &) { std::cout << 2; }
void f(int &&) { std::cout << 3; }

void g(int &&x) {
  f(x);
  cout << std::endl;
  f(std::move(x));
}

template <typename T> void h(T &&x) { f(std::forward<T>(x)); }

class Person {
public:
  explicit Person(const std::string &n) : name(n) {}
  explicit Person(std::string &&n) : name(std::move(n)) {}
  Person(const Person &p) : name(p.name) {}
  Person(Person &&p) : name(std::move(p.name)) {}

private:
  std::string name;
};
// template<typename T>
// concept ConvertiableToString = std::is_convertible_v<T,std::string>;

template <typename T>
using EnableIfString = std::enable_if_t<std::is_convertible_v<T, std::string>>;

class T_Person {
public:
  template <typename STR, typename = EnableIfString<STR>>
  //   requires std::is_convertible_v<STR,std::string>
  explicit T_Person(STR &&n) : name(std::forward<STR>(n)) {}
  T_Person(const T_Person &p) : name(p.name) {}
  T_Person(T_Person &&p) : name(std::move(p.name)) {}

private:
  std::string name;
};

class C {
public:
  C() = default;
  C(const volatile C &) =
      delete; // copy-construct move-construct 赋值 优先使用生成
  template <typename T> C(const T &) { cout << "C(T&)\n"; }
};

int main() {
  h(3);
  pline int x;
  auto lamda = [](auto &&x) { h<decltype(x)>(x); };
  lamda(x);
  pline std::string s = "sname";
  Person p1(s);
  Person p2("tmp");
  Person p3(p1);
  Person p4(std::move(p1));

  T_Person p11(s);
  T_Person p12("tmp");
  T_Person p13(p11);
  //   T_Person p14(std::move(p11));
  C c1;
  C c2(c1);
}