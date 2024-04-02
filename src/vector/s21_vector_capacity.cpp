#include "s21_vector.h"

using namespace s21;

template <typename value_type>
void vector<value_type>::reserve(size_type size) {
  if (size > 0) {
    if (head_node == NULL) {
      head_node = (value_type *)calloc(1, sizeof(value_type) * size);
      if (!head_node) throw ERROR_MEM;
    } else {
      value_type *new_head =
          (value_type *)realloc(head_node, sizeof(value_type) * size);
      if (new_head)
        head_node = new_head;
      else
        throw ERROR_MEM;
    }
    max_number = size;
  }
}

template <typename value_type>
typename vector<value_type>::size_type vector<value_type>::capacity() const {
  return this->max_number;
}

template <typename value_type>
void vector<value_type>::shrink_to_fit() {
  if (capacity() > size()) reserve(size());
}

template <typename value_type>
typename vector<value_type>::size_type vector<value_type>::size() const {
  return this->number;
}

template <typename value_type>
bool vector<value_type>::empty() const {
  return (size() == 0);
}
