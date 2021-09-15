#include "utils/type.h"
#include <algorithm>
#include <iostream>
#include <type_traits>
#include <vector>

using std::cout;
using std::endl;

template <class InputIter1, class InputIter2>
bool my_includes(InputIter1 first1, InputIter1 last1, InputIter2 first2,
                 InputIter2 last2) {
  while (first1 != last1 && first2 != last2)
    if (*first2 < *first1)
      return false;
    else if (*first1 < *first2)
      ++first1;
    else
      ++first1, ++first2;

  return first2 == last2;
}

template <class ForwardIter1, class ForwardIter2>
ForwardIter1 find_end(ForwardIter1 first1, ForwardIter1 last1,
                      ForwardIter2 first2, ForwardIter2 last2,
                      std::forward_iterator_tag, std::forward_iterator_tag) {
  cout << "forward\n";
  if (first2 == last2)
    return last1;
  else {
    ForwardIter1 result = last1;
    while (1) {
      ForwardIter1 newresult = search(first1, last1, first2, last2);
      if (newresult == last1)
        return result;
      else {
        result = newresult;
        first1 = newresult;
        ++first1;
      }
    }
  }
}

template <class BidirectionalIter1, class BidirectionalIter2>
BidirectionalIter1 find_end(BidirectionalIter1 first1, BidirectionalIter1 last1,
                            BidirectionalIter2 first2, BidirectionalIter2 last2,
                            std::bidirectional_iterator_tag,
                            std::bidirectional_iterator_tag) {
  using RevIter1 = std::reverse_iterator<BidirectionalIter1>;
  using RevIter2 = std::reverse_iterator<BidirectionalIter2>;
  RevIter1 rlast1(first1);
  RevIter2 rlast2(first2);
  RevIter1 rresult =
      std::search(RevIter1(last1), rlast1, RevIter2(last2), rlast2);

  if (rresult == rlast1)
    return last1;
  else {
    BidirectionalIter1 result = rresult.base();
    advance(result, -distance(first2, last2));
    return result;
  }
}

template <class ForwardIter1, class ForwardIter2>
inline ForwardIter1 my_find_end(ForwardIter1 first1, ForwardIter1 last1,
                                ForwardIter2 first2, ForwardIter2 last2) {
  return find_end(
      first1, last1, first2, last2,
      typename std::iterator_traits<ForwardIter1>::iterator_category(),
      typename std::iterator_traits<ForwardIter2>::iterator_category());
}

template <class ForwardIter>
ForwardIter rotate(ForwardIter first, ForwardIter middle, ForwardIter last,
                   std::forward_iterator_tag) {
  if (first == middle)
    return last;
  if (last == middle)
    return first;

  ForwardIter first2 = middle;
  do {
    std::swap(*first++, *first2++);
    if (first == middle)
      middle = first2;
  } while (first2 != last);

  ForwardIter newmiddle = first;

  first2 = middle;

  while (first2 != last) {
    std::swap(*first++, *first2++);
    if (first == middle)
      middle = first2;
    else if (first2 == last)
      first2 = middle;
  }

  return newmiddle;
}

template <class BidirectionalIter>
void reverse(BidirectionalIter first, BidirectionalIter last,
             std::bidirectional_iterator_tag) {
  while (true)
    if (first == last || first == --last)
      return;
    else
      std::iter_swap(first++, last);
}

template <class RandomAccessIter>
void reverse(RandomAccessIter first, RandomAccessIter last,
             std::random_access_iterator_tag) {
  while (first < last)
    iterswap(first++, --last);
}

template <class BidirectionalIter>
inline void reverse(BidirectionalIter first, BidirectionalIter last) {
  reverse(first, last,
          std::iterator_traits<BidirectionalIter>::iterator_category());
}

template <class EuclideanRingElement>
EuclideanRingElement gcd(EuclideanRingElement m, EuclideanRingElement n) {
  while (n != 0) {
    EuclideanRingElement t = m % n;
    m = n;
    n = t;
  }
  return m;
}

template <class BidirectionalIter>
BidirectionalIter rotate(BidirectionalIter first, BidirectionalIter middle,
                         BidirectionalIter last,
                         std::bidirectional_iterator_tag) {
  if (first == middle)
    return last;
  if (last == middle)
    return first;

  reverse(first, middle, std::bidirectional_iterator_tag());
  reverse(middle, last, std::bidirectional_iterator_tag());

  while (first != middle && middle != last)
    std::swap(*first++, *--last);

  if (first == middle) {
    reverse(middle, last, std::bidirectional_iterator_tag());
    return last;
  } else {
    reverse(first, middle, std::bidirectional_iterator_tag());
    return first;
  }
}

template <class RandomAccessIter>
RandomAccessIter rotate(RandomAccessIter first, RandomAccessIter middle,
                        RandomAccessIter last, std::random_access_iterator_tag) {
  cout<<" random\n";
  using Tp = typename std::iterator_traits<RandomAccessIter>::value_type;
  ptrdiff_t n = last - first;
  ptrdiff_t k = middle - first;
  ptrdiff_t l = n - k;
  RandomAccessIter result = first + (last - middle);

  if (k == 0)
    return last;

  else if (k == l) {
    std::swap_ranges(first, middle, middle);
    return result;
  }

  ptrdiff_t d = gcd(n, k);

  for (ptrdiff_t i = 0; i < d; i++) {
    Tp tmp = *first;
    RandomAccessIter p = first;

    if (k < l) {
      for (ptrdiff_t j = 0; j < l / d; j++) {
        if (p > first + l) {
          *p = *(p - l);
          p -= l;
        }

        *p = *(p + k);
        p += k;
      }
    }

    else {
      for (ptrdiff_t j = 0; j < k / d - 1; j++) {
        if (p < last - k) {
          *p = *(p + k);
          p += k;
        }

        *p = *(p - l);
        p -= l;
      }
    }

    *p = tmp;
    ++first;
  }

  return result;
}

template <class ForwardIter>
inline ForwardIter my_rotate(ForwardIter first, ForwardIter middle,
                             ForwardIter last) {
  return rotate(
      first, middle, last,
      typename std::iterator_traits<ForwardIter>::iterator_category());
}

int main() {
  std::vector<int> a{1, 2, 3, 4, 5, 7, 7, 7};
  std::vector<int> b{2, 3, 4};
  std::vector<int> c{2, 3, 4, 6};
  std::vector<int> d{7, 7};
  shuxin::pt(a);
  shuxin::pt(b);
  shuxin::pt(c);
  cout << my_includes(a.begin(), a.end(), b.begin(), b.end()) << endl;
  cout << my_includes(a.begin(), a.end(), c.begin(), c.end()) << endl;
  cout << (*my_find_end(a.begin(), a.end(), d.begin(), d.end())) << endl;
  shuxin::pt(a);
  my_rotate(a.begin(), a.begin() + 3, a.end());
  shuxin::pt(a);
}