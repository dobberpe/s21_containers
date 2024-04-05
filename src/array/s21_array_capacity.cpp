#include "s21_array.h"

using namespace s21;


template <typename value_type, size_t _MAX>
typename array<value_type, _MAX>::size_type array<value_type, _MAX>::size() const {
  return this->number;
}

template <typename value_type, size_t _MAX>
bool array<value_type, _MAX>::empty() const {
  return (size() == 0);
}
