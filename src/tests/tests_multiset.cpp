#include "tests.hpp"

TEST(s21_multiset, constructor) {
  s21::multiset<int> set;
  EXPECT_EQ(set.size(), static_cast<size_t>(0));
  EXPECT_TRUE(set.empty());
}

TEST(s21_multiset, empty) {
  s21::multiset<int> set;
  EXPECT_TRUE(set.empty());
  set.insert(1);
  EXPECT_FALSE(set.empty());
}

TEST(s21_multiset, size) {
  s21::multiset<int> set;
  EXPECT_EQ(set.size(), static_cast<size_t>(0));
  set.insert(1);
  EXPECT_EQ(set.size(), static_cast<size_t>(1));
  set.insert(2);
  EXPECT_EQ(set.size(), static_cast<size_t>(2));
  set.insert(3);
  EXPECT_EQ(set.size(), static_cast<size_t>(3));
}

TEST(s21_multiset, max_size) {
  s21::multiset<int> set;
  EXPECT_EQ(set.max_size(), static_cast<size_t>(230584300921369395));
}

TEST(s21_multiset, clear) {
  s21::multiset<int> set;
  set.insert(1);
  set.insert(2);
  set.insert(3);
  EXPECT_EQ(set.size(), static_cast<size_t>(3));
  set.clear();
  EXPECT_EQ(set.size(), static_cast<size_t>(0));
  EXPECT_TRUE(set.empty());
}

TEST(s21_multiset, insert) {
  s21::multiset<int> set;
  set.insert(1);
  set.insert(2);
  set.insert(3);
  EXPECT_EQ(set.size(), static_cast<size_t>(3));
}

TEST(s21_multiset, erase) {
  s21::multiset<int> set;
  set.insert(1);
  set.insert(2);
  set.insert(3);
  EXPECT_EQ(set.size(), static_cast<size_t>(3));
  set.erase(set.begin());
  EXPECT_EQ(set.size(), static_cast<size_t>(2));
}

TEST(s21_multiset, swap) {
  s21::multiset<int> set;
  set.insert(1);
  set.insert(2);
  set.insert(3);
  s21::multiset<int> set2;
  set2.insert(4);
  set2.insert(5);
  set.swap(set2);
  EXPECT_EQ(set.size(), static_cast<size_t>(2));
  EXPECT_EQ(set2.size(), static_cast<size_t>(3));
}

TEST(s21_multiset, merge) {
  s21::multiset<int> set;
  set.insert(1);
  set.insert(2);
  set.insert(3);
  s21::multiset<int> set2;
  set2.insert(4);
  set2.insert(5);
  set.merge(set2);
  EXPECT_EQ(set.size(), static_cast<size_t>(5));
}

// TEST(s21_multiset, find) {
//     s21::multiset<int> set;
//     set.insert(1);
//     set.insert(2);
//     set.insert(3);
//     auto it = set.find(2);
//     EXPECT_EQ(*it, 2);
// }

TEST(s21_multiset, count) {
  s21::multiset<int> set;
  set.insert(1);
  set.insert(2);
  set.insert(3);
  EXPECT_EQ(set.count(2), static_cast<size_t>(1));
}

TEST(s21_multiset, contains) {
  s21::multiset<int> set;
  set.insert(1);
  set.insert(2);
  set.insert(3);
  EXPECT_TRUE(set.contains(2));
}

TEST(s21_multiset, equal_range) {
  s21::multiset<int> set;
  set.insert(1);
  set.insert(2);
  set.insert(3);
  auto range = set.equal_range(2);
  EXPECT_EQ(*range.first, 2);
  EXPECT_EQ(*range.second, 3);
}

TEST(s21_multiset, lower_bound) {
  s21::multiset<int> set;
  set.insert(1);
  set.insert(2);
  set.insert(3);
  auto it = set.lower_bound(2);
  EXPECT_EQ(*it, 2);
}

TEST(s21_multiset, upper_bound) {
  s21::multiset<int> set;
  set.insert(1);
  set.insert(2);
  set.insert(3);
  auto it = set.upper_bound(2);
  EXPECT_EQ(*it, 3);
}

TEST(s21_multiset, insert_many) {
  s21::multiset<int> set;
  set.insert_many(1, 2, 3);
  EXPECT_EQ(set.size(), static_cast<size_t>(3));
}
