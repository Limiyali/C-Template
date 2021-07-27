#include <functional>
#include <iostream>
using namespace std;

struct mydata{
    operator std::function<int(void)>(){
        cout <<"yes\n";
        int a = 4;
        std::function<int(void)> f;
        return f;
    }
};

template <typename T>
void print_type(T obj)
{
    cout << typeid(obj).name() << endl;
}

struct Op {
  const std::function<int(void)> &func;
  Op(const std::function<int(void)> &func) : func(func) {}
};

int main() {
  int a = 1;

  auto func = [&] {
    printf("%d\n", a);
    return 0;
  };

  mydata b;
  Op op(func);
  cout <<"2\n";
  cout <<&op<<endl;
  op.func();
  return 0;
}