#ifndef SRC_S21_CONTAINERS_S21_ARRAY_H_
#define SRC_S21_CONTAINERS_S21_ARRAY_H_

#include <initializer_list>
#include <iostream>
#include <limits>
#include <stdexcept>

namespace s21 {
template <class T, size_t N>
class S21Array {
 public:
  // Member types
  typedef T value_type;
  typedef T &reference;
  typedef const T &const_reference;
  typedef T *iterator;
  typedef const T *const_iterator;
  typedef size_t size_type;

  // Array Member functions
  S21Array();
  S21Array(std::initializer_list<value_type> const &items);
  S21Array(const S21Array &a);
  S21Array(S21Array &&a);
  ~S21Array();
  S21Array &operator=(S21Array &a);

  // Array Element access
  reference at(size_type pos);
  reference operator[](size_type pos);
  const_reference front();
  const_reference back();
  iterator data();

  // Vector Iterators
  iterator begin();
  iterator end();

  // Vector Capacity
  bool empty();
  size_type size();
  size_type max_size();

  // Vector Modifiers
  void swap(S21Array &other);
  void fill(const_reference value);

  //   void print_array();
 private:
  T array[N];
};
}  // namespace s21

namespace s21 {

// default constructor, creates empty array
template <class T, size_t N>
S21Array<T, N>::S21Array() {}

// initializer list constructor, creates array initizialized using
// std::initializer_list
template <class T, size_t N>
S21Array<T, N>::S21Array(std::initializer_list<value_type> const &items) {
  size_type i = 0;
  for (const auto &item : items) {
    if (i < N) {
      array[i++] = item;
    }
  }
}

// copy constructor
template <class T, size_t N>
S21Array<T, N>::S21Array(const S21Array &a) {
  for (size_type i = 0; i < N; i++) {
    array[i] = a.array[i];
  }
}

// move constructor
template <class T, size_t N>
S21Array<T, N>::S21Array(S21Array &&a) {
  for (size_type i = 0; i < N; i++) {
    array[i] = std::move(a.array[i]);
  }
}

// destructor
template <class T, size_t N>
S21Array<T, N>::~S21Array() {}

// assignment operator overload for moving object
template <class T, size_t N>
S21Array<T, N> &S21Array<T, N>::operator=(S21Array<T, N> &a) {
  if (this != &a) {
    for (size_type i = 0; i < N; i++) {
      array[i] = a.array[i];
    }
  }
  return *this;
}

// access specified element with bounds checking
template <class T, size_t N>
typename S21Array<T, N>::reference S21Array<T, N>::at(size_type pos) {
  if (pos < N) {
    return array[pos];
  } else {
    throw std::out_of_range("Index out of range");
  }
}

// access specified element
template <class T, size_t N>
typename S21Array<T, N>::reference S21Array<T, N>::operator[](size_type pos) {
  return at(pos);
}

// access the first element
template <class T, size_t N>
typename S21Array<T, N>::const_reference S21Array<T, N>::front() {
  return at(0);
}

// access the last element
template <class T, size_t N>
typename S21Array<T, N>::const_reference S21Array<T, N>::back() {
  return at(N - 1);
}

// direct access to the underlying array
template <class T, size_t N>
typename S21Array<T, N>::iterator S21Array<T, N>::data() {
  return array;
}

// returns an iterator to the beginning
template <class T, size_t N>
typename S21Array<T, N>::iterator S21Array<T, N>::begin() {
  return array;
}

// returns an iterator to the end
template <class T, size_t N>
typename S21Array<T, N>::iterator S21Array<T, N>::end() {
  return array + N;
}

// checks whether the container is empty
template <class T, size_t N>
bool S21Array<T, N>::empty() {
  return N == 0;
}

// returns the number of elements
template <class T, size_t N>
typename S21Array<T, N>::size_type S21Array<T, N>::size() {
  return N;
}

// returns the maximum possible number of elements
template <class T, size_t N>
typename S21Array<T, N>::size_type S21Array<T, N>::max_size() {
  return N;
}

// swaps the contents
template <class T, size_t N>
void S21Array<T, N>::swap(S21Array &other) {
  S21Array temp = *this;
  *this = other;
  other = temp;
}

template <class T, size_t N>
void S21Array<T, N>::fill(const_reference value) {
  for (size_type i = 0; i < size(); ++i) {
    array[i] = value;
  }
}

// template <class T, size_t N>
// void S21Array<T, N>::print_array() {
//   for (size_type i = 0; i < size(); ++i) {
//     std::cout << at(i) << " ";
//   }
//   std::cout << std::endl;
// }

}  // namespace s21

#endif  // SRC_S21_CONTAINERS_S21_ARRAY_H_