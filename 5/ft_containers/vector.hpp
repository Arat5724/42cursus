#ifndef VECTOR_HPP
#define VECTOR_HPP

//#include <exception>
#include <iostream>
#include <memory>

#include "iterator.hpp"
#include "type_traits.hpp"
#include "utils.hpp"

namespace ft {

template <typename T, typename Alloc = std::allocator<T> >
class vector {
 public:
  typedef T value_type;
  typedef Alloc allocator_type;

  typedef typename allocator_type::reference reference;
  typedef typename allocator_type::const_reference const_reference;

  typedef typename allocator_type::pointer pointer;
  typedef typename allocator_type::const_pointer const_pointer;

  typedef T* iterator;
  typedef const T* const_iterator;

  typedef ft::reverse_iterator<iterator> reverse_iterator;
  typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

  typedef typename allocator_type::size_type size_type;
  typedef
      typename ft::iterator_traits<iterator>::difference_type difference_type;

 private:
  allocator_type _alloc;
  pointer _start;
  pointer _finish;
  pointer _end_of_storage;

 public:
  // constructor
  vector()
      : _alloc(allocator_type()),
        _start(NULL),
        _finish(NULL),
        _end_of_storage(0) {}

  explicit vector(const allocator_type& alloc)
      : _alloc(alloc), _start(NULL), _finish(NULL), _end_of_storage(0) {}

  explicit vector(size_type count, const value_type& value = T(),
                  const allocator_type& alloc = allocator_type())
      : _alloc(alloc),
        _start(_alloc.allocate(count)),
        _finish(_start),
        _end_of_storage(_start + count) {
    while (count--) {
      _alloc.construct(_finish, value);
      _finish++;
    }
  }

  template <typename InputIt>
  vector(InputIt first,
         typename enable_if<ft::is_input_iterator<typename ft::iterator_traits<
                                InputIt>::iterator_category>::value,
                            InputIt>::type last,
         const allocator_type& alloc = allocator_type())
      : _alloc(alloc) {
    difference_type n = ft::distance(first, last);
    _start = _alloc.allocate(n);
    _finish = _start;
    _end_of_storage = _start + n;
    for (difference_type i = 0; i < n; i++) {
      _alloc.construct(_finish, *first);
      first++;
      _finish++;
    }
  }

  vector(const vector& other)
      : _alloc(other._alloc),
        _start(_alloc.allocate(other.capacity())),
        _finish(_start),
        _end_of_storage(_start + other.capacity()) {
    this->insert(this->begin(), other.begin(), other.end());
  }

  ~vector() {
    if (this->_start) {
      this->clear();
      this->_alloc.deallocate(this->_start,
                              this->_end_of_storage - this->_start);
    }
  }

  vector& operator=(const vector& other) {
    if (this != &other) {
      this->clear();
      this->insert(this->end(), other.begin(), other.end());
    }
    return (*this);
  }

  void assign(size_type count, const value_type& value) {
    this->clear();
    this->insert(this->begin(), count, value);
  }

  template <typename InputIt>
  void assign(
      InputIt first,
      typename enable_if<ft::is_input_iterator<typename ft::iterator_traits<
                             InputIt>::iterator_category>::value,
                         InputIt>::type last) {
    // void assign(InputIt first, InputIt last) {
    this->clear();
    this->insert(this->begin(), first, last);
  }

  reference at(size_type n) {
    if (_start + n >= _finish) {
      throw std::out_of_range("out_of_range");
    }
    return (*(_start + n));
  }
  const_reference at(size_type n) const {
    if (_start + n >= _finish) {
      throw std::out_of_range("out_of_range");
    }
    return (*(_start + n));
  }

  reference operator[](size_type n) { return (*(_start + n)); }
  const_reference operator[](size_type n) const { return (*(_start + n)); }

  reference front() { return (*_start); }
  const_reference front() const { return (*_start); }

  reference back() { return (*(_finish - 1)); }
  const_reference back() const { return (*(_finish - 1)); }

  T* data() { return (&*this[0]); }

  /////////////////////////////////////////

  iterator begin() { return (_start); };
  const_iterator begin() const { return (_start); }

  iterator end() { return (_finish); }
  const_iterator end() const { return (_finish); }

  reverse_iterator rbegin() { return (reverse_iterator(this->end())); }
  const_reverse_iterator rbegin() const {
    return (reverse_iterator(this->end()));
  }

  reverse_iterator rend() { return (reverse_iterator(this->begin())); }
  const_reverse_iterator rend() const {
    return (reverse_iterator(this->begin()));
  }

  bool empty() const { return (this->_finish == this->_start ? true : false); }

  size_type size() const { return (this->_finish - this->_start); }

  size_type max_size() const { return allocator_type().max_size(); }

  void reserve(size_type n) {
    if (n > this->max_size()) throw(std::length_error("length_error"));
    if (n > this->capacity()) {
      pointer new_start = _alloc.allocate(n);
      pointer new_finish = new_start;
      pointer new_end_of_storage = new_start + n;
      for (iterator it = this->begin(); it != this->end(); it++)
        _alloc.construct(new_finish++, *it);
      this->clear();
      _alloc.deallocate(this->_start, this->_end_of_storage - this->_start);
      this->_start = new_start;
      this->_finish = new_finish;
      this->_end_of_storage = new_end_of_storage;
    }
  }

  size_type capacity() const { return (this->_end_of_storage - this->_start); }

  /////////////////////////////////

  void clear() {
    if (_finish != _start) {
      this->_finish -= 1;
      for (; this->_finish != this->_start; this->_finish--) {
        _alloc.destroy(_finish);
      }
      _alloc.destroy(_finish);
    }
  }

  iterator insert(iterator pos, const value_type& value) {
    size_type start_index = &(*(pos)) - _start;
    if (_finish == _end_of_storage) {
      if (this->size() == 0) {
        this->reserve(1);
      } else {
        this->reserve(this->size() * 2);
      }
    }
    pos = iterator(_start + start_index);
    for (pointer temp = _finish; temp != &(*pos); temp--) {
      _alloc.construct(temp, *(temp - 1));
      _alloc.destroy(temp - 1);
    }
    _alloc.construct(&(*pos), value);
    _finish++;
    return pos;
  }

  void insert(iterator pos, size_type count, const value_type& value) {
    size_type start_index = &(*(pos)) - _start;
    if (_finish + count > _end_of_storage) {
      this->reserve(this->size() + count);
    }
    pos = iterator(_start + start_index);
    if (&(*(pos)) != _finish) {
      pointer temp = _finish + count - 1;
      size_type n = this->size() - start_index;
      for (size_type i = 0; i < n; i++) {
        _alloc.construct(temp - i, *(temp - count - i));
        _alloc.destroy(temp - count - i);
      }
    }
    for (size_type i = 0; i < count; i++) {
      _alloc.construct(&(*(pos + i)), value);
    }
    _finish += count;
  }

  template <typename InputIt>
  void insert(
      iterator pos, InputIt first,
      typename enable_if<ft::is_input_iterator<typename ft::iterator_traits<
                             InputIt>::iterator_category>::value,
                         InputIt>::type last) {
    // void insert(iterator pos, InputIt first, InputIt last) {
    size_type start_index = &(*(pos)) - _start;
    difference_type count = ft::distance(first, last);
    if (_finish + count >= _end_of_storage) {
      this->reserve(this->size() + count);
    }
    pos = iterator(_start + start_index);
    if (&(*(pos)) != _finish) {
      pointer temp = _finish + count - 1;
      size_type n = this->size() - start_index;
      for (size_type i = 0; i < n; i++) {
        _alloc.construct(temp - i, *(temp - count - i));
        _alloc.destroy(temp - count - i);
      }
    }
    for (difference_type i = 0; i < count; i++) {
      _alloc.construct(&(*(pos + i)), *first);
      first++;
    }
    _finish += count;
  }

  iterator erase(iterator pos) {
    pointer temp = &(*pos);
    if (temp < _finish) {
      _alloc.destroy(temp);
      for (; temp + 1 != _finish; temp++) {
        _alloc.construct(temp, *(temp + 1));
        _alloc.destroy(temp + 1);
      }
      _finish = &(*temp);
    }
    return pos;
  }

  iterator erase(iterator first, iterator last) {
    if (last != first) {
      iterator ret = first;
      for (iterator temp = first; temp != last; temp++) {
        _alloc.destroy(&(*temp));
      }
      while (&(*last) != _finish) {
        _alloc.construct(&(*first), *(last));
        _alloc.destroy(&(*last));
        first++;
        last++;
      }
      _finish = &(*first);
      return ret;
    }
    return last;
  }

  void push_back(const value_type& value) {
    if (_finish == _end_of_storage) {
      if (this->size() == 0) {
        this->reserve(1);
      } else {
        this->reserve(this->size() * 2);
      }
    }
    _alloc.construct(_finish, value);
    _finish++;
  }

  void pop_back() { _alloc.destroy(--_finish); }

  void resize(size_type count, T value = T()) {
    size_type current_size = this->size();
    if (count <= current_size) {
      for (; current_size != count; current_size--) {
        _alloc.destroy(--_finish);
      }
    } else {
      for (; current_size != count; current_size++) {
        push_back(value);
      }
    }
  }

  void swap(vector& other) {
    if (this != &other) {
      pointer temp_start = this->_start;
      pointer temp_finish = this->_finish;
      pointer temp_end_of_storage = this->_end_of_storage;
      allocator_type temp_alloc = this->_alloc;

      this->_start = other._start;
      this->_finish = other._finish;
      this->_end_of_storage = other._end_of_storage;
      this->_alloc = other._alloc;

      other._start = temp_start;
      other._finish = temp_finish;
      other._end_of_storage = temp_end_of_storage;
      other._alloc = temp_alloc;
    }
  }
};

template <typename T, typename Alloc>
bool operator==(const ft::vector<T, Alloc>& lhs,
                const ft::vector<T, Alloc>& rhs) {
  if (lhs.size() != rhs.size()) {
    return false;
  }
  typename ft::vector<T, Alloc>::const_iterator lit = lhs.begin();
  typename ft::vector<T, Alloc>::const_iterator rit = rhs.begin();
  while (lit != lhs.end()) {
    if (*lit != *rit) {
      return false;
    }
    lit++;
    rit++;
  }
  return true;
}

template <typename T, typename Alloc>
bool operator!=(const ft::vector<T, Alloc>& lhs,
                const ft::vector<T, Alloc>& rhs) {
  return (!(lhs == rhs));
}

template <typename T, typename Alloc>
bool operator<(const ft::vector<T, Alloc>& lhs,
               const ft::vector<T, Alloc>& rhs) {
  return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(),
                                     rhs.end());
  // typename ft::vector<T, Alloc>::const_iterator lit = lhs.begin();
  // typename ft::vector<T, Alloc>::const_iterator rit = rhs.begin();
  // while (lit != lhs.end() && rit != rhs.end()) {
  //   if (*lit > *rit) {
  //     return false;
  //   } else if (*lit < *rit) {
  //     return true;
  //   }
  //   lit++;
  //   rit++;
  // }
  // if (rit == rhs.end()) {
  //   return false;
  // }
  // return true;
}

template <typename T, typename Alloc>
bool operator>(const ft::vector<T, Alloc>& lhs,
               const ft::vector<T, Alloc>& rhs) {
  return rhs < lhs;
}

template <typename T, typename Alloc>
bool operator<=(const ft::vector<T, Alloc>& lhs,
                const ft::vector<T, Alloc>& rhs) {
  return (!(lhs > rhs));
}

template <typename T, typename Alloc>
bool operator>=(const ft::vector<T, Alloc>& lhs,
                const ft::vector<T, Alloc>& rhs) {
  return (!(lhs < rhs));
}

template <typename T, typename Alloc>
void swap(vector<T, Alloc>& lhs, vector<T, Alloc>& rhs) {
  lhs.swap(rhs);
}

}  // namespace ft
#endif