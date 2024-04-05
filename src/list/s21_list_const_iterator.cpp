#include "s21_list.h"

using namespace s21;

template <typename value_type>
ListConstIterator<value_type>::ListConstIterator() {
  index_ptr = nullptr;
}

template <typename value_type>
ListConstIterator<value_type>::ListConstIterator(
    typename list<value_type>::list_node *copy) {
  index_ptr = copy;
}

template <typename value_type>
ListConstIterator<value_type>::ListConstIterator(
    const ListConstIterator &copy) {
  index_ptr = copy.index_ptr;
}

template <typename value_type>
ListConstIterator<value_type>::ListConstIterator(
    const ListIterator<value_type> &copy) {
  index_ptr = copy.get_iter_ptr();
}

template <typename value_type>
ListConstIterator<value_type> &ListConstIterator<value_type>::operator++() {
  if (index_ptr->next != nullptr) index_ptr = index_ptr->next;
  return *this;
}

template <typename value_type>
ListConstIterator<value_type> &ListConstIterator<value_type>::operator--() {
  index_ptr = index_ptr->prev;
  return *this;
}

template <typename value_type>
typename list<value_type>::const_reference
ListConstIterator<value_type>::operator*() const {
  return this->index_ptr->data;
}

template <typename value_type>
bool ListConstIterator<value_type>::operator==(const ListConstIterator &pos) {
  return (this->index_ptr == pos.index_ptr);
}

template <typename value_type>
bool ListConstIterator<value_type>::operator!=(const ListConstIterator &pos) {
  return (this->index_ptr != pos.index_ptr);
}

// template <typename value_type>
// ListConstIterator<value_type> &ListConstIterator<value_type>::operator=(
//     ListConstIterator &pos) {
//   index_ptr = pos.index_ptr;
//   return *this;
// }

template <typename value_type>
ListConstIterator<value_type> &ListConstIterator<value_type>::operator=(
    ListIterator<value_type> pos) {
  index_ptr = pos.get_iter_ptr();
  return *this;
}

template <typename value_type>
typename list<value_type>::list_node *
ListConstIterator<value_type>::get_iter_ptr() const {
  return index_ptr;
}
