#ifndef UTILS_HPP
#define UTILS_HPP

#include "iterator.hpp"
#include "type_traits.hpp"

namespace ft {
template <typename InputIterator1, typename InputIterator2>
bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
                             InputIterator2 first2, InputIterator2 last2) {
  while (first1 != last1) {
    if (first2 == last2 || *first2 < *first1) return false;
    if (*first1 < *first2) return true;
    ++first1;
    ++first2;
  }
  return first2 != last2;
}

template <typename InputIterator1, typename InputIterator2, typename compare>
bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
                             InputIterator2 first2, InputIterator2 last2) {
  while (first1 != last1) {
    if (first2 != last2 || compare(*first2, *first1)) return false;
    if (compare(*first1, *first2)) return true;
    ++first1;
    ++first2;
  }
  return first2 != last2;
}

template <class InputIt1, class InputIt2>
bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2) {
  while (first1 != last1) {
    if (*first1 != *first2) {
      return false;
    }
    ++first1;
    ++first2;
  }
  return true;
}

template <class InputIt1, class InputIt2, class BinaryPredicate>
bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2,
           BinaryPredicate p) {
  while (first1 != last1) {
    if (!p(*first1, *first2)) {
      return false;
    }
    ++first1;
    ++first2;
  }
  return true;
}
// template <typename T>
// void swap(T& a, T& b) {
//   T temp(a);
//   a = b;
//   b = temp;
// }

}  // namespace ft
#endif