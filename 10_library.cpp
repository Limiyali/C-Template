#include <functional>
#include <iostream>
#include <vector>
#include "utils/type.h"
using std::cout;
using std::endl;

template <typename Iter, typename Callable>
void ForEach(Iter current, Iter end, Callable op) {
  while (current != end) {
    op(*current);
    ++current;
  }
}

template <typename Iter, typename Callable, typename... Args>
void ForEach(Iter current, Iter end, Callable op, Args... args) {
  while (current != end) {
    std::invoke(op, args..., *current);
    ++current;
  }
}

void fun(int i) { std::cout << i << std::endl; }

struct FuncObj {
  void operator()(int i) const { std::cout << i << std::endl; }
  void f(int i) const { std::cout << "flag " << i << std::endl; }
};

void fun2(int r, int i) {
  for (int j = 0; j < r; ++j)
    cout << i;
  cout << endl;
}

template <typename Callable, typename... Args>
decltype(auto) call(Callable &&op, Args &&... args) {
  if constexpr (std::is_same_v<std::invoke_result_t<Callable, Args...>, void>) {
    std::invoke(std::forward<Callable>(op), std::forward<Args>(args)...);
    return;
  } else {
    decltype(auto) ret{
        std::invoke(std::forward<Callable>(op), std::forward<Args>(args)...)};
    return ret;
  }
}

struct has_default {
  int foo() const { return 1; }
};

struct no_default {
  no_default(const no_default &){};
  int foo() const { return 1; }
};

int main() {
  std::vector<int> a = {1};
  ForEach(a.begin(), a.end(), fun);
  ForEach(a.begin(), a.end(), &fun);
  ForEach(a.begin(), a.end(), FuncObj());
  ForEach(a.begin(), a.end(), [](int i) { cout << i << endl; });
  ForEach(a.begin(), a.end(), fun2, 3);
  FuncObj f;
  ForEach(a.begin(), a.end(), &FuncObj::f, f);
  call(fun2, 10, 1);
  decltype(has_default().foo()) n1 = 1;
  //   decltype(no_default().foo()) n2;
  decltype(std::declval<no_default>().foo()) n2;
  shuxin::print_full_type<decltype(std::declval<int>())>();
}