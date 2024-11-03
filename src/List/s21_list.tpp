#ifndef S21_CONTAINERS_LIST_TPP
#define S21_CONTAINERS_LIST_TPP

namespace s21 {

// functions

// Default constructor, initializes an empty list
template <typename T>
list<T>::list() : front_(nullptr), back_(nullptr), size_(0) {}

// Constructor that creates a list with n elements, initialized with the default
// value of T
template <typename T>
list<T>::list(size_type n) : front_(nullptr), back_(nullptr), size_(0) {
  for (size_type i = 0; i < n; ++i) {
    push_back(T());
  }
}

// Constructor that creates a list from an initializer list
template <typename T>
list<T>::list(std::initializer_list<value_type> const &items)
    : front_(nullptr), back_(nullptr), size_(0) {
  for (const auto &item : items) {
    push_back(item);
  }
}

// Copy constructor, creates a new list by copying elements from another list
template <typename T>
list<T>::list(const list &l) : front_(nullptr), back_(nullptr), size_(0) {
  for (auto it = l.cbegin(); it != l.cend(); ++it) {
    push_back(*it);
  }
}

// Move constructor, transfers ownership of elements from one list to another
template <typename T>
list<T>::list(list &&l) : front_(l.front_), back_(l.back_), size_(l.size_) {
  l.front_ = nullptr;
  l.back_ = nullptr;
  l.size_ = 0;
}

// Destructor, deallocates memory used by the list
template <typename T>
list<T>::~list() {
  while (front_ != nullptr) {
    Node *temp = front_;
    front_ = front_->next_;
    delete temp;
  }
  back_ = nullptr;
  size_ = 0;
}

// Move assignment operator, transfers ownership of elements from one list to
// another
template <typename T>
typename list<T>::list &list<T>::operator=(list &&l) {
  if (this != &l) {
    clear();
    front_ = l.front_;
    back_ = l.back_;
    size_ = l.size_;
    l.front_ = nullptr;
    l.back_ = nullptr;
    l.size_ = 0;
  }
  return *this;
}

// element access

// Returns a reference to the first element in the list (const version)
template <typename T>
typename list<T>::const_reference list<T>::front() {
  if (empty()) throw std::out_of_range("List is empty");
  return front_->data_;
}

// Returns a reference to the last element in the list (const version)
template <typename T>
typename list<T>::const_reference list<T>::back() {
  if (empty()) throw std::out_of_range("List is empty");
  return back_->data_;
}

// iterators

// Returns an iterator pointing to the first element in the list
template <typename T>
typename list<T>::iterator list<T>::begin() {
  return iterator(front_);
}

// Returns a const iterator pointing to the first element in the list
template <typename T>
typename list<T>::const_iterator list<T>::cbegin() const {
  return const_iterator(front_);
}

// Returns an iterator pointing to the element after the last element in the
// list
template <typename T>
typename list<T>::iterator list<T>::end() {
  return iterator(back_->next_);
}

// Returns a const iterator pointing to the element after the last element in
// the list
template <typename T>
typename list<T>::const_iterator list<T>::cend() const {
  return const_iterator(back_->next_);
}
// capacity

// Returns true if the list is empty, false otherwise
template <typename T>
bool list<T>::empty() {
  return size_ == 0;
}

// Returns the number of elements in the list
template <typename T>
typename list<T>::size_type list<T>::size() {
  return size_;
}

// Returns the maximum number of elements the list can hold
template <typename T>
typename list<T>::size_type list<T>::max_size() {
  return std::numeric_limits<size_type>::max() / sizeof(value_type);
}

// modifiers

// Removes all elements from the list
template <typename T>
void list<T>::clear() {
  while (front_ != nullptr) {
    Node *temp = front_;
    front_ = front_->next_;
    delete temp;
  }
  back_ = nullptr;
  size_ = 0;
}

// Inserts a new element before the position specified by the iterator
template <typename T>
typename list<T>::iterator list<T>::insert(iterator pos,
                                           const_reference value) {
  Node *node = new Node(value);
  if (pos == begin()) {
    // If inserting at the beginning of the list
    node->next_ = front_;
    if (front_ != nullptr) {
      front_->prev_ = node;
    }
    front_ = node;
    if (back_ == nullptr) {
      back_ = node;
    }
  } else if (pos == end()) {
    // If inserting at the end of the list
    back_->next_ = node;
    node->prev_ = back_;
    back_ = node;
  } else {
    // If inserting in the middle of the list
    Node *current = pos.getNode();
    node->next_ = current;
    node->prev_ = current->prev_;
    current->prev_->next_ = node;
    current->prev_ = node;
  }
  ++size_;
  return iterator(node);
}
// Removes the element at the position specified by the iterator
template <typename T>
void list<T>::erase(iterator pos) {
  Node *node = pos.getNode();
  if (node == nullptr) {
    throw std::out_of_range("Iterator is out of range");
  }
  if (node == front_) {
    // If removing the first element
    front_ = front_->next_;
    if (front_ != nullptr) {
      front_->prev_ = nullptr;
    }
  } else if (node == back_) {
    // If removing the last element
    back_ = back_->prev_;
    back_->next_ = nullptr;
  } else {
    // If removing an element in the middle
    node->prev_->next_ = node->next_;
    node->next_->prev_ = node->prev_;
  }
  delete node;
  --size_;
}

// Adds a new element to the end of the list
template <typename T>
void list<T>::push_back(const_reference value) {
  Node *node = new Node(value);
  if (empty()) {
    front_ = node;
    back_ = node;
  } else {
    node->prev_ = back_;
    back_->next_ = node;
    back_ = node;
  }
  ++size_;
}

// Removes the last element from the list
template <typename T>
void list<T>::pop_back() {
  if (empty()) {
    throw std::out_of_range("List is empty");
  }
  if (front_ == back_) {
    clear();
  } else {
    Node *temp = back_;
    back_ = back_->prev_;
    back_->next_ = nullptr;
    delete temp;
    --size_;
  }
}

// Adds a new element to the beginning of the list
template <typename T>
void list<T>::push_front(const_reference value) {
  Node *node = new Node(value);
  if (empty()) {
    front_ = node;
    back_ = node;
  } else {
    node->next_ = front_;
    front_->prev_ = node;
    front_ = node;
  }
  ++size_;
}

// Removes the first element from the list
template <typename T>
void list<T>::pop_front() {
  if (empty()) {
    throw std::out_of_range("List is empty");
  }
  if (front_ == back_) {
    clear();
  } else {
    erase(begin());
  }
}

// Swaps the contents of the list with another list
template <typename T>
void list<T>::swap(list &other) {
  std::swap(front_, other.front_);
  std::swap(back_, other.back_);
  std::swap(size_, other.size_);
}

// Merges the contents of another list into the current list, preserving the
// sorting order
template <typename T>
void list<T>::merge(list &other) {
  if (this != &other) {
    sort();
    other.sort();
    auto it = begin();
    auto otherIt = other.begin();
    while (otherIt != other.end()) {
      if (it == end() || *otherIt < *it) {
        insert(it, *otherIt);
        ++otherIt;
      } else {
        ++it;
      }
    }
    other.clear();
  }
}

// Inserts the elements of another list before the specified position in the
// current list
template <typename T>
void list<T>::splice(iterator pos, list &other) {
  if (this != &other) {
    for (auto it = other.begin(); it != other.end(); ++it) {
      insert(pos, *it);
    }
    other.clear();
  }
}

// Reverses the order of elements in the list
template <typename T>
void list<T>::reverse() {
  if (size_ > 1) {
    Node *left = front_;
    Node *right = back_;
    while (left != right && left->prev_ != right) {
      std::swap(left->data_, right->data_);
      left = left->next_;
      right = right->prev_;
    }
  }
}

// Removes consecutive duplicate elements from the list
template <typename T>
void list<T>::unique() {
  if (size_ > 1) {
    Node *current = front_->next_;
    Node *prev = front_;
    while (current != nullptr) {
      if (current->data_ == prev->data_) {
        Node *nextNode = current->next_;
        erase(current);
        current = nextNode;
      } else {
        prev = current;
        current = current->next_;
      }
    }
  }
}

// Sorts the elements in the list in ascending order
template <typename T>
void list<T>::sort() {
  if (size_ > 1) {
    bool swapped;
    Node *current;
    Node *lastSorted = nullptr;
    do {
      swapped = false;
      current = front_;
      while (current->next_ != lastSorted) {
        if (current->data_ > current->next_->data_) {
          std::swap(current->data_, current->next_->data_);
          swapped = true;
        }
        current = current->next_;
      }
      lastSorted = current;
    } while (swapped);
  }
}

// Inserts multiple elements before the specified position in the list
template <typename T>
template <typename... Args>
typename list<T>::iterator list<T>::insert_many(const_iterator pos,
                                                Args &&...args) {
  iterator it(const_cast<Node *>(pos.cgetNode()));
  for (const auto &arg : {args...}) {
    insert(it, arg);
  }
  return it;
}

// Inserts multiple elements at the end of the list
template <typename T>
template <typename... Args>
void list<T>::insert_many_back(Args &&...args) {
  insert_many(cend(), args...);
}

// Inserts multiple elements at the beginning of the list
template <typename T>
template <typename... Args>
void list<T>::insert_many_front(Args &&...args) {
  insert_many(cbegin(), args...);
}

};  // namespace s21

#endif
