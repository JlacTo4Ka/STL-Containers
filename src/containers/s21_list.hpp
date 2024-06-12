#ifndef _S21_LIST_H_
#define _S21_LIST_H_

#include <exception>
#include <iostream>
#include <memory>

#include "s21_stack.hpp"

#define MAX_SIZE_VALUE 384307168202282325

namespace s21 {
// template <class T, class Allocator = std::allocator<T>>
template <class T>
class List {
 public:
  using value_type = T;
  using size_type = size_t;

 private:
  template <class value_type>
  class Node {
   public:
    value_type data;
    Node *prev;
    Node *next;

    Node(value_type data = value_type(), Node *next = nullptr,
         Node *prev = nullptr) {
      this->data = data;
      this->next = next;
      this->prev = prev;
    }

    Node(const Node<value_type> &other) {
      this->data = other.data;
      this->next = other.next;
      this->prev = other.prev;
    }
  };

  Node<value_type> *head;
  Node<value_type> *tail;
  size_type size_list;

 public:
  using reference = T &;
  using const_reference = const T &;
  // using allocator_type = Allocator;

  List();
  List(size_type n);
  List(std::initializer_list<value_type> const &items);
  List(const List<value_type> &old_list);
  List(List<value_type> &&l);

  ~List() {
    Node<value_type> *curr = head;

    while (curr != nullptr) {
      Node<value_type> *temp = curr;
      curr = curr->next;
      delete temp;
    }
    delete curr;
  }

  // мой метод
  void print_list();

  void operator=(List<value_type> &&l);

  const_reference front();
  const_reference back();

  bool empty();
  size_type size();
  size_type max_size();

  void clear();
  void push_back(const_reference value);
  void pop_back();
  void push_front(const_reference value);
  void pop_front();
  void swap(List<value_type> &other);  // -
  // void merge(List<value_type> &other);  // -
  void reverse();
  void unique();  // -
  void sort();    // -

  void merge(List<value_type> &other) {
    for (auto it = other.begin(); it != other.end(); ++it) {
      push_back(*it);
    }
  }

  // void megre_sort(size_type start, size_type end);
  // void res_sort(size_type start, size_type end);

  class ListIterator {
   private:
    friend class List<value_type>;
    Node<value_type> *curr;

   public:
    ListIterator(Node<value_type> *cur_node = nullptr) : curr(cur_node) {}

    reference operator*() { return this->curr->data; }

    ListIterator operator++(int) {
      curr = curr->next;
      return *this;
    }

    ListIterator operator--(int) {
      curr = curr->prev;
      return *this;
    }

    ListIterator &operator++() {
      curr = curr->next;
      return *this;
    }

    ListIterator &operator--() {
      curr = curr->prev;
      return *this;
    }

    ListIterator operator+(const size_type value) {
      Node<value_type> *tmp = curr;
      for (size_type i = 0; i < value; i++) {
        if (tmp) {
          tmp = tmp->next;
        } else {
          throw std::out_of_range("Incorrect input, index is out of range");
        }
      }

      ListIterator res(tmp);
      return res;
    }

    reference operator-(int shift) {
      int count = shift;
      while (curr != nullptr && count != 0) {
        curr = curr->prev;
        count--;
      }

      if (count != 0)
        throw std::out_of_range("Incorrect input, index is out of range");

      return curr->data;
    }

    bool operator==(const ListIterator &other) {
      return this->curr->data == other.curr->data;
    }

    bool operator!=(const ListIterator &other) {
      return this->curr->data != other.curr->data;
    }

    void print_Node() { std::cout << this->curr->data << '\n'; }
  };

  class ListConstIterator : public s21::List<value_type>::ListIterator {
   public:
    ListConstIterator(s21::List<value_type>::ListIterator other)
        : s21::List<value_type>::ListIterator(other) {}
    const T &operator*() {
      return s21::List<value_type>::ListIterator::operator*();
    }
  };

  using iterator = s21::List<value_type>::ListIterator;
  using const_iterator = s21::List<value_type>::ListConstIterator;
  iterator begin();
  iterator end();  // исправить!

  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void splice(const_iterator pos, List<value_type> &other);  // -

  // для сортировки
  void swap_elem(iterator a, iterator b);

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args &&...args) {
    List args_list = {args...};
    for (auto it = args_list.begin(); it != args_list.end(); ++it) {
      this->insert(pos, *it);
      ++pos;
    }

    return pos;
  }

  template <typename... Args>
  void insert_many_back(Args &&...args) {
    List args_list = {args...};
    for (auto it = args_list.begin(); it != args_list.end(); ++it) {
      this->push_back(*it);
    }
  }

  template <typename... Args>
  void insert_many_front(Args &&...args) {
    stack args_list = {args...};
    size_type s = args_list.size();
    for (size_type i = 0; i < s; i++) {
      this->push_front(args_list.top());
      args_list.pop();
    }
  }
};

};  // namespace s21

// ---------------- конструкторы и деструктор ----------------

// template <typename value_type, class Allocator>
template <typename value_type>
s21::List<value_type>::List() : head(nullptr), tail(nullptr), size_list(0) {}

template <typename value_type>
s21::List<value_type>::List(size_t n)
    : head(nullptr), tail(nullptr), size_list(0) {
  if (n >= max_size()) {
    throw std::out_of_range("Limit of the container is exceeded");
  }

  if (n > 0) {
    size_list = n;
    head = new Node<value_type>();
    Node<value_type> *curr_head = head;
    // head = curr_head;
    size_type count = 1;

    while (count < size_list) {
      Node<value_type> *new_node = new Node<value_type>();
      new_node->prev = curr_head;
      curr_head->next = new_node;

      curr_head = new_node;
      tail = curr_head;
      count++;
    }
  } else {
    throw std::out_of_range("Incorrect input, index is out of range");
  }
}

template <typename value_type>
s21::List<value_type>::List(const List<value_type> &old_list)
    : head(nullptr), tail(nullptr), size_list(old_list.size_list) {
  if (this->size_list > 0) {
    Node<value_type> *curr_of_old = old_list.head;
    Node<value_type> *curr_of_new = new Node<value_type>(curr_of_old->data);
    this->head = curr_of_new;

    while (curr_of_old->next != nullptr) {
      curr_of_old = curr_of_old->next;
      Node<value_type> *new_node =
          new Node<value_type>(curr_of_old->data, nullptr, curr_of_new);
      curr_of_new->next = new_node;
      curr_of_new = new_node;
    }

    this->tail = curr_of_new;
  }
}

template <typename value_type>
s21::List<value_type>::List(List<value_type> &&l) {
  if (l.head != nullptr) {
    Node<value_type> *curr_old = l.head;
    this->head =
        new Node<value_type>(curr_old->data, curr_old->next, curr_old->prev);
    Node<value_type> *curr_new = head;

    while (curr_old->next != nullptr) {
      curr_old = curr_old->next;
      Node<value_type> *new_node =
          new Node<value_type>(curr_old->data, curr_old->next, curr_old->prev);
      curr_new->next = new_node;
      new_node->prev = curr_new;
      curr_new = new_node;
    }

    this->tail = curr_old;
    this->size_list = l.size_list;

    l.head = nullptr;
    l.tail = nullptr;
    l.size_list = 0;
  } else {
    throw std::out_of_range("Incorrect input, index is out of range");
  }
}

template <typename value_type>
s21::List<value_type>::List(std::initializer_list<value_type> const &items)
    : head(nullptr), tail(nullptr), size_list(items.size()) {
  auto it = items.begin();
  head = new Node<value_type>(*it++);
  Node<value_type> *curr = head;

  while (it != items.end()) {
    Node<value_type> *new_node = new Node<value_type>(*it);
    curr->next = new_node;
    new_node->prev = curr;
    curr = new_node;
    ++it;
  }

  tail = curr;
}

// template <typename value_type>
// s21::List<value_type>::~List() {
//     Node<value_type> *curr = head;

//     while (curr != nullptr) {
//         Node<value_type> *temp = curr;
//         curr = curr->next;
//         delete temp;
//     }
// }

// ---------------- operators ----------------

template <typename value_type>
void s21::List<value_type>::operator=(List<value_type> &&l) {
  if (l.head != nullptr) {
    Node<value_type> *curr_old = l.head;
    this->head =
        new Node<value_type>(curr_old->data, curr_old->next, curr_old->prev);
    Node<value_type> *curr_new = head;

    while (curr_old->next != nullptr) {
      curr_old = curr_old->next;
      Node<value_type> *new_node =
          new Node<value_type>(curr_old->data, curr_old->next, curr_old->prev);
      curr_new->next = new_node;
      curr_new = new_node;
    }

    this->tail = curr_old;
    this->size_list = l.size_list;

  } else {
    throw std::out_of_range("Incorrect input, index is out of range");
  }
}

// ---------------- front() and back() ----------------

template <typename value_type>
typename s21::List<value_type>::const_reference s21::List<value_type>::front() {
  if (head != nullptr) {
    return head->data;
  } else {
    throw std::out_of_range("List is empty");
  }
}

template <typename value_type>
typename s21::List<value_type>::const_reference s21::List<value_type>::back() {
  if (head != nullptr) {
    return tail->data;
  } else {
    throw std::out_of_range("List is empty");
  }
}

// ---------------- begin() and end() ----------------

template <typename value_type>
typename s21::List<value_type>::iterator s21::List<value_type>::begin() {
  return iterator(head);
}

template <typename value_type>
typename s21::List<value_type>::iterator s21::List<value_type>::end() {
  Node<value_type> *past_the_last =
      new Node<value_type>(value_type(), nullptr, tail);
  tail->next = past_the_last;
  return iterator(past_the_last);
}

// ---------------- iterators methods ----------------

template <typename value_type>
typename s21::List<value_type>::iterator s21::List<value_type>::insert(
    iterator pos, const_reference value) {
  if (pos.curr != nullptr) {
    Node<value_type> *next_node = pos.curr->next;
    pos.curr->next = new Node<value_type>(value, next_node, pos.curr);
    size_list++;
  } else {
    throw "There is no elem at this position";
  }

  return pos.curr->next;
}

template <typename value_type>
void s21::List<value_type>::erase(iterator pos) {
  // if (pos.curr != nullptr) {
  //   pos.curr->prev->next = pos.curr->next;
  //   size_list--;

  //   delete pos.curr;
  // } else {
  //   throw "There is no elem at this position";
  // }
  if (!head || !pos.curr) {
    throw std::runtime_error(
        "Trying to erase from an empty list or using an invalid iterator");
  }

  if (pos.curr == head) {
    head = head->next;
    if (head) head->prev = nullptr;
  } else {
    pos.curr->prev->next = pos.curr->next;
    if (pos.curr->next) pos.curr->next->prev = pos.curr->prev;
  }

  delete pos.curr;
  size_list--;
}

template <typename value_type>
void s21::List<value_type>::splice(const_iterator pos,
                                   List<value_type> &other) {
  if (this == &other) {
    throw "this container = other";
  }

  if (!other.empty()) {
    Node<value_type> *curr_tail = other.tail;
    Node<value_type> *curr_head = other.head;

    Node<value_type> *curr_node = pos.curr;
    Node<value_type> *next_node = curr_node->next;

    curr_node->next = curr_head;
    curr_head->prev = curr_node;

    next_node->prev = curr_tail;
    curr_tail->next = next_node;

    this->size_list += other.size_list;

    other.size_list = 0;

    other.tail = nullptr;
    other.head = nullptr;

  } else {
    throw "Other container is empty!\n";
  }
}

// ---------------- all about size ----------------

template <typename value_type>
bool s21::List<value_type>::empty() {
  if (head == nullptr)
    return true;
  else
    return false;
}

template <typename value_type>
typename s21::List<value_type>::size_type s21::List<value_type>::size() {
  return size_list;
}

template <typename value_type>
typename s21::List<value_type>::size_type s21::List<value_type>::max_size() {
  return MAX_SIZE_VALUE;
}

// ---------------- all methods ----------------

template <typename value_type>
void s21::List<value_type>::clear() {
  Node<value_type> *curr_node = head;
  Node<value_type> *next_node = nullptr;

  while (curr_node != nullptr) {
    next_node = curr_node->next;
    delete curr_node;
    curr_node = next_node;
  }

  head = nullptr;
  tail->next = nullptr;
  tail = nullptr;
  size_list = 0;
}

template <typename value_type>
void s21::List<value_type>::push_back(const_reference value) {
  if (head == nullptr) {
    head = new Node<value_type>(value);
    tail = head;
  } else {
    Node<value_type> *curr = tail;
    tail = new Node<value_type>(value, nullptr, curr);
    curr->next = tail;
  }
  size_list++;
}

template <typename value_type>
void s21::List<value_type>::pop_back() {
  if (head == nullptr) {
    throw std::out_of_range("List is empty");
  } else {
    if (size_list == 1) {
      delete head;
      head = nullptr;
      tail = nullptr;
      size_list = 0;
    } else {
      Node<value_type> *prev_node = tail->prev;
      prev_node->next = nullptr;
      delete tail;
      tail = prev_node;
      size_list--;
    }
  }
}

template <typename value_type>
void s21::List<value_type>::push_front(const_reference value) {
  if (head == nullptr) {
    head = new Node<value_type>(value);
    tail = head;
  } else {
    Node<value_type> *head_next = head;
    head = new Node<value_type>(value, head_next, nullptr);
    head_next->prev = head;
  }
  size_list++;
}

template <typename value_type>
void s21::List<value_type>::pop_front() {
  if (head == nullptr) {
    throw std::out_of_range("List is empty");
  } else {
    if (size_list == 1) {
      delete head;
      head = nullptr;
      tail = nullptr;
    } else {
      Node<value_type> *new_head = head->next;
      new_head->prev = nullptr;
      delete head;
      head = new_head;
    }
    size_list--;
  }
}

template <typename value_type>
void s21::List<value_type>::swap(List<value_type> &other) {  // leaks
  if (this != &other) std::swap(*this, other);
}

template <typename value_type>
void s21::List<value_type>::reverse() {
  Node<value_type> *curr = head;
  Node<value_type> *temp = nullptr;
  tail = curr;

  while (curr != nullptr) {
    temp = curr->prev;
    curr->prev = curr->next;
    curr->next = temp;
    curr = curr->prev;
  }

  if (temp != nullptr) {
    head = temp->prev;
  }
}

template <typename value_type>
void s21::List<value_type>::sort() {
  List<value_type> copied = *this;
  clear();
  size_type size = copied.size();
  // for (auto it = copied.begin(); it != copied.end(); ++it) {
  //   value_type min = copied.front();
  //   auto it_min = it;
  //   for (auto it2 = copied.begin(); it2 != copied.end(); ++it2) {
  //     if (*it < min) {
  //       min = *it;
  //       it_min = it;
  //     }
  //   }
  //   push_back(min);
  //   copied.erase(it_min);
  // }
  for (size_type i = 0; i < size; i++) {
    value_type min = copied.front();
    auto it_min = copied.begin();
    for (auto it = copied.begin(); it != copied.end(); ++it) {
      if (*it < min) {
        min = *it;
        it_min = it;
      }
    }
    push_back(min);
    copied.erase(it_min);
  }
}

template <typename value_type>
void s21::List<value_type>::swap_elem(iterator a, iterator b) {
  Node<value_type> *tmp_node = a.curr;

  if (b.curr->next != nullptr) {
    a.curr->prev = b.curr->prev;
  }
  b.curr->prev->next = a.curr;
  a.curr->next = b.curr->next;
  if (b.curr->next != nullptr) {
    b.curr->next->prev = a.curr;
  }

  b.curr->prev = tmp_node->prev;
  if (tmp_node->prev != nullptr) {
    tmp_node->prev->next = b.curr;
  }
  if (b.curr->next != nullptr) {
    b.curr->next = tmp_node->next;
    tmp_node->next->prev = b.curr;
  }
}

template <typename value_type>
void s21::List<value_type>::unique() {
  for (auto it = this->begin(); it != this->end(); ++it) {
    for (auto next_it = it + 1; next_it != this->end();) {
      if (*it == *next_it) {
        this->erase(next_it);
      } else {
        ++next_it;
      }
    }
  }
  // this->erase(this->end());
}

// ---------------- helpers ----------------

template <typename value_type>
void s21::List<value_type>::print_list() {
  Node<value_type> *curr_head = head;

  for (auto i = 0; i < (int)size_list; i++) {
    if (curr_head != nullptr) {
      std::cout << curr_head->data << ' ';
      curr_head = curr_head->next;
    }
  }
  std::cout << '\n';
}

#endif