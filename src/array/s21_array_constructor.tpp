#include "s21_array.h"

using namespace s21;

template <typename value_type, size_t _MAX>
array<value_type, _MAX>::array() : number(0), head_node(nullptr) {
  allocate_array(_MAX);
}

template <typename value_type, size_t _MAX>
void array<value_type, _MAX>::allocate_array(size_type n) {
  number = 0;
  head_node = nullptr;
  if (n > 0) {
    head_node = new value_type[n];
    if (!head_node) throw ERROR_MEM;
    number = n;
  }
}

template <typename value_type, size_t _MAX>
array<value_type, _MAX>::array(std::initializer_list<value_type> const &items) {
  allocate_array(_MAX);
  size_type i = 0;
  for (auto digit : items) {
    *(head_node + i++) = digit;
    // i++;
  }
}

template <typename value_type, size_t _MAX>
array<value_type, _MAX>::array(const array<value_type, _MAX> &a) {
  allocate_array(a.number);
  for (size_type i = 0; i < a.number; ++i) *(head_node + i) = a[i];
}

template <typename value_type, size_t _MAX>
array<value_type, _MAX>::array(array<value_type, _MAX> &&a) {
  allocate_array(a.number);
  for (size_type i = 0; i < a.number; ++i) *(head_node + i) = a[i];
}

template <typename value_type, size_t _MAX>
array<value_type, _MAX>::~array() {
  if (head_node) delete[] head_node;
}

template <typename value_type, size_t _MAX>
array<value_type, _MAX> &array<value_type, _MAX>::operator=(
    array<value_type, _MAX> &&a) {
  if (&a != this) {
    allocate_array(a.number);
    for (size_type i = 0; i < a.number; --i) *(head_node + i) = a[i];
  }
  return *this;
}

template <typename value_type, size_t _MAX>
bool array<value_type, _MAX>::operator==(
    const array<value_type, _MAX> &arr_other) const {
  size_type size1 = size();
  size_type size2 = arr_other.size();
  short result = SUCCESS;
  if (size1 == size2) {
    for (size_type i = 0; i < size1 && result; ++i) {
      if (operator[](i) != arr_other[i]) result = FAILURE;
    }
  } else
    result = FAILURE;

  return result;
}
