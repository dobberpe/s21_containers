#include "s21_vector.h"

using namespace s21;

template <typename T>
VectorConstIterator<T>::VectorConstIterator() {
  index_ptr = nullptr;
}

template <typename T>
VectorConstIterator<T>::VectorConstIterator(const VectorConstIterator &copy) {
  index_ptr = copy.index_ptr;
}

template <typename T>
VectorConstIterator<T>::VectorConstIterator(T *node) {
  index_ptr = node;
}

template <typename T>
VectorConstIterator<T> &VectorConstIterator<T>::operator++() {
  index_ptr += 1;
  return *this;
}

template <typename T>
VectorConstIterator<T> &VectorConstIterator<T>::operator--() {
  index_ptr -= 1;
  return *this;
}

template <typename T>
VectorConstIterator<T> &VectorConstIterator<T>::operator=(
    const VectorConstIterator &iter) {
  index_ptr = iter.index_ptr;
  return *this;
}

template <typename T>
VectorConstIterator<T> &VectorConstIterator<T>::operator=(
    VectorIterator<T> iter) {
  index_ptr = iter.get_iter_ptr();
  return *this;
}

template <typename T>
typename vector<T>::const_reference VectorConstIterator<T>::operator*() const{
  return *(this->index_ptr);
}

template <typename T>
bool VectorConstIterator<T>::operator!=(const VectorConstIterator &pos) {
  return (index_ptr != pos.index_ptr);
}

