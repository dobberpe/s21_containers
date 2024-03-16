#include "s21_list.h"

template <typename T>
typename list<T>::list_node *list<T>::begin() {
  return head_node;
}

template <typename T>
typename list<T>::list_node *list<T>::end() {
  return tail_node;
}

template <typename T>
const T &list<T>::front() {
  return begin()->data;
}

template <typename T>
const T &list<T>::back() {
  return end()->prev->data;
}
