#include "s21_list.h"

template <typename Type>
list<Type>::iterator::iterator() {
  index_ptr = nullptr;
}

template <typename Type>
void list<Type>::iterator::operator=(const list<Type>::iterator &iter2) {
  index_ptr = iter2.index_ptr;
}

template <typename Type>
void list<Type>::iterator::operator=(list_node *node) {
  index_ptr = node;
}

template <typename Type>
void list<Type>::iterator::operator++() {
  if (index_ptr->next != nullptr) index_ptr = index_ptr->next;
}

template <typename Type>
void list<Type>::iterator::operator--() {
  if (index_ptr->prev != nullptr) {
    index_ptr = index_ptr->prev;
  }
}

template <typename Type>
Type &list<Type>::iterator::operator*() {
  return this->index_ptr->data;
}

template <typename Type>
bool list<Type>::iterator::operator==(const list<Type>::iterator &iter2) {
  return (this->index_ptr == iter2.index_ptr);
}

template <typename Type>
bool list<Type>::iterator::operator!=(const list<Type>::iterator &iter2) {
  return (this->index_ptr != iter2.index_ptr);
}

template <typename Type>
bool list<Type>::iterator::operator!=(const list_node *node) {
  return (this->index_ptr != node);
}