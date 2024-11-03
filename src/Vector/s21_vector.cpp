#include "s21_vector.hpp"

namespace s21 {

template <typename T, typename Allocator>
vector<T, Allocator>::vector() : size_(0), capacity_(0), data_(nullptr) {}

template <typename T, typename Allocator>
vector<T, Allocator>::~vector() {
  if (data_ != nullptr) {
    for (size_type i = 0; i < size_; i++) {
      allocator_.destroy(data_ + i);
    }
    allocator_.deallocate(data_, capacity_);
  }
}

template <typename T, typename Allocator>
vector<T, Allocator>::vector(std::initializer_list<T> initList)
    : size_(0), capacity_(0), data_(nullptr) {
  assign(initList);
}

template <typename T, typename Allocator>
void vector<T, Allocator>::assign(size_t count, const T& value) {
  clear();  // Очищаем вектор перед добавлением новых элементов
  reserve(count);  // Резервируем достаточное место для count элементов

  for (size_t i = 0; i < count; ++i) {
    data_[i] = value;  // Присваиваем значение value элементу вектора
  }

  size_ = count;  // Устанавливаем новый размер вектора
}

template <typename T, typename Allocator>
void vector<T, Allocator>::assign(std::initializer_list<T> init_list) {
  clear();  // Очищаем вектор перед добавлением новых элементов
  reserve(init_list.size());
  for (const auto& element : init_list) {
    push_back(element);
  }
}

template <typename T, typename Allocator>
void vector<T, Allocator>::assign(const T* first, const T* last) {
  clear();  // Очищаем вектор перед добавлением новых элементов
  reserve(last - first);
  for (auto it = first; it != last; ++it) {
    push_back(*it);
  }
}

template <typename T, typename Allocator>
typename vector<T, Allocator>::reference vector<T, Allocator>::at(
    size_type position) {
  if (position >= size_) {
    throw std::out_of_range("Index out of range");
  }
  return data_[position];
}

// Возвращает константную ссылку на элемент по указанной позиции
template <typename T, typename Allocator>
typename vector<T, Allocator>::const_reference vector<T, Allocator>::at(
    size_type position) const {
  if (position >= size_) {
    throw std::out_of_range("Index out of range");
  }
  return data_[position];
}
template <typename T, typename Allocator>
typename vector<T, Allocator>::reference vector<T, Allocator>::back() {
  if (empty()) {
    throw std::out_of_range("Vector is empty");
  }
  return data_[size_ - 1];
}

// Возвращает константную ссылку на последний элемент вектора
template <typename T, typename Allocator>
typename vector<T, Allocator>::const_reference vector<T, Allocator>::back()
    const {
  if (empty()) {
    throw std::out_of_range("Vector is empty");
  }
  return data_[size_ - 1];
}

template <typename T, typename Allocator>
typename vector<T, Allocator>::const_iterator vector<T, Allocator>::cbegin()
    const {
  return &data_[0];
}

template <typename T, typename Allocator>
void vector<T, Allocator>::swap(vector<T, Allocator>& right) {
  // Обмениваем значения всех членов класса справа и слева
  size_type temp_size = size_;
  size_ = right.size_;
  right.size_ = temp_size;

  size_type temp_capacity = capacity_;
  capacity_ = right.capacity_;
  right.capacity_ = temp_capacity;

  pointer temp_data = data_;
  data_ = right.data_;
  right.data_ = temp_data;
}

// Определение friend-функции swap
template <typename T, typename Allocator>
void swap(vector<T, Allocator>& left, vector<T, Allocator>& right) {
  left.swap(right);  // Используем метод swap класса vector
}

// template <typename T, typename Allocator>
// void vector<T, Allocator>::clear() {
//   while (!empty()) {
//     pop_back();
//   }
// }
template <typename T, class Allocator>
void s21::vector<T, Allocator>::clear() {
  for (size_type i = 0; i < size_; ++i) {
    allocator_.destroy(&data_[i]);  // Уничтожаем каждый элемент
  }
  size_ = 0;  // Устанавливаем размер вектора в 0
}

// Возвращает размер вектора
template <typename T, typename Allocator>
typename vector<T, Allocator>::size_type vector<T, Allocator>::size() const {
  return size_;
}

// Возвращает емкость вектора
template <typename T, typename Allocator>
typename vector<T, Allocator>::size_type vector<T, Allocator>::capacity()
    const {
  return capacity_;
}

// Проверяет, пуст ли вектор
template <typename T, typename Allocator>
bool vector<T, Allocator>::empty() const {
  return size_ == 0;
}

// Добавляет элемент в конец вектора
template <typename T, typename Allocator>
void vector<T, Allocator>::push_back(const T& value) {
  if (size_ == 0 or capacity_ == 0) reserve(1);
  if (size_ == capacity_) {
    reserve(capacity_ * 2);
  }
  data_[size_] = value;
  size_++;
}

template <typename T, typename Allocator>
void vector<T, Allocator>::pop_back() {
  if (!empty()) {
    --size_;            // Уменьшаем размер вектора
    data_[size_].~T();  // Вызываем деструктор для последнего элемента
  }
}

// Доступ к элементу по индексу (неконстантная версия)
template <typename T, typename Allocator>
typename vector<T, Allocator>::reference vector<T, Allocator>::operator[](
    size_type index) {
  if (index >= size_) {
    throw std::out_of_range("Index out of range");
  }
  return data_[index];
}

// Доступ к элементу по индексу (константная версия)
template <typename T, typename Allocator>
typename vector<T, Allocator>::const_reference vector<T, Allocator>::operator[](
    size_type index) const {
  if (index >= size_) {
    throw std::out_of_range("Index out of range");
  }
  return data_[index];
}

// Возвращает итератор на начало вектора
template <typename T, typename Allocator>
typename vector<T, Allocator>::iterator vector<T, Allocator>::begin() {
  return &data_[0];
}

// Возвращает итератор на конец вектора
template <typename T, typename Allocator>
typename vector<T, Allocator>::iterator vector<T, Allocator>::end() {
  return &data_[size_];
}

// Возвращает константный итератор на начало вектора
template <typename T, typename Allocator>
typename vector<T, Allocator>::const_iterator vector<T, Allocator>::begin()
    const {
  return &data_[0];
}

// Возвращает константный итератор на конец вектора
template <typename T, typename Allocator>
typename vector<T, Allocator>::const_iterator vector<T, Allocator>::end()
    const {
  return &data_[size_];
}

// template <typename T, typename Allocator>
// void vector<T, Allocator>::reserve(size_type new_capacity) {
//     if (new_capacity <= capacity()) {
//         return; // Нет необходимости перевыделять память, если новая емкость
//         меньше или равна текущей
//     }

//     // Выделяем новую память
//     T* new_data = allocator_.allocate(new_capacity);

//     // Копируем существующие элементы в новую память
//     for (size_type i = 0; i < size(); ++i) {
//         allocator_.construct(&new_data[i], std::move(data_[i]));
//     }

//     // Деинициализируем старые элементы
//     for (size_type i = 0; i < size(); ++i) {
//         allocator_.destroy(&data_[i]);
//     }

//     // Освобождаем старый блок памяти
//     allocator_.deallocate(data_, capacity());

//     // Обновляем указатели на данные и емкость
//     data_ = new_data;
//     capacity_ = new_capacity;
// }

template <typename T, class Allocator>
void s21::vector<T, Allocator>::reserve(size_type new_capacity) {
  if (new_capacity > capacity_) {
    // Выделение новой памяти с запрошенной емкостью
    pointer new_data = allocator_.allocate(new_capacity);

    // Проверка на успешное выделение памяти
    if (new_data == nullptr) {
      throw std::bad_alloc();
    }

    // Копирование существующих элементов в новую память
    for (size_type i = 0; i < size_; ++i) {
      // Копирование элементов, используя перемещающий конструктор, если
      // доступен
      allocator_.construct(&new_data[i], std::move(data_[i]));
    }

    // Освобождение старой памяти
    for (size_type i = 0; i < size_; ++i) {
      allocator_.destroy(&data_[i]);
    }
    allocator_.deallocate(data_, capacity_);

    // Обновление указателей и емкости
    data_ = new_data;
    capacity_ = new_capacity;
  }
}

};  // namespace s21