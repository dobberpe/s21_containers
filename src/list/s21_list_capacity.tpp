#include "s21_list.h"
using namespace s21;

template <typename value_type>
bool list<value_type>::empty() const {
  return (size() == 0);
}

template <typename value_type>
typename list<value_type>::size_type list<value_type>::size() const {
  return number;
}

template <typename value_type>
typename list<value_type>::size_type list<value_type>::max_size() const {
  return std::numeric_limits<size_type>::max() / sizeof(list_node) / 2;
}
