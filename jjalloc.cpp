#include <climits>
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <new>
#include <vector>

using std::cerr;
using std::cout;
using std::endl;

namespace shuxin {

#if 1
template <class T> inline T *_allocate(ptrdiff_t size, T *) {
  std::set_new_handler(0); //当new失败时，呼叫该函数所设的参数
  T *tmp = (T *)(::operator new((size_t)(size * sizeof(T))));
  if (tmp == 0) {
    cerr << "out of memory" << endl;
    exit(1);
  }
  return tmp;
}

template <class T> inline void _deallocate(T *buffer) {
  ::operator delete(buffer);
}

template <class T1, class T2> inline void _construct(T1 *p, const T2 &value) {
  new (p) T1(value);
}

template <class T> inline void _destroy(T *ptr) { ptr->~T(); }

template <class T> class allocator {
public:
  typedef T value_type;
  typedef T *pointer;
  typedef const T *const_pointer;
  typedef T &reference;
  typedef const T &const_reference;
  typedef size_t size_type;
  typedef ptrdiff_t difference_type;

  template <class U> struct rebind { typedef allocator<U> other; };

  pointer allocate(size_type n, const void *hint = 0) {
    return _allocate((difference_type)n, (pointer)0);
  }

  void deallocate(pointer p, size_type n) { _deallocate(p); }

  void construct(pointer p, const T &value) { _construct(p, value); }

  void destroy(pointer p) { _destroy(p); }

  void destroy(pointer start, pointer end) {
    for (pointer it = start; it != end; ++it)
      _destroy(it);
  }

  pointer address(reference x) { return (pointer)&x; }

  const_pointer const_address(const_reference x) { return (const_pointer)&x; }

  size_type max_size() const { return size_type(UINT_MAX / sizeof(T)); }

  pointer _Zero_range(pointer first, pointer last) {
    for (; first != last; ++first)
      (*first) = 0;
    return last;
  }
};

template <> void allocator<char>::destroy(char *p) {
  cout << "char*" << endl;
  _destroy(p);
}

template <> char *allocator<char>::_Zero_range(char *first, char *last) {
  cout << "char*" << endl;
  memset(first, 0, static_cast<size_t>(last - first));
  return last;
}
#endif
#if 1
class malloc_alloc {
public:
  static void *allocate(size_t);
  static void *reallocate(void *, size_t);
  static void deallocate(void *, size_t);
  static void (*set_new_handler(void (*)()))();

private:
  static void (*oom_handler)();
  static void *oom_alloc(size_t);
  static void *oom_realloc(void *, size_t);
};

void (*malloc_alloc::oom_handler)() = 0;

void *malloc_alloc::allocate(size_t n) {
  cout << "maloc_alloc" << endl;
  void *ret = malloc(n);
  if (!ret)
    ret = oom_alloc(n);
  return ret;
}

void *malloc_alloc::reallocate(void *p, size_t n) {
  void *ret = realloc(p, n);
  if (!ret)
    ret = oom_realloc(p, n);
  return ret;
}

void malloc_alloc::deallocate(void *p, size_t n) { free(p); }

void (*malloc_alloc::set_new_handler(void (*f)()))() {
  void (*old)() = oom_handler;
  oom_handler = f;
  return old;
}

void *malloc_alloc::oom_alloc(size_t n) {
  void *ret;
  for (;;) {
    if (!oom_handler)
      exit(1);
    (*oom_handler)();
    ret = malloc(n);
    if (ret)
      return ret;
  }
}

void *malloc_alloc::oom_realloc(void *p, size_t n) {
  void *ret;
  for (;;) {
    if (!oom_handler)
      exit(1);
    (*oom_handler)();
    ret = realloc(p, n);
    if (ret)
      return ret;
  }
}

static const size_t __ALIGN = 8;
static const size_t __MAX_BYTES = 128;
static const size_t __FREELISTS_NUMS = __MAX_BYTES / __ALIGN;

union obj {
  union obj *next_free_list; //下一个freelist
  char client_data[1];       //用户能看到的
};

class pool_alloc {
public:
  static void *allocate(size_t);
  static void deallocate(void *, size_t);

private:
  static size_t ROUND_UP(size_t);
  static size_t FREELIST_INDEX(size_t);

public:
  static obj *free_list[__FREELISTS_NUMS];
  static char *start_pos;
  static char *end_pos;
  static size_t pool_size;

private:
  static void *refill(size_t);
  static char *chunk_alloc(size_t, int &);
};

size_t pool_alloc::pool_size = 0;
char *pool_alloc::start_pos = 0;
char *pool_alloc::end_pos = 0;

obj *pool_alloc::free_list[__FREELISTS_NUMS] = {0, 0, 0, 0, 0, 0, 0, 0,
                                                0, 0, 0, 0, 0, 0, 0, 0};

size_t pool_alloc::ROUND_UP(size_t n) {
  return (((n) + __ALIGN - 1) & ~(__ALIGN - 1));
}

size_t pool_alloc::FREELIST_INDEX(size_t n) {
  return (((n) + __ALIGN - 1) / __ALIGN - 1);
}

void *pool_alloc::allocate(size_t n) {
  cout << " memory pool" << endl;
  if (n > __MAX_BYTES)
    return malloc_alloc::allocate(n);

  obj **ptr_free_list;
  obj *result;
  ptr_free_list = free_list + FREELIST_INDEX(n);
  result = *ptr_free_list;

  if (!result) {
    void *r = refill(ROUND_UP(n));
    return r;
  }
  *ptr_free_list = result->next_free_list;

  return (result);
}

void pool_alloc::deallocate(void *p, size_t n) {
  if (n > __MAX_BYTES || !n) {
    malloc_alloc::deallocate(p, n);
    return;
  }

  obj *q = (obj *)p;
  obj **ptr_free_list = free_list + FREELIST_INDEX(n);
  q->next_free_list = *ptr_free_list;
  *ptr_free_list = q;
}

void *pool_alloc::refill(size_t n) {
  int nobj = 15;
  char *chunk = chunk_alloc(n, nobj);

  if (nobj == 1)
    return (chunk);

  obj *curr;
  obj **ptr_free_list = free_list + FREELIST_INDEX(n);

  *ptr_free_list = curr = (obj *)(chunk + n);
  int len = nobj - 1;
  for (int i = 1; i < len; i++) {
    curr->next_free_list = (obj *)((char *)curr + n);
    curr = curr->next_free_list;
  }
  curr->next_free_list = 0;
  return (chunk);
}

char *pool_alloc::chunk_alloc(size_t n, int &nobj) {
  size_t pool_left = end_pos - start_pos;
  char *ret;
  if (pool_left >= n * nobj) {
    ret = start_pos;
    start_pos += n * nobj;
    return ret;
  } else if (pool_left >= n) {
    nobj = pool_left / n;
    ret = start_pos;
    start_pos += n * nobj;
    return ret;
  } else {
    size_t bytes_needed = (n << 1) * nobj + ROUND_UP(pool_size >> 4);
    if (pool_left > 0) {
      obj **ptr_free_list = free_list + FREELIST_INDEX(pool_left);
      ((obj *)start_pos)->next_free_list = *ptr_free_list;
      *ptr_free_list = (obj *)start_pos;
    }
    start_pos = (char *)malloc(bytes_needed);
    if (!start_pos) {
      obj **ptr_free_list;
      obj *p;
      for (int i = n; i < __MAX_BYTES; i += __ALIGN) {
        ptr_free_list = free_list + FREELIST_INDEX(i);
        p = *ptr_free_list;
        if (p) {
          *ptr_free_list = p->next_free_list;
          start_pos = (char *)p;
          end_pos = start_pos + i;
          return (chunk_alloc(n, nobj));
        }
      }
      end_pos = 0;
      start_pos = (char *)malloc_alloc::allocate(bytes_needed);
    }
    pool_size += bytes_needed;
    end_pos = start_pos + bytes_needed;
    return chunk_alloc(n, nobj);
  }
}

typedef pool_alloc alloc;
#endif
template <typename T, typename Alloc = alloc> class simple_alloc {
public:
  typedef T value_type;
  typedef T *pointer;
  typedef const T *const_pointer;
  typedef T &reference;
  typedef const T &const_reference;
  typedef size_t size_type;
  typedef ptrdiff_t difference_type;

  template <class U> struct rebind { typedef simple_alloc<U> other; };

  static T *allocate(const size_t n) {
    return n ? (T *)Alloc::allocate(n * sizeof(T)) : 0;
  }
  static void deallocate(T *p, const size_t n) {
    Alloc::deallocate(p, n * sizeof(T));
  }
};
} // namespace shuxin

// int main()
// {
//     std::vector<int, shuxin::simple_alloc<int>>my_vector;
//     for (int i = 0; i < 10; i++)
//         my_vector.push_back(i);
//     for (auto it : my_vector)
//         cout << it << endl;
//     return 0;
// }