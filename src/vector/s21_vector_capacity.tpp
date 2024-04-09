#include "s21_vector.h"

using namespace s21;

template <typename value_type>
void vector<value_type>::reserve(size_type new_size) {
  if (new_size > 0 && new_size <= this->max_size()) {
    value_type *new_mem =
        (value_type *)calloc(1, sizeof(value_type) * new_size);
    if (!new_mem) throw ERROR_MEM;

    if (head_node != NULL) {
      for (size_type i = 0; i < this->size(); i++) new_mem[i] = head_node[i];
      if (head_node) free(head_node);
    }
    head_node = new_mem;
    max_number = new_size;
  } else if (new_size == 0) {
    if (head_node) free(head_node);
    head_node = nullptr;
    max_number = new_size;
  }
}

template <typename value_type>
typename vector<value_type>::size_type vector<value_type>::capacity()
    const noexcept {
  return this->max_number;
}

template <typename value_type>
void vector<value_type>::shrink_to_fit() noexcept {
  if (capacity() > size()) reserve(size());
}

template <typename value_type>
typename vector<value_type>::size_type vector<value_type>::size()
    const noexcept {
  return this->number;
}

template <typename value_type>
typename vector<value_type>::size_type vector<value_type>::max_size()
    const noexcept {
  return std::numeric_limits<size_type>::max() / sizeof(value_type) / 2;
}

template <typename value_type>
bool vector<value_type>::empty() const noexcept {
  return (size() == 0);
}
