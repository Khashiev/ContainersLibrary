
#ifndef S21_CONTAINERS_QUEUE_H
#define S21_CONTAINERS_QUEUE_H

#include <iostream>

namespace s21 {
template <typename T>
class queue {
 public:
  // member type
  // Определение типов данных, используемых в классе
  using value_type = T;  // Тип элементов очереди
  using reference = T &;  // Ссылочный тип для элементов очереди
  using const_reference = const T &;  // Константная ссылка на элементы очереди
  using size_type = size_t;  // Тип для хранения количества элементов

  // functions
  queue();  // Конструктор по умолчанию
  queue(std::initializer_list<value_type> const
            &items);  // Конструктор, принимающий std::initializer_list
  queue(const queue &q);  // Конструктор копирования
  queue(queue &&q);       // Конструктор перемещения
  ~queue();               // Деструктор
  queue &operator=(queue &&q);  // Оператор присваивания перемещением

  // element access
  const_reference front();  // Доступ к первому элементу очереди
  const_reference back();  // Доступ к последнему элементу очереди

  // capacity
  bool empty();  // Проверка на пустоту очереди
  size_type size();  // Получение количества элементов в очереди

  // modifiers
  void push(
      const_reference value);  // Добавление нового элемента в конец очереди
  void pop();  // Удаление первого элемента из очереди
  void swap(queue &other);  // Обмен содержимым с другой очередью

  // insert_many
  template <typename... Args>
  void insert_many_back(
      Args &&...args);  // Добавление нескольких элементов в конец очереди

 private:
  struct Node {  // Структура узла связного списка
    value_type data_node;  // Данные узла
    Node *next_node;  // Указатель на следующий узел
    Node(const_reference value)
        : data_node(value), next_node(nullptr) {}  // Конструктор узла
  };

  Node *front_node;  // Указатель на первый узел
  Node *back_node;   // Указатель на последний узел
  size_type size_queue;  // Количество элементов в очереди
};
};  // namespace s21

#include "s21_queue.tpp"

#endif
