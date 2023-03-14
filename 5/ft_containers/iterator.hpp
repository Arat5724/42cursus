#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <iterator>

#include "type_traits.hpp"

namespace ft {

// template <typename _Category, typename T, typename _Distance = ptrdiff_t,
//           typename _Pointer = T*, typename _Reference = T&>
// struct iterator {
//   typedef _Category iterator_category;
//   typedef T value_type;
//   typedef _Distance difference_type;
//   typedef _Pointer pointer;
//   typedef _Reference reference;
// };

template <typename T>
struct has_iterator_typedefs {
 private:
  struct two {
    char lx;
    char lxx;
  };
  template <typename up>
  static two test(...);
  template <typename up>
  static char test(typename ft::void_t<typename up::iterator_category>::type*,
                   typename ft::void_t<typename up::difference_type>::type*,
                   typename ft::void_t<typename up::value_type>::type*,
                   typename ft::void_t<typename up::reference>::type*,
                   typename ft::void_t<typename up::pointer>::type*);

 public:
  static const bool value = sizeof(test<T>(0, 0, 0, 0, 0)) == 1;
};

template <typename Iterator, bool>
struct iterator_traits_helper {};

template <typename Iterator>
struct iterator_traits_helper<Iterator, true> {
  typedef typename Iterator::iterator_category iterator_category;
  typedef typename Iterator::value_type value_type;
  typedef typename Iterator::difference_type difference_type;
  typedef typename Iterator::pointer pointer;
  typedef typename Iterator::reference reference;
};

template <typename Iterator>
struct iterator_traits
    : public iterator_traits_helper<Iterator,
                                    has_iterator_typedefs<Iterator>::value> {};

template <typename T>
struct iterator_traits<T*> {
  typedef std::random_access_iterator_tag iterator_category;
  typedef T value_type;
  typedef std::ptrdiff_t difference_type;
  typedef T* pointer;
  typedef T& reference;
};

template <typename T>
struct iterator_traits<const T*> {
  typedef std::random_access_iterator_tag iterator_category;
  typedef T value_type;
  typedef std::ptrdiff_t difference_type;
  typedef const T* pointer;
  typedef const T& reference;
};

template <typename T>
struct is_input_iterator : ft::is_convertible<T, std::input_iterator_tag> {};

template <typename T>
struct is_forward_iterator : ft::is_convertible<T, std::forward_iterator_tag> {
};

template <typename T>
struct is_bidirectional_iterator
    : ft::is_convertible<T, std::bidirectional_iterator_tag> {};

template <typename T>
struct is_random_access_iterator
    : ft::is_convertible<T, std::random_access_iterator_tag> {};
//
//
//
//
//

template <typename Iterator>
class reverse_iterator {
 protected:
  Iterator current;
  typedef iterator_traits<Iterator> traits_type;

 public:
  typedef Iterator iterator_type;
  typedef typename traits_type::iterator_category iterator_category;
  typedef typename traits_type::value_type value_type;
  typedef typename traits_type::difference_type difference_type;
  typedef typename traits_type::pointer pointer;
  typedef typename traits_type::reference reference;

  reverse_iterator() : current() {}
  explicit reverse_iterator(iterator_type x) : current(x) {}

  // reverse_iterator(const reverse_iterator& other) : current(other.current) {}
  template <typename U>
  reverse_iterator(const reverse_iterator<U>& other) : current(other.base()) {}

  iterator_type base() const { return current; }

  // template <typename U>
  // reverse_iterator& operator=(const reverse_iterator<U>& other) {
  //   current = other.current;
  //   return *this;
  // }
  template <typename U>
  reverse_iterator& operator=(const reverse_iterator<U>& other) {
    current = other.base();
    return *this;
  }

  reference operator*() const {
    Iterator tmp = current;
    return *--tmp;
  }

  pointer operator->() const {
    Iterator tmp = current;
    --tmp;
    // return &(operator*());
    return this->_S_to_pointer(tmp);
  }

  reference operator[](difference_type n) const { return *(*this + n); }

  reverse_iterator& operator++() {
    --current;
    return *this;
  }

  reverse_iterator operator++(int) {
    reverse_iterator<Iterator> temp = *this;
    --current;
    return temp;
  }

  reverse_iterator& operator+=(difference_type n) {
    current -= n;
    return *this;
  }

  reverse_iterator operator+(difference_type n) const {
    return reverse_iterator(current - n);
  }

  reverse_iterator& operator--() {
    ++current;
    return *this;
  }

  reverse_iterator operator--(int) {
    reverse_iterator<Iterator> temp = *this;
    ++current;
    return temp;
  }

  reverse_iterator& operator-=(difference_type n) {
    current += n;
    return *this;
  }

  reverse_iterator operator-(difference_type n) const {
    return reverse_iterator(current + n);
  }

 private:
  template <typename T>
  static T* _S_to_pointer(T* _p) {
    return _p;
  }

  template <typename T>
  static pointer _S_to_pointer(T _t) {
    return _t.operator->();
  }
};

template <typename Iterator1, typename Iterator2>
bool operator==(const reverse_iterator<Iterator1>& lhs,
                const reverse_iterator<Iterator2>& rhs) {
  return lhs.base() == rhs.base();
}
template <typename Iterator1, typename Iterator2>
bool operator!=(const reverse_iterator<Iterator1>& lhs,
                const reverse_iterator<Iterator2>& rhs) {
  return lhs.base() != rhs.base();
}
template <typename Iterator1, typename Iterator2>
bool operator<(const reverse_iterator<Iterator1>& lhs,
               const reverse_iterator<Iterator2>& rhs) {
  return lhs.base() > rhs.base();
}
template <typename Iterator1, typename Iterator2>
bool operator<=(const reverse_iterator<Iterator1>& lhs,
                const reverse_iterator<Iterator2>& rhs) {
  return lhs.base() >= rhs.base();
}
template <typename Iterator1, typename Iterator2>
bool operator>(const reverse_iterator<Iterator1>& lhs,
               const reverse_iterator<Iterator2>& rhs) {
  return lhs.base() < rhs.base();
}
template <typename Iterator1, typename Iterator2>
bool operator>=(const reverse_iterator<Iterator1>& lhs,
                const reverse_iterator<Iterator2>& rhs) {
  return lhs.base() <= rhs.base();
}

template <typename Iterator>
reverse_iterator<Iterator> operator+(
    typename reverse_iterator<Iterator>::difference_type n,
    const reverse_iterator<Iterator>& it) {
  return reverse_iterator<Iterator>(it.base() - n);
}

template <typename Iterator>
typename reverse_iterator<Iterator>::difference_type operator-(
    const reverse_iterator<Iterator>& lhs,
    const reverse_iterator<Iterator>& rhs) {
  return rhs.base() - lhs.base();
}

template <typename Iterator1, typename Iterator2>
typename reverse_iterator<Iterator1>::difference_type operator-(
    const reverse_iterator<Iterator1>& lhs,
    const reverse_iterator<Iterator2>& rhs) {
  return rhs.base() - lhs.base();
}

template <typename InputIterator>
typename ft::iterator_traits<InputIterator>::difference_type _distance(
    InputIterator __first, InputIterator __last, std::input_iterator_tag) {
  typename ft::iterator_traits<InputIterator>::difference_type __n = 0;
  while (__first != __last) {
    ++__first;
    ++__n;
  }
  return __n;
}

template <typename RandomAccessIterator>
std::size_t _distance(RandomAccessIterator first, RandomAccessIterator last,
                      std::random_access_iterator_tag) {
  return last - first;
}

template <typename Iter>
std::size_t distance(Iter first, Iter last) {
  return _distance(first, last,
                   typename iterator_traits<Iter>::iterator_category());
}

}  // namespace ft
#endif