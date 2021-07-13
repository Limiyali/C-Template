#include <functional>
#include <iostream>
using std::cout;
using std::endl;

struct Op {
  const std::function<int(void)> &func;
  Op(const std::function<int(void)> &func) : func(func) {}
};

int main() {
  int a = 1;

  auto func = [&] {
    cout<<a<<endl;
    return 0;
  };

  Op op(func);
  op.func();
  return 0;
}