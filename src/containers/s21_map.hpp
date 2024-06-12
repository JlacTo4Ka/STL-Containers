#ifndef _S21_MAP_H_
#define _S21_MAP_H_

#include "AVL.hpp"

namespace s21 {
template <class Key, class T, class Compare = std::less<Key>>
class map : public s21::AVLTree<Key, T> {
 public:
  using avl_tree = s21::AVLTree<Key, T>;
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = typename avl_tree::iterator;
  using const_iterator = const value_type*;
  using size_type = size_t;

 private:
  // key_type key;
  // mapped_type value_in_pair;
  // value_type value;

 public:
  map() : avl_tree() {}

  map(std::initializer_list<value_type> const& items) {
    for (auto it = items.begin(); it != items.end(); it++) {
      insert(*it);
    }
  }

  map(const map& m) : avl_tree(m) {}

  map(map&& m) {
    *this = std::move(m);
    m.destroy_node_tree();
  }

  ~map() { this->clear(); }

  map& operator=(map&& m) {
    if (this != &m) {
      avl_tree::operator=(std::move(m));
    }
    return *this;
  }

  T& at(const key_type& key) { return avl_tree::get_node_at(key); }

  T& operator[](const key_type& key) {
    return avl_tree::get_node_and_insert(key);
  }

  iterator begin() { return avl_tree::begin(); }
  iterator end() { return avl_tree::end(); }

  bool empty() { return avl_tree::empty(); }

  size_type size() { return avl_tree::size_tree(); }
  size_type max_size() { return avl_tree::max_size_tree(); }

  void clear() { avl_tree::destroy_node_tree(); }

  std::pair<iterator, bool> insert(const value_type& value) {
    auto result = avl_tree::insert_unique(value.first, value.second);
    return {result.first, result.second};
  }

  std::pair<iterator, bool> insert(const key_type& key,
                                   const mapped_type& obj) {
    auto result = avl_tree::insert_unique(key, obj);
    return {result.first, result.second};
  }

  std::pair<iterator, bool> insert_or_assign(const key_type& key,
                                             const T& obj) {
    return avl_tree::insert_or_assign(key, obj);
  }

  void erase(iterator pos) { avl_tree::delete_node(*pos); }

  void swap(map& other) { avl_tree::swap(other); }

  void merge(map& other) { avl_tree::merge_unique(other); }

  bool contains(const Key& key) { return avl_tree::get_node_bool(key); }

  void print_map_tree() { avl_tree::print_tree(); }

  void print_map_sort() {
    avl_tree::sort_print();
    std::cout << '\n';
  }

  template <class... Args>
  vector<std::pair<iterator, bool>> insert_many(Args&&... args) {
    vector<std::pair<iterator, bool>> result;
    stack temp_stack{std::forward<Args>(args)...};

    while (!temp_stack.empty()) {
      std::pair<iterator, bool> temp = avl_tree::insert_unique(
          temp_stack.top().first, temp_stack.top().second);
      // result.push_back(temp);
      temp_stack.pop();
    }

    return result;
  }
};

};  // namespace s21

#endif