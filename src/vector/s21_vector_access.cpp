#include "s21_vector.h"

using namespace s21;

template <typename value_type>
typename vector<value_type>::reference vector<value_type>::at(
    typename vector<value_type>::size_type pos) {
  if (this->empty() || pos >= number) throw ERROR_OUT_OF_RANGE;
  return *(this->head_node + pos);
}

template <typename value_type>
typename vector<value_type>::reference vector<value_type>::front() {
  return *(begin());
}

template <typename value_type>
typename vector<value_type>::reference vector<value_type>::back() {
  if (empty() == CONTAINER_EMPTY)
    return *end();
  else
    return *(--end());
}

template <typename value_type>
typename vector<value_type>::value_type *vector<value_type>::data() {
  return this->head_node;
}

template <typename value_type>
typename vector<value_type>::reference vector<value_type>::operator[](
    size_type pos) {
      
  return *(this->head_node + pos);
}

template <typename value_type>
typename vector<value_type>::const_reference vector<value_type>::operator[](
    size_type pos) const {
  return *(this->head_node + pos);
}