#ifndef S21_VECTOR_H
#define S21_VECTOR_H

#include <cstdlib>  // для std::malloc и std::free
#include <iostream>
#include <stdexcept>

namespace my_allocator {

// Шаблон класса аллокатора
template <typename T>
class Allocator {
 public:
  // Тип, представляющий указатель на T
  using pointer = T*;

  // Функция выделения памяти
  pointer allocate(size_t n) {
    // Используем std::malloc для выделения памяти
    return static_cast<pointer>(std::malloc(n * sizeof(T)));
  }

  // Функция освобождения памяти
  void deallocate(pointer p, size_t /* n */) { std::free(p); }
};

}  // namespace my_allocator
namespace s21 {
template <typename T, class Allocator = std::allocator<T>>
class vector {
 public:
  typedef T* iterator;
  typedef const T* const_iterator;
  typedef T value_type;
  typedef size_t size_type;
  typedef ptrdiff_t difference_type;
  typedef T& reference;
  typedef const T& const_reference;
  typedef typename Allocator::pointer pointer;
  typedef const T* const_pointer;
  typedef std::reverse_iterator<iterator> reverse_iterator;
  typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

  // Конструктор по умолчанию
  vector();

  // Деструктор
  ~vector();

  vector(std::initializer_list<T> initList);

  void assign(size_t count, const T& value);

  // Присваивание значений из initializer_list
  void assign(std::initializer_list<T> init_list);

  // Присваивание значений из диапазона [first, last)

  void assign(const T* first, const T* last);

  reference at(size_type position);

  // Возвращает константную ссылку на элемент по указанной позиции
  const_reference at(size_type position) const;

  reference back();

  // Возвращает константную ссылку на последний элемент вектора
  const_reference back() const;

  const_iterator cbegin() const;

  void swap(vector<T, Allocator>& right);

  // Дружественная функция swap
  friend void swap(vector<T, Allocator>& left, vector<T, Allocator>& right) {
    left.swap(right);
  }

  // Возвращает размер вектора
  size_type size() const;

  // Возвращает емкость вектора
  size_type capacity() const;

  // Проверяет, пуст ли вектор
  bool empty() const;
  void clear();
  // Добавляет элемент в конец вектора
  void push_back(const T& value);
  void pop_back();

  // Доступ к элементу по индексу (неконстантная версия)
  reference operator[](size_type index);

  // Доступ к элементу по индексу (константная версия)
  const_reference operator[](size_type index) const;

  // Возвращает итератор на начало вектора
  iterator begin();

  // Возвращает итератор на конец вектора
  iterator end();

  // Возвращает константный итератор на начало вектора
  const_iterator begin() const;

  // Возвращает константный итератор на конец вектора
  const_iterator end() const;

  // Увеличивает емкость вектора
  void reserve(size_type new_capacity);

 private:
  size_type size_;      // Текущий размер вектора
  size_type capacity_;  // Емкость вектора
  pointer data_;        // Указатель на данные
  Allocator allocator_;  // Аллокатор для управления памятью
};

template <typename T, class Allocator = std::allocator<T>>
class vector_iterator {
 public:
  typedef T value_type;
  typedef T* pointer;
  typedef T& reference;
  typedef std::ptrdiff_t difference_type;
  typedef std::random_access_iterator_tag iterator_category;
  // Конструкторы
  vector_iterator() : ptr_(nullptr) {}
  vector_iterator(pointer ptr) : ptr_(ptr) {}

  // Операторы сравнения
  bool operator==(const vector_iterator& other) const {
    return ptr_ == other.ptr_;
  }
  bool operator!=(const vector_iterator& other) const {
    return !(*this == other);
  }

  // Операторы разыменования
  reference operator*() const { return *ptr_; }
  pointer operator->() const { return ptr_; }

  // Операторы инкремента/декремента
  vector_iterator& operator++() {
    ++ptr_;
    return *this;
  }
  vector_iterator operator++(int) {
    vector_iterator tmp(*this);
    ++(*this);
    return tmp;
  }
  vector_iterator& operator--() {
    --ptr_;
    return *this;
  }
  vector_iterator operator--(int) {
    vector_iterator tmp(*this);
    --(*this);
    return tmp;
  }

  // Операторы смещения
  vector_iterator& operator+=(difference_type n) {
    ptr_ += n;
    return *this;
  }
  vector_iterator& operator-=(difference_type n) {
    ptr_ -= n;
    return *this;
  }
  vector_iterator operator+(difference_type n) const {
    return vector_iterator(ptr_ + n);
  }
  vector_iterator operator-(difference_type n) const {
    return vector_iterator(ptr_ - n);
  }
  difference_type operator-(const vector_iterator& other) const {
    return ptr_ - other.ptr_;
  }

  // Операторы сравнения отношений
  bool operator<(const vector_iterator& other) const {
    return ptr_ < other.ptr_;
  }
  bool operator>(const vector_iterator& other) const {
    return ptr_ > other.ptr_;
  }
  bool operator<=(const vector_iterator& other) const {
    return ptr_ <= other.ptr_;
  }
  bool operator>=(const vector_iterator& other) const {
    return ptr_ >= other.ptr_;
  }

 private:
  pointer ptr_;
};

}  // namespace s21
#endif  // S21_VECTOR_HPP
