#include "AVLTree.hpp"

namespace s21 {
template <typename T, typename V>
AVLTree<T, V>::AVLTree() : root(nullptr), nil(nullptr), inserted(false) {}

template <typename T, typename V>
AVLTree<T, V>::AVLTree(const AVLTree& other)
    : root(CopyTree(other.GetRoot())) {}

template <typename T, typename V>
AVLTree<T, V>& AVLTree<T, V>::operator=(AVLTree&& other) noexcept {
  if (this != &other) {
    Clear(root);
    root = exchange(other.root, nullptr);
  }

  return *this;
}

template <typename T, typename V>
AVLTree<T, V>::~AVLTree() {
  Clear(root);
}

template <typename T, typename V>
int AVLTree<T, V>::Height(Node<T, V>* node) {
  if (!node) return 0;
  return node->height;
}

template <typename T, typename V>
int AVLTree<T, V>::BalanceFactor(Node<T, V>* node) {
  if (!node) return 0;
  return Height(node->left) - Height(node->right);
}

template <typename T, typename V>
void AVLTree<T, V>::UpdateHeight(Node<T, V>* node) {
  int hl = Height(node->left);
  int hr = Height(node->right);
  node->height = (hl > hr ? hl : hr) + 1;
}

template <typename T, typename V>
Node<T, V>* AVLTree<T, V>::RotateRight(Node<T, V>* node) {
  Node<T, V>* newRoot = node->left;
  node->left = newRoot->right;
  if (newRoot->right) newRoot->right->parent = node;

  newRoot->right = node;
  newRoot->parent = node->parent;
  node->parent = newRoot;

  UpdateHeight(newRoot);
  UpdateHeight(node);

  return newRoot;
}

template <typename T, typename V>
Node<T, V>* AVLTree<T, V>::RotateLeft(Node<T, V>* node) {
  Node<T, V>* newRoot = node->right;
  node->right = newRoot->left;
  if (newRoot->left) newRoot->left->parent = node;

  newRoot->left = node;
  newRoot->parent = node->parent;
  node->parent = newRoot;

  UpdateHeight(newRoot);
  UpdateHeight(node);

  return newRoot;
}

template <typename T, typename V>
Node<T, V>* AVLTree<T, V>::Balance(Node<T, V>* node) {
  UpdateHeight(node);

  if (BalanceFactor(node) == 2) {
    if (BalanceFactor(node->right) < -1) {
      node->left = RotateLeft(node->left);
      UpdateSize(node->left);
    }
    node = RotateRight(node);
    UpdateSize(node);
  }

  if (BalanceFactor(node) == -2) {
    if (BalanceFactor(node->left) > 1) {
      node->right = RotateRight(node->right);
      UpdateSize(node->right);
    }

    node = RotateLeft(node);
    UpdateSize(node);
  }

  UpdateSize(node);
  return node;
}

template <typename T, typename V>
Node<T, V>* AVLTree<T, V>::Insert(Node<T, V>* node, T key, Node<T, V>* parent) {
  this->inserted = false;

  if (!node) {
    node = new Node<T, V>(key);
    node->parent = parent;
    this->inserted = true;

    return Balance(node);
  }

  if (key < node->key) {
    node->left = Insert(node->left, key, node);
  } else if (key > node->key) {
    node->right = Insert(node->right, key, node);
  } else {
    this->inserted = false;
  }

  return Balance(node);
}

template <typename T, typename V>
Node<T, V>* AVLTree<T, V>::FindMin(Node<T, V>* node) {
  if (!node->left) return node;
  return FindMin(node->left);
}

template <typename T, typename V>
Node<T, V>* AVLTree<T, V>::RemoveMin(Node<T, V>* node) {
  if (!node->left) return node->right;
  node->left = RemoveMin(node->left);
  return Balance(node);
}

template <typename T, typename V>
Node<T, V>* AVLTree<T, V>::Remove(Node<T, V>* node, T key) {
  if (!node) return nullptr;

  if (key < node->key) {
    node->left = Remove(node->left, key);
  } else if (key > node->key) {
    node->right = Remove(node->right, key);
  } else {
    Node<T, V>* left = node->left;
    Node<T, V>* right = node->right;
    delete node;

    if (!right) return left;
    if (!left) return right;

    Node<T, V>* min = FindMin(right);
    min->right = RemoveMin(right);

    min->left = left;
    min->size_--;
    min->parent = node->parent;

    UpdateHeight(min);
    return Balance(min);
  }

  node->size_--;
  UpdateHeight(node);
  return Balance(node);
}

template <typename T, typename V>
void AVLTree<T, V>::Clear(Node<T, V>* node) {
  if (node != nullptr) {
    Clear(node->left);
    Clear(node->right);
    delete node;
  }
  root = nullptr;
}

template <typename T, typename V>
Node<T, V>* AVLTree<T, V>::Search(Node<T, V>* node, T key) {
  if (!node || node->key == key) {
    return node;
  }

  if (key < node->key) {
    return Search(node->left, key);
  } else {
    return Search(node->right, key);
  }
}

template <typename T, typename V>
void AVLTree<T, V>::SetRoot(Node<T, V>* root) {
  this->root = root;

  if (this->root != nullptr) {
    this->root->parent = nullptr;
  }
}

template <typename T, typename V>
void AVLTree<T, V>::UpdateSize(Node<T, V>* node) {
  if (node) {
    node->size_ = Size(node->left) + Size(node->right) + 1;
    UpdateSize(node->left);
    UpdateSize(node->right);
  }
}

template <typename T, typename V>
int AVLTree<T, V>::Size(Node<T, V>* node) {
  if (node) return node->size_;

  return 0;
}

template <typename T, typename V>
Node<T, V>* AVLTree<T, V>::Insert(T key) {
  root = Insert(root, key, nullptr);
  return root;
}

template <typename T, typename V>
void AVLTree<T, V>::Remove(T key) {
  root = Remove(root, key);
}

template <typename T, typename V>
Node<T, V>* AVLTree<T, V>::Search(T key) {
  return Search(root, key);
}

template <typename T, typename V>
Node<T, V>* AVLTree<T, V>::GetRoot() const {
  return this->root;
}

template <typename T, typename V>
void AVLTree<T, V>::Swap(AVLTree<T, V>& other) {
  std::swap(root, other.root);
}

template <typename T, typename V>
bool AVLTree<T, V>::GetInserted() {
  return inserted;
}

template <typename T, typename V>
Node<T, V>* AVLTree<T, V>::CopyTree(Node<T, V>* node) {
  if (node == nullptr) return nullptr;

  Node<T, V>* new_node = new Node<T, V>(node->key);
  new_node->size_ = node->size_;
  new_node->left = CopyTree(node->left);
  new_node->right = CopyTree(node->right);
  new_node->parent = node->parent;

  return new_node;
}

template <typename T, typename V>
Node<T, V>* AVLTree<T, V>::MaxKey(Node<T, V>* node) {
  if (node != nullptr) {
    while (node->right != nullptr) {
      return this->MaxKey(node->right);
    }
    return node;
  }

  return nullptr;
}

template <typename T, typename V>
Iterator<T, V> Iterator<T, V>::operator+(const size_t value) {
  Iterator tmp = *this;
  for (size_t i = 0; i < value; i++) {
    ++tmp;
  }

  return tmp;
}

template <typename T, typename V>
Iterator<T, V>& Iterator<T, V>::operator++() {
  if (node_ != nullptr) {
    if (node_->right != nullptr) {
      node_ = node_->right;
      while (node_->left != nullptr) {
        node_ = node_->left;
      }
    } else {
      Node<T, V>* parent = node_->parent;
      while (parent != nullptr && node_ == parent->right) {
        node_ = parent;
        parent = parent->parent;
      }
      node_ = parent;
    }
    return *this;
  }

  return *this;
}

template <typename T, typename V>
Iterator<T, V> Iterator<T, V>::operator++(int) {
  Iterator tmp = *this;
  ++(*this);
  return tmp;
}

template <typename T, typename V>
Iterator<T, V>& Iterator<T, V>::operator--() {
  if (Size(root_) > 0) {
    if (node_ != nullptr) {
      return OperatorHelper();
    }
    node_ = MaxKey(root_);
    return *this;
  }

  return OperatorHelper();
}

template <typename T, typename V>
Iterator<T, V> Iterator<T, V>::operator--(int) {
  Iterator tmp = *this;
  --(*this);
  return tmp;
}

template <typename T, typename V>
T& Iterator<T, V>::operator*() {
  if (node_ == nullptr) {
    static T default_value = T{};
    return default_value;
  }

  return node_->key;
}

template <typename T, typename V>
Node<T, V>* Iterator<T, V>::MaxKey(Node<T, V>* node) {
  if (node != nullptr) {
    while (node->right != nullptr) {
      this->MaxKey(node->right);
    }
    return node;
  }
  return nullptr;
}

template <typename T, typename V>
Iterator<T, V>& Iterator<T, V>::OperatorHelper() {
  if (node_ != nullptr) {
    if (node_->left != nullptr) {
      node_ = node_->left;

      while (node_->right) {
        node_ = node_->right;
      }
    } else {
      Node<T, V>* parent = node_->parent;
      while (parent != nullptr && node_ == parent->left) {
        node_ = parent;
        parent = parent->parent;
      }
      node_ = parent;
    }
    return *this;
  }

  return *this;
}

}  // namespace s21
