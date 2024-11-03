#include <gtest/gtest.h>

#include <array>
#include <deque>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <utility>
#include <vector>

#include "s21_containers.h"
#include "s21_containersplus.h"

// array
TEST(test_constructor_array, test_1) {
  s21::S21Array<int, 0> a;
  std::array<int, 0> b;
  ASSERT_EQ(a.size(), b.size());
}

TEST(test_constructor_array, test_2) {
  s21::S21Array<int, 3> a = {1, 2, 3};
  std::array<int, 3> b = {1, 2, 3};
  EXPECT_EQ(a.size(), b.size());
}

TEST(test_constructor_array, test_3) {
  s21::S21Array<int, 3> a = {1, 2, 3};
  s21::S21Array<int, 3> b(a);

  std::array<int, 3> c = {1, 2, 3};
  std::array<int, 3> d(c);
  EXPECT_EQ(b.size(), d.size());
}

TEST(test_constructor_array, test_4) {
  s21::S21Array<int, 3> a = {1, 2, 3};
  s21::S21Array<int, 3> b(std::move(a));
  EXPECT_EQ(a.size(), 3u);
  EXPECT_EQ(b.size(), 3u);
  EXPECT_EQ(b[0], 1);
  EXPECT_EQ(b[1], 2);
  EXPECT_EQ(b[2], 3);
}

TEST(test_constructor_array, test_5) {
  s21::S21Array<int, 3> a = {1, 2, 3};
  s21::S21Array<int, 3> b = a;
  EXPECT_EQ(a.size(), 3u);
  EXPECT_EQ(b.size(), 3u);
  EXPECT_EQ(b[0], 1);
  EXPECT_EQ(b[1], 2);
  EXPECT_EQ(b[2], 3);
}

TEST(test_constructor_array, test_6) {
  s21::S21Array<int, 3> a = {1, 2, 3};
  s21::S21Array<int, 3> b = {1, 2, 3};
  b = a;
  EXPECT_EQ(a.size(), 3u);
  EXPECT_EQ(b.size(), 3u);
  EXPECT_EQ(b[0], 1);
  EXPECT_EQ(b[1], 2);
  EXPECT_EQ(b[2], 3);
}

TEST(test_element_access_array, test_1) {
  s21::S21Array<int, 3> a = {1, 2, 3};
  std::array<int, 3> b = {1, 2, 3};
  EXPECT_EQ(a.at(2), b.at(2));
}

TEST(test_element_access_array, test_2) {
  s21::S21Array<int, 3> a = {1, 2, 3};
  bool catch_ex = false;
  try {
    a.at(3);
  } catch (const std::out_of_range &e) {
    std::cerr << e.what() << '\n';
    catch_ex = true;
  }
  ASSERT_EQ(catch_ex, true);
}

TEST(test_element_access_array, test_3) {
  s21::S21Array<int, 3> a = {1, 2, 3};
  std::array<int, 3> b = {1, 2, 3};
  EXPECT_EQ(a[2], b[2]);
}

TEST(test_element_access_array, test_4) {
  s21::S21Array<int, 3> a = {1, 2, 3};
  bool catch_ex = false;
  try {
    a[3];
  } catch (const std::out_of_range &e) {
    std::cerr << e.what() << '\n';
    catch_ex = true;
  }
  ASSERT_EQ(catch_ex, true);
}

TEST(test_element_access_array, test_5) {
  s21::S21Array<int, 3> a = {1, 2, 3};
  std::array<int, 3> b = {1, 2, 3};
  EXPECT_EQ(a.front(), b.front());
}

TEST(test_element_access_array, test_6) {
  s21::S21Array<int, 3> a = {1, 2, 3};
  std::array<int, 3> b = {1, 2, 3};
  EXPECT_EQ(a.back(), b.back());
}

TEST(test_element_access_array, test_7) {
  s21::S21Array<int, 3> a = {1, 2, 3};
  std::array<int, 3> b = {1, 2, 3};
  int *a_ptr = a.data();
  int *b_ptr = b.data();

  ASSERT_NE(a_ptr, nullptr);
  EXPECT_EQ(a_ptr[0], b_ptr[0]);
  EXPECT_EQ(a_ptr[1], b_ptr[1]);
  EXPECT_EQ(a_ptr[2], b_ptr[2]);

  a_ptr[1] = 25;
  b_ptr[1] = 25;
  EXPECT_EQ(a[1], b[1]);
}

TEST(test_iterators_array, test_1) {
  s21::S21Array<int, 3> a = {1, 2, 3};
  std::array<int, 3> b = {1, 2, 3};

  EXPECT_EQ(*a.begin(), *b.begin());
  *a.begin() = 10;
  *b.begin() = 10;
  EXPECT_EQ(a[0], b[0]);
}

TEST(test_iterators_array, test_2) {
  s21::S21Array<int, 3> a = {1, 2, 3};
  std::array<int, 3> b = {1, 2, 3};

  EXPECT_EQ(*(a.end() - 1), *(b.end() - 1));
  *(a.end() - 1) = 10;
  *(b.end() - 1) = 10;
  EXPECT_EQ(*(a.end() - 1), *(b.end() - 1));
}

TEST(test_capacity_array, test_1) {
  s21::S21Array<int, 0> a;
  std::array<int, 0> b;

  EXPECT_EQ(a.empty(), b.empty());
}

TEST(test_capacity_array, test_2) {
  s21::S21Array<int, 0> a;
  std::array<int, 0> b;

  EXPECT_EQ(a.size(), b.size());
}

TEST(test_capacity_array, test_3) {
  s21::S21Array<int, 3> a = {1, 2, 3};
  std::array<int, 3> b = {1, 2, 3};

  EXPECT_EQ(a.size(), b.size());
}

TEST(test_capacity_array, test_4) {
  s21::S21Array<int, 3> a = {1, 2, 3};
  std::array<int, 3> b = {1, 2, 3};

  EXPECT_EQ(a.max_size(), b.max_size());
}

TEST(test_modifiers_array, test_1) {
  s21::S21Array<int, 3> a = {1, 2, 3};
  s21::S21Array<int, 3> c = {5, 6, 7};
  a.swap(c);

  std::array<int, 3> b = {1, 2, 3};
  std::array<int, 3> d = {5, 6, 7};
  b.swap(d);

  EXPECT_EQ(a.size(), b.size());
  EXPECT_EQ(a[0], b[0]);
  EXPECT_EQ(a[1], b[1]);
  EXPECT_EQ(a[2], b[2]);

  EXPECT_EQ(c.size(), d.size());
  EXPECT_EQ(c[0], d[0]);
  EXPECT_EQ(c[1], d[1]);
  EXPECT_EQ(c[2], d[2]);
}

TEST(test_modifiers_array, test_2) {
  s21::S21Array<int, 3> a = {1, 2, 3};
  a.fill(1000);

  std::array<int, 3> b = {1, 2, 3};
  b.fill(1000);

  EXPECT_EQ(a.size(), b.size());
  EXPECT_EQ(a[0], b[0]);
  EXPECT_EQ(a[1], b[1]);
  EXPECT_EQ(a[2], b[2]);
}

// set
TEST(setTest, Default) {
  s21::set<int> s;
  EXPECT_TRUE(s.empty());
  EXPECT_EQ(s.size(), 0);
}

TEST(setTest, InitializerList) {
  s21::set<int> s = {1, 2, 3};
  EXPECT_EQ(s.size(), 3);
  EXPECT_TRUE(s.contains(1));
  EXPECT_TRUE(s.contains(2));
  EXPECT_TRUE(s.contains(3));
}

TEST(setTest, Copy) {
  s21::set<int> s1 = {1, 2, 3};
  s21::set<int> s2(s1);
  EXPECT_EQ(s1.size(), s2.size());
}

TEST(setTest, Move) {
  s21::set<int> s1 = {1, 2, 3};
  s21::set<int> s2(std::move(s1));
  EXPECT_EQ(s2.size(), 3);
  EXPECT_TRUE(s2.contains(1));
  EXPECT_TRUE(s2.contains(2));
  EXPECT_TRUE(s2.contains(3));
}
TEST(setTest, BeginEnd) {
  s21::set<int> s{3, 5, 1, 4, 2};
  auto it = s.begin();
  ASSERT_EQ(*it, 1);

  it = s.end();
  ASSERT_EQ(it, nullptr);

  s.clear();
  it = s.begin();
  ASSERT_EQ(it, nullptr);
}

TEST(setTest, Erase) {
  s21::set<int> s{1, 2, 3, 4, 5};
  auto it = s.find(3);
  s.erase(it);
  EXPECT_EQ(s.size(), 4);
  EXPECT_FALSE(s.contains(3));
}

TEST(setTest, Swap) {
  s21::set<int> s1{1, 2, 3};
  s21::set<int> s2{4, 5, 6};
  s1.swap(s2);
  EXPECT_EQ(s1.size(), 3);
  EXPECT_EQ(s2.size(), 3);
  EXPECT_TRUE(s2.contains(1));
  EXPECT_TRUE(s1.contains(4));
}

TEST(setTest, Merge) {
  s21::set<int> s1{1, 2, 3};
  s21::set<int> s2{3, 4, 5};
  s1.merge(s2);
  EXPECT_EQ(s1.size(), 5);
  EXPECT_EQ(s2.size(), 0);
  EXPECT_TRUE(s1.contains(4));
  EXPECT_FALSE(s2.contains(3));
}

TEST(setTest, Find) {
  s21::set<int> s{1, 2, 3};
  auto it1 = s.find(2);
  EXPECT_EQ(*it1, 2);
  auto it2 = s.find(4);
  EXPECT_EQ(it2, s.end());
}

TEST(setTest, Remove) {
  s21::AVLTree<int, int> tree;
  tree.Insert(5);
  tree.Insert(3);
  tree.Insert(7);
  tree.Insert(2);
  tree.Insert(4);
  tree.Insert(6);
  tree.Insert(8);

  tree.Remove(6);
  tree.Remove(8);
}

TEST(AVLTreeTest, RemoveTest) {
  s21::AVLTree<int, int> tree;
  tree.Insert(10);
  tree.Insert(20);
  tree.Insert(30);
  tree.Insert(40);
  tree.Insert(50);

  tree.Remove(50);
}

// map
TEST(mapTest, Default) {
  s21::map<int, std::string> m;
  EXPECT_EQ(m.size(), 0);
  EXPECT_TRUE(m.empty());
}

TEST(mapTest, InitializerList) {
  s21::map<int, std::string> m{{1, "one"}, {2, "two"}, {3, "three"}};
  EXPECT_EQ(m.size(), 3);
  EXPECT_FALSE(m.empty());
  EXPECT_EQ(m.at(1), "one");
  EXPECT_EQ(m.at(2), "two");
  EXPECT_EQ(m.at(3), "three");
}

TEST(mapTest, Copy) {
  s21::map<int, std::string> m{{1, "one"}, {2, "two"}, {3, "three"}};
  s21::map<int, std::string> copy_m(m);
  EXPECT_EQ(copy_m.size(), 3);
  EXPECT_FALSE(copy_m.empty());
  EXPECT_EQ(copy_m.at(1), "one");
}

TEST(mapTest, InsertKeyValue) {
  s21::map<int, std::string> map;
  map.insert(1, "one");
  EXPECT_EQ(map.size(), 1);

  EXPECT_EQ(map.contains(1), true);
  EXPECT_EQ(map[1], "one");

  map.insert(2, "two");
  EXPECT_EQ(map.size(), 2);
  EXPECT_EQ(map.contains(1), true);
  EXPECT_EQ(map[1], "one");
  EXPECT_EQ(map.contains(2), true);
  EXPECT_EQ(map[2], "two");
}

TEST(mapTest, Insert) {
  s21::map<int, std::string> map;
  map.insert(3, "three");
  map.insert(1, "one");
  map.insert(2, "two");

  EXPECT_EQ(map.size(), 3);
  EXPECT_EQ(map.contains(1), true);
  EXPECT_EQ(map.contains(2), true);
}

TEST(mapTest, InsertPair) {
  s21::map<int, std::string> map;
  map.insert(std::make_pair(1, "one"));
  EXPECT_EQ(map.size(), 1);
  EXPECT_EQ(map.contains(1), true);
  EXPECT_EQ(map[1], "one");

  map.insert(std::make_pair(2, "two"));
  EXPECT_EQ(map.size(), 2);
  EXPECT_EQ(map.contains(1), true);
  EXPECT_EQ(map[1], "one");
  EXPECT_EQ(map.contains(2), true);
  EXPECT_EQ(map[2], "two");
}
TEST(mapTest, InsertOrAssign) {
  s21::map<int, std::string> map;
  auto [it1, inserted1] = map.insert_or_assign(1, "one");
  EXPECT_TRUE(inserted1);
  EXPECT_EQ(it1->first, 1);
  EXPECT_EQ(it1->second, "one");

  auto [it2, inserted2] = map.insert_or_assign(1, "ONE");
  EXPECT_FALSE(inserted2);
  EXPECT_EQ(it2->first, 1);
  EXPECT_EQ(it2->second, "ONE");

  map.insert_or_assign(2, "two");
  map.insert_or_assign(3, "three");
  map.insert_or_assign(4, "four");
  map.insert_or_assign(5, "five");
  EXPECT_EQ(map.size(), 5);
  EXPECT_EQ(map[1], "ONE");
  EXPECT_EQ(map[2], "two");
  EXPECT_EQ(map[3], "three");
  EXPECT_EQ(map[4], "four");
  EXPECT_EQ(map[5], "five");
}
TEST(mapTest, AtAndOperatorBrackets) {
  s21::map<int, std::string> map = {{1, "one"}, {2, "two"}, {3, "three"}};

  EXPECT_EQ(map.at(1), "one");
  EXPECT_EQ(map[2], "two");
  EXPECT_THROW(map.at(4), std::invalid_argument);
  map[4] = "four";
  EXPECT_EQ(map[4], "four");
  map[2] = "TWO";
  EXPECT_EQ(map[2], "TWO");
}

TEST(mapTest, EmptyAndSize) {
  s21::map<int, std::string> empty_map;
  s21::map<int, std::string> map = {{1, "one"}, {2, "two"}, {3, "three"}};

  EXPECT_TRUE(empty_map.empty());
  EXPECT_EQ(empty_map.size(), 0);

  EXPECT_FALSE(map.empty());
  EXPECT_EQ(map.size(), 3);
}

TEST(mapTest, Erase) {
  s21::map<int, std::string> map;

  map.insert({1, "one"});
  map.insert({2, "two"});
  map.insert({3, "three"});
  map.insert({5, "five"});

  auto it1 = map.begin()++;
  map.erase(it1);
  EXPECT_EQ(map.size(), 3);
  EXPECT_FALSE(map.contains(1));
}

TEST(mapTest, Swap) {
  s21::map<int, std::string> map1;
  map1.insert({1, "one"});
  map1.insert({2, "two"});

  s21::map<int, std::string> map2;
  map2.insert({3, "three"});
  map2.insert({4, "four"});

  map1.swap(map2);

  EXPECT_EQ(map1.size(), 2);
  EXPECT_TRUE(map1.contains(3));
  EXPECT_TRUE(map1.contains(4));

  EXPECT_EQ(map2.size(), 2);
  EXPECT_TRUE(map2.contains(1));
  EXPECT_TRUE(map2.contains(2));
}

TEST(mapTest, Contains) {
  s21::map<int, std::string> map;

  map.insert({1, "one"});
  map.insert({2, "two"});
  EXPECT_TRUE(map.contains(2));
  EXPECT_FALSE(map.contains(3));
}

// list
template <typename value_type>
bool compare_lists(s21::list<value_type> my_list,
                   std::list<value_type> std_list) {
  bool result = true;
  if (my_list.size() == std_list.size()) {
    auto my_it = my_list.begin();
    auto std_it = std_list.begin();
    for (size_t i = 0; i != my_list.size(); ++i) {
      if (*my_it != *std_it) {
        result = false;
        break;
      }
      my_it++;
      std_it++;
    }
  } else {
    result = false;
  }
  return result;
}

TEST(ListTest, CompareLists) {
  s21::list<int> my_list{1, 2, 3, 4, 5};
  std::list<int> std_list{1, 2, 3, 4, 5};
  EXPECT_TRUE(compare_lists(my_list, std_list));
  std_list.push_back(6);
  EXPECT_FALSE(compare_lists(my_list, std_list));
  std_list.pop_back();
  my_list.push_front(0);
  std_list.push_front(0);
  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListTest, SizeConstructor) {
  s21::list<int> my_list(1000);
  std::list<int> std_list(1000);
  EXPECT_EQ(my_list.size(), std_list.size());
  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListTest, InitializerListConstructor) {
  s21::list<int> my_list{1, 2, 3, 7, 9};
  std::list<int> std_list{1, 2, 3, 7, 9};
  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListTest, CopyConstructor) {
  s21::list<int> my_list{1, 2, 3};
  s21::list<int> my_list_copy(my_list);
  std::list<int> std_list{1, 2, 3};
  std::list<int> std_list_copy(std_list);
  EXPECT_TRUE(compare_lists(my_list_copy, std_list_copy));
}

TEST(ListTest, MoveConstructor) {
  s21::list<int> my_list{1, 2, 3};
  s21::list<int> my_list_copy(my_list);
  s21::list<int> my_list_move(std::move(my_list));
  std::list<int> std_list{1, 2, 3};
  std::list<int> std_list_copy(std_list);
  std::list<int> std_list_move(std::move(std_list));
  EXPECT_TRUE(compare_lists(my_list_copy, std_list_copy));
}

TEST(ListTest, MoveAssignmentOperator) {
  s21::list<int> my_list{1, 2, 3};
  s21::list<int> my_list_copy(my_list);
  s21::list<int> my_list_move = std::move(my_list);
  std::list<int> std_list{1, 2, 3};
  std::list<int> std_list_copy(std_list);
  std::list<int> std_list_move = std::move(std_list);
  EXPECT_TRUE(compare_lists(my_list_move, std_list_move));
}

TEST(ListTest, Front) {
  s21::list<int> my_list{99, 2, 3, 4, 5};
  std::list<int> std_list{99, 2, 3, 4, 5};
  EXPECT_EQ(my_list.front(), std_list.front());
}

TEST(ListTest, Back) {
  s21::list<int> my_list{1, 2, 3, 4, 99};
  std::list<int> std_list{1, 2, 3, 4, 99};
  EXPECT_EQ(my_list.back(), std_list.back());
}

TEST(ListTest, Empty) {
  s21::list<int> my_list;
  std::list<int> std_list;
  EXPECT_EQ(my_list.empty(), std_list.empty());
  my_list.push_back(10);
  std_list.push_back(10);
  EXPECT_EQ(my_list.empty(), std_list.empty());
}

TEST(ListTest, Size) {
  s21::list<int> my_list{1, 2, 3, 4, 5, 6, 7, 8};
  std::list<int> std_list{1, 2, 3, 4, 5, 6, 7, 8};
  EXPECT_EQ(my_list.size(), std_list.size());
}

TEST(ListTest, SizeEmpty) {
  s21::list<int> my_list;
  std::list<int> std_list;
  EXPECT_EQ(my_list.size(), std_list.size());
}

TEST(ListTest, PushBack) {
  s21::list<int> my_list{1, 2, 3, 4, 5};
  my_list.push_back(6);
  std::list<int> std_list{1, 2, 3, 4, 5};
  std_list.push_back(6);
  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListTest, PopBack) {
  s21::list<int> my_list{1, 2, 3, 4, 5};
  my_list.pop_back();
  std::list<int> std_list{1, 2, 3, 4, 5};
  std_list.pop_back();
  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListTest, PushFront) {
  s21::list<int> my_list{1, 2, 3, 4, 5};
  my_list.push_front(0);
  std::list<int> std_list{1, 2, 3, 4, 5};
  std_list.push_front(0);
  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListTest, PopFront) {
  s21::list<int> my_list{1, 2, 3, 4, 5};
  my_list.pop_front();
  std::list<int> std_list{1, 2, 3, 4, 5};
  std_list.pop_front();
  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListTest, Swap) {
  s21::list<int> my_list1{1, 2, 3, 4, 5};
  s21::list<int> my_list2{6, 7, 8, 9, 10, 11};
  my_list1.swap(my_list2);

  std::list<int> std_list1{1, 2, 3, 4, 5};
  std::list<int> std_list2{6, 7, 8, 9, 10, 11};
  std_list1.swap(std_list2);

  EXPECT_TRUE(compare_lists(my_list1, std_list1));
  EXPECT_TRUE(compare_lists(my_list2, std_list2));
}

TEST(ListTest, begin_1) {
  s21::list<int> my_list1{500, 15000, 30000};

  std::list<int> std_list2{500, 15000, 30000};
  EXPECT_EQ(*my_list1.begin(), *std_list2.begin());
}

TEST(ListTest, begin_2) {
  s21::list<int> my_list1(4);

  std::list<int> std_list2(4);
  EXPECT_EQ(*my_list1.begin(), *std_list2.begin());
}

TEST(ListTest, end_1) {
  s21::list<int> my_list1{500, 15000, 30000};

  std::list<int> std_list2{500, 15000, 30000};
  EXPECT_EQ(*my_list1.begin(), *std_list2.begin());
}

TEST(ListTest, Merge_1) {
  s21::list<int> my_list1{1, 9999, 20000};
  s21::list<int> my_list2{500, 15000, 30000};
  my_list1.merge(my_list2);

  std::list<int> std_list1{1, 9999, 20000};
  std::list<int> std_list2{500, 15000, 30000};
  std_list1.merge(std_list2);
  EXPECT_TRUE(compare_lists(my_list1, std_list1));
}

TEST(ListTest, Merge_2) {
  s21::list<int> my_list1{1, 9999, 20000};
  s21::list<int> my_list2{15000, 30000};
  my_list1.merge(my_list2);

  std::list<int> std_list1{1, 9999, 20000};
  std::list<int> std_list2{15000, 30000};
  std_list1.merge(std_list2);
  EXPECT_TRUE(compare_lists(my_list1, std_list1));
}

TEST(ListTest, Reverse_1) {
  s21::list<int> my_list{1, 2, 3, 4, 5};
  std::list<int> std_list{1, 2, 3, 4, 5};
  my_list.reverse();
  std_list.reverse();
  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListTest, Reverse_2) {
  s21::list<int> my_list(4);
  std::list<int> std_list(4);
  my_list.reverse();
  std_list.reverse();
  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListTest, Unique_1) {
  s21::list<int> my_list{90, 10, 3, 40, 30, 20, 10, 10, 90, 90, 90};
  std::list<int> std_list{90, 10, 3, 40, 30, 20, 10, 10, 90, 90, 90};
  my_list.unique();
  std_list.unique();
  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListTest, Unique_2) {
  s21::list<int> my_list(3);
  std::list<int> std_list(3);
  my_list.unique();
  std_list.unique();
  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListTest, Splice_1) {
  s21::list<int> my_list1{1, 9999, 20000};
  s21::list<int> my_list2{500, 15000, 30000};
  my_list1.splice(my_list1.begin(), my_list2);

  std::list<int> std_list1{1, 9999, 20000};
  std::list<int> std_list2{500, 15000, 30000};
  std_list1.splice(std_list1.begin(), std_list2);
  EXPECT_TRUE(compare_lists(my_list1, std_list1));
}

TEST(ListTest, Splice_2) {
  s21::list<int> my_list1;
  s21::list<int> my_list2{500, 15000, 30000};
  my_list1.splice(my_list1.begin(), my_list2);

  std::list<int> std_list1;
  std::list<int> std_list2{500, 15000, 30000};
  std_list1.splice(std_list1.begin(), std_list2);
  EXPECT_TRUE(compare_lists(my_list1, std_list1));
}

TEST(ListTest, Insert_1) {
  s21::list<int> my_list1{1, 9999, 20000};
  my_list1.insert(my_list1.begin(), 5);

  std::list<int> std_list1{1, 9999, 20000};
  std_list1.insert(std_list1.begin(), 5);

  EXPECT_TRUE(compare_lists(my_list1, std_list1));
}

TEST(ListTest, Insert_2) {
  s21::list<int> my_list1{1, 9999, 20000};
  my_list1.insert(my_list1.end(), 5);

  std::list<int> std_list1{1, 9999, 20000};
  std_list1.insert(std_list1.end(), 5);

  EXPECT_TRUE(compare_lists(my_list1, std_list1));
}

TEST(ListTest, Insert_3) {
  s21::list<int> my_list1;
  my_list1.insert(my_list1.begin(), 5);

  std::list<int> std_list1;
  std_list1.insert(std_list1.begin(), 5);

  EXPECT_TRUE(compare_lists(my_list1, std_list1));
}

TEST(ListTest, Insert_5) {
  s21::list<int> my_list1(4);
  my_list1.insert(my_list1.begin(), 5);

  std::list<int> std_list1(4);
  std_list1.insert(std_list1.begin(), 5);

  EXPECT_TRUE(compare_lists(my_list1, std_list1));
}

TEST(ListTest, Insert_6) {
  s21::list<int> my_list1(4);
  my_list1.insert(my_list1.end(), 5);

  std::list<int> std_list1(4);
  std_list1.insert(std_list1.end(), 5);

  EXPECT_TRUE(compare_lists(my_list1, std_list1));
}

TEST(ListTest, Erase_1) {
  s21::list<int> my_list1{1, 9999, 20000};
  my_list1.erase(my_list1.begin());

  std::list<int> std_list1{1, 9999, 20000};
  std_list1.erase(std_list1.begin());

  EXPECT_TRUE(compare_lists(my_list1, std_list1));
}

// queue
TEST(test_container, queue_test_1) {
  s21::queue<int> s21_queue;
  std::queue<int> orig_queue;

  s21_queue.push(12);
  s21_queue.push(143);
  s21_queue.push(56);
  s21_queue.push(45);
  s21_queue.push(742);

  orig_queue.push(12);
  orig_queue.push(143);
  orig_queue.push(56);
  orig_queue.push(45);
  orig_queue.push(742);

  ASSERT_TRUE(s21_queue.front() == 12);
  ASSERT_TRUE(s21_queue.back() == 742);

  ASSERT_TRUE(s21_queue.front() == orig_queue.front());
  ASSERT_TRUE(s21_queue.back() == orig_queue.back());
  s21_queue.pop();
  orig_queue.pop();

  ASSERT_TRUE(s21_queue.front() == orig_queue.front());
  ASSERT_TRUE(s21_queue.back() == orig_queue.back());
  s21_queue.pop();
  orig_queue.pop();

  ASSERT_TRUE(s21_queue.front() == orig_queue.front());
  ASSERT_TRUE(s21_queue.back() == orig_queue.back());
  s21_queue.pop();
  orig_queue.pop();

  ASSERT_TRUE(s21_queue.front() == orig_queue.front());
  ASSERT_TRUE(s21_queue.back() == orig_queue.back());
  s21_queue.pop();
  orig_queue.pop();
}

TEST(test_container, queue_test_2) {
  s21::queue<int> s21_queue({12, 44, 23, 56, 13, 5});
  std::queue<int> orig_queue({12, 44, 23, 56, 13, 5});

  ASSERT_TRUE(s21_queue.size() == orig_queue.size());
  ASSERT_TRUE(s21_queue.empty() == orig_queue.empty());

  ASSERT_TRUE(s21_queue.front() == orig_queue.front());
  ASSERT_TRUE(s21_queue.front() == 12);
  s21_queue.pop();
  orig_queue.pop();

  ASSERT_TRUE(s21_queue.front() == orig_queue.front());
  ASSERT_TRUE(s21_queue.front() == 44);
  s21_queue.pop();
  orig_queue.pop();

  ASSERT_TRUE(s21_queue.front() == orig_queue.front());
  ASSERT_TRUE(s21_queue.front() == 23);
  s21_queue.pop();
  orig_queue.pop();

  ASSERT_TRUE(s21_queue.front() == orig_queue.front());
  ASSERT_TRUE(s21_queue.front() == 56);
  s21_queue.pop();
  orig_queue.pop();
}

TEST(test_container, queue_test_swap) {
  s21::queue<int> s21_queue({12, 44, 23, 56, 13, 5});
  std::queue<int> orig_queue({12, 44, 23, 56, 13, 5});

  s21::queue<int> s21_queue2;
  std::queue<int> orig_queue2;

  s21_queue2.push(3);
  s21_queue2.push(34);

  orig_queue2.push(3);
  orig_queue2.push(34);

  s21_queue.swap(s21_queue2);
  orig_queue.swap(orig_queue2);

  ASSERT_TRUE(s21_queue.size() == 2);
  ASSERT_TRUE(s21_queue.size() == orig_queue.size());

  ASSERT_TRUE(s21_queue.front() == orig_queue.front());
  ASSERT_TRUE(s21_queue.back() == orig_queue.back());
  ASSERT_TRUE(s21_queue2.size() == orig_queue2.size());

  ASSERT_TRUE(s21_queue2.front() == orig_queue2.front());
  ASSERT_TRUE(s21_queue2.back() == orig_queue2.back());
  ASSERT_TRUE(s21_queue2.size() == 6);
}

TEST(test_container, queue_test_copy) {
  s21::queue<int> s21_queue;
  std::queue<int> orig_queue;

  s21_queue.push(144);
  s21_queue.push(12);
  s21_queue.push(75);
  s21_queue.push(13);
  s21_queue.push(532);
  s21_queue.push(1345);
  s21_queue.push(99);

  orig_queue.push(144);
  orig_queue.push(12);
  orig_queue.push(75);
  orig_queue.push(13);
  orig_queue.push(532);
  orig_queue.push(1345);
  orig_queue.push(99);

  s21::queue<int> s21_queue1 = s21_queue;
  s21::queue<int> s21_queue2(s21_queue);

  ASSERT_TRUE(s21_queue1.front() == orig_queue.front());
  ASSERT_TRUE(s21_queue2.front() == orig_queue.front());
  ASSERT_TRUE(s21_queue1.back() == orig_queue.back());
  ASSERT_TRUE(s21_queue2.back() == orig_queue.back());
  ASSERT_TRUE(s21_queue1.empty() == orig_queue.empty());
  ASSERT_TRUE(s21_queue1.size() == orig_queue.size());
  ASSERT_TRUE(s21_queue2.size() == s21_queue1.size());
  ASSERT_TRUE(s21_queue2.empty() == orig_queue.empty());

  orig_queue.pop();
  s21_queue1.pop();
  s21_queue2.pop();

  ASSERT_TRUE(s21_queue1.front() == orig_queue.front());
  ASSERT_TRUE(s21_queue2.front() == orig_queue.front());
  ASSERT_TRUE(s21_queue1.back() == orig_queue.back());
  ASSERT_TRUE(s21_queue2.back() == orig_queue.back());
  ASSERT_TRUE(s21_queue1.empty() == orig_queue.empty());
  ASSERT_TRUE(s21_queue1.size() == orig_queue.size());
  ASSERT_TRUE(s21_queue2.size() == s21_queue1.size());
  ASSERT_TRUE(s21_queue2.empty() == orig_queue.empty());

  orig_queue.pop();
  s21_queue1.pop();
  s21_queue2.pop();

  ASSERT_TRUE(s21_queue1.front() == orig_queue.front());
  ASSERT_TRUE(s21_queue2.front() == orig_queue.front());
  ASSERT_TRUE(s21_queue1.back() == orig_queue.back());
  ASSERT_TRUE(s21_queue2.back() == orig_queue.back());
  ASSERT_TRUE(s21_queue1.empty() == orig_queue.empty());
  ASSERT_TRUE(s21_queue1.size() == orig_queue.size());
  ASSERT_TRUE(s21_queue2.size() == s21_queue1.size());
  ASSERT_TRUE(s21_queue2.empty() == orig_queue.empty());
}

TEST(test_container, queue_test_move) {
  s21::queue<int> s21_queue(
      {12, 44, 23, 56, 13, 5, 3, 3, 2, 1, 67, 4, 1487, 22211});
  std::queue<int> orig_queue(
      {12, 44, 23, 56, 13, 5, 3, 3, 2, 1, 67, 4, 1487, 22211});

  s21::queue<int> s21_queue2 = std::move(s21_queue);
  std::queue<int> orig_queue2 = std::move(orig_queue);

  ASSERT_TRUE(s21_queue.size() == orig_queue.size());
  ASSERT_TRUE(s21_queue.size() == 0);

  ASSERT_TRUE(s21_queue2.front() == orig_queue2.front());
  ASSERT_TRUE(s21_queue2.back() == orig_queue2.back());
  ASSERT_TRUE(s21_queue2.size() == orig_queue2.size());
  ASSERT_TRUE(s21_queue2.size() == 14);

  ASSERT_TRUE(s21_queue.empty() == orig_queue.empty());
}

TEST(test_container, insert_many_back) {
  s21::queue<int> s21_queue;
  int arr[] = {144, 12, 75, 13, 532, 1345, 99, 12, 4, 5, 6, 1};

  s21_queue.push(144);
  s21_queue.push(12);
  s21_queue.push(75);
  s21_queue.push(13);
  s21_queue.push(532);
  s21_queue.push(1345);
  s21_queue.push(99);
  s21_queue.insert_many_back(12, 4, 5, 6, 1);
  int i = 0;
  while (!s21_queue.empty()) {
    ASSERT_TRUE(s21_queue.front() == arr[i]);
    i++;
    s21_queue.pop();
  }
}

// stack
TEST(StackTest, test1) {
  s21::stack<int> stack;
  std::stack<int> stack_orig;
  stack.push(10);
  stack.push(11);
  stack.push(12);
  stack_orig.push(10);
  stack_orig.push(11);
  stack_orig.push(12);
  ASSERT_EQ(stack.top(), stack_orig.top());
}

TEST(StackTest, test2) {
  s21::stack<int> stack;
  std::stack<int> stack_orig;
  stack.push(10);
  stack.push(11);
  stack_orig.push(10);
  stack_orig.push(11);

  stack.pop();
  stack_orig.pop();
  ASSERT_EQ(stack.top(), stack_orig.top());
}

TEST(StackTest, test3) {
  s21::stack<int> stack;
  std::stack<int> stack_orig;
  stack.push(10);
  stack.push(11);
  stack_orig.push(10);
  stack_orig.push(11);

  ASSERT_EQ(stack.empty(), stack_orig.empty());
  ASSERT_EQ(stack.size(), stack_orig.size());
}

// vector
TEST(VectorTest, test1) {
  s21::vector<int> vec;

  vec.assign(5, 10);
  ASSERT_EQ(vec.at(0), 10);
  vec.push_back(11);
  ASSERT_EQ(vec.at(5), 11);
}

TEST(VectorTest, test2) {
  s21::vector<int> vec1 = {1, 2, 3, 4, 5};
  s21::vector<int> vec2 = {6, 7, 8, 9, 10};
  vec1.swap(vec2);
  ASSERT_EQ(vec1.at(0), 6);
}

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
