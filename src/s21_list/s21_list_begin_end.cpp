#include "s21_list.h"
using namespace s21;

template <typename T>
typename list<T>::iterator &list<T>::begin() {
  this->iter_head = head_node;
  return this->iter_head;
}

template <typename T>
typename list<T>::iterator &list<T>::end() {
  this->iter_tail = tail_node;
  return this->iter_tail;
}

template <typename T>
T &list<T>::front() {
  iterator iter = begin();

  return *iter;
}

template <typename T>
T &list<T>::back() {
  iterator iter = end();
  if (empty() == CONTAINER_NOT_EMPTY) --iter;

  return *iter;
}

template <typename T>
T &list<T>::operator()(const size_type i) {
  iterator pos = begin();
  if (i < size()) {
    size_type index = 0;
    for (; index < i; ++pos, index++)
      ;
  }
  return *pos;
}