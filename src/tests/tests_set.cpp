#include <gtest/gtest.h>

#include <set>
#include <string>

#include "../s21_containers.hpp"
#include "tests.hpp"

TEST(SetConstructorTest, test_1) {
  s21::Set<int, int> s21_set;
  std::set<int> std_set;
  EXPECT_EQ(s21_set.size(), std_set.size());
  EXPECT_TRUE(s21_set.empty());
}

TEST(SetConstructorTest, test_2) {
  s21::Set<char> s21_set = {'a', 'b', 'c', '/'};
  std::set<char> std_set = {'a', 'b', 'c', '/'};

  EXPECT_EQ(s21_set.size(), std_set.size());
  auto it_std = std_set.begin();
  for (auto it = std_set.begin(); it != std_set.end(); ++it) {
    EXPECT_EQ(*it, *it_std);
    ++it_std;
  }
}

TEST(set, empty) {
  s21::Set<char> s21_set = {'a', 'b', 'c', '/'};
  EXPECT_FALSE(s21_set.empty());

  s21_set.clear();
  EXPECT_TRUE(s21_set.empty());
}

TEST(set, max_size) {
  s21::Set<char> s21_set = {'a', 'b', 'c', '/'};
  EXPECT_EQ(s21_set.max_size(), static_cast<size_t>(230584300921369395));
}

TEST(set, insert) {
  s21::Set<char> s21_set = {'a', 'b', 'c', '/'};
  s21_set.insert('d');

  std::set<char> std_set = {'a', 'b', 'c', '/'};
  std_set.insert('d');

  EXPECT_EQ(s21_set.size(), std_set.size());
  auto it_std = std_set.begin();
  for (auto it = std_set.begin(); it != std_set.end(); ++it) {
    EXPECT_EQ(*it, *it_std);
    ++it_std;
  }
}

TEST(set, erase) {
  s21::Set<char> s21_set = {'a', 'b', 'c', '/'};
  s21_set.erase(s21_set.begin());
  EXPECT_EQ(s21_set.size(), static_cast<size_t>(3));
}

TEST(set, clear) {
  s21::Set<char> s21_set = {'a', 'b', 'c', '/'};
  s21_set.clear();
  EXPECT_EQ(s21_set.size(), static_cast<size_t>(0));
}

TEST(set, swap) {
  s21::Set<char> s21_set = {'a', 'b'};
  s21::Set<char> s21_set2 = {'b', 'c', '/'};
  s21_set.swap(s21_set2);
  EXPECT_EQ(s21_set.size(), static_cast<size_t>(3));
}

TEST(set, merge) {
  s21::Set<char> s21_set = {'a', 'b', 'c', '/'};
  s21::Set<char> s21_set2 = {'d', 'e', 'f'};
  s21_set.merge(s21_set2);
  std::cout << s21_set.size() << std::endl;
  EXPECT_EQ(s21_set.size(), static_cast<size_t>(7));
}

TEST(set, find) {
  s21::Set<char> s21_set = {'a', 'b', 'c', 'a'};
  auto it = s21_set.find('a');
  EXPECT_EQ(*it, 'a');
}

TEST(set, contains) {
  s21::Set<char> s21_set = {'a', 'b', 'c', '/'};
  EXPECT_TRUE(s21_set.contains('a'));
  EXPECT_FALSE(s21_set.contains('d'));
}

TEST(set, insert_many) {
  s21::Set<char> s21_set = {'a', 'b', 'c', '/'};
  s21_set.insert_many('d', 'e', 'f');
  EXPECT_EQ(s21_set.size(), static_cast<size_t>(7));
}