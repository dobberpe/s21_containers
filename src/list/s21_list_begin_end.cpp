#include "s21_list.h"
using namespace s21;

template <typename value_type>
typename List<value_type>::iterator List<value_type>::begin() {
  return iterator(head_node);
}

template <typename value_type>
typename List<value_type>::iterator List<value_type>::end() {
  return iterator(tail_node);
}

template <typename value_type>
typename List<value_type>::const_iterator List<value_type>::begin() const {
  const_iterator iter;
  iter.index_ptr = head_node;
  return iter;
}

template <typename value_type>
typename List<value_type>::const_iterator List<value_type>::end() const {
  const_iterator iter;
  iter.index_ptr = tail_node;
  return iter;
  // return ListConstIterator(tail_node);
}

template <typename value_type>
typename List<value_type>::const_reference List<value_type>::front() const {
  return *begin();
}

template <typename value_type>
typename List<value_type>::const_reference List<value_type>::back() const {
  const_iterator iter = end();
  if (empty() == CONTAINER_NOT_EMPTY) --iter;

  return *iter;
}

template <typename value_type>
typename List<value_type>::reference List<value_type>::front() {
  return *begin();
}

template <typename value_type>
typename List<value_type>::reference List<value_type>::back() {
  iterator iter = end();
  if (empty() == CONTAINER_NOT_EMPTY) --iter;

  return *iter;
}

template <typename value_type>
typename List<value_type>::reference List<value_type>::operator()(size_type i) {
  iterator pos = begin();
  if (i > 0 && i < size()) {
    for (; i > 0; ++pos, i--)
      ;
  }
  return *pos;
}

template <typename value_type>
typename List<value_type>::const_reference List<value_type>::operator()(
    size_type i) const {
  const_iterator pos = begin();
  if (i > 0 && i < size()) {
    for (; i > 0; ++pos, i--)
      ;
  }
  return *pos;
}