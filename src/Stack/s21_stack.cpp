#include "./s21_stack.hpp"

namespace s21 {

template <typename T, typename Container>
stack<T, Container>::stack() = default;

// Конструктор, принимающий объект типа container_type
template <typename T, typename Container>
stack<T, Container>::stack(const container_type& right) : data(right) {}

// Помещает элемент на вершину стека
template <typename T, typename Container>
void stack<T, Container>::push(const value_type& val) {
  data.push_back(val);
}
// Удаляет элемент с вершины стека и возвращает его значение
template <typename T, typename Container>
typename stack<T, Container>::value_type stack<T, Container>::pop() {
  if (data.empty()) {
    throw std::out_of_range("Stack is empty");
  }
  value_type item = data.back();
  data.pop_back();
  return item;
}

// Проверяет, пуст ли стек
template <typename T, typename Container>
bool stack<T, Container>::empty() const {
  return data.empty();
}

// Возвращает количество элементов в стеке
template <typename T, typename Container>
typename stack<T, Container>::size_type stack<T, Container>::size() const {
  return data.size();
}

// Возвращает значение элемента на вершине стека без его удаления
template <typename T, typename Container>
typename stack<T, Container>::reference stack<T, Container>::top() {
  if (data.empty()) {
    throw std::out_of_range("Stack is empty");
  }
  return data.back();
}

// Возвращает константное значение элемента на вершине стека без его удаления
template <typename T, typename Container>
typename stack<T, Container>::const_reference stack<T, Container>::top() const {
  if (data.empty()) {
    throw std::out_of_range("Stack is empty");
  }
  return data.back();
}
}  // namespace s21