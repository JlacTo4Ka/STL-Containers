#ifndef __S21VECTOR_H__
#define __S21VECTOR_H__

#include <cstddef>
#include <exception>
#include <initializer_list>
#include <stdexcept>

namespace s21 {
template <class T>
class vector {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

  //   Functions
  vector() {
    values = nullptr;
    size_ = 0;
    capacity_ = 0;
  };
  vector(size_type n) {
    values = new T[n]{};
    size_ = n;
    capacity_ = n;
  };
  vector(std::initializer_list<value_type> const &items) {
    size_ = items.size();
    capacity_ = items.size();
    size_type i = 0;
    values = new T[items.size()]{};
    for (auto element : items) values[i++] = element;
  };
  vector(const vector &v) {
    values = new T[v.size_];
    for (size_type i = 0; i < v.size_; i++) values[i] = v.values[i];
    size_ = v.size_;
    capacity_ = v.size_;
  };
  vector(vector &&v) noexcept : vector() {
    std::swap(size_, v.size_);
    std::swap(capacity_, v.capacity_);
    std::swap(values, v.values);
  };
  vector &operator=(vector &&v) noexcept {
    if (this != &v) {
      std::swap(size_, v.size_);
      std::swap(capacity_, v.capacity_);
      std::swap(values, v.values);
    }
    return *this;
  };
  ~vector() {
    capacity_ = 0;
    size_ = 0;
    delete[] values;
  };
  // Element access
  reference at(size_type pos) {
    if (pos >= size_)
      throw std::out_of_range("Incorrect input, index is out of range");
    return values[pos];
  };
  reference operator[](size_type pos) { return values[pos]; };
  const_reference front() { return values[0]; };
  const_reference back() { return values[size_ - 1]; };
  iterator data() { return values; };
  //   Iterators
  iterator begin() { return &values[0]; };
  iterator end() { return &values[size_]; };
  // Capacity
  bool empty() {
    bool flag = true;
    if (&values[0] != &values[size_]) flag = false;
    return flag;
  };
  size_type size() { return size_; };
  size_type max_size() { return SIZE_MAX / sizeof(value_type); };
  void reserve(size_type size) {
    if (size > capacity_) {
      iterator new_storage = new T[size]{};
      for (size_type i = 0; i < size_; i++) {
        new_storage[i] = values[i];
      }
      delete[] values;
      values = new_storage;
      capacity_ = size;
    }
  };
  size_type capacity() { return capacity_; };
  void shrink_to_fit() { capacity_ = size_; };
  //   Modifiers
  void clear() {
    delete[] values;
    values = nullptr;
    size_ = 0;
  };

  iterator insert(iterator pos, const_reference value) {
    size_type index = pos - values;
    if (size_ >= capacity_) {
      size_type new_capacity = capacity_ == 0 ? 1 : capacity_ * 2;
      reserve(new_capacity);
    }
    for (size_type i = size_; i > index; --i) {
      values[i] = values[i - 1];
    }
    values[index] = value;
    size_++;
    return values + index;
  };

  void erase(iterator pos) {
    size_type index = pos - values;
    for (size_type i = index; i < size_ - 1; ++i) {
      values[i] = values[i + 1];
    }
    size_--;
  };

  void push_back(const_reference value) {
    if (capacity_ == size_ && capacity_ != 0) reserve(capacity_ * 2);
    if (capacity_ == 0) reserve(1);
    values[size_] = value;
    size_++;
  };

  void pop_back() { size_--; };

  void swap(vector &other) {
    if (this != &other) std::swap(*this, other);
  };

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args &&...args) {
    iterator temp_begin = begin();
    if (capacity_ < size_ + sizeof...(args)) reserve(size_ + sizeof...(args));
    iterator position = begin() + (pos - temp_begin);
    vector<value_type> temp = {args...};
    for (size_t i = 0; i < temp.size(); ++i) {
      position = insert(position, temp[i]);
      position++;
    }
    return position;
  }

  template <typename... Args>
  void insert_many_back(Args &&...args) {
    insert_many(this->end(), args...);
  }

 private:
  T *values;
  size_type size_;
  size_type capacity_;
};
}  // namespace s21
#endif