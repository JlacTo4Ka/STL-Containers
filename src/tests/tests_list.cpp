#include <gtest/gtest.h>

#include <list>
#include <string>

#include "../s21_containers.hpp"
#include "tests.hpp"

TEST(ListConstructorTest, test_1) {
  s21::List<int> s21_list;
  std::list<int> std_list;
  EXPECT_EQ(s21_list.size(), std_list.size());
  EXPECT_TRUE(s21_list.empty());
}

TEST(ListConstructorTest, test_2) {
  s21::List<char> s21_list(5);
  std::list<char> std_list(5);

  EXPECT_EQ(s21_list.size(), std_list.size());
  auto it_std = std_list.begin();
  for (auto it = s21_list.begin(); it != s21_list.end(); ++it) {
    EXPECT_EQ(*it, *it_std);
    ++it_std;
  }
}

TEST(ListConstructorTest, test_3) {
  EXPECT_THROW(s21::List<char> s21_list(-1), std::out_of_range);
}

TEST(ListConstructorTest, test_4) {
  EXPECT_THROW(s21::List<char> s21_list(3843071682022823251),
               std::out_of_range);
}

TEST(ListConstructorTest, test_5) {
  s21::List<double> s21_list = {1.1, 2.2, 3.3, 4.4, 5.5};
  s21::List<double> s21_list_copy(s21_list);

  std::list<double> std_list = {1.1, 2.2, 3.3, 4.4, 5.5};
  std::list<double> std_list_copy(std_list);

  EXPECT_EQ(s21_list_copy.size(), std_list_copy.size());
  auto it_std = std_list_copy.begin();
  for (auto it = s21_list_copy.begin(); it != s21_list_copy.end(); ++it) {
    EXPECT_EQ(*it, *it_std);
    ++it_std;
  }
}

TEST(ListConstructorTest, test_6) {  // исправить !
  s21::List<double> s21_list = {1.1, 2.2, 3.3, 4.4, 5.5};
  s21::List<double> s21_list_copy(std::move(s21_list));

  std::list<double> std_list = {1.1, 2.2, 3.3, 4.4, 5.5};
  std::list<double> std_list_copy(std::move(std_list));

  EXPECT_EQ(s21_list_copy.size(), std_list_copy.size());
  auto it_s21 = s21_list_copy.begin();
  for (auto it = std_list_copy.begin(); it != std_list_copy.end(); ++it) {
    EXPECT_EQ(*it, *it_s21);
    ++it_s21;
  }
}

TEST(ListConstructorTest, test_7) {
  s21::List<const char *> s21_list = {"bla", "это", "полный", "кринж", "!"};

  std::list<const char *> std_list = {"bla", "это", "полный", "кринж", "!"};

  EXPECT_EQ(s21_list.size(), std_list.size());
  auto it_std = std_list.begin();
  for (auto it = s21_list.begin(); it != s21_list.end(); ++it) {
    EXPECT_STREQ(*it, *it_std);
    ++it_std;
  }
}

TEST(ListOperatorsTests, test_1) {
  s21::List<int> s21_list = {1, 2, 3};
  s21::List<int> s21_list_new = std::move(s21_list);

  std::list<int> std_list = {1, 2, 3};
  std::list<int> std_list_new = std::move(std_list);

  EXPECT_EQ(s21_list_new.size(), std_list_new.size());
  size_t count = s21_list_new.size();

  auto it_std = std_list_new.begin();
  auto it = s21_list_new.begin();
  while (count > 0) {
    EXPECT_EQ(*it, *it_std);
    count--;
    ++it_std;
    ++it;
  }
}

TEST(ListFrontBackTests, test_1) {
  s21::List<int> s21_list = {1, 2, 3};
  std::list<int> std_list = {1, 2, 3};

  EXPECT_EQ(s21_list.front(), std_list.front());
}

TEST(ListFrontBackTests, test_2) {
  s21::List<int> s21_list = {1, 2, 3};
  std::list<int> std_list = {1, 2, 3};

  EXPECT_EQ(s21_list.back(), std_list.back());
}

TEST(ListFrontBackTests, test_3) {
  s21::List<char> s21_list;
  EXPECT_THROW(s21_list.front(), std::out_of_range);
}

TEST(ListFrontBackTests, test_4) {
  s21::List<char> s21_list;
  EXPECT_THROW(s21_list.back();, std::out_of_range);
}

TEST(ListIteratorTests, test_1) {
  s21::List<int> s21_list = {1, 2, 3};
  std::list<int> std_list = {1, 2, 3};
  auto it_std = std_list.begin();
  auto it = s21_list.begin();
  while (it != s21_list.end()) {
    EXPECT_EQ(*it, *it_std);
    ++it_std;
    ++it;
  }
}

TEST(ListSortTests, test_1) {
  s21::List<int> s21_list = {5, 3, 1, 2, 4, 8, 7, 6, 10, 9};
  s21::List<int> list_sorted = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  s21_list.sort();
  std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!size: " << s21_list.size() << '\n';
  s21_list.print_list();
  for (auto it = s21_list.begin(); it != s21_list.end(); ++it) {
    EXPECT_EQ(*it, list_sorted.front());
    list_sorted.pop_front();
  }
}

TEST(ListClearTests, test_1) {
  s21::List<int> s21_list = {5, 3, 1, 2, 4, 8, 7, 6, 10, 9};
  s21_list.clear();
  EXPECT_EQ(s21_list.size(), static_cast<size_t>(0));
  EXPECT_EQ(s21_list.empty(), true);
}

TEST(ListPushBackTests, test_1) {
  s21::List<int> s21_list;
  s21_list.push_back(1);
  s21_list.push_back(2);
  s21_list.push_back(3);
  EXPECT_EQ(s21_list.size(), static_cast<size_t>(3));
  int i = 1;
  for (auto it = s21_list.begin(); it != s21_list.end(); ++it) {
    EXPECT_EQ(*it, i);
    i++;
  }
}

TEST(ListPopBackTests, test_1) {
  s21::List<int> s21_list = {1, 2, 3};
  s21_list.pop_back();
  EXPECT_EQ(s21_list.size(), static_cast<size_t>(2));
  EXPECT_EQ(s21_list.back(), 2);
  s21_list.pop_back();
  EXPECT_EQ(s21_list.size(), static_cast<size_t>(1));
  EXPECT_EQ(s21_list.back(), 1);
  s21_list.pop_back();
  EXPECT_EQ(s21_list.size(), static_cast<size_t>(0));
  EXPECT_EQ(s21_list.empty(), true);
}

TEST(ListPushFrontTests, test_1) {
  s21::List<int> s21_list;
  s21_list.push_front(1);
  s21_list.push_front(2);
  s21_list.push_front(3);
  EXPECT_EQ(s21_list.size(), static_cast<size_t>(3));
  int i = 3;
  for (auto it = s21_list.begin(); it != s21_list.end(); ++it) {
    EXPECT_EQ(*it, i);
    i--;
  }
}

TEST(ListPopFrontTests, test_1) {
  s21::List<int> s21_list = {1, 2, 3};
  s21_list.pop_front();
  EXPECT_EQ(s21_list.size(), static_cast<size_t>(2));
  EXPECT_EQ(s21_list.front(), 2);
  s21_list.pop_front();
  EXPECT_EQ(s21_list.size(), static_cast<size_t>(1));
  EXPECT_EQ(s21_list.front(), 3);
  s21_list.pop_front();
  EXPECT_EQ(s21_list.size(), static_cast<size_t>(0));
  EXPECT_EQ(s21_list.empty(), true);
}

TEST(ListSwapTests, test_1) {
  s21::List<int> s21_list = {1, 2, 3};
  s21::List<int> s21_list2 = {4, 5, 6};
  s21_list.swap(s21_list2);
  EXPECT_EQ(s21_list.size(), static_cast<size_t>(3));
  EXPECT_EQ(s21_list.front(), 4);
  EXPECT_EQ(s21_list2.size(), static_cast<size_t>(3));
  EXPECT_EQ(s21_list2.front(), 1);
}

TEST(ListMergeTests, test_1) {
  s21::List<int> s21_list = {1, 2, 3};
  s21::List<int> s21_list2 = {4, 5, 6};
  s21_list.merge(s21_list2);
  EXPECT_EQ(s21_list.size(), static_cast<size_t>(6));
  EXPECT_EQ(s21_list.front(), 1);
  EXPECT_EQ(s21_list.back(), 6);
}

TEST(ListReverseTests, test_2) {
  s21::List<int> s21_list = {1, 2, 3};
  s21_list.reverse();
  EXPECT_EQ(s21_list.size(), static_cast<size_t>(3));
  EXPECT_EQ(s21_list.front(), 3);
  EXPECT_EQ(s21_list.back(), 1);
}

TEST(ListUniqueTests, test_1) {
  s21::List<int> s21_list = {1, 2, 3, 1, 2, 3};
  s21_list.unique();
  // std::cout << "!!!!!!!!!!!!!size: " << s21_list.size() << '\n';
  // s21_list.print_list();
  EXPECT_EQ(s21_list.size(), static_cast<size_t>(3));
  EXPECT_EQ(s21_list.front(), 1);
  // EXPECT_EQ(s21_list.back(), 3);
}

TEST(ListEraseTests, test_1) {
  s21::List<int> s21_list = {1, 2, 3, 1, 2, 3};
  s21_list.erase(s21_list.begin());
  EXPECT_EQ(s21_list.size(), static_cast<size_t>(5));
  EXPECT_EQ(s21_list.front(), 2);
  EXPECT_EQ(s21_list.back(), 3);
}

TEST(ListSpliceTest, test_1) {
  s21::List<int> s21_list = {1, 2, 3};
  s21::List<int> s21_list2 = {4, 5, 6};

  ASSERT_FALSE(s21_list.empty());

  if (!s21_list.empty()) {
    s21_list.splice(s21_list.begin(), s21_list2);
    EXPECT_EQ(s21_list.size(), static_cast<size_t>(6));
    EXPECT_EQ(s21_list.front(), 1);
    EXPECT_EQ(s21_list.back(), 3);
  } else {
    FAIL() << "s21_list is empty";
  }
}

TEST(list, insert_many_front) {
  s21::List<int> s21_list = {1, 2, 3};
  s21_list.insert_many_front(4, 5, 6);
  EXPECT_EQ(s21_list.size(), static_cast<size_t>(6));
  EXPECT_EQ(s21_list.front(), 4);
  EXPECT_EQ(s21_list.back(), 3);
}

TEST(list, insert_many_back) {
  s21::List<int> s21_list = {1, 2, 3};
  s21_list.insert_many_back(4, 5, 6);
  EXPECT_EQ(s21_list.size(), static_cast<size_t>(6));
  EXPECT_EQ(s21_list.front(), 1);
  EXPECT_EQ(s21_list.back(), 6);
}

TEST(list, insert_many) {
  s21::List<int> s21_list = {1, 2, 3};
  auto it = s21_list.begin();
  s21_list.insert_many(it, 4, 5, 6);
  std::cout << "!!!!!!!!!!!!!size: " << s21_list.size() << '\n';
  s21_list.print_list();
  EXPECT_EQ(s21_list.size(), static_cast<size_t>(6));
}