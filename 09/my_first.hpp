#ifndef MYFIRST_HPP
#define MYFIRST_HPP
template<typename T>
void printTypeof(T&);
extern template void printTypeof<double>(double&);
// #include "my_first.cpp"
#endif