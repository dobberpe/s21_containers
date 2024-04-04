#include "s21_list.h"

using namespace s21;

template <typename T>
list<T>::ListIterator::ListIterator() {
  index_ptr = nullptr;
}

template <typename T>
typename list<T>::ListIterator &list<T>::ListIterator::operator=(
    list_node *node) {
  index_ptr = node;
  return *this;
}

template <typename T>
typename list<T>::ListIterator &list<T>::ListIterator::operator++() {
  if (index_ptr->next != nullptr) index_ptr = index_ptr->next;
  return *this;
}

template <typename T>
typename list<T>::ListIterator &list<T>::ListIterator::operator--() {
  index_ptr = index_ptr->prev;
  return *this;
}

template <typename T>
T &list<T>::ListIterator::operator*() {
  return this->index_ptr->data;
}

template <typename T>
bool list<T>::ListIterator::operator==(const ListIterator &pos) {
  return (this->index_ptr == pos.index_ptr);
}

template <typename T>
bool list<T>::ListIterator::operator!=(const ListIterator &pos) {
  return (this->index_ptr != pos.index_ptr);
}

template <typename T>
typename list<T>::list_node *list<T>::ListIterator::get_iter_ptr() {
  return this->index_ptr;
}
