#include "s21_vector.h"

using namespace s21;

template <typename value_type>
typename vector<value_type>::iterator vector<value_type>::begin() {
  return iterator(head_node);
}

template <typename value_type>
typename vector<value_type>::iterator vector<value_type>::end() {
  return iterator(head_node + number);
}

template <typename value_type>
typename vector<value_type>::const_iterator vector<value_type>::cbegin() const {
  return const_iterator(head_node);
}

template <typename value_type>
typename vector<value_type>::const_iterator vector<value_type>::cend() const {
  return const_iterator(head_node + number);
}