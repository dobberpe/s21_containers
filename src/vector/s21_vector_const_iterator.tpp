#include "s21_vector.h"

using namespace s21;

template <typename T>
VectorConstIterator<T>::VectorConstIterator(const VectorIterator<T> &copy)
    : VectorIterator<T>(copy) {}

template <typename T>
typename vector<T>::const_reference VectorConstIterator<T>::operator*() const {
  return VectorIterator<T>::operator*();
}

template <typename value_type>
VectorConstIterator<value_type> &VectorConstIterator<value_type>::operator=(
    typename vector<value_type>::iterator pos) {
  this->index_ptr = pos.index_ptr;
  return *this;
}
