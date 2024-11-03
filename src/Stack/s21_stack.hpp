#ifndef S21_STACK_H
#define S21_STACK_H

#include <iostream>

#include "../Vector/s21_vector.hpp"

namespace s21 {

template <typename T, typename Container = s21::vector<T>>
class stack {
 public:
  using container_type = Container;
  using size_type = typename Container::size_type;
  using value_type =
      typename container_type::value_type;  // Тип объекта, хранящегося в стеке
  using reference =
      typename container_type::reference;  // Тип ссылки на элемент стека
  using const_reference =
      typename container_type::const_reference;  // Тип константной ссылки на
                                                 // элемент стека

 private:
  container_type data;

 public:
  stack();
  stack(const container_type& right);
  void push(const value_type& val);
  value_type pop();
  bool empty() const;
  size_type size() const;
  reference top();
  const_reference top() const;
};
}  // namespace s21
#endif  // S21_STACK_HPP