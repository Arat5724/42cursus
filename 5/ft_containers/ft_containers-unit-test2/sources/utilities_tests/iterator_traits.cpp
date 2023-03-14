#include "../system/system_methods.ipp"
#include UTILITIES
#include VECTOR

#define traits std::iterator_traits

typedef std::iterator_traits<std::vector<int>::iterator> stditer;
typedef ft::iterator_traits<_vector<int>::iterator> ftiter;
bool iterator_traits_test() {
  std::vector<string> res;
  std::vector<string> res2;
  g_start1 = g_end1 = timer();

  res.push_back(typeid(stditer::iterator_category).name());
  res.push_back(typeid(stditer::value_type).name());
  res.push_back(typeid(stditer::difference_type).name());
  res.push_back(typeid(stditer::pointer).name());
  res.push_back(typeid(stditer::reference).name());
  res.push_back(
      typeid(std::vector<int>::reverse_iterator::iterator_category).name());
  res.push_back(typeid(std::vector<int>::reverse_iterator::value_type).name());
  res.push_back(
      typeid(std::vector<int>::reverse_iterator::difference_type).name());
  res.push_back(typeid(std::vector<int>::reverse_iterator::pointer).name());
  res.push_back(typeid(std::vector<int>::reverse_iterator::reference).name());

  res2.push_back(typeid(ftiter::iterator_category).name());
  res2.push_back(typeid(ftiter::value_type).name());
  res2.push_back(typeid(ftiter::difference_type).name());
  res2.push_back(typeid(ftiter::pointer).name());
  res2.push_back(typeid(ftiter::reference).name());
  res2.push_back(
      typeid(_vector<int>::reverse_iterator::iterator_category).name());
  res2.push_back(typeid(_vector<int>::reverse_iterator::value_type).name());
  res2.push_back(
      typeid(_vector<int>::reverse_iterator::difference_type).name());
  res2.push_back(typeid(_vector<int>::reverse_iterator::pointer).name());
  res2.push_back(typeid(_vector<int>::reverse_iterator::reference).name());

  return res == res2;
}

int main() {
  exit(run_bool_unit_test("iterators_traits", iterator_traits_test));
}
