#include "s21_vector.h"

using namespace s21;

template <typename T>
VectorIterator<T>::VectorIterator() {
  index_ptr = nullptr;
}

template <typename T>
VectorIterator<T>::VectorIterator(T *node) {
  index_ptr = node;
}

template <typename T>
VectorIterator<T>::VectorIterator(const VectorIterator &copy) {
  index_ptr = copy.index_ptr;
}

template <typename T>
VectorIterator<T> &VectorIterator<T>::operator++() {
  index_ptr += 1;
  return *this;
}

template <typename T>
VectorIterator<T> &VectorIterator<T>::operator--() {
  index_ptr -= 1;
  return *this;
}

template <typename T>
VectorIterator<T> &VectorIterator<T>::operator=(const VectorIterator &iter) {
  index_ptr = iter.index_ptr;
  return *this;
}

template <typename T>
typename vector<T>::reference VectorIterator<T>::operator*() const {
  return *(this->index_ptr);
}

template <typename T>
bool VectorIterator<T>::operator!=(const VectorIterator &pos) const {
  return (index_ptr != pos.index_ptr);
}
