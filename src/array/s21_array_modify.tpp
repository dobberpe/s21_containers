#include "s21_array.h"

using namespace s21;

template <typename value_type, size_t _MAX>
void array<value_type, _MAX>::swap(array<value_type, _MAX> &other) {
  if (this != &other) {
    value_type *save = head_node;
    head_node = other.head_node;
    other.head_node = save;

    size_type save_mn = number;
    number = other.number;
    other.number = save_mn;
  }
}

template <typename value_type, size_t _MAX>
void array<value_type, _MAX>::fill(const_reference value) {
  for (size_type i = 0; i < size(); i++) operator[](i) = value;
}