#include <iostream>
#include <ostream>
#include <type_traits>
#include <tuple>


namespace shuxin {

template <typename T> class AddSpace {
private:
  T const &ref; // refer to argument passed in constructor
public:
  AddSpace(T const &r) : ref(r) {}
  friend std::ostream &operator<<(std::ostream &os, AddSpace<T> s) {
    return os << s.ref << " "; // output passed argument and a space
  }
};

template <typename T, size_t... idx>
void printByIdx(T t, std::index_sequence<idx...>) {
  (std::cout << ... << AddSpace(std::get<idx>(t))) << std::endl;
}

template <typename T> void printTuple(T t) {
  printByIdx(t,
             std::make_index_sequence<std::tuple_size<decltype(t)>::value>());
}

} // namespace shuxin