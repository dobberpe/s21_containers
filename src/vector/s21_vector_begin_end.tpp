#include "s21_vector.h"

using namespace s21;

template <typename value_type>
typename vector<value_type>::iterator vector<value_type>::begin() {
  return VectorIterator(head_node);
}

template <typename value_type>
typename vector<value_type>::iterator vector<value_type>::end() {
  return VectorIterator(head_node + number);
}

template <typename value_type>
typename vector<value_type>::const_iterator vector<value_type>::begin() const {
  return VectorConstIterator(head_node);
}

template <typename value_type>
typename vector<value_type>::const_iterator vector<value_type>::end() const {
  return VectorConstIterator(head_node + number);
}