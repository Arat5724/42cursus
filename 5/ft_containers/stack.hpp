#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"

namespace ft {
template <typename T, typename Container = ft::vector<T> >
class _LIBCPP_TEMPLATE_VIS stack {
 public:
  typedef Container container_type;
  typedef typename container_type::value_type value_type;
  typedef typename container_type::reference reference;
  typedef typename container_type::const_reference const_reference;
  typedef typename container_type::size_type size_type;

 protected:
  container_type c;

 public:
  explicit stack(const Container& cont = Container()) : c(cont) {}
  stack(const stack& other) : c(other.c) {}
  ~stack() {}

  stack& operator=(const stack& other) { c = other.c; }

  reference top() { return c.back(); }
  const_reference top() const { return c.back(); }

  bool empty() const { return c.empty(); }

  size_type size() const { return c.size(); }
  void push(const value_type& value) { c.push_back(value); }
  void pop() { c.pop_back(); }

  template <typename _T, typename _Container>
  friend bool operator==(const stack<_T, _Container>& lhs,
                         const stack<_T, _Container>& rhs);

  template <typename _T, typename _Container>
  friend bool operator<(const stack<_T, _Container>& lhs,
                        const stack<_T, _Container>& rhs);
};

template <typename _T, typename _Container>
bool operator==(const stack<_T, _Container>& lhs,
                const stack<_T, _Container>& rhs) {
  return lhs.c == rhs.c;
}

template <typename _T, typename _Container>
bool operator!=(const stack<_T, _Container>& lhs,
                const stack<_T, _Container>& rhs) {
  return !(lhs == rhs);
}

template <typename _T, typename _Container>
bool operator<(const stack<_T, _Container>& lhs,
               const stack<_T, _Container>& rhs) {
  return lhs.c < rhs.c;
}

template <typename _T, typename _Container>
bool operator<=(const stack<_T, _Container>& lhs,
                const stack<_T, _Container>& rhs) {
  return !(rhs < lhs);
}

template <typename _T, typename _Container>
bool operator>(const stack<_T, _Container>& lhs,
               const stack<_T, _Container>& rhs) {
  return rhs < lhs;
}

template <typename _T, typename _Container>
bool operator>=(const stack<_T, _Container>& lhs,
                const stack<_T, _Container>& rhs) {
  return !(lhs < rhs);
}
}  // namespace ft

#endif