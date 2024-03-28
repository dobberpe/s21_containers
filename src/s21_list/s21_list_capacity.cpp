#include "s21_list.h"
using namespace s21;

template <typename value_type>
bool list<value_type>::empty() {
  return (size() == 0);
}

template <typename value_type>
typename list<value_type>::size_type list<value_type>::size() {
  return number;
}

template <typename value_type>
typename list<value_type>::size_type list<value_type>::max_size() {
  size_type size = 384307168202282325;
  return size;
}
