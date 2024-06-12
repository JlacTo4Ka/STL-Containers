#ifndef __S21QUEUE_H__
#define __S21QUEUE_H__

#include <algorithm>
#include <cstddef>
#include <initializer_list>
#include <stdexcept>

namespace s21 {
template <class T>
class queue {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

 private:
  class ListNode {
   public:
    value_type value = value_type();
    ListNode *next = nullptr;
    ListNode() = default;
    ListNode(value_type value_) { value = value_; }
    ~ListNode() = default;
  };

 private:
  ListNode *head = nullptr;
  ListNode *tail = nullptr;
  size_type amount_of_nodes = 0;
  //   Functions
 public:
  queue() = default;

  queue(std::initializer_list<value_type> const &items) {
    if (items.size() != 0) {
      for (auto elems : items) {
        push(elems);
      }
    }
  };

  queue(const queue &q) {
    ListNode *queueOther = q.head;
    while (queueOther != nullptr) {
      push(queueOther->value);
      queueOther = queueOther->next;
    }
    amount_of_nodes = q.amount_of_nodes;
  };

  queue(queue &&q) noexcept {
    if (this != &q) {
      head = q.head;
      tail = q.tail;
      q.head = nullptr;
      q.tail = nullptr;
      amount_of_nodes = q.amount_of_nodes;
      q.amount_of_nodes = 0;
    }
  };

  ~queue() {
    while (amount_of_nodes != 0) {
      pop();
    };
  };
  queue &operator=(queue &&q) noexcept {
    if (this != &q) {
      if (amount_of_nodes > 0) {
        while (amount_of_nodes != 0) {
          pop();
        };
      }
      head = q.head;
      tail = q.tail;
      q.head = nullptr;
      q.tail = nullptr;
      amount_of_nodes = q.amount_of_nodes;
      q.amount_of_nodes = 0;
    }
    return *this;
  };

  // Element access
  const_reference front() { return head->value; };
  const_reference back() { return tail->value; };

  //   Capacity
  bool empty() { return amount_of_nodes == 0; };

  size_type size() { return amount_of_nodes; };
  // Modifiers
  void push(const_reference value) {
    auto *tmp = new ListNode(value);
    if (tail == nullptr) {
      head = tmp;
      tail = tmp;
    } else {
      tail->next = tmp;
      tail = tmp;
    }
    amount_of_nodes++;
  };
  void pop() {
    ListNode *buf = head->next;
    if (head != nullptr) {
      delete head;
    }
    head = buf;
    amount_of_nodes--;
  };
  void swap(queue &other) {
    if (this != &other) std::swap(*this, other);
  };
  template <typename... Args>
  void insert_many_back(Args &&...args) {
    queue<value_type> temp = {args...};
    size_type s = temp.size();
    for (size_type i = 0; i < s; i++) {
      push(temp.front());
      temp.pop();
    }
  }
};
}  // namespace s21
#endif