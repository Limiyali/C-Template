#include "jjalloc.cpp"
#include "utils/type.h"
#include <iostream>
#include <memory>
#include <type_traits>
using std::cout;
using std::endl;

template <typename T, typename Alloc = shuxin::pool_alloc> class my_vector {

public:
  typedef T value_type;
  typedef value_type *pointer;
  typedef value_type *iterator;
  typedef value_type &reference;
  typedef const value_type &const_reference;
  typedef ptrdiff_t difference_type;
  typedef size_t size_type;

protected:
  typedef shuxin::simple_alloc<value_type, Alloc> data_allocator;
  iterator start;
  iterator finish;
  iterator end_of_storage; //可用空间的尾

  void deallocate() {
    if (start)
      data_allocator::deallocate(start, end_of_storage - start);
  }
  void fill_initialize(size_type n, const T &value) {
    start = allocate_and_fill(n, value);
    finish = start + n;
    end_of_storage = finish;
  }

public:
  iterator begin() { return start; }
  iterator end() { return finish; }
  size_type size() { return size_type(end() - begin()); }
  size_type capacity() { return size_type(end_of_storage - begin()); }
  bool empty() const { return begin() == end(); }
  reference operator[](size_type n) { return *(begin() + n); }
  my_vector() : start(0), finish(0), end_of_storage(0) {}
  my_vector(size_type n, const T &value) { fill_initialize(n, value); }
  my_vector(int n, const T &value) { fill_initialize(n, value); }
  my_vector(long n, const T &value) { fill_initialize(n, value); }
  explicit my_vector(size_type n) { fill_initialize(n, T()); }

  ~my_vector() {
    std::destroy(start, finish);
    deallocate();
  }
  reference front() { return *begin(); }
  reference back() { return *(end() - 1); }
  void push_back(const T &x) {
    if (finish != end_of_storage) {
      shuxin::_construct(finish, x);
      ++finish;
    } else
      insert_aux(end(), x);
  }
  void push_back(const T &&x) {
    if (finish != end_of_storage) {
      shuxin::_construct(finish, x);
      ++finish;
    } else
      insert_aux(end(), x);
  }
  void pop_back() {
    --finish;
    std::destroy(finish);
  }
  iterator erase(iterator position) {
    if (position + 1 != end())
      std::copy(position + 1, finish, position);
    --finish;
    std::destroy_at(finish);
    return position;
  }
  void resize(size_type new_size, const T &x) {
    if (new_size < size())
      erase(begin() + new_size, end());
    else
      insert(end(), new_size - size(), x);
  }
  void resize(size_type new_size) { resize(new_size, T()); }
  void clear() { erase(begin(), end()); }

protected:
  iterator allocate_and_fill(size_type n, const T &x) {
    iterator result = data_allocator::allocate(n);
    uninitialized_fill_n(result, n, x);
    return result;
  }
  void insert_aux(iterator position, const T &x) {
    if (finish != end_of_storage) // 还有备用空间
    {
      shuxin::_construct(finish, *(finish - 1));
      ++finish;
      T x_copy = x;
      std::copy_backward(position, finish - 2, finish - 1);
      // copy [_First, _Last) backwards to [..., _Dest)
      *position = x_copy;
    } else // 已无备用空间
    {
      const size_type old_size = size();
      const size_type len = old_size != 0 ? 2 * old_size : 1;

      iterator new_start = data_allocator::allocate(len);
      iterator new_finish = new_start;
      new_finish = std::uninitialized_copy(start, position, new_start);
      shuxin::_construct(new_finish, x);
      ++new_finish;
      new_finish = std::uninitialized_copy(position, finish, new_finish);
      std::destroy(begin(), end());
      deallocate();

      start = new_start;
      finish = new_finish;
      end_of_storage = new_start + len;
    }
  }
};

// int main() {
//   my_vector<int, shuxin::malloc_alloc> a;
//   a.push_back(3);
//   a.push_back(4);
//   a.push_back(5);
//   a.erase(a.begin() + 1);
//   for (auto it : a)
//     cout << it << " ";
//   cout << endl;
//   cout << a[0] << endl;
//   my_vector<int>::iterator it;
//   std::iterator_traits<my_vector<int>::iterator>::iterator_category it2;
//   shuxin::print_type(it2);
//   shuxin::print_type(it);
//   return 0;
// }