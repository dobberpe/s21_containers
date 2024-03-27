#include "s21_list.h"

using namespace s21;

template <typename T>
List<T>::iterator::iterator() {
  index_ptr = nullptr;
}

template <typename T>
typename List<T>::iterator &List<T>::iterator::operator=(list_node *node) {
  index_ptr = node;
  return *this;
}

template <typename T>
typename List<T>::iterator &List<T>::iterator::operator++() {
  if (index_ptr->next != nullptr) index_ptr = index_ptr->next;
  return *this;
}

template <typename T>
typename List<T>::iterator &List<T>::iterator::operator--() {
  index_ptr = index_ptr->prev;
  return *this;
}

template <typename T>
T &List<T>::iterator::operator*() {
  return this->index_ptr->data;
}

template <typename T>
bool List<T>::iterator::operator==(const iterator &pos) {
  return (this->index_ptr == pos.index_ptr);
}

template <typename T>
bool List<T>::iterator::operator!=(const iterator &pos) {
  return (this->index_ptr != pos.index_ptr);
}

template <typename T>
typename List<T>::list_node *List<T>::iterator::get_iter_ptr() {
  return this->index_ptr;
}
