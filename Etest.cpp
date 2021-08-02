#include <assert.h>
#include <deque>
#include <iostream>
#include <string>
#include <vector>

using std::begin;
using std::cout;
using std::deque;
using std::end;
using std::endl;
using std::string;
using std::vector;

template <size_t N> class fact {
public:
  const static int value = N * fact<N - 1>::value;
};

template <> class fact<0> {
public:
  const static int value = 1;
};

template <size_t N> class sum {
public:
  const static int value = N + sum<N - 1>::value;
};

template <> class sum<0> {
public:
  const static int value = 1;
};


int main() {
    cout<<fact<5>::value<<endl;
    cout<<sum<100>::value<<endl;
}