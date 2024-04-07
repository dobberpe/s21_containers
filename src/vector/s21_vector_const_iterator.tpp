#include "s21_vector.h"

using namespace s21;

template <typename T>
typename vector<T>::const_reference VectorConstIterator<T>::operator*() const {
  return *(this->index_ptr);
}
