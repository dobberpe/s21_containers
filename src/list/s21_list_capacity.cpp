#include "s21_list.h"
using namespace s21;

template <typename value_type>
bool List<value_type>::empty() const {
  return (size() == 0);
}

template <typename value_type>
typename List<value_type>::size_type List<value_type>::size() const {
  return number;
}

template <typename value_type>
typename List<value_type>::size_type List<value_type>::max_size() const {
  // size_type size = ;
  return 384307168202282325;
}
