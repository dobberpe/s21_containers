#include "s21_list.h"
using namespace s21;

template <typename T>
bool List<T>::empty() {
  return (size() == 0);
}

template <typename T>
typename List<T>::size_type List<T>::size() {
  return number;
}

template <typename T>
typename List<T>::size_type List<T>::max_size() {
  size_type count = 384307168202282325;
  return count;
}
