#include "s21_vector.h"

using namespace s21;

template <typename T>
VectorConstIterator<T>::VectorConstIterator(const VectorIterator<T> &copy)
    : VectorIterator<T>(copy) {}

template <typename T>
typename vector<T>::const_reference VectorConstIterator<T>::operator*() const {
  return VectorIterator<T>::operator*();
}
