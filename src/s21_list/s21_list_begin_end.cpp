#include "s21_list.h"
using namespace s21;

template <typename value_type>
typename list<value_type>::iterator list<value_type>::begin() {
  iterator iter;
  iter = head_node;
  return iter;
}

template <typename value_type>
typename list<value_type>::iterator list<value_type>::end() {
  iterator iter;
  iter = tail_node;
  return iter;
}

template <typename value_type>
typename list<value_type>::const_iterator list<value_type>::cbegin() const{
  const_iterator iter;
  iter = head_node;
  return iter;
}

template <typename value_type>
typename list<value_type>::const_iterator list<value_type>::cend() const{
  const_iterator iter;
  iter = tail_node;
  return iter;
}

template <typename value_type>
typename list<value_type>::const_reference list<value_type>::front() {
  iterator iter = begin();
  return *iter;
}

template <typename value_type>
typename list<value_type>::const_reference list<value_type>::back() {
  iterator iter = end();
  if (empty() == CONTAINER_NOT_EMPTY) --iter;

  return *iter;
}

template <typename value_type>
typename list<value_type>::reference list<value_type>::operator()(const size_type i) {
  iterator pos = begin();
  if (i < size()) {
    size_type index = 0;
    for (; index < i; ++pos, index++)
      ;
  }
  return *pos;
}