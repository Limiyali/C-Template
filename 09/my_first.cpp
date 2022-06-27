#include "my_first.hpp"
#include <iostream>
#include <cxxabi.h>

template <typename T> void printTypeof(T &x) {
  std::cout << abi::__cxa_demangle(typeid(T).name(), nullptr, nullptr, nullptr)<<std::endl;
}
template void printTypeof<double>(double&);