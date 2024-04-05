#include "s21_list.h"

using namespace s21;

template <typename value_type>
ListConstIterator<value_type>::ListConstIterator(
    const ListIterator<value_type> &copy)
    : ListIterator<value_type>(copy) {}

template <typename value_type>
typename list<value_type>::const_reference
ListConstIterator<value_type>::operator*() const {
  return ListIterator<value_type>::get_iter_ptr()->data;
  // return ListIterator<value_type>::operator*();
}
