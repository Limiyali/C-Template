#include "utils/type.h"
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

template <typename T> class Stack {
public:
  void push(T const &);
  Stack() : elems(){};
  Stack(T elem) : elems({elem}){};
  Stack(Stack const &);
  bool operator==(Stack const &);
  void pop();
  T const &top();
  void pt(std::ostream & = cout) const;
  bool empty() const { return elems.empty(); }
  template <typename U>
  friend std::ostream &operator<<(std::ostream &strm, Stack<U> const &);

private:
  std::vector<T> elems;
};

template <typename T>
std::ostream &operator<<(std::ostream &strm, Stack<T> const &s) {
  s.pt(strm);
  return strm;
}

template <typename T> void Stack<T>::push(T const &elem) {
  elems.push_back(elem);
}

template <typename T> void Stack<T>::pop() {
  assert(!elems.empty());
  elems.pop_back();
}

template <typename T> T const &Stack<T>::top() {
  assert(!elems.empty());
  return elems.back();
}

template <typename T> void Stack<T>::pt(std::ostream &out) const {
  for (T const &it : elems)
    out << it << " ";
  out << endl;
}

template <typename T> Stack<T>::Stack(Stack<T> const &stack) {
  elems = stack.elems;
}

template <typename T> bool Stack<T>::operator==(Stack<T> const &rhs) {
  return this->elems == rhs.elems;
}

template <> class Stack<string> {
public:
  void push(string const &);
  Stack() : elems() { cout << "string\n"; };
  Stack(string elem) : elems({elem}){};
  Stack(Stack const &);
  bool operator==(Stack const &);
  void pop();
  string const &top();
  void pt(std::ostream & = cout) const;
  bool empty() const { return elems.empty(); }
  friend std::ostream &operator<<(std::ostream &strm, Stack<string> const &);

private:
  std::deque<string> elems;
};

std::ostream &operator<<(std::ostream &strm, Stack<string> const &s) {
  s.pt(strm);
  return strm;
}

void Stack<string>::push(string const &elem) { elems.push_back(elem); }

void Stack<string>::pop() {
  assert(!elems.empty());
  elems.pop_back();
}

string const &Stack<string>::top() {
  assert(!elems.empty());
  return elems.back();
}

void Stack<string>::pt(std::ostream &out) const {
  for (string const &it : elems)
    out << it << " ";
  out << endl;
}

Stack<string>::Stack(Stack<string> const &stack) { elems = stack.elems; }

bool Stack<string>::operator==(Stack<string> const &rhs) {
  return this->elems == rhs.elems;
}

template <typename T> class Stack<T *> {
public:
  void push(T *const &);
  Stack() : elems() { cout << "T*\n"; };
  Stack(T *elem) : elems({elem}){};
  Stack(Stack const &);
  bool operator==(Stack const &);
  void pop();
  T *top();
  void pt(std::ostream & = cout) const;
  bool empty() const { return elems.empty(); }
  template <typename U>
  friend std::ostream &operator<<(std::ostream &strm, Stack<U *> const &);

private:
  std::vector<T *> elems;
};

template <typename T>
std::ostream &operator<<(std::ostream &strm, Stack<T *> const &s) {
  s.pt(strm);
  return strm;
}

template <typename T> void Stack<T *>::push(T *const &elem) {
  elems.push_back(elem);
}

template <typename T> void Stack<T *>::pop() {
  assert(!elems.empty());
  elems.pop_back();
}

template <typename T> T *Stack<T *>::top() {
  assert(!elems.empty());
  return elems.back();
}

template <typename T> void Stack<T *>::pt(std::ostream &out) const {
  for (T *const &it : elems)
    out << *it << " ";
  out << endl;
}

template <typename T> Stack<T *>::Stack(Stack<T *> const &stack) {
  elems = stack.elems;
}

template <typename T> bool Stack<T *>::operator==(Stack<T *> const &rhs) {
  return this->elems == rhs.elems;
}

Stack(const char *)->Stack<string>;

template <typename T> struct A {
  T x;
  string s;
};
A(const char *, const char *)->A<string>;

int main() {
  Stack<int> a;
  a.push(3);
  Stack<string> b;
  b.push("123");
  Stack<int *> c;
  int aa = 3;
  c.push(&aa);
  a.pt();
  b.pt();
  cout << c << endl;
  Stack<std::pair<int, int>> d;
  d.push({1, 2});
  cout << d.top().first << " " << d.top().second << endl;
  //   d.pt();
  Stack stringStack{"buttom"};
  shuxin::print_full_type<decltype(stringStack.top())>();
  A e = {"hi", "initial value"};
  cout << e.x << endl;
  return 0;
}