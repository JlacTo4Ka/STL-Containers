#include <gtest/gtest.h>

#include "tests.hpp"

TEST(map, init_list) {
  s21::map<int, int> res = {{1, 1}, {2, 2}, {3, 3}};
  EXPECT_EQ(static_cast<size_t>(3), res.size());
}

TEST(map, empty) {
  s21::map<int, int> res;
  EXPECT_EQ(res.empty(), true);
  res.insert({1, 1});
  EXPECT_EQ(res.empty(), false);
}

TEST(map, size) {
  s21::map<int, int> res;
  EXPECT_EQ(static_cast<size_t>(0), res.size());
  res.insert({1, 1});
  EXPECT_EQ(static_cast<size_t>(1), res.size());
}

TEST(map, max_size) {
  s21::map<int, int> res;
  EXPECT_EQ(static_cast<size_t>(230584300921369395), res.max_size());
}

TEST(map, clear) {
  s21::map<int, int> res;
  res.insert({1, 1});
  res.clear();
  EXPECT_EQ(static_cast<size_t>(0), res.size());
}

TEST(map, insert) {
  s21::map<int, int> res;
  res.insert({1, 1});
  res.insert({2, 2});
  res.insert({3, 3});
  EXPECT_EQ(static_cast<size_t>(3), res.size());
}

TEST(map, insert_or_assign) {
  s21::map<int, int> res;
  res.insert_or_assign(1, 1);
  res.insert_or_assign(2, 2);
  res.insert_or_assign(3, 3);
  res.insert_or_assign(1, 4);
  EXPECT_EQ(static_cast<size_t>(3), res.size());
  EXPECT_EQ(4, res.at(1));
}

TEST(map, erase) {
  s21::map<int, int> res;
  res.insert({1, 1});
  res.insert({2, 2});
  res.insert({3, 3});
  res.erase(res.begin()++);
  EXPECT_EQ(static_cast<size_t>(2), res.size());
}

TEST(map, swap) {
  s21::map<int, int> res;
  res.insert({1, 1});
  s21::map<int, int> res1;
  res1.insert({2, 2});
  res1.insert({3, 3});
  res.swap(res1);
  EXPECT_EQ(static_cast<size_t>(2), res.size());
  EXPECT_EQ(static_cast<size_t>(1), res1.size());
  EXPECT_EQ(2, res.at(2));
  EXPECT_EQ(1, res1.at(1));
}

TEST(map, merge) {
  s21::map<int, int> res;
  res.insert({1, 1});
  s21::map<int, int> res1;
  res1.insert({2, 2});
  res1.insert({3, 3});
  res.merge(res1);
  EXPECT_EQ(static_cast<size_t>(3), res.size());
  EXPECT_EQ(3, res.at(3));
}

TEST(map, contains) {
  s21::map<int, int> res;
  res.insert({1, 1});
  EXPECT_EQ(res.contains(1), true);
  EXPECT_EQ(res.contains(2), false);
}

TEST(map, insert_many) {
  s21::map<int, int> res;
  res.insert_many(std::pair<int, int>(1, 1), std::pair<int, int>(2, 2),
                  std::pair<int, int>(3, 3), std::pair<int, int>(4, 4));
  EXPECT_EQ(static_cast<size_t>(4), res.size());
  EXPECT_EQ(1, res.at(1));
  EXPECT_EQ(2, res.at(2));
  EXPECT_EQ(3, res.at(3));
  EXPECT_EQ(4, res.at(4));
}