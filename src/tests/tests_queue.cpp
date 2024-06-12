#include <gtest/gtest.h>

#include <queue>

#include "tests.hpp"

TEST(queue, size1) {
  s21::queue<int> res;
  res.push(2);
  res.push(3);
  EXPECT_EQ(res.size(), static_cast<size_t>(2));
}

TEST(queue, emtyTrue) {
  s21::queue<int> res;
  EXPECT_EQ(res.empty(), true);
}
TEST(queue, emtyFalse) {
  s21::queue<int> res;
  res.push(3);
  EXPECT_EQ(res.empty(), false);
}

TEST(queue, clear) {
  s21::queue<int> res;
  res.push(3);
  res.push(1);
  res.push(1);
  while (res.size() != 0) {
    res.pop();
  }
  EXPECT_EQ(res.empty(), true);
}

TEST(queue, size_in_class1) {
  s21::queue<int> res;
  res.push(3);
  res.push(2);
  res.push(1);
  EXPECT_EQ(res.size(), static_cast<size_t>(3));
}

TEST(queue, copy) {
  s21::queue<int> res;

  res.push(3);
  res.push(2);
  res.push(1);

  s21::queue<int> res1(res);
  while (!res1.empty()) {
    int a = res.front();
    int b = res1.front();
    EXPECT_EQ(a, b);
    res.pop();
    res1.pop();
  }
}

TEST(queue, copy_constructor) {
  s21::queue<int> res;

  res.push(3);
  res.push(2);
  res.push(1);

  s21::queue<int> res1(res);
  while (!res1.empty()) {
    int a = res.front();
    int b = res1.front();
    EXPECT_EQ(a, b);
    res.pop();
    res1.pop();
  }
}

TEST(queue, move) {
  s21::queue<int> res;

  res.push(3);
  res.push(2);
  res.push(1);
  s21::queue<int> res1(std::move(res));
  int a = 3;
  int b = 0;
  while (!res1.empty()) {
    b = res1.front();
    EXPECT_EQ(a, b);
    res1.pop();
    a--;
  }
}

TEST(queue, move_operator) {
  s21::queue<int> res;

  res.push(3);
  res.push(2);
  res.push(1);
  s21::queue<int> res1;
  res1 = std::move(res);
  EXPECT_EQ(true, res.empty());
}
TEST(queue, move_operator1) {
  s21::queue<int> res;

  res.push(3);
  res.push(2);
  res.push(1);
  s21::queue<int> res1;
  res1 = std::move(res);
  int size_ = res1.size();
  EXPECT_EQ(3, size_);
  EXPECT_EQ(3, res1.front());
  res1.pop();
  EXPECT_EQ(2, res1.front());
  res1.pop();
  EXPECT_EQ(1, res1.front());
  res1.pop();
}

TEST(queue, swap_value) {
  s21::queue<int> res;
  res.push(2);
  res.push(1);

  s21::queue<int> res1;
  res1.push(3);
  res1.push(2);
  res1.push(1);

  res.swap(res1);
  EXPECT_EQ(res.size(), static_cast<size_t>(3));
  EXPECT_EQ(res1.size(), static_cast<size_t>(2));

  int a = 3;
  while (!res.empty()) {
    EXPECT_EQ(a, res.front());
    res.pop();
    a--;
  }
  int b = 2;
  while (!res1.empty()) {
    EXPECT_EQ(b, res1.front());
    res1.pop();
    b--;
  }
}

TEST(queue, swap_size) {
  s21::queue<int> res{2, 1};
  s21::queue<int> res1{3, 2, 1};
  res.swap(res1);
  EXPECT_EQ(res.size(), static_cast<size_t>(3));
  EXPECT_EQ(res1.size(), static_cast<size_t>(2));
}

TEST(queue, init_list) {
  s21::queue<int> res{1, 2, 3};
  EXPECT_EQ(static_cast<size_t>(3), res.size());
}

TEST(queue, def_construcotr_1) {
  s21::queue<int> res;
  EXPECT_EQ(res.empty(), true);
}

TEST(queue, construcotor_1) {
  s21::queue<int> res{1, 2, 3};
  s21::queue<int> res1(res);
  while (!res1.empty()) {
    int a = res.front();
    int b = res1.front();
    EXPECT_EQ(a, b);
    res.pop();
    res1.pop();
  }
}
TEST(queue, InsertManyBack) {
  s21::queue<int> our_queue_int;
  our_queue_int.insert_many_back(1, 2, 3);
  EXPECT_EQ(our_queue_int.front(), 1);
  EXPECT_EQ(our_queue_int.back(), 3);
}

TEST(queue, pop) {
  s21::queue<int> res;
  std::queue<int> res1;
  res.push(1);
  res.push(2);
  res.push(3);
  res.push(4);

  res1.push(1);
  res1.push(2);
  res1.push(3);
  res1.push(4);
  res.pop();
  res1.pop();
  int a = res.front();
  int b = res1.front();
  EXPECT_EQ(a, b);
  EXPECT_EQ(a, 2);
}