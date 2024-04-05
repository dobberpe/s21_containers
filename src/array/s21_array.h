#ifndef _S21_ARRAY_H_
#define _S21_ARRAY_H_

#include <stdlib.h>

#include "../vector/s21_vector.h"

namespace s21 {

template <typename T, size_t _MAX=0>
class array : public vector<T> {
 public:
  using value_type = T;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = size_t;
  using iterator = value_type *;
  using const_iterator = const value_type *;

 private:
  size_type number;
  value_type *head_node;
  void allocate_array(size_type n);

 public:
  // bool operator==(const array<value_type, _MAX> &arr_other) const;

  // *Array Element access*
  reference at(size_type pos);
  reference operator[](size_type pos);
  const_reference operator[](size_type pos) const;
  reference front();
  reference back();
  iterator data();

  // *Array Iterators*
  iterator begin();
  iterator end();

  // *Array Capacity*
  bool empty() const;
  size_type size() const;
  // size_type max_size() ; // from vector-->list

  // *Array Modifiers*
  void swap(array<value_type, _MAX> &other);
  void fill(const_reference value);

  array();
  array(std::initializer_list<value_type> const &items);
  array(const array<value_type, _MAX> &a);
  array(array<value_type, _MAX> &&a);
  array<value_type, _MAX> &operator=(array<value_type, _MAX> &&a);
  ~array();
};

template class array<int,1>;
template class array<double, 1>;
template class array<int, 2>;
template class array<double, 2>;
template class array<int, 3>;
template class array<double, 3>;
template class array<int, 4>;
template class array<double, 4>;
template class array<int, 5>;
template class array<double, 5>;
template class array<int, 6>;
template class array<double, 6>;
template class array<int, 7>;
template class array<double, 7>;
template class array<int, 8>;
template class array<double, 8>;
template class array<int, 9>;
template class array<double, 9>;
template class array<int, 10000>;
template class array<double, 10000>;
template class array<int, 0>;
template class array<double, 0>;

}  // namespace s21

#endif  //_S21_ARRAY_H_
