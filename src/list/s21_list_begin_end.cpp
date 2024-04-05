#include "s21_list.h"
using namespace s21;

template <typename value_type>
typename list<value_type>::iterator list<value_type>::begin() {
  return iterator(head_node);
}

template <typename value_type>
typename list<value_type>::iterator list<value_type>::end() {
  return iterator(tail_node);
}

template <typename value_type>
typename list<value_type>::const_iterator list<value_type>::begin() const {
  return const_iterator(head_node);
}

template <typename value_type>
typename list<value_type>::const_iterator list<value_type>::end() const {
  return const_iterator(tail_node);
}

template <typename value_type>
typename list<value_type>::const_reference list<value_type>::front() const {
  return *begin();
}

template <typename value_type>
typename list<value_type>::const_reference list<value_type>::back() const {
  const_iterator iter = end();
  if (empty() == CONTAINER_NOT_EMPTY) --iter;

  return *iter;
}

template <typename value_type>
typename list<value_type>::reference list<value_type>::front() {
  return *begin();
}

template <typename value_type>
typename list<value_type>::reference list<value_type>::back() {
  iterator iter = end();
  if (empty() == CONTAINER_NOT_EMPTY) --iter;

  return *iter;
}

template <typename value_type>
typename list<value_type>::reference list<value_type>::operator()(size_type i) {
  iterator pos = begin();
  if (i > 0 && i < size()) {
    for (; i > 0; ++pos, i--)
      ;
  }
  return *pos;
}

template <typename value_type>
typename list<value_type>::const_reference list<value_type>::operator()(
    size_type i) const {
  const_iterator pos = begin();
  if (i > 0 && i < size()) {
    for (; i > 0; ++pos, i--)
      ;
  }
  return *pos;
}