#ifndef _S21_MULTISET_H_
#define _S21_MULTISET_H_

#include "AVL.hpp"

namespace s21 {
template <class Key, class T = Key>
class multiset : public s21::AVLTree<Key, T> {
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

  multiset() : avl_tree() {}  // done

  multiset(std::initializer_list<T> const& items) {
    for (auto it = items.begin(); it != items.end(); it++) {
      insert(*it);
    }
  }

  ~multiset() { this->clear(); }

  multiset(const multiset& m) : avl_tree(m) {}  // done

  multiset(multiset&& m) {
    *this = std::move(m);
    m.destroy_node_tree();
  }

  multiset& operator=(multiset&& m) {  // done
    if (this != &m) {
      avl_tree::operator=(std::move(m));
    }
    return *this;
  }

  // ----------iterators ----------

  iterator find(const key_type& key) { return avl_tree::find_tree(key); }

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
    return avl_tree::insert(key);
  }

  std::pair<iterator, bool> insert(const key_type& key,
                                   const value_type& value) {
    return avl_tree::insert(key, value);
  }

  // ---------- delete elem ----------

  void erase(iterator pos) { avl_tree::delete_node(*pos); }

  void swap(multiset& other) { avl_tree::swap(other); }

  void merge(multiset& other) { avl_tree::merge(other); }

  // ---------- print multiset like tree or sequence ----------

  void print_multiset_tree() { avl_tree::print_tree(); }

  void print_multiset_sort() {
    avl_tree::sort_print();
    std::cout << '\n';
  }

  // ---------- count, equal_range, lower_bound, upper_bound ----------

  size_type count(const key_type& key) { return avl_tree::count(key); }

  std::pair<iterator, iterator> equal_range(const key_type& key) {
    iterator lower = avl_tree::first_big_or_equal(key);
    iterator upper = avl_tree::first_big(key);
    return std::make_pair(lower, upper);
  }

  iterator lower_bound(const key_type& key) {
    return avl_tree::first_big_or_equal(key);
  }

  iterator upper_bound(const key_type& key) { return avl_tree::first_big(key); }

  template <class... Args>
  vector<std::pair<iterator, bool>> insert_many(Args&&... args) {
    return avl_tree::insert_many(args...);
  }
};
};  // namespace s21

#endif  // _S21_MULTISET_H_
