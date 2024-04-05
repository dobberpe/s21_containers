#include "s21_array.h"

using namespace s21;

template <typename value_type, size_t _MAX>
typename array<value_type, _MAX>::reference array<value_type, _MAX>::at(
    typename array<value_type, _MAX>::size_type pos) {
  if (this->empty() || pos >= number) throw ERROR_OUT_OF_RANGE;
  return *(head_node + pos);
}

template <typename value_type, size_t _MAX>
typename array<value_type, _MAX>::reference array<value_type, _MAX>::operator[](
    size_type pos) {
      
  return *(head_node + pos);
}


template <typename value_type, size_t _MAX>
typename array<value_type, _MAX>::const_reference array<value_type, _MAX>::operator[](
    size_type pos) const {
  return *(head_node + pos);
}

template <typename value_type, size_t _MAX>
typename array<value_type, _MAX>::reference array<value_type, _MAX>::front() {
  return *(begin());
}

template <typename value_type, size_t _MAX>
typename array<value_type, _MAX>::reference array<value_type, _MAX>::back() {
  if (empty() == CONTAINER_EMPTY)
    return *end();
  else
    return *(end()-1);
}

template <typename value_type, size_t _MAX>
typename array<value_type, _MAX>::iterator array<value_type, _MAX>::data() {
  return head_node;
}
