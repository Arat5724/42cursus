
#include <deque>
#include <map>
#include <set>
#include <stack>
#include <vector>

#include "map.hpp"
#include "pair.hpp"
#include "set.hpp"
#include "stack.hpp"
#include "vector.hpp"

int main(void) {
  std::cout << "--------------------vector--------------------" << std::endl;
  ft::vector<int> v1;
  for (int i = 0; i < 10; i++) {
    v1.push_back(i);
    v1.push_back(v1.size());
  }
  v1.insert(v1.begin(), 50);
  v1.erase(v1.begin());
  v1.pop_back();
  std::vector<int> v2;
  for (int i = 0; i < 10; i++) {
    v2.push_back(i);
    v2.push_back(v2.size());
  }
  v2.insert(v2.begin(), 50);
  v2.erase(v2.begin());
  v2.pop_back();

  ft::vector<int>::iterator it1 = v1.begin();
  std::vector<int>::iterator it2 = v2.begin();

  while (it1 != v1.end() && it2 != v2.end()) {
    std::cout << "ft : " << *(it1) << " std: " << *(it2) << std::endl;
    it1++;
    it2++;
  }

  std::cout << "--------------------stack--------------------" << std::endl;
  ft::stack<int> st1;
  for (int i = 0; i < 10; i++) {
    st1.push(i);
    st1.push(st1.size());
  }
  st1.pop();
  std::stack<int> st2;
  for (int i = 0; i < 10; i++) {
    st2.push(i);
    st2.push(st2.size());
  }
  st2.pop();
  while (!st1.empty() && !st2.empty()) {
    std::cout << "ft : " << st1.top() << " std: " << st2.top() << std::endl;
    st1.pop();
    st2.pop();
  }
  std::cout << "--------------------stack2--------------------" << std::endl;
  ft::stack<int, std::deque<int> > st12;
  for (int i = 0; i < 10; i++) {
    st12.push(i);
    st12.push(st12.size());
  }
  st12.pop();
  std::stack<int, std::deque<int> > st22;
  for (int i = 0; i < 10; i++) {
    st22.push(i);
    st22.push(st22.size());
  }
  st22.pop();
  while (!st12.empty() && !st22.empty()) {
    std::cout << "ft : " << st12.top() << " std: " << st22.top() << std::endl;
    st12.pop();
    st22.pop();
  }

  std::cout << "--------------------map--------------------" << std::endl;

  ft::map<int, int> map1;
  std::map<int, int> map2;

  for (int i = 1; i < 11; i++) {
    map1.insert(ft::make_pair(i, i * 3));
    map1[i * 10] = i;
  }
  map1.erase(++ ++map1.begin());

  for (int i = 1; i < 11; i++) {
    map2.insert(std::make_pair(i, i * 3));
    map2[i * 10] = i;
  }
  map2.erase(++ ++map2.begin());
  ft::map<int, int>::iterator mapit1 = map1.begin();
  std::map<int, int>::iterator mapit2 = map2.begin();

  while (mapit1 != map1.end()) {
    std::cout << "ft : " << (mapit1)->first << ", " << (mapit1)->second
              << " std: " << (mapit2)->first << ", " << (mapit2)->second
              << std::endl;
    mapit1++;
    mapit2++;
  }

  std::cout << "bound test" << std::endl;
  mapit1 = map1.lower_bound(-5);
  mapit2 = map2.lower_bound(-5);
  if (mapit1 != map1.end() && mapit2 != map2.end()) {
    std::cout << "ft : " << (mapit1)->first << ", " << (mapit1)->second
              << " std: " << (mapit2)->first << ", " << (mapit2)->second
              << std::endl;
  } else {
    std::cout << "It's end()!" << std::endl;
  }
  mapit1 = map1.upper_bound(-5);
  mapit2 = map2.upper_bound(-5);
  if (mapit1 != map1.end() && mapit2 != map2.end()) {
    std::cout << "ft : " << (mapit1)->first << ", " << (mapit1)->second
              << " std: " << (mapit2)->first << ", " << (mapit2)->second
              << std::endl;
  } else {
    std::cout << "It's end()!" << std::endl;
  }

  mapit1 = map1.lower_bound(6);
  mapit2 = map2.lower_bound(6);
  if (mapit1 != map1.end() && mapit2 != map2.end()) {
    std::cout << "ft : " << (mapit1)->first << ", " << (mapit1)->second
              << " std: " << (mapit2)->first << ", " << (mapit2)->second
              << std::endl;
  } else {
    std::cout << "It's end()!" << std::endl;
  }
  mapit1 = map1.upper_bound(6);
  mapit2 = map2.upper_bound(6);
  if (mapit1 != map1.end() && mapit2 != map2.end()) {
    std::cout << "ft : " << (mapit1)->first << ", " << (mapit1)->second
              << " std: " << (mapit2)->first << ", " << (mapit2)->second
              << std::endl;
  } else {
    std::cout << "It's end()!" << std::endl;
  }

  mapit1 = map1.lower_bound(16);
  mapit2 = map2.lower_bound(16);
  if (mapit1 != map1.end() && mapit2 != map2.end()) {
    std::cout << "ft : " << (mapit1)->first << ", " << (mapit1)->second
              << " std: " << (mapit2)->first << ", " << (mapit2)->second
              << std::endl;
  } else {
    std::cout << "It's end()!" << std::endl;
  }
  mapit1 = map1.upper_bound(16);
  mapit2 = map2.upper_bound(16);
  if (mapit1 != map1.end() && mapit2 != map2.end()) {
    std::cout << "ft : " << (mapit1)->first << ", " << (mapit1)->second
              << " std: " << (mapit2)->first << ", " << (mapit2)->second
              << std::endl;
  } else {
    std::cout << "It's end()!" << std::endl;
  }

  std::cout << "--------------------set--------------------" << std::endl;
  ft::set<int> set1;
  std::set<int> set2;

  for (int i = 1; i < 11; i++) {
    set1.insert(i * 2);
  }
  set1.erase(++ ++set1.begin());

  for (int i = 1; i < 11; i++) {
    set2.insert(i * 2);
  }
  set2.erase(++ ++set2.begin());

  ft::set<int>::iterator setit1 = set1.begin();
  std::set<int>::iterator setit2 = set2.begin();

  while (setit1 != set1.end()) {
    std::cout << "ft : " << *(setit1) << " std: " << *(setit2) << std::endl;
    setit1++;
    setit2++;
  }

  std::cout << "bound test" << std::endl;
  setit1 = set1.lower_bound(-2);
  setit2 = set2.lower_bound(-2);
  if (setit1 != set1.end() && setit2 != set2.end()) {
    std::cout << "ft : " << *(setit1) << " std: " << *(setit2) << std::endl;
  } else {
    std::cout << "It's end()!" << std::endl;
  }
  setit1 = set1.upper_bound(-2);
  setit2 = set2.upper_bound(-2);
  if (setit1 != set1.end() && setit2 != set2.end()) {
    std::cout << "ft : " << *(setit1) << " std: " << *(setit2) << std::endl;
  } else {
    std::cout << "It's end()!" << std::endl;
  }

  setit1 = set1.lower_bound(6);
  setit2 = set2.lower_bound(6);
  if (setit1 != set1.end() && setit2 != set2.end()) {
    std::cout << "ft : " << *(setit1) << " std: " << *(setit2) << std::endl;
  } else {
    std::cout << "It's end()!" << std::endl;
  }
  setit1 = set1.upper_bound(6);
  setit2 = set2.upper_bound(6);
  if (setit1 != set1.end() && setit2 != set2.end()) {
    std::cout << "ft : " << *(setit1) << " std: " << *(setit2) << std::endl;
  } else {
    std::cout << "It's end()!" << std::endl;
  }

  setit1 = set1.lower_bound(16);
  setit2 = set2.lower_bound(16);
  if (setit1 != set1.end() && setit2 != set2.end()) {
    std::cout << "ft : " << *(setit1) << " std: " << *(setit2) << std::endl;
  } else {
    std::cout << "It's end()!" << std::endl;
  }
  setit1 = set1.upper_bound(16);
  setit2 = set2.upper_bound(16);
  if (setit1 != set1.end() && setit2 != set2.end()) {
    std::cout << "ft : " << *(setit1) << " std: " << *(setit2) << std::endl;
  } else {
    std::cout << "It's end()!" << std::endl;
  }
}