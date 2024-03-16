#include "s21_list.h"

template <typename T>
list<T>::iterator::iterator() {
  index_ptr = nullptr;
}

template <typename T>
void list<T>::iterator::operator=(const list<T>::iterator &iter2) {
  index_ptr = iter2.index_ptr;
}

template <typename T>
void list<T>::iterator::operator=(list_node *node) {
  index_ptr = node;
}

template <typename T>
void list<T>::iterator::operator++() {
  if (index_ptr->next != nullptr) index_ptr = index_ptr->next;
}

template <typename T>
void list<T>::iterator::operator--() {
  if (index_ptr->prev != nullptr) {
    index_ptr = index_ptr->prev;
  }
}

template <typename T>
T &list<T>::iterator::operator*() {
  return this->index_ptr->data;
}

template <typename T>
bool list<T>::iterator::operator==(const list<T>::iterator &iter2) {
  return (this->index_ptr == iter2.index_ptr);
}

template <typename T>
bool list<T>::iterator::operator!=(const list<T>::iterator &iter2) {
  return (this->index_ptr != iter2.index_ptr);
}

template <typename T>
bool list<T>::iterator::operator!=(const list_node *node) {
  return (this->index_ptr != node);
}