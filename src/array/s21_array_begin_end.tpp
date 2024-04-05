#include "s21_array.h"

using namespace s21;

template <typename value_type, size_t _MAX>
typename array<value_type, _MAX>::iterator array<value_type, _MAX>::begin() {
  return head_node;
}

template <typename value_type, size_t _MAX>
typename array<value_type, _MAX>::iterator array<value_type, _MAX>::end() {
  return (head_node + number);
}

// template <typename value_type, size_t _MAX>
// typename array<value_type, _MAX>::const_iterator array<value_type,
// _MAX>::begin() const{
//   return VectorConstIterator(head_node);
// }

// template <typename value_type, size_t _MAX>
// typename array<value_type, _MAX>::const_iterator array<value_type,
// _MAX>::end() const{
//   return VectorConstIterator(head_node + number);
// }