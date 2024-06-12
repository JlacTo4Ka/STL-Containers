#include <gtest/gtest.h>

#include "tests.hpp"

TEST(stack, size1) {
  s21::stack<int> res;
  res.push(2);
  res.push(3);
  EXPECT_EQ(res.size(), static_cast<size_t>(2));
}

TEST(stack, size2) {
  s21::stack<int> res;
  EXPECT_EQ(res.size(), static_cast<size_t>(0));
}

TEST(stack, size3) {
  s21::stack<int> res;
  for (int i = 0; i < 10; i++) {
    res.push(i);
  }
  EXPECT_EQ(res.size(), static_cast<size_t>(10));
}

TEST(stack, emtyTrue) {
  s21::stack<int> res;
  EXPECT_EQ(res.empty(), true);
}
TEST(stack, emtyFalse) {
  s21::stack<int> res;
  res.push(3);
  EXPECT_EQ(res.empty(), false);
}

TEST(stack, clear) {
  s21::stack<int> res;
  for (int i = 0; i < 10; i++) {
    res.push(i);
  }
  for (int i = 0; i < 10; i++) {
    res.pop();
  }
  EXPECT_EQ(res.empty(), true);
}

TEST(stack, empty) {
  s21::stack<int> res;
  EXPECT_EQ(res.empty(), true);
  res.push(3);
  EXPECT_EQ(res.empty(), false);
}

TEST(stack, insert_many_front) {
  s21::stack<int> res;
  res.insert_many_front(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
  EXPECT_EQ(res.size(), static_cast<size_t>(10));
}