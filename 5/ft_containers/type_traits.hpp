#ifndef TYPE_TRAITS_HPP
#define TYPE_TRAITS_HPP

namespace ft {

template <bool B, typename T = void>
struct enable_if {};

template <typename T>
struct enable_if<true, T> {
  typedef T type;
};

/////

template <typename>
struct void_t {
  typedef void type;
};

template <typename T, typename U>
struct is_convertible {
 private:
  struct two {
    char _lx;
    char _lxx;
  };
  static two test(...);
  static char test(U u);

 public:
  static const bool value = sizeof(test(T())) == 1;
};

///

// struct true_type {
//   const static bool value = true;
// };
// struct false_type {
//   const static bool value = false;
// };

template <typename T>
struct remove_cv {
  typedef T type;
};

template <typename T>
struct remove_cv<const T> {
  typedef T type;
};

template <typename T>
struct remove_cv<volatile T> {
  typedef T type;
};

template <typename T>
struct remove_cv<const volatile T> {
  typedef T type;
};

// template <typename T>
// struct is_integral_helper : public ft::false_type {};

// template <>
// struct is_integral_helper<bool> : public ft::true_type {};

// template <>
// struct is_integral_helper<char> : public ft::true_type {};

// template <>
// struct is_integral_helper<signed char> : public ft::true_type {};

// template <>
// struct is_integral_helper<unsigned char> : public ft::true_type {};

// #ifndef _LIBCPP_NO_HAS_CHAR8_T
// template <>
// struct is_integral_helper<char8_t> : public ft::true_type {};
// #endif

// #ifndef _LIBCPP_HAS_NO_UNICODE_CHARS
// template <>
// struct is_integral_helper<char16_t> : public ft::true_type {};

// template <>
// struct is_integral_helper<char32_t> : public ft::true_type {};
// #endif

// template <>
// struct is_integral_helper<wchar_t> : public ft::true_type {};

// template <>
// struct is_integral_helper<short> : public ft::true_type {};

// template <>
// struct is_integral_helper<unsigned short> : public ft::true_type {};

// template <>
// struct is_integral_helper<int> : public ft::true_type {};

// template <>
// struct is_integral_helper<unsigned int> : public ft::true_type {};

// template <>
// struct is_integral_helper<long> : public ft::true_type {};

// template <>
// struct is_integral_helper<unsigned long> : public ft::true_type {};

// template <>
// struct is_integral_helper<long long> : public ft::true_type {};

// template <>
// struct is_integral_helper<unsigned long long> : public ft::true_type {};

template <typename T>
struct is_integral_helper : public std::false_type {};

template <>
struct is_integral_helper<bool> : public std::true_type {};

template <>
struct is_integral_helper<char> : public std::true_type {};

template <>
struct is_integral_helper<signed char> : public std::true_type {};

template <>
struct is_integral_helper<unsigned char> : public std::true_type {};

#ifndef _LIBCPP_NO_HAS_CHAR8_T
template <>
struct is_integral_helper<char8_t> : public std::true_type {};
#endif

#ifndef _LIBCPP_HAS_NO_UNICODE_CHARS
template <>
struct is_integral_helper<char16_t> : public std::true_type {};

template <>
struct is_integral_helper<char32_t> : public std::true_type {};
#endif

template <>
struct is_integral_helper<wchar_t> : public std::true_type {};

template <>
struct is_integral_helper<short> : public std::true_type {};

template <>
struct is_integral_helper<unsigned short> : public std::true_type {};

template <>
struct is_integral_helper<int> : public std::true_type {};

template <>
struct is_integral_helper<unsigned int> : public std::true_type {};

template <>
struct is_integral_helper<long> : public std::true_type {};

template <>
struct is_integral_helper<unsigned long> : public std::true_type {};

template <>
struct is_integral_helper<long long> : public std::true_type {};

template <>
struct is_integral_helper<unsigned long long> : public std::true_type {};

template <typename T>
struct is_integral
    : public is_integral_helper<typename remove_cv<T>::type>::type {};

}  // namespace ft

#endif