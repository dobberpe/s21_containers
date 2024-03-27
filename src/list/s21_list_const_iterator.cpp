#include "s21_list.h"

using namespace s21;

template <typename T>
List<T>::ListConstIterator::ListConstIterator() {
  index_ptr = nullptr;
}

template <typename T>
List<T>::ListConstIterator::ListConstIterator(list_node *node) {
  index_ptr = node;
}

template <typename T>
typename List<T>::ListConstIterator &List<T>::ListConstIterator::operator=(
    list_node *node) {
  index_ptr = node;
  return *this;
}

template <typename T>
typename List<T>::ListConstIterator &List<T>::ListConstIterator::operator++() {
  if (index_ptr->next != nullptr) index_ptr = index_ptr->next;
  return *this;
}

template <typename T>
typename List<T>::ListConstIterator &List<T>::ListConstIterator::operator--() {
  index_ptr = index_ptr->prev;
  return *this;
}

template <typename T>
const T &List<T>::ListConstIterator::operator*() const {
  return this->index_ptr->data;
}

template <typename T>
bool List<T>::ListConstIterator::operator==(const ListConstIterator &pos) {
  return (this->index_ptr == pos.index_ptr);
}

template <typename T>
bool List<T>::ListConstIterator::operator!=(const ListConstIterator &pos) {
  return (this->index_ptr != pos.index_ptr);
}

template <typename T>
typename List<T>::list_node *List<T>::ListConstIterator::get_iter_ptr() {
  return this->index_ptr;
}
