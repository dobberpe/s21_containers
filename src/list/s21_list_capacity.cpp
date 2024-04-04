#include "s21_list.h"
using namespace s21;

template <typename T>
bool list<T>::empty() const {
  return (size() == 0);
}

template <typename T>
typename list<T>::size_type list<T>::size() const {
  return number;
}

template <typename T>
typename list<T>::size_type list<T>::max_size() const {
  size_type count = 384307168202282325;
  return count;
}
