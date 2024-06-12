#ifndef _S21_SET_H_
#define _S21_SET_H_

#include "AVL.hpp"

namespace s21 {
template <class Key, class T = Key>
class Set : public s21::AVLTree<Key, T> {
 public:
  using key_type = Key;
  using value_type = T;
  using avl_tree = s21::AVLTree<Key, T>;

 private:
  template <class key_type, class value_type>
  struct Node {
    key_type key;
    value_type value;
    Node(key_type key = key_type()) : key(key) {}
    Node(key_type key = key_type(), value_type value = value_type())
        : key(key), value(value) {}
  };

 public:
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = typename avl_tree::TreeIterator;
  using const_iterator = const value_type*;
  using size_type = size_t;

  // ---------- constructors, destructor ----------

  Set() : avl_tree() {}  // done

  Set(std::initializer_list<T> const& items) {
    for (auto it = items.begin(); it != items.end(); it++) {
      insert(*it);
    }
  }

  ~Set() { this->clear(); }

  Set(const Set& m) : avl_tree(m) {}  // done

  Set(Set&& m) {
    *this = std::move(m);
    m.destroy_node_tree();
  }

  Set& operator=(Set&& m) {  // done
    if (this != &m) {
      avl_tree::operator=(std::move(m));
    }
    return *this;
  }

  // ----------iterators ----------

  iterator find(const key_type& key) { return avl_tree::find_tree(key); }

  // key_type _get_root() { return avl_tree::get_root_key(); }

  bool contains(const key_type& key) { return avl_tree::get_node_bool(key); }

  iterator begin() { return avl_tree::begin(); }

  iterator end() { return avl_tree::end(); }

  // ---------- size funcs ----------
  bool empty() { return avl_tree::empty(); }
  size_type size() { return avl_tree::size_tree(); }
  size_type max_size() { return avl_tree::max_size_tree(); }

  // ---------- clear ----------

  void clear() { avl_tree::destroy_node_tree(); }

  // ---------- inserts funcs ----------

  std::pair<iterator, bool> insert(const value_type& key) {
    return avl_tree::insert_unique(key);
  }

  std::pair<iterator, bool> insert(const key_type& key,
                                   const value_type& value) {
    return avl_tree::insert_unique(key, value);
  }

  // ---------- delete elem ----------

  void erase(iterator pos) { avl_tree::delete_node(*pos); }

  void swap(Set& other) { avl_tree::swap(other); }

  void merge(Set& other) { avl_tree::merge_unique(other); }

  // ---------- print set like tree or sequence ----------

  void print_set_tree() { avl_tree::print_tree(); }

  void print_set_sort() {
    avl_tree::sort_print();
    std::cout << '\n';
  }

  template <class... Args>
  vector<std::pair<iterator, bool>> insert_many(Args&&... args) {
    return avl_tree::insert_many(args...);
  }
};
};  // namespace s21

#endif  // S21_SET_H_
