#ifndef AVLTREE_H
#define AVLTREE_H

#include <cstddef>
#include <iostream>

namespace s21 {
template <typename T, typename V>
class Node {
 public:
  mutable T key;
  int height;
  size_t size_;

  Node<T, V>* left;
  Node<T, V>* right;
  Node<T, V>* parent;

  Node(T& k)
      : key(k),
        height(1),
        size_(1),
        left(nullptr),
        right(nullptr),
        parent(nullptr) {}

  Node(const T& k)
      : key(k),
        height(1),
        size_(1),
        left(nullptr),
        right(nullptr),
        parent(nullptr) {}
};

template <typename T, typename V>
class AVLTree {
 public:
  AVLTree();
  AVLTree(const AVLTree& other);
  ~AVLTree();
  AVLTree<T, V>& operator=(AVLTree&& other) noexcept;

  Node<T, V>* Insert(T key);
  void Remove(T key);
  Node<T, V>* Search(T key);
  void Swap(AVLTree<T, V>& other);
  void Clear(Node<T, V>* node);

  Node<T, V>* GetRoot() const;
  Node<T, V>* GetNil();
  bool GetInserted();
  void SetRoot(Node<T, V>* root);
  Node<T, V>* MaxKey(Node<T, V>* node);

 private:
  Node<T, V>* root;
  Node<T, V>* nil;
  bool inserted;

  int Size(Node<T, V>* node);
  int Height(Node<T, V>* node);
  void UpdateSize(Node<T, V>* node);
  int BalanceFactor(Node<T, V>* node);
  void UpdateHeight(Node<T, V>* node);

  Node<T, V>* Balance(Node<T, V>* node);
  Node<T, V>* CopyTree(Node<T, V>* node);
  Node<T, V>* RotateLeft(Node<T, V>* node);
  Node<T, V>* RotateRight(Node<T, V>* node);

  Node<T, V>* Search(Node<T, V>* node, T key);
  Node<T, V>* FindMin(Node<T, V>* node);

  Node<T, V>* Insert(Node<T, V>* node, T key, Node<T, V>* parent);
  Node<T, V>* Remove(Node<T, V>* node, T key);
  Node<T, V>* RemoveMin(Node<T, V>* node);
};

template <typename T, typename V>
class Iterator {
 public:
  using key_type = T;
  using reference = T&;
  using const_reference = const reference;
  using pointer = T*;

  Iterator(Node<T, V>* node = nullptr) : node_(node) {}
  Iterator(Node<T, V>* nil, Node<T, V>* root) : node_(nil), root_(root) {}
  Iterator(const Iterator&) = default;
  Iterator& operator=(const Iterator&) = default;
  ~Iterator() = default;

  Iterator operator+(const size_t value);
  Iterator& operator++();
  Iterator operator++(int);
  Iterator& operator--();
  Iterator operator--(int);

  bool operator==(const Iterator& other) const { return node_ == other.node_; }
  bool operator!=(const Iterator& other) const { return node_ != other.node_; }

  reference operator*();
  pointer operator->() const { return &node_->key; }

  int Size(Node<T, V>* node) { return node ? node->size_ : 0; }
  Node<T, V>* MaxKey(Node<T, V>* node);
  Iterator& OperatorHelper();

 protected:
  Node<T, V>* node_;
  Node<T, V>* root_;
};

template <typename T, typename V>
class ConstIterator : public Iterator<const T, const V> {
 public:
  using Iterator<const T, const V>::Iterator;
  using typename Iterator<const T, const V>::key_type;
  using typename Iterator<const T, const V>::reference;
  using typename Iterator<const T, const V>::const_reference;
  using typename Iterator<const T, const V>::pointer;
};

}  // namespace s21

#endif  // AVLTREE_H