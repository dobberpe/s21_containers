#include "s21_list.h"

using namespace s21;

template <typename value_type>
ListIterator<value_type>::ListIterator() {
  index_ptr = nullptr;
}

template <typename value_type>
ListIterator<value_type>::ListIterator(
    typename list<value_type>::list_node *copy) {
  index_ptr = copy;
}

template <typename value_type>
ListIterator<value_type>::ListIterator(const ListIterator &copy) {
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
bool ListIterator<value_type>::operator==(const ListIterator &pos) const {
  return (this->index_ptr == pos.index_ptr);
}

template <typename value_type>
bool ListIterator<value_type>::operator!=(const ListIterator &pos) const {
  return (this->index_ptr != pos.index_ptr);
}

template <typename value_type>
ListIterator<value_type> &ListIterator<value_type>::operator=(
    ListIterator pos) {
  index_ptr = pos.index_ptr;
  return *this;
}

template <typename value_type>
typename list<value_type>::list_node *ListIterator<value_type>::get_iter_ptr()
    const {
  return index_ptr;
}
