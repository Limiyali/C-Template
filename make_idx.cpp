#include <assert.h>
#include <deque>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

using std::begin;
using std::cout;
using std::deque;
using std::end;
using std::endl;
using std::string;
using std::vector;
using std::get;
using std::tuple;
template <typename... T> using Void_T = void;

template <size_t... indices> struct index_sequence {};

template <size_t N, size_t... Others>
struct make_idx_seq : public make_idx_seq<N - 1, N - 1, Others...> {};

template <size_t... Others>
struct make_idx_seq<0, Others...> : public index_sequence<Others...> {};

template <typename T, size_t... idx>
void printByIdx(T t, index_sequence<idx...>) {
  (cout << ... << get<idx>(t)) << endl;
}

int main() {
  //make_idx_seq<4> a;
  index_sequence<0,2,1>idx;
  tuple<int, int, string, string> d = {1, 2, "a", "b"};
  printByIdx(d,idx);
  return 0;
}