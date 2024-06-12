#ifndef __S21ARRAY_H__
#define __S21ARRAY_H__

#include <cstddef>
#include <exception>
#include <initializer_list>
#include <iostream>

namespace s21 {
template <class T, std::size_t N>
class array {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;
  // Functions
  array() {
    values = new T[N];
    size_ = N;
  };
  array(std::initializer_list<value_type> const &items) {
    values = new T[N]{};
    size_type i = 0;
    for (auto element : items) values[i++] = element;
    size_ = N;
  };
  array(const array &a) {
    values = new T[N];
    size_ = N;
    for (size_type i = 0; i < size_; i++) values[i] = a.values[i];
  };
  array(array &&a) noexcept : array() { std::swap(values, a.values); };
  ~array() {
    size_ = 0;
    delete[] values;
  };
  array &operator=(array &&a) {
    for (size_type i = 0; i < size_; i++) values[i] = a.values[i];
    return *this;
  };
  //   Element access
  reference at(size_type pos) {
    if (pos >= N)
      throw std::out_of_range("Incorrect input, index is out of range");
    return values[pos];
  };
  reference operator[](size_type pos) { return values[pos]; };
  const_reference front() { return values[0]; };
  const_reference back() { return values[N - 1]; };
  iterator data() { return values; }
  //   capacity
  bool empty() {
    bool flag = true;
    if (size_ != 0) {
      flag = false;
    }
    return flag;
  };
  size_type size() const { return size_; };
  size_type max_size() const { return size_; };
  //   iterators
  iterator begin() const { return &values[0]; };
  iterator end() const { return &values[size_]; };
  // Modifiers
  void swap(array &other) {
    if (this != &other) {
      for (size_type i = 0; i < size_; i++) {
        std::swap(values[i], other.values[i]);
      }
    }
  };
  void fill(const_reference value) {
    for (size_type i = 0; i < size_; i++) {
      values[i] = value;
    }
  };

 private:
  T *values;
  size_type size_;
};
}  // namespace s21

#endif
