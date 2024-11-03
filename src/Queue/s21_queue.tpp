#ifndef S21_CONTAINERS_QUEUE_TPP
#define S21_CONTAINERS_QUEUE_TPP

#include <iostream>

namespace s21 {

// functions

// Конструктор по умолчанию, инициализирует пустую очередь
template <typename T>
queue<T>::queue() : front_node(nullptr), back_node(nullptr), size_queue(0) {}

// Конструктор, инициализирующий очередь элементами из std::initializer_list
template <typename T>
queue<T>::queue(std::initializer_list<value_type> const &items)
    : front_node(nullptr), back_node(nullptr), size_queue(0) {
  for (const auto &item : items) {
    push(item);  // Добавляем каждый элемент в конец очереди
  }
}

// Конструктор копирования, создает глубокую копию переданной очереди
template <typename T>
queue<T>::queue(const queue &q)
    : front_node(nullptr), back_node(nullptr), size_queue(0) {
  Node *current_node = q.front_node;
  while (current_node != nullptr) {
    push(current_node
             ->data_node);  // Добавляем каждый элемент в конец новой очереди
    current_node = current_node->next_node;
  }
}

// Конструктор перемещения, перемещает ресурсы из переданной очереди в новую
template <typename T>
queue<T>::queue(queue &&q)
    : front_node(q.front_node),
      back_node(q.back_node),
      size_queue(q.size_queue) {
  q.front_node = nullptr;
  q.back_node = nullptr;
  q.size_queue = 0;
}

// Деструктор, освобождает память, занимаемую очередью
template <typename T>
queue<T>::~queue() {
  while (!empty()) pop();  // Удаляем все элементы очереди
}

// Оператор присваивания перемещением
template <typename T>
queue<T> &queue<T>::operator=(queue &&q) {
  while (!empty()) pop();  // Удаляем все элементы текущей очереди

  // Перемещаем ресурсы из переданной очереди в текущую
  front_node = q.front_node;
  back_node = q.back_node;
  size_queue = q.size_queue;

  // Обнуляем поля переданной очереди
  q.front_node = nullptr;
  q.back_node = nullptr;
  q.size_queue = 0;

  return *this;
}

// element access

// Возвращает ссылку на первый элемент очереди
template <typename T>
typename queue<T>::const_reference queue<T>::front() {
  if (empty()) throw std::out_of_range("Queue is empty");
  return front_node->data_node;
}

// Возвращает ссылку на последний элемент очереди
template <typename T>
typename queue<T>::const_reference queue<T>::back() {
  if (empty()) throw std::out_of_range("Queue is empty");
  return back_node->data_node;
}

// capacity

// Проверяет, пуста ли очередь
template <typename T>
bool queue<T>::empty() {
  return (front_node == nullptr && back_node == nullptr && size_queue == 0);
}

// Возвращает количество элементов в очереди
template <typename T>
typename queue<T>::size_type queue<T>::size() {
  return size_queue;
}

// modifiers

// Добавляет новый элемент в конец очереди
template <typename T>
void queue<T>::push(const_reference value) {
  Node *new_node = new Node(value);
  if (empty()) {
    front_node = new_node;
  } else {
    back_node->next_node = new_node;
  }
  back_node = new_node;
  ++size_queue;
}

// Удаляет первый элемент из очереди
template <typename T>
void queue<T>::pop() {
  if (empty()) throw std::out_of_range("Queue is empty");
  Node *temp_node = front_node;
  front_node = front_node->next_node;
  delete temp_node;
  --size_queue;
  if (front_node == nullptr) {
    back_node = nullptr;  // Если очередь опустела, обнуляем указатель на
                          // последний элемент
  }
}

// Обменивает содержимое текущей очереди с переданной
template <typename T>
void queue<T>::swap(queue &other) {
  std::swap(front_node, other.front_node);
  std::swap(back_node, other.back_node);
  std::swap(size_queue, other.size_queue);
}

// insert_many

// Добавляет несколько элементов в конец очереди
template <typename T>
template <typename... Args>
void queue<T>::insert_many_back(Args &&...args) {
  for (const auto &arg : {args...}) {
    push(arg);
  }
}

};  // namespace s21

#endif