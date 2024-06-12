#ifndef _S21_AVL_H_
#define _S21_AVL_H_

#include <exception>
#include <iostream>
#include <memory>
#include <stack>

#include "s21_stack.hpp"
#include "s21_vector.hpp"

#define MAX_SIZE_VALUE_TREE 230584300921369395

namespace s21 {
template <class Key, class T = Key>
class AVLTree {
 public:
  using key_type = Key;
  using value_type = T;
  using size_type = size_t;
  using reference = T&;
  using const_reference = const T&;

 private:
  template <class value_type>
  class Node {
   public:
    key_type key;
    value_type value;
    int height;
    Node<value_type>* left;
    Node<value_type>* right;

    Node()
        : key(key_type()),
          value(value_type()),
          height(1),
          left(nullptr),
          right(nullptr) {}

    Node(key_type key = key_type(), value_type value = value_type()) {
      this->key = key;
      this->value = value;
      height = 1;
      left = right = nullptr;
    }
  };

  Node<value_type>* root;
  size_type size_of_tree;

  int height(Node<value_type>* target) {
    if (target)
      return target->height;
    else
      return 0;
  }

  int calculate_diff(Node<value_type>* target) {
    return height(target->right) - height(target->left);
  }

  void recalculate_height(Node<value_type>* target) {
    int left_height = height(target->left);
    int right_height = height(target->right);
    target->height =
        (left_height > right_height ? left_height : right_height) + 1;
  }

  size_type calc_count(Node<value_type>* target) {
    if (!target) {
      return 0;
    }
    if (!target->left && !target->right) {
      return 1;
    }
    return calc_count(target->left) + calc_count(target->right) + 1;
  }

  Node<value_type>* right_rotate(Node<value_type>* target) {
    Node<value_type>* target_child = target->left;
    target->left = target_child->right;
    target_child->right = target;
    recalculate_height(target);
    recalculate_height(target_child);
    return target_child;
  }

  Node<value_type>* left_rotate(Node<value_type>* target) {
    Node<value_type>* target_child = target->right;
    target->right = target_child->left;
    target_child->left = target;
    recalculate_height(target);
    recalculate_height(target_child);
    return target_child;
  }

  Node<value_type>* rebalance(Node<value_type>* target) {
    recalculate_height(target);
    if (calculate_diff(target) == 2) {
      if (calculate_diff(target->right) < 0) {
        target->right = right_rotate(target->right);
      }
      return left_rotate(target);
    }
    if (calculate_diff(target) == -2) {
      if (calculate_diff(target->left) > 0) {
        target->left = left_rotate(target->left);
      }
      return right_rotate(target);
    }
    return target;
  }

  void _merge_unique(Node<value_type>*& root1, Node<value_type>* root2) {
    if (root2 == NULL) return;

    _merge_unique(root1, root2->left);
    _merge_unique(root1, root2->right);

    root1 = insert_node_unique(root1, root2->key, root2->value);
  }

  void _merge(Node<value_type>*& root1, Node<value_type>* root2) {
    if (root2 == NULL) return;

    _merge(root1, root2->left);
    _merge(root1, root2->right);

    root1 = insert_node(root1, root2->key, root2->value);
  }

  Node<value_type>* find_min(Node<value_type>* target) {
    if (target->left) {
      return find_min(target->left);
    } else
      return target;
  }

  Node<value_type>* delete_min(Node<value_type>* target) {
    if (!target->left) {
      return target->right;
    }
    target->left = delete_min(target->left);
    return rebalance(target);
  }

  Node<value_type>* _delete_node(Node<value_type>* target, key_type key) {
    if (!target) {
      return nullptr;
    }
    if (key < target->key) {
      target->left = _delete_node(target->left, key);
    } else if (key > target->key) {
      target->right = _delete_node(target->right, key);
    } else {
      Node<value_type>* left_child = target->left;    // 2
      Node<value_type>* right_child = target->right;  // 9
      delete target;
      if (!right_child) {
        return left_child;
      }
      Node<value_type>* min = find_min(right_child);
      root = min;
      min->right = delete_min(right_child);
      min->left = left_child;
      return rebalance(min);
    }
    return rebalance(target);
  }

  void _print_tree(Node<value_type>* target, int level = 0) {
    if (!target) return;

    _print_tree(target->right, level + 1);

    for (int i = 0; i < level; i++) {
      std::cout << "      ";
    }

    std::cout << target->key << '[' << target->value << ']' << std::endl;

    _print_tree(target->left, level + 1);
  }

  void inorderTraversal(Node<value_type>* root) {
    if (root != nullptr) {
      inorderTraversal(root->left);
      std::cout << root->key << "[" << root->value << "] ";
      inorderTraversal(root->right);
    }
  }

  size_type _count(Node<value_type>* root, const key_type& key) {
    size_type count = 0;
    if (root != nullptr) {
      // std::cout << root->key;
      if (key == root->key) {
        count += _count(root->left, key) + _count(root->right, key);
        // count += _count(root->right, key);
        count++;
      } else {
        count += _count(root->left, key) + _count(root->right, key);
        // count += _count(root->right, key);
      }
    }

    return count;
  }

  Node<value_type>* copy_node(const Node<value_type>* source) {
    if (!source) {
      return nullptr;
    }

    Node<value_type>* new_node =
        new Node<value_type>(source->key, source->value);
    new_node->height = source->height;
    new_node->left = copy_node(source->left);
    new_node->right = copy_node(source->right);
    return new_node;
  }

  void destroy_node(Node<value_type>* node) {
    if (node) {
      destroy_node(node->left);
      destroy_node(node->right);
      delete node;
      root = nullptr;
      size_of_tree = 0;
    }
  }

 protected:
  // ---------- constructors ----------

  AVLTree() {
    root = nullptr;
    size_of_tree = 0;
  }

  AVLTree(const AVLTree& other) { root = copy_node(other.root); }

  // ---------- operator= ----------

  AVLTree& operator=(const AVLTree& other) {
    if (this != &other) {
      destroy_node(root);
      root = copy_node(other.root);
    }
    return *this;
  }

  // ---------- base methods ----------
  // get_node, delete

  Node<value_type>* get_root() { return root; }

  void set_root(Node<value_type>* other) { root = other; }

  Node<value_type>* get_node(Node<value_type>* target = nullptr,
                             key_type key = key_type()) {
    if (!target) {
      return nullptr;
    }
    if (target->key == key) {
      return target;
    } else if (target->key < key) {
      return get_node(target->right, key);
    } else {
      return get_node(target->left, key);
    }
  }

  bool get_node_bool(const key_type& key) { return _get_node_bool(root, key); }

  bool _get_node_bool(Node<value_type>* target, const key_type& key) {
    if (!target) {
      return false;
    }
    if (target->key == key) {
      return true;
    } else if (target->key < key) {
      return _get_node_bool(target->right, key);
    } else {
      return _get_node_bool(target->left, key);
    }
  }

  void delete_node(key_type key) {
    if (this->empty()) {
      throw std::out_of_range("Пустое дерево");
    } else {
      _delete_node(root, key);
    }
    size_of_tree--;
  }

  // merge with unique or simple keys

  void merge_unique(AVLTree& other) {
    _merge_unique(root, other.get_root());
    other.destroy_node_tree();
  }

  void merge(AVLTree& other) {
    _merge(root, other.get_root());
    other.destroy_node_tree();
  }

  // swap!

  void swap(AVLTree& other) {
    Node<value_type>* tmp_root = other.get_root();
    other.set_root(this->root);
    this->set_root(tmp_root);
    size_t tmp_size = other.size_of_tree;
    other.size_of_tree = this->size_of_tree;
    this->size_of_tree = tmp_size;
  }

  // ---------- empty(), size(), max_size() ----------

  bool empty() { return root == nullptr; }

  size_type size_tree() { return size_of_tree; }

  size_type max_size_tree() { return MAX_SIZE_VALUE_TREE; }

  // ---------- count ----------
  // ---------- for_multiset ----------

  size_type count(const key_type& key) {
    size_type count_node = 0;

    count_node += _count(root, key);

    return count_node;
  }

  // ---------- print funcs ----------

  void print_tree(Node<value_type>* target = nullptr, int level = 0) {
    if (root == nullptr) {
      std::cout << "container is empty!\n";
    }

    if (target == nullptr) {
      target = root;
    }
    _print_tree(target, level);
  }

  void sort_print() { inorderTraversal(root); }

  // ---------- destructors ----------
  // не нужен из-за классов наследников set и map

  // ~AVLTree() { destroy_node(root); }

  void destroy_node_tree() { destroy_node(root); }

  // ---------- iterators ----------

  class TreeIterator {
   private:
    Node<value_type>* curr;
    stack<Node<value_type>*> path_stack;

    void push_left_branch(Node<value_type>* node) {
      while (node) {
        path_stack.push(node);
        node = node->left;
      }
    }

   public:
    Node<value_type>* push_right_branch(Node<value_type>* node) {
      while (node) {
        path_stack.push(node);
        if (!node->right) return node;
        node = node->right;
      }
      return node;
    }

    TreeIterator(Node<value_type>* node = nullptr) : curr(node) {
      if (curr) {
        push_left_branch(curr);
        curr = path_stack.empty() ? nullptr : path_stack.top();
        path_stack.pop();
      }
    }

    // Новый конструктор, который устанавливает curr на переданный узел и
    // заполняет стек
    TreeIterator(Node<value_type>* node, Node<value_type>*& tree_root)
        : curr(node) {
      Node<value_type>* temp = tree_root;
      if (temp) {
        push_left_branch(temp);
        curr = path_stack.empty() ? nullptr : path_stack.top();
        path_stack.pop();
      }
      // Убедимся, что curr останется на текущем узле
      curr = node;
    }

    reference operator*() {
      if (curr) {
        return curr->key;
      } else {
        throw std::out_of_range("Invalid iterator");
      }
    }

    TreeIterator& operator++() {
      if (curr->right) {
        push_left_branch(curr->right);
      }
      curr = path_stack.empty() ? nullptr : path_stack.top();
      path_stack.pop();
      return *this;
    }

    TreeIterator operator++(int) {
      TreeIterator tmp = *this;
      ++(*this);
      return tmp;
    }

    TreeIterator& operator--() {
      if (curr->left) {
        push_right_branch(curr->left);
      }
      curr = path_stack.empty() ? nullptr : path_stack.top();
      path_stack.pop();
      return *this;
    }

    TreeIterator operator--(int) {
      TreeIterator tmp = *this;
      --(*this);
      return tmp;
    }

    bool operator==(const TreeIterator& other) const {
      return curr == other.curr;
    }

    bool operator!=(const TreeIterator& other) const {
      return !(*this == other);
    }

    TreeIterator iter_find(const key_type& key, Node<value_type>*& curr_node,
                           Node<value_type>*& tree_root) {
      if (!curr_node) {
        return TreeIterator(push_right_branch(tree_root));
      }
      if (key > curr_node->key) {
        return iter_find(key, curr_node->right,
                         tree_root);  // рекурсивный поиск в правом поддереве
      }
      if (key < curr_node->key) {
        return iter_find(key, curr_node->left,
                         tree_root);  // рекурсивный поиск в левом поддереве
      }
      if (key == curr_node->key) {
        return TreeIterator(
            curr_node);  // возвращает итератор, указывающий на текущий узел
      }
      // std::cout << "here!\n";
      return TreeIterator(curr_node);
    }

    TreeIterator _first_big_or_equal(Node<value_type>* curr_node,
                                     const key_type& key,
                                     Node<value_type>*& tree_root) {
      Node<value_type>* result = nullptr;
      while (curr_node) {
        if (curr_node->key >= key) {
          result = curr_node;
          if (curr_node->left) {
            if (curr_node->left->key >= key) {
              curr_node = curr_node->left;
            } else {
              return TreeIterator(result, tree_root);
            }
          } else {
            break;
          }
        } else {
          if (curr_node->right) {
            curr_node = curr_node->right;
          } else {
            result = curr_node;
            break;
          }
        }
      }
      return TreeIterator(result);
    }

    TreeIterator _first_big(Node<value_type>* curr_node, const key_type& key,
                            Node<value_type>*& tree_root) {
      Node<value_type>* result = nullptr;
      while (curr_node) {
        if (curr_node->key > key) {
          result = curr_node;
          return TreeIterator(result, tree_root);
        } else {
          result = curr_node;
          curr_node = curr_node->right;
        }
      }
      return TreeIterator(result, tree_root);
    }
  };

  using iterator = typename s21::AVLTree<key_type, value_type>::TreeIterator;

  iterator find_tree(const key_type& key) {
    auto it = TreeIterator(this->root);
    iterator res = it.iter_find(key, root, root);
    return res;
  }

  iterator begin() {
    Node<value_type>* current = root;
    while (current && current->left) {
      current = current->left;
    }
    return iterator(current);
  }

  iterator end() {
    Node<value_type>* current = root;
    while (current && current->right) {
      current = current->right;
    }
    return iterator(current);
  }

  std::pair<iterator, bool> insert_unique(key_type key,
                                          value_type value = value_type()) {
    root = insert_node_unique(root, key, value);
    iterator it = find_tree(key);
    if (root == nullptr) {
      return {it, false};
    } else {
      return {it, true};
    }
  }

  // value_type& insert(key_type key, value_type value = value_type()) {
  std::pair<iterator, bool> insert(key_type key,
                                   value_type value = value_type()) {
    root = insert_node(root, key, value);
    // iterator it = find_tree_no_unique(key);
    iterator it = find_tree(key);
    if (root == nullptr) {
      return {it, false};
    } else {
      return {it, true};
    }
  }

  reference get_node_at(const key_type& key) { return _get_node_at(root, key); }

  std::pair<iterator, bool> insert_or_assign(const key_type& key,
                                             const value_type& obj) {
    root = insert_node_unique_or_assign(root, key, obj);
    iterator it = find_tree(key);
    if (root == nullptr) {
      return {it, false};
    } else {
      return {it, true};
    }
  }

  reference get_node_and_insert(const key_type& key) {
    return _get_node_and_insert(root, key);
  }

  // ------- equal_range, lower_bound, upper_bound -------

  iterator first_big_or_equal(const key_type& key) {
    auto it = TreeIterator(this->root);
    return it._first_big_or_equal(root, key, root);
  }

  iterator first_big(const key_type& key) {
    auto it = TreeIterator(this->root);
    return it._first_big(root, key, root);
  }

 private:
  Node<value_type>* insert_node_unique(Node<value_type>* target, key_type key,
                                       value_type value) {
    if (!target) {
      size_of_tree++;
      return new Node<value_type>(key, value);
    }
    if (key < target->key) {
      target->left = insert_node_unique(target->left, key, value);
    }
    if (key > target->key) {
      target->right = insert_node_unique(target->right, key, value);
    }
    if (key == target->key) {
      // return nullptr; до изменений была просто это строка!
    }
    return rebalance(target);
  }
  Node<value_type>* insert_node_unique_or_assign(Node<value_type>* target,
                                                 key_type key,
                                                 const value_type& value) {
    if (!target) {
      size_of_tree++;
      return new Node<value_type>(key, value);
    }
    if (key < target->key) {
      target->left = insert_node_unique_or_assign(target->left, key, value);
    }
    if (key > target->key) {
      target->right = insert_node_unique_or_assign(target->right, key, value);
    }
    if (key == target->key) {
      target->value = value;
    }
    return rebalance(target);
  }

  Node<value_type>* insert_node(Node<value_type>* target, key_type key,
                                value_type value) {
    if (!target) {
      size_of_tree++;
      return new Node<value_type>(key, value);
    }
    if (key < target->key) {
      target->left = insert_node(target->left, key, value);
    } else {
      target->right = insert_node(target->right, key, value);
    }
    return rebalance(target);
  }

  reference _get_node_at(Node<value_type>* target, const key_type& key) {
    if (!target) {
      throw std::out_of_range("Key not found");
    }
    if (target->key == key) {
      return target->value;
    } else if (target->key < key) {
      return _get_node_at(target->right, key);
    } else {
      return _get_node_at(target->left, key);
    }
  }

  reference _get_node_and_insert(Node<value_type>* target, key_type key) {
    if (!target) {
      throw std::out_of_range("Key not found");
    }
    if (key < target->key) {
      target->left = _get_node_and_insert(target->left, key);
    }
    if (key > target->key) {
      target->right = _get_node_and_insert(target->right, key);
    }
    if (key == target->key) {
      return target->value;
    }
    return rebalance(target);
  }

 public:
  template <typename... Args>
  vector<std::pair<iterator, bool>> insert_many(Args&&... args) {
    vector<std::pair<iterator, bool>> result;
    stack temp_stack{std::forward<Args>(args)...};

    while (!temp_stack.empty()) {
      std::pair<iterator, bool> temp =
          insert(temp_stack.top(), temp_stack.top());
      // result.push_back(temp);
      temp_stack.pop();
    }

    return result;
  }
};

};  // namespace s21

#endif  // _S21_AVL_H_
