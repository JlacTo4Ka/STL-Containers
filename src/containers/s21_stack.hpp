#ifndef _S21_STACK_H_
#define _S21_STACK_H_

#include <algorithm>
#include <cstddef>
#include <initializer_list>
#include <stdexcept>
#include <utility>

#include "s21_queue.hpp"

// #include "../s21_containers.hpp"

namespace s21 {
template <typename T>
class stack {
 private:
  struct Node {
    T data;
    Node *next;
    Node(const T &value) : data(value), next(nullptr) {}
  };

  size_t size_;
  Node *top_;

 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = std::size_t;

  stack() : size_(0), top_(nullptr){};

  stack(std::initializer_list<value_type> const &items)
      : size_(0), top_(nullptr) {
    for (auto it = items.begin(); it != items.end(); it++) {
      push(*it);
    }
  };

  stack(const stack &s) : size_(0), top_(nullptr) {
    Node *current = s.top_;
    while (current != nullptr) {
      push(current->data);
      current = current->next;
    }
  };

  stack(stack &&s) noexcept : size_(s.size_), top_(s.top_) {
    s.size_ = 0;
    // s.capacity_ = 0;
    s.top_ = nullptr;
  };

  ~stack() {
    while (!empty()) {
      pop();
    }
  };

  stack &operator=(stack &&s) noexcept {
    if (this != &s) {
      while (!empty()) {
        pop();
      }
      size_ = s.size_;
      top_ = s.top_;
      s.size_ = 0;
      s.top_ = nullptr;
    }
    return *this;
  };

  const_reference top() {
    if (this->empty()) {
      throw std::out_of_range("Stack is empty");
    } else {
      return top_->data;
    }
  }

  bool empty() { return top_ == nullptr; };

  size_type size() { return size_; };

  void push(const_reference value) {
    Node *new_node = new Node(value);
    new_node->next = top_;
    top_ = new_node;
    size_++;
  };

  void pop() {
    if (!empty()) {
      Node *tmp = top_;
      top_ = top_->next;
      delete tmp;
      size_--;
    }
  }

  void swap(stack &other) noexcept {
    std::swap(size_, other.size_);
    std::swap(top_, other.top_);
  }

  template <class... Args>
  void insert_many_front(Args &&...args) {
    stack temp_stack{std::forward<Args>(args)...};
    while (!temp_stack.empty()) {
      push(temp_stack.top());
      temp_stack.pop();
    }
  }
};
}  // namespace s21

#endif