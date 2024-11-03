#ifndef S21_CONTAINERS_LIST_H
#define S21_CONTAINERS_LIST_H

#include <iostream>
#include <limits>

namespace s21 {
template <typename T>
class list {
 public:
  // member type
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  class ListIterator;
  using iterator = ListIterator;
  class ListConstIterator;
  using const_iterator = ListConstIterator;
  using size_type = size_t;

  // functions
  list();
  list(size_type n);
  list(std::initializer_list<value_type> const& items);
  list(const list& l);
  list(list&& l);
  ~list();
  list& operator=(list&& l);

  // element access
  const_reference front();
  const_reference back();

  // iterators
  iterator begin();
  const_iterator cbegin() const;
  iterator end();
  const_iterator cend() const;

  // capacity
  bool empty();
  size_type size();
  size_type max_size();

  // modifiers
  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void push_front(const_reference value);
  void pop_front();
  void swap(list& other);
  void merge(list& other);
  void splice(iterator pos, list& other);
  void reverse();
  void unique();
  void sort();

  // insert_many
  template <typename... Args>
  iterator insert_many(const_iterator pos, Args&&... args);
  template <typename... Args>
  void insert_many_back(Args&&... args);
  template <typename... Args>
  void insert_many_front(Args&&... args);

 private:
  struct Node {
    value_type data_;
    Node* prev_;
    Node* next_;
    Node(const_reference value)
        : data_(value), prev_(nullptr), next_(nullptr) {}
  };
  Node* front_;
  Node* back_;
  size_type size_;
};

template <typename T>
class list<T>::ListIterator {
 public:
  // member type
  using value_type = T;
  using reference = T&;
  using pointer = T*;
  using difference_type = std::ptrdiff_t;
  using iterator_category = std::forward_iterator_tag;

  // constructor
  ListIterator(typename list<T>::Node* node) : node_(node) {}

  // operators
  reference operator*() const { return node_->data_; }

  ListIterator& operator++() {
    node_ = node_->next_;
    return *this;
  }

  ListIterator operator++(int) {
    ListIterator temp = *this;
    ++(*this);
    return temp;
  }

  bool operator==(const ListIterator& other) const {
    return node_ == other.node_;
  }

  bool operator!=(const ListIterator& other) const { return !(*this == other); }

  typename list<T>::Node* getNode() { return node_; }

 private:
  typename list<T>::Node* node_;
};

template <typename T>
class list<T>::ListConstIterator {
 public:
  // member type
  using value_type = T;
  using reference = const T&;
  using pointer = const T*;
  using difference_type = std::ptrdiff_t;
  using iterator_category = std::forward_iterator_tag;

  // constructor
  ListConstIterator(const typename list<T>::Node* node) : node_(node) {}

  // operators
  reference operator*() const { return node_->data_; }

  ListConstIterator& operator++() {
    node_ = node_->next_;
    return *this;
  }

  ListConstIterator operator++(int) {
    ListConstIterator temp = *this;
    ++(*this);
    return temp;
  }

  bool operator==(const ListConstIterator& other) const {
    return node_ == other.node_;
  }

  bool operator!=(const ListConstIterator& other) const {
    return !(*this == other);
  }

  const typename list<T>::Node* cgetNode() { return node_; }

 private:
  const typename list<T>::Node* node_;
};
};  // namespace s21

#include "s21_list.tpp"

#endif
