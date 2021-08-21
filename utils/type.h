#include <iostream>
using std::cout;
using std::endl;

namespace shuxin {
template <typename T> void print_type(T obj) {
  cout << typeid(obj).name() << endl;
}

template <typename T> 
void pt(T objs) {
  for (auto it : objs)
    cout << it << " ";
  cout << endl;
}
} // namespace shuxin