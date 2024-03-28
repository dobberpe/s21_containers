#include "s21_list.h"

using namespace s21;

template <typename value_type>
ListIterator<value_type>::ListIterator() {
  index_ptr = nullptr;
}

template <typename value_type>
ListIterator<value_type>::ListIterator(ListIterator &copy) {
  index_ptr = copy.index_ptr;
}

template <typename value_type>
ListIterator<value_type> &ListIterator<value_type>::operator++() {
  if (index_ptr->next != nullptr) index_ptr = index_ptr->next;
  return *this;
}

template <typename value_type>
ListIterator<value_type> &ListIterator<value_type>::operator--() {
  index_ptr = index_ptr->prev;
  return *this;
}

template <typename value_type>
typename list<value_type>::reference ListIterator<value_type>::operator*() {
  return this->index_ptr->data;
}

template <typename value_type>
bool ListIterator<value_type>::operator==(const ListIterator &pos) {
  return (this->index_ptr == pos.index_ptr);
}

template <typename value_type>
bool ListIterator<value_type>::operator!=(const ListIterator &pos) {
  return (this->index_ptr != pos.index_ptr);
}

template <typename value_type>
ListIterator<value_type> &ListIterator<value_type>::operator=(
    typename list<value_type>::list_node *node) {
  index_ptr = node;
  return *this;
}

template <typename value_type>
ListIterator<value_type> &ListIterator<value_type>::operator=(
    const typename list<value_type>::iterator &pos) {
  index_ptr = pos.index_ptr;
  return *this;
}

template <typename value_type>
typename list<value_type>::list_node *ListIterator<value_type>::get_iter_ptr() {
  return this->index_ptr;
}
