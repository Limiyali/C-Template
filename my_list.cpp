#include "jjalloc.cpp"
#include "utils/type.h"
#include <iostream>
#include <memory>
#include <type_traits>
using std::cout;
using std::endl;

template<typename T>
struct __list_node
{
  typedef __list_node<T>* pointer;
  pointer prev;
  pointer next;
  T data;
};

template<typename T, typename Ref, typename Ptr>
struct __list_iterator {

	typedef __list_iterator<T, T&, T*>        iterator;
	typedef __list_iterator<T,Ref,Ptr>        self;

  typedef std::bidirectional_iterator_tag   iterator_category;
	typedef T				                          value_type;
	typedef Ptr				                        pointer;
	typedef Ref				                        reference;
	typedef __list_node<T>*	                  link_type;
	typedef size_t			                      size_type;
	typedef ptrdiff_t		                      difference_type;


  link_type node;

  __list_iterator() {}
  __list_iterator(link_type x) : node(x) {}
  __list_iterator(const iterator &rhs) : node(rhs.node) {}

  bool operator==(const self &x) const { return node == x.node; }
  bool operator!=(const self &x) const { return node != x.node; };

  reference operator*() { return (*node).data; }
  pointer operator->() { return &operator*(); }

  self &operator++() {
    node = node->next;
    return *this;
	}
	self operator++(int) {
		self temp = *this;
		node = node->next;
		return temp;
	}
	self& operator--() {
		node = node->prev;
		return *this;
	}
	self operator--(int) {
		self temp = *this;
		node = node->prev;
		return temp;
	}

};

template <typename T, typename Alloc = shuxin::pool_alloc> class my_list {

public:
  typedef T                                          value_type;
  typedef value_type                                 *pointer;
  typedef value_type                                 &reference;
  typedef __list_iterator<T,reference,pointer>       iterator;
  typedef ptrdiff_t                                  difference_type;
  typedef size_t                                     size_type;

protected:
  typedef __list_node<T>                             list_node;
  typedef shuxin::simple_alloc<list_node, Alloc>     list_node_allocator;
public:
  typedef list_node*                                 link_type;
protected:
  link_type node;

public:
  iterator begin() { return (*node).next; }
  iterator end() { return node; }
  bool empty(){ return node->next == node;}
  size_type size() {
    size_type result = 0;
    result = std::distance(begin(), end());
    return result;
   }
  reference front(){ return *begin();}
  reference back() { return *(--end()); }
protected:
  link_type get_node(size_type n = 1) {
    return list_node_allocator::allocate(n);
  }
  void put_node(link_type p) { list_node_allocator::deallocate(p, 1); }
  link_type creat_node(const T &x) {
    link_type p = get_node();
    shuxin::_construct(&p->data, x);
    return p;
  }
  void destory_node(link_type p) {
    shuxin::_destroy(&p->data);
    put_node(p);
  }

public:
  my_list(){ empty_initialize();}
  void push_back(const T &x) {
    insert(end(),x);
  }
  void push_front(const T &x) {
    insert(begin(),x);
  }
  void pop_back() {
    erase(begin());
  }
  void pop_front() {
    iterator tmp = end();
    erase(--tmp);
  }
  iterator erase(iterator position) {
    link_type next_node = position.node->next;
    link_type prev_node = position.node->prev;
    prev_node->next = next_node;
    next_node->prev = prev_node;
    destory_node(position.node);
    return iterator(next_node);
  }
  void clear() {
    link_type cur = node->next;
    while (cur != node) {
      link_type tmp = cur;
      cur = cur->next;
      destory_node(tmp);
    }
    node->next = node;
    node->prev = node;
  }
  void remove(const T& value) {
    iterator first = begin();
    iterator last = end();
    while (first != last) {
      iterator next = first;
      ++next;
      if(*first == value) erase(first);
      first = next;
    }
  }
  void unique() {
    iterator first = begin();
    iterator last = end();
    if(first == last) return;
    iterator next = first;
    while (++next != last) {
      if (*first == *next)
        erase(next);
      else
        first = next;
      next = first;
    }
  }
  void splice(iterator position, my_list &x) {
    if (!x.empty()) {
      transfer(position, x.begin(), x.end());
    }
  }
  void splice(iterator position, my_list &, iterator i) {
    iterator j = i;
    ++j;
    if (position == i || position == j)
      return;
    transfer(position, i, j);
  }
  void splice(iterator position, my_list &, iterator first, iterator last) {
    if (first != last)
      transfer(position, first, last);
  }
  void merge(my_list& x){
    iterator first1 = begin();
    iterator last1 = end();
    iterator first2 = x.begin();
    iterator last2 = x.end();
    while(first1!=last1 && first2!=last2){
      if(*first2<*first1){
        iterator next =first2;
        transfer(first1,first2,++next);
        first2 = next;
      }
      else ++first1;
    }
    if(first2!=last2)transfer(last1,first2,last2);
  }
  void reverse() {
    if (node->next == node || node->next->next == node)
      return;
    iterator first = begin();
    ++first;
    while(first!=end()){
      iterator old =first;
      ++first;
      transfer(begin(),old,first);
    }
  }

protected:
  void transfer(iterator position,iterator first, iterator last){
    if (position!=last){
      last.node->prev->next=position.node;
      first.node->prev->next = last.node;
      position.node->prev->next=first.node;
      link_type tmp = position.node->prev;
      position.node->prev = last.node->prev;
      last.node->prev = first.node->prev;
      first.node->prev = tmp;
    }
  }

protected:
  void empty_initialize(){
    node = get_node();
    node->next = node;
    node->prev = node;
  }
  iterator insert(iterator positon , const T& x){
    link_type tmp = creat_node(x);
    tmp->next = positon.node;
    tmp->prev = positon.node->prev;
    positon.node->prev->next = tmp;
    positon.node->prev = tmp;
    return tmp;
  }
};

int main() {
  my_list<int>a;
  a.push_back(1);
  a.push_back(2);
  a.push_front(0);
  a.push_front(0);
  a.push_front(0);
  a.push_front(-1);
  a.push_front(-2);
  my_list<int>b;
  b.push_back(7);
  b.push_back(8);
  b.push_back(9);
  b.push_back(10);
  b.push_back(11);
  a.splice(a.end(),b);
  shuxin::pt(a);
  shuxin::pt(b);
  // a.merge(b);
  shuxin::pt(a);
  a.reverse();
  shuxin::pt(a);
  cout<<a.size()<<endl;
  return 0;
}